#include <opencv2/core.hpp>

#include "Sphere.h"

using namespace cv;
using namespace Glucose;

Sphere::Sphere(Vec3d position, float radius) {
    this->radius = radius;
    this->position = position;
    this->scale = Vec3d(1, 1, 1);
}

long double Sphere::getDistanceFromCamera(Vec3d cameraPosition) {
    return norm(cameraPosition - this->position);
}