#include <opencv2/core.hpp>

#include "Sphere.h"

using namespace cv;
using namespace Glucose;

Sphere::Sphere(Point3d position, double radius)
{
    this->radius = radius;
    this->position = position;
    this->scale = Point3d(1, 1, 1);
}

long double Sphere::getDistance(Point3d pos) const
{
    return norm(pos - position) - radius;
}

Vec3f Sphere::getColor() const
{
    return Vec3f(1, 0, 1);
}

Point3d Sphere::getNormal(Point3d pos) const
{
    return (pos - position) / norm(pos - position);
}