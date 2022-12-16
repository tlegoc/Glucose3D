#include "Frame.h"

using namespace Glucose;

Frame::Frame(int width, int height)
{
    this->size = Size(width, height);
    this->final = std::make_shared<Mat>(height, width, CV_8UC3);
    this->depth = std::make_shared<Mat>(height, width, CV_32FC1);
    this->normals = std::make_shared<Mat>(height, width, CV_32FC3);
    this->albedo = std::make_shared<Mat>(height, width, CV_32FC3);
    this->specular = std::make_shared<Mat>(height, width, CV_32FC1);
    this->roughness = std::make_shared<Mat>(height, width, CV_32FC1);
    this->passes = std::make_shared<Mat>(height, width, CV_32SC1);
    this->steps = std::make_shared<Mat>(height, width, CV_32SC1);
}

Frame::Frame(Size size)
{
    this->size = size;
    this->final = std::make_shared<Mat>(size.height, size.width, CV_8UC3);
    this->depth = std::make_shared<Mat>(size.height, size.width, CV_32FC1);
    this->normals = std::make_shared<Mat>(size.height, size.width, CV_32FC3);
    this->albedo = std::make_shared<Mat>(size.height, size.width, CV_32FC3);
    this->specular = std::make_shared<Mat>(size.height, size.width, CV_32FC3);
    this->roughness = std::make_shared<Mat>(size.height, size.width, CV_32FC1);
    this->passes = std::make_shared<Mat>(size.height, size.width, CV_32SC1);
    this->steps = std::make_shared<Mat>(size.height, size.width, CV_32SC1);
}

void Frame::writeAlbedo(const Size pos, const Mat values)
{
    albedo_mutex.lock();
    values.copyTo(albedo->rowRange(pos.height, pos.height + values.rows).colRange(pos.width, pos.width + values.cols));
    albedo_mutex.unlock();
}