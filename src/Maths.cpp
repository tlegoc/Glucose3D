#include "Maths.h"
#include <spdlog/spdlog.h>

Matx44d Glucose::Maths::getRotationMatrix(Point3d rot)
{
    Matx44d xRotation = Matx44d(
        1, 0, 0, 0,
        0, cos(rot.x), -sin(rot.x), 0,
        0, sin(rot.x), cos(rot.x), 0,
        0, 0, 0, 1
    );

    Matx44d yRotation = Matx44d(
        cos(rot.y), 0, sin(rot.y), 0,
        0, 1, 0, 0,
        -sin(rot.y), 0, cos(rot.y), 0,
        0, 0, 0, 1
    );

    Matx44d zRotation = Matx44d(
        cos(rot.z), -sin(rot.z), 0, 0,
        sin(rot.z), cos(rot.z), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );

    return xRotation * yRotation * zRotation;
}

Matx44d Glucose::Maths::getTranslationMatrix(Point3d pos)
{
    return Matx44d(
        1, 0, 0, pos.x,
        0, 1, 0, pos.y,
        0, 0, 1, pos.z,
        0, 0, 0, 1
    );
}

Matx44d Glucose::Maths::getScaleMatrix(Point3d scale)
{
    return Matx44d(
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, 1
    );
}

Matx44d Glucose::Maths::getScaleMatrix(double scale)
{
    return Glucose::Maths::getScaleMatrix(Point3d(scale, scale, scale));
}

Matx44d Glucose::Maths::getTransformationMatrix(Point3d pos, Point3d rot, Point3d scale)
{
    return Glucose::Maths::getScaleMatrix(scale) * Glucose::Maths::getRotationMatrix(rot) * Glucose::Maths::getTranslationMatrix(pos);
}

Matx44d Glucose::Maths::getTransformationMatrix(Point3d pos, Point3d rot, double scale)
{
    return Glucose::Maths::getTransformationMatrix(pos, rot, Point3d(scale, scale, scale));
}

Matx44d Glucose::Maths::getProjectionMatrix(double fov, double nearPlane, double farPlane, double aspectRatio)
{
    double yScale = 1 / tan(fov * M_PI / 360);
    double xScale = yScale / aspectRatio;
    double frustumLength = farPlane - nearPlane;

    return Matx44d(
        xScale, 0, 0, 0,
        0, yScale, 0, 0,
        0, 0, -((farPlane + nearPlane) / frustumLength), -1,
        0, 0, -((2 * nearPlane * farPlane) / frustumLength), 0
    );
}

Matx44d Glucose::Maths::getOrthographicMatrix(double left, double right, double bottom, double top, double nearPlane, double farPlane)
{
    double width = right - left;
    double height = top - bottom;
    double depth = farPlane - nearPlane;

    return Matx44d(
        2 / width, 0, 0, -(right + left) / width,
        0, 2 / height, 0, -(top + bottom) / height,
        0, 0, -2 / depth, -(farPlane + nearPlane) / depth,
        0, 0, 0, 1
    );
}

Matx44d Glucose::Maths::getLookAtMatrix(Point3d eye, Point3d center, Point3d up)
{
    Point3d f = (center - eye);
    f = f / sqrt(norm(f)*norm(f));
    Point3d s = f.cross(up);
    s = s / sqrt(norm(s)*norm(s));
    Point3d u = s.cross(f);

    return Matx44d(
        s.x, u.x, -f.x, 0,
        s.y, u.y, -f.y, 0,
        s.z, u.z, -f.z, 0,
        0, 0, 0, 1
    ) * Glucose::Maths::getTranslationMatrix(-eye);
}

Point3d Glucose::Maths::transformPoint(Point3d point, Matx44d transformation)
{
    Matx41d pointMat = Matx41d(point.x, point.y, point.z, 1);
    Matx41d transformedPointMat = transformation * pointMat;
    transformedPointMat /= transformedPointMat(3);
    spdlog::debug("Transformed point: {}, {}, {}", transformedPointMat(0), transformedPointMat(1), transformedPointMat(2));
    return Point3d(transformedPointMat(0), transformedPointMat(1), transformedPointMat(2));
}