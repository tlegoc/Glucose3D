#include "Renderer.h"

#include <spdlog/spdlog.h>

using namespace Glucose;

Renderer::Renderer(const uint thread_count, const Size size) : Renderer::Renderer(thread_count, size, {128, 128})
{
}

Renderer::Renderer(const uint thread_count, const Size size, const Size region_size) : thread_count(thread_count),
                                                                                       region_size(region_size),
                                                                                       region_count_x(roundUp(size.width, region_size.width) / region_size.width),
                                                                                       region_count_y(roundUp(size.height, region_size.height) / region_size.height),
                                                                                       output_size(size)
{
    if (thread_count < 1)
        throw std::invalid_argument("Thread count must be at least 1");

    this->output = std::make_shared<Frame>(size);
    this->threads_all_ready = false;
    this->computed = Mat::zeros(Size(region_count_x, region_count_y), CV_32SC1);

    spdlog::info("Created renderer with {} threads", thread_count);
    spdlog::info("Region size: {}x{}", region_size.width, region_size.height);
    spdlog::info("Region count: {}x{}", region_count_x, region_count_y);
    spdlog::info("Output size: {}x{}", output_size.width, output_size.height);
    spdlog::info("Computed size: {}x{}", computed.size().width, computed.size().height);
    spdlog::info("Frame size: {}:{}",
                 output.get()->getSize().width,
                 output.get()->getSize().height);
}

bool Renderer::render(std::shared_ptr<const Scene> scene, std::shared_ptr<const Camera> camera)
{
    if (!this->renderFinished())
    {
        spdlog::error("Already rendering!");
        return false;
    }

    clearThreads();

    this->current_scene = scene;
    this->current_camera = camera;

    spdlog::warn("Starting rendering...");
    for (int i = 0; i < thread_count; i++)
    {
        try
        {
            spdlog::warn("Creating thread {}", i);
            std::shared_ptr<std::thread> t = std::make_shared<std::thread>(&Renderer::renderThread, this, i);
            threads.push_back(t);
            threads_render_status.push_back(RenderStatus::Waiting);
        }
        catch (const std::exception &e)
        {
            spdlog::error("Failed to create thread {}: {}", i, e.what());

            // Just in case
            threads_all_ready = false;
            return false;
        }
    }

    spdlog::warn("Theads created (count:{}), starting rendering...", thread_count);
    threads_all_ready = true;
    return true;
}

void Renderer::renderThread(const int id)
{
    // Random color that will distinguish the thread
    Point3f color = Point3f(static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
                        static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
                        static_cast<float>(rand()) / static_cast<float>(RAND_MAX));

    // Wait for all threads to be created
    spdlog::info("Waiting for rendering to start...");
    while (!threads_all_ready)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Sets thread status
    spdlog::info("Rendering started on thread {}.", id);
    threads_render_status[id] = RenderStatus::Running;

    // Start and end pos of the region that will be rendered
    Size start, end;
    // Objects to be used.
    // We wont run the algorithm on the full object list as it will take
    // too much time. Instead we request for objects that will be seen
    // From the pov of the ray.
    // Note that this breaks the closest distance mesured values, as some objects
    // Might be right next to the region but not used in calculations.
    std::vector<std::shared_ptr<const Object>> objects;

    // As long as we have regions to render
    while (requestRegion(id, start, end))
    {
        spdlog::info("Thread {} rendering region: (start: {}:{}, end: {}:{})", id, start.width, start.height, end.width,
                     end.height);

        // if (!requestObjectsInRegion(id, start, end, objects))
        // continue;

        // Create a matrix of the correct region size
        // Avoids all threads writing to the same matrix
        Mat region = Mat::zeros(end - start, CV_32FC3);
        for (int i = 0; i < region.size().width; i++)
        {
            for (int j = 0; j < region.size().height; j++)
            {
                // Calculations
                region.at<Point3f>(j, i) = color;
            }
        }

        spdlog::info("Thread {} writing region.", id);
        output.get()->writeAlbedo(start, region);
        spdlog::info("Thread {} finished rendering region.", id);
    }

    threads_render_status[id] = RenderStatus::Finished;
    spdlog::info("Rendering finished on thread {}.", id);
}

/**
 * Loop through all active threads and returns true if all threads
 * have status "finished"
 */
bool Renderer::renderFinished()
{
    for (RenderStatus rs : threads_render_status)
    {
        if (rs != RenderStatus::Finished)
            return false;
    }
    return true;
}

bool Renderer::requestRegion(const int thread_id, Size &start, Size &end)
{
    request_mutex.lock();

    spdlog::info("Processing request for thread {}.", thread_id);
    bool found = false;

    for (int i = 0; i < computed.size().height; i++)
    {
        for (int j = 0; j < computed.size().width; j++)
        {
            if (computed.at<int>(i, j) < 1)
            {
                // Create the start position and end position of the region
                // It needs to be cropped if it is outside the image
                start = Size(j * region_size.width, i * region_size.height);
                end = Size((j + 1) * region_size.width, (i + 1) * region_size.height);
                if (end.width > output_size.width)
                    end.width = output_size.width;
                if (end.height > output_size.height)
                    end.height = output_size.height;

                found = true;
                computed.at<int>(i, j) = thread_id + 1;
                goto found_region;
            }
        }
    }

found_region:

    request_mutex.unlock();
    return found;
}

bool Renderer::requestObjectsInRegion(const int thread_id, const Vec2i start, const Vec2i end, std::vector<std::shared_ptr<const Object>> &objects)
{

    return false;
}

void Renderer::clearThreads()
{
    for (auto t : threads)
    {
        try
        {
            t->~thread();
        }
        catch (const std::exception &e)
        {
            spdlog::error("Failed to delete thread: {}", e.what());
        }
    }

    threads = {};
    threads_render_status = {};
}