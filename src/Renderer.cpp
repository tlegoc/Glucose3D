#include "Renderer.h"

#include <spdlog/spdlog.h>

using namespace Glucose;

Renderer::Renderer(const uint thread_count, const Size size) : Renderer::Renderer(thread_count, size, {128, 128})
{
}

Renderer::Renderer(const uint thread_count, const Size size, const Size region_size) : thread_count(thread_count),
                                                                                      region_size(region_size),
                                                                                      region_count_x(size.width / region_size.width),
                                                                                      region_count_y(size.height / region_size.height),
                                                                                      output_size(size)
{
    if (thread_count < 1) throw std::invalid_argument("Thread count must be at least 1");
    
    this->output = std::make_shared<Frame>(size);
    this->threads_all_ready = false;
    this->computed = Mat::zeros(Size(region_count_x, region_count_y), CV_32SC1);
}

bool Renderer::render(std::shared_ptr<const Scene> scene, std::shared_ptr<const Camera> camera)
{
    if (!this->renderFinished())
    {
        spdlog::error("Already rendering!");
        return false;
    }

    this->current_scene = scene;
    this->current_camera = camera;

    spdlog::warn("Starting rendering...");
    for (int i = 0; i < thread_count; i++)
    {
        try
        {
            spdlog::warn("Creating thread {}", i);
            std::thread *t = new std::thread(&Renderer::renderThread, this, i);
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
    spdlog::info("Waiting for rendering to start...");
    while (!threads_all_ready)
    {
    };

    spdlog::info("Rendering started on thread {}.", id);
    threads_render_status[id] = RenderStatus::Running;

    Vec2i start, end;
    std::vector<std::shared_ptr<const Object>> objects;

    while (requestRegion(id, start, end))
    {
        spdlog::info("Thread {} rendering region.", id);
        //if (!requestObjectsInRegion(id, start, end, objects))
            //continue;
        
        
        sleep(rand() % 5);

        spdlog::info("Thread {} finished rendering region.", id);
    }

    threads_render_status[id] = RenderStatus::Finished;
    spdlog::info("Rendering finished on thread {}.", id);
}

bool Renderer::renderFinished()
{
    for (RenderStatus rs : threads_render_status)
    {
        if (rs != RenderStatus::Finished)
            return false;
    }
    return true;
}

bool Renderer::requestRegion(const int thread_id, Vec2i &start, Vec2i &end)
{
    request_lock.lock();

    spdlog::info("Processing request for thread {}.", thread_id);
    bool found = false;

    for (int i = 0; i < computed.size().height; i++)
    {
        for (int j = 0; j < computed.size().width; j++)
        {
            if (computed.at<int>(i, j) < 1) {
                start = {j * region_size.width, i * region_size.height};    
                end = {std::min(start[0] + region_size.width, output_size.width), std::min(start[1] + region_size.height, output_size.height)};
                found = true;
                computed.at<int>(i, j) = thread_id + 1;
                goto found_region;
            }
        }
    }

found_region:

    request_lock.unlock();
    return found;
}

bool Renderer::requestObjectsInRegion(const int thread_id, const Vec2i start, const Vec2i end, std::vector<std::shared_ptr<const Object>> &objects)
{

    return false;
}
