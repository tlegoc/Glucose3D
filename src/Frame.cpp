#include "Frame.h"

using namespace Glucose;

Frame::Frame(int width, int height)
{
    this->size = Size(width, height);
    this->final = std::make_unique<Mat>(height, width, CV_8UC3);
    this->image = std::make_unique<Mat>(height, width, CV_8UC3);
    this->depth = std::make_unique<Mat>(height, width, CV_32FC1);
    this->normals = std::make_unique<Mat>(height, width, CV_32FC3);
    this->albedo = std::make_unique<Mat>(height, width, CV_32FC3);
    this->specular = std::make_unique<Mat>(height, width, CV_32FC1);
    this->roughness = std::make_unique<Mat>(height, width, CV_32FC1);
    this->passes = std::make_unique<Mat>(height, width, CV_32SC1);
    this->steps = std::make_unique<Mat>(height, width, CV_32SC1);
}

Frame::Frame(Size size)
{
    this->size = size;
    this->final = std::make_unique<Mat>(size.width, size.height, CV_8UC3);
    this->image = std::make_unique<Mat>(size.width, size.height, CV_8UC3);
    this->depth = std::make_unique<Mat>(size.width, size.height, CV_32FC1);
    this->normals = std::make_unique<Mat>(size.width, size.height, CV_32FC3);
    this->albedo = std::make_unique<Mat>(size.width, size.height, CV_32FC3);
    this->specular = std::make_unique<Mat>(size.width, size.height, CV_32FC3);
    this->roughness = std::make_unique<Mat>(size.width, size.height, CV_32FC1);
    this->passes = std::make_unique<Mat>(size.width, size.height, CV_32SC1);
    this->steps = std::make_unique<Mat>(size.width, size.height, CV_32SC1);
}