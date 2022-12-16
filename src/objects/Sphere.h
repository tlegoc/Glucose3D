#pragma once

#include <opencv2/core.hpp>

#include "Object.h"

using namespace cv;

namespace Glucose {
    class Sphere : public Object {
        private:
            float radius;

        public:
            Sphere(Point3f position, float radius);
            long double getDistanceFromCamera(Point3f cameraPosition);
    };
};