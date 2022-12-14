#include "Camera.h"

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