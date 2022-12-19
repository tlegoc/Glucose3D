#pragma once

#include "Frame.h"
#include "Scene.h"
#include "Camera.h"

#include <opencv2/core.hpp>

#include <memory>
#include <vector>
#include <mutex>
#include <thread>

using namespace cv;

namespace Glucose
{
    enum RenderStatus {
        Waiting,
        Running,
        Finished
    };

    class Renderer
    {
    public:
        Renderer(const uint thread_count, const Size region_size = {128, 128}, const double threshold = 0.001, const double max_distance = 1000);
        ~Renderer();
        bool render(std::shared_ptr<const Scene> scene, std::shared_ptr<const Camera> camera);
        bool renderFinished();

        Mat getComputed() const { return computed; }
        std::shared_ptr<const Frame> getOutput() const { return output; }

    private:
        std::shared_ptr<Frame> output;
        Size region_size;
        int region_count_x;
        int region_count_y;
        const double threshold;
        const double max_distance;
        Mat computed;

        bool threads_all_ready;
        const uint thread_count;
        std::vector<std::shared_ptr<std::thread>> threads;
        std::vector<RenderStatus> threads_render_status;

        std::shared_ptr<const Scene> current_scene;
        std::shared_ptr<const Camera> current_camera;

        void renderThread(const int id);

        std::mutex request_mutex;
        bool requestRegion(const int thread_id, Size &start, Size &end);
        bool requestObjectsInRegion(const int thread_id, const Vec2i start, const Vec2i end, std::vector<std::shared_ptr<const Object>> &objects);
        void clearThreads();

    };
}
