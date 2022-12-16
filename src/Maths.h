#pragma once 

#include <opencv2/core.hpp>

using namespace cv;

namespace Glucose::Maths {
    Matx44f getRotationMatrix(Point3f rot);
    Matx44f getTranslationMatrix(Point3f pos);
    Matx44f getScaleMatrix(Point3f scale);
    Matx44f getScaleMatrix(float scale);
    Matx44f getTransformationMatrix(Point3f pos, Point3f rot, Point3f scale);
    Matx44f getTransformationMatrix(Point3f pos, Point3f rot, float scale);
    Matx44f getProjectionMatrix(float fov, float nearPlane, float farPlane, float aspectRatio);
    Matx44f getOrthographicMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane);
    Matx44f getLookAtMatrix(Point3f eye, Point3f center, Point3f up);
}