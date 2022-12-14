#pragma once

#include <opencv2/core.hpp>


using namespace cv;

namespace Glucose
{
    class Object
    {
        private:

        public: 
            Vec3d position;
            Vec3d rotation;
            Vec3d scale;

            virtual long double getDistanceFromCamera(Vec3d cameraPosition) = 0;
    };
};