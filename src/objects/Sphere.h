#pragma once

#include <opencv2/core.hpp>

#include "Object.h"

using namespace cv;

namespace Glucose {
    class Sphere : public Object {
        private:
            double radius;

        public:
            Sphere(Point3d position, double radius);
            long double getDistance(Point3d pos) const;
    };
};