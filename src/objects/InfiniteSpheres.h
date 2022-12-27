#pragma once

#include <opencv2/core.hpp>

#include "Object.h"

using namespace cv;

namespace Glucose {
    class InfiniteSpheres : public Object {
        private:
            double radius;
            double modulo;

        public:
            InfiniteSpheres(Point3d position, double radius, double modulo);
            long double getDistance(Point3d pos) const;
    };
};