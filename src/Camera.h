#pragma once

#include "objects/Object.h"
#include "Frame.h"

#include <opencv2/core.hpp>

#include <memory>

using namespace cv;

namespace Glucose
{
    class Camera
    {
    public:
        Camera(float fov, float nearPlane, float farPlane);

        void setFOV(float fov);
        float getFOV();
        void setNearPlane(float nearPlane);
        float getNearPlane();
        void setFarPlane(float farPlane);
        float getFarPlane();

    private:
        float fov;
        float nearPlane;
        float farPlane;
    };
}