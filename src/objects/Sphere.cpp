#include <opencv2/core.hpp>

#include "Sphere.h"

using namespace cv;
using namespace Glucose;

Sphere::Sphere(Point3f position, float radius) {
    this->radius = radius;
    this->position = position;
    this->scale = Point3f(1, 1, 1);
}

long double Sphere::getDistanceFromCamera(Point3f cameraPosition) {
    return norm(cameraPosition - this->position);
}