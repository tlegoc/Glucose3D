#pragma once

#include <opencv2/core.hpp>

using namespace cv;

namespace Glucose
{

    enum Pass
    {
        Image,
        Depth,
        Normals,
        Albedo,
        Specular,
        Roughness,
        Samples,
        Steps
    };

    struct Frame
    {

    public:
        Frame() = delete;
        Frame(int width, int height);
        Frame(Size size);
        void setSize(int width, int height) { setSize(Size(width, height)); }
        void setSize(Size size) { this->size = size; }
        Size getSize() { return this->size; }

        bool writePixel(Pass pass, int x, int y, auto value);

        Mat getFinal() { return *final; }

    private:
        Size size;
        std::unique_ptr<Mat> final;
        std::unique_ptr<Mat> image;
        std::unique_ptr<Mat> depth;
        std::unique_ptr<Mat> normals;
        std::unique_ptr<Mat> albedo;
        std::unique_ptr<Mat> specular;
        std::unique_ptr<Mat> roughness;
        std::unique_ptr<Mat> passes;
        std::unique_ptr<Mat> steps;
    };
};