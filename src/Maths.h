#pragma once 

#include <opencv2/core.hpp>

using namespace cv;

namespace Glucose::Maths {
    Matx44d getRotationMatrix(Point3d rot);
    Matx44d getTranslationMatrix(Point3d pos);
    Matx44d getScaleMatrix(Point3d scale);
    Matx44d getScaleMatrix(double scale);
    Matx44d getTransformationMatrix(Point3d pos, Point3d rot, Point3d scale);
    Matx44d getTransformationMatrix(Point3d pos, Point3d rot, double scale);
    Matx44d getProjectionMatrix(double fov, double nearPlane, double farPlane, double aspectRatio);
    Matx44d getOrthographicMatrix(double left, double right, double bottom, double top, double nearPlane, double farPlane);
    Matx44d getLookAtMatrix(Point3d eye, Point3d center, Point3d up);
    Point3d transformPoint(Point3d point, Matx44d transformation);
}