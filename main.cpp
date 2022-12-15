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
    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vec3f(0, 0, 0), 1.0);
    scene.get()->addObject(sphere);

    std::shared_ptr<Camera> cam = std::make_shared<Camera>(90, .001, 100);

    Renderer renderer = Renderer(6, {600, 600}, {128, 128});


    clock_t begin = clock();
    renderer.render(scene, cam);
    while (!renderer.renderFinished());
    clock_t end = clock();

    spdlog::info("Rendered in {}s", double(end - begin) / CLOCKS_PER_SEC);

    Mat img = renderer.getOutput().get()->getAlbedo();

    namedWindow("Display window", WINDOW_AUTOSIZE);

    imshow("Display window", img);

    waitKey(0);

    return 0;
}
