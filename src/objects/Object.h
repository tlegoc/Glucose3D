#pragma once

#include <opencv2/core.hpp>


using namespace cv;

namespace Glucose
{
    class Object
    {
        private:

        public: 
            Point3f position;
            Point3f rotation;
            Point3f scale;

            virtual long double getDistanceFromCamera(Point3f cameraPosition) = 0;
    };
};