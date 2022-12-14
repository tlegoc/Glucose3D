#pragma once

#include <opencv2/core.hpp>

#include "Object.h"

using namespace cv;

namespace Glucose {
    class Sphere : public Object {
        private:
            float radius;

        public:
            Sphere(Vec3d position, float radius);
            long double getDistanceFromCamera(Vec3d cameraPosition);
    };
};