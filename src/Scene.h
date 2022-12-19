#pragma once

#include <vector>
#include <memory>

#include "objects/Object.h"

namespace Glucose
{
    class Scene
    {        
    public:
        Scene();

        void addObject(std::shared_ptr<Object> object);
        std::vector<std::shared_ptr<Object>> getObjects() const { return objects; }

        static double closestDistance(std::vector<std::shared_ptr<const Object>> objects, Point3d pos);

    private:
        std::vector<std::shared_ptr<Object>> objects;
    };
}