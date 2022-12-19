#include "Camera.h"

#include "Maths.h"

using namespace Glucose;

Camera::Camera(Size resolution, double fov, double nearPlane, double farPlane)
{
    this->fov = fov;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
    this->resolution = resolution;
}

void Camera::setFOV(double fov)
{
    this->fov = fov;
}

double Camera::getFOV() const
{
    return this->fov;
}

void Camera::setNearPlane(double nearPlane)
{
    this->nearPlane = nearPlane;
}

double Camera::getNearPlane() const
{
    return this->nearPlane;
}

void Camera::setFarPlane(double farPlane)
{
    this->farPlane = farPlane;
}

double Camera::getFarPlane() const
{
    return this->farPlane;
}

void Camera::setPos(Point3d pos)
{
    this->pos = pos;
}

Point3d Camera::getPos() const
{
    return this->pos;
}

void Camera::setRot(Point3d rot)
{
    this->rot = rot;
}

Point3d Camera::getRot() const
{
    return this->rot;
}

void Camera::setResolution(Size resolution)
{
    this->resolution = resolution;
}

Size Camera::getResolution() const
{
    return this->resolution;
}

/**
 * Calucalte ray direction based from camera information and the pixel's position
 * @param position The position of the pixel
 * @return The direction of the ray
 */
Point3d Camera::getRayDirection(const Size position) const
{
    double aspectRatio = (double)resolution.width / resolution.height;
    double x = (2 * ((position.width + 0.5) / resolution.width) - 1) * tan(fov / 2 * M_PI / 180.0) * aspectRatio;
    double y = (1 - 2 * ((position.height + 0.5) / resolution.height)) * tan(fov / 2 * M_PI / 180.0);

    Point3d rayDirection(x, y, -1);
    Point3d rayOrigin(0, 0, 0);
    Matx44d cameraToWorld = Maths::getTransformationMatrix(this->getPos(), this->getRot(), 1);
    Point3d rayDirectionWorld, rayOriginWorld;
    rayDirectionWorld = Maths::transformPoint(rayDirection, cameraToWorld);
    rayOriginWorld = Maths::transformPoint(rayOrigin, cameraToWorld);

    return (rayDirectionWorld - rayOriginWorld)/norm(rayDirectionWorld - rayOriginWorld);
}