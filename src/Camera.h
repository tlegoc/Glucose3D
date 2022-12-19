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
        Camera(Size resolution, double fov, double nearPlane, double farPlane);

        void setFOV(double fov);
        double getFOV() const;
        void setNearPlane(double nearPlane);
        double getNearPlane() const;
        void setFarPlane(double farPlane);
        double getFarPlane() const;
        void setPos(Point3d pos);
        Point3d getPos() const;
        void setRot(Point3d rot);
        Point3d getRot() const;
        void setResolution(Size resolution);
        Size getResolution() const;

        Point3d getRayDirection(const Size position) const;

    private:
        double fov;
        double nearPlane;
        double farPlane;
        Point3d pos;
        Point3d rot;
        Size resolution;
    };
}