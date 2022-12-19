#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>

#include "src/Scene.h"
#include "src/Camera.h"
#include "src/objects/Sphere.h"
#include "src/Renderer.h"

using namespace Glucose;

int main(int argc, char const *argv[])
{
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Point3d(0, 0, 0), 1.0);
    scene.get()->addObject(sphere);

    std::shared_ptr<Camera> cam = std::make_shared<Camera>(Size(1600, 900), 90, .001, 100);
    cam.get()->setPos(Point3d(0, 0, -5));

    Renderer renderer = Renderer(6);

    spdlog::info("Object count: {}", scene.get()->getObjects().size());
    renderer.render(scene, cam);
    clock_t begin = clock();
    while (!renderer.renderFinished())
    {
        // Wait. Refresh every 100ms to avoid cpu hogging
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    clock_t end = clock();

    spdlog::info("Rendered in {}s", double(end - begin) / CLOCKS_PER_SEC);

    Mat img = renderer.getOutput().get()->getDepth();
    img /= 5000;

    imwrite("test.bmp", img);

    namedWindow("Display window", WINDOW_AUTOSIZE);

    imshow("Display window", img);

    waitKey(0);

    destroyAllWindows();

    return 0;
}
