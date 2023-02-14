#pragma once

#include <opencv2/core.hpp>

#include "Object.h"

using namespace cv;

namespace Glucose
{
    class InfiniteSpheres : public Object
    {
    private:
        double radius;
        double modulo;

    public:
        InfiniteSpheres(Point3d position, double radius, double modulo);
        long double getDistance(Point3d pos) const;
        Vec3f getColor() const { return Vec3f(1, 1, 1); };
        Point3d getNormal(Point3d pos) const { return Point3d(0, 0, 0); }
    };
};