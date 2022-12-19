#include "Scene.h"

using namespace Glucose;

Scene::Scene()
{
    this->objects = std::vector<std::shared_ptr<Object>>();
    // this->cameras = std::vector<std::shared_ptr<Camera>>();
}

void Scene::addObject(std::shared_ptr<Object> object)
{
    this->objects.push_back(object);
}

double Scene::closestDistance(std::vector<std::shared_ptr<const Object>> objects, Point3d pos)
{
    double closest = INFINITY;
    for (auto object : objects)
    {
        double distance = object.get()->getDistance(pos);
        if (distance < closest)
        {
            closest = distance;
        }
    }
    return closest;
}