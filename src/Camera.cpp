#include "Camera.h"

#include "Maths.h"

using namespace Glucose;

Camera::Camera(float fov, float nearPlane, float farPlane)
{
    this->fov = fov;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
}

void Camera::setFOV(float fov)
{
    this->fov = fov;
}

float Camera::getFOV()
{
    return this->fov;
}

void Camera::setNearPlane(float nearPlane)
{
    this->nearPlane = nearPlane;
}

float Camera::getNearPlane()
{
    return this->nearPlane;
}

void Camera::setFarPlane(float farPlane)
{
    this->farPlane = farPlane;
}

float Camera::getFarPlane()
{
    return this->farPlane;
}

void Camera::setPos(Point3f pos)
{
    this->pos = pos;
}

Point3f Camera::getPos()
{
    return this->pos;
}

void Camera::setRot(Point3f rot)
{
    this->rot = rot;
}

Point3f Camera::getRot()
{
    return this->rot;
}


/**
 * Calucalte ray direction based from camera information and the pixel's position
 * @param position The position of the pixel
 * @return The direction of the ray
 */
Point3f Camera::getRayDirection(const Size position, const Size size)
{
    float aspectRatio = (float)size.width / size.height;
    float x = (2 * (position.width + 0.5) / size.width - 1) * aspectRatio * tan((fov * M_PI / 180.0) / 2);
    float y = (1 - 2 * (position.height + 0.5) / size.height) * tan((fov * M_PI / 180.0) / 2);

    Point3f rayDirection(x, y, - 1);
    Point3f rayOrigin(0, 0, 0);
    Matx44f cameraToWorld = Maths::getTransformationMatrix(this->getPos(), this->getRot(), 1);
    Point3f rayDirectionWorld, rayOriginWorld;

    

    return Point3f(0, 0, 0);
}