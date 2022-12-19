#include "Frame.h"

using namespace Glucose;

Frame::Frame(int width, int height) : Frame(Size(width, height))
{
}

Frame::Frame(Size size)
{
    this->size = size;
    this->final = std::make_shared<Mat>(size, CV_8UC3);
    this->depth = std::make_shared<Mat_<double>>(size);
    this->normals = std::make_shared<Mat>(size, CV_32FC3);
    this->threads = std::make_shared<Mat>(size, CV_32FC3);
    this->albedo = std::make_shared<Mat>(size, CV_32FC3);
    this->specular = std::make_shared<Mat>(size, CV_32FC3);
    this->roughness = std::make_shared<Mat>(size, CV_32FC1);
    this->passes = std::make_shared<Mat>(size, CV_32SC1);
    this->steps = std::make_shared<Mat>(size, CV_32SC1);
}

void Frame::writeAlbedo(const Size pos, const Mat values)
{
    albedo_mutex.lock();
    values.copyTo(albedo->rowRange(pos.height, pos.height + values.rows).colRange(pos.width, pos.width + values.cols));
    albedo_mutex.unlock();
}

void Frame::writeDepth(const Size pos, const Mat values)
{
    depth_mutex.lock();
    values.copyTo(depth->rowRange(pos.height, pos.height + values.rows).colRange(pos.width, pos.width + values.cols));
    depth_mutex.unlock();
}

void Frame::writeThreads(const Size pos, const Mat values)
{
    threads_mutex.lock();
    values.copyTo(threads->rowRange(pos.height, pos.height + values.rows).colRange(pos.width, pos.width + values.cols));
    threads_mutex.unlock();
}

void Frame::writeNormals(const Size pos, const Mat values)
{
    normals_mutex.lock();
    values.copyTo(normals->rowRange(pos.height, pos.height + values.rows).colRange(pos.width, pos.width + values.cols));
    normals_mutex.unlock();
}

void Frame::writePasses(const Size pos, const Mat values)
{
    passes_mutex.lock();
    values.copyTo(passes->rowRange(pos.height, pos.height + values.rows).colRange(pos.width, pos.width + values.cols));
    passes_mutex.unlock();
}
