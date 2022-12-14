#include "Scene.h"

using namespace Glucose;

Scene::Scene()
{
    this->objects = std::vector<std::shared_ptr<Object>>();
    //this->cameras = std::vector<std::shared_ptr<Camera>>();
}

void Scene::addObject(std::shared_ptr<Object> object)
{
    this->objects.push_back(object);
}