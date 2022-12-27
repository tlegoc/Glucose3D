#include <opencv2/core.hpp>

#include "InfiniteSpheres.h"

using namespace cv;
using namespace Glucose;

InfiniteSpheres::InfiniteSpheres(Point3d position, double radius, double modulo)
{
    this->radius = radius;
    this->position = position;
    this->scale = Point3d(1, 1, 1);
    this->modulo = modulo;
}

long double InfiniteSpheres::getDistance(Point3d pos) const
{
    return norm(Point3d(fmod(pos.x, modulo) + modulo / 2, fmod(pos.y, modulo) + modulo / 2, fmod(pos.z, modulo) + modulo / 2) - position) - radius;
}