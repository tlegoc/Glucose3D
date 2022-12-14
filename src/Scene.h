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

    private:
        std::vector<std::shared_ptr<Object>> objects;
    };
}