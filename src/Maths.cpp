#include "Maths.h"

Matx44f Glucose::Maths::getRotationMatrix(Point3f rot)
{
    Matx44f xRotation = Matx44f(
        1, 0, 0, 0,
        0, cos(rot.x), -sin(rot.x), 0,
        0, sin(rot.x), cos(rot.x), 0,
        0, 0, 0, 1
    );

    Matx44f yRotation = Matx44f(
        cos(rot.y), 0, sin(rot.y), 0,
        0, 1, 0, 0,
        -sin(rot.y), 0, cos(rot.y), 0,
        0, 0, 0, 1
    );

    Matx44f zRotation = Matx44f(
        cos(rot.z), -sin(rot.z), 0, 0,
        sin(rot.z), cos(rot.z), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );

    return xRotation * yRotation * zRotation;
}

Matx44f Glucose::Maths::getTranslationMatrix(Point3f pos)
{
    return Matx44f(
        1, 0, 0, pos.x,
        0, 1, 0, pos.y,
        0, 0, 1, pos.z,
        0, 0, 0, 1
    );
}

Matx44f Glucose::Maths::getScaleMatrix(Point3f scale)
{
    return Matx44f(
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, 1
    );
}

Matx44f Glucose::Maths::getScaleMatrix(float scale)
{
    return Glucose::Maths::getScaleMatrix(Point3f(scale, scale, scale));
}

Matx44f Glucose::Maths::getTransformationMatrix(Point3f pos, Point3f rot, Point3f scale)
{
    return Glucose::Maths::getScaleMatrix(scale) * Glucose::Maths::getRotationMatrix(rot) * Glucose::Maths::getTranslationMatrix(pos);
}

Matx44f Glucose::Maths::getTransformationMatrix(Point3f pos, Point3f rot, float scale)
{
    return Glucose::Maths::getTransformationMatrix(pos, rot, Point3f(scale, scale, scale));
}

Matx44f Glucose::Maths::getProjectionMatrix(float fov, float nearPlane, float farPlane, float aspectRatio)
{
    float yScale = 1 / tan(fov * M_PI / 360);
    float xScale = yScale / aspectRatio;
    float frustumLength = farPlane - nearPlane;

    return Matx44f(
        xScale, 0, 0, 0,
        0, yScale, 0, 0,
        0, 0, -((farPlane + nearPlane) / frustumLength), -1,
        0, 0, -((2 * nearPlane * farPlane) / frustumLength), 0
    );
}

Matx44f Glucose::Maths::getOrthographicMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    float width = right - left;
    float height = top - bottom;
    float depth = farPlane - nearPlane;

    return Matx44f(
        2 / width, 0, 0, -(right + left) / width,
        0, 2 / height, 0, -(top + bottom) / height,
        0, 0, -2 / depth, -(farPlane + nearPlane) / depth,
        0, 0, 0, 1
    );
}

Matx44f Glucose::Maths::getLookAtMatrix(Point3f eye, Point3f center, Point3f up)
{
    Point3f f = (center - eye);
    f = f / sqrt(norm(f)*norm(f));
    Point3f s = f.cross(up);
    s = s / sqrt(norm(s)*norm(s));
    Point3f u = s.cross(f);

    return Matx44f(
        s.x, u.x, -f.x, 0,
        s.y, u.y, -f.y, 0,
        s.z, u.z, -f.z, 0,
        0, 0, 0, 1
    ) * Glucose::Maths::getTranslationMatrix(-eye);
}