#pragma once

#include <opencv2/core.hpp>

using namespace cv;

namespace Glucose
{
    class Object
    {
        private:

        public: 
            Point3d position;
            Point3d rotation;
            Point3d scale;

            virtual long double getDistance(Point3d pos) const = 0;
    };
};