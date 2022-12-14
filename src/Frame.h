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
        Passes,
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
        Size getSize() const { return this->size; }

        std::mutex albedo_mutex;
        void writeAlbedo(const Size pos, const Mat values);

        Mat getFinal() const { return *final; }
        Mat getImage() const { return *image; }
        Mat getDepth() const { return *depth; }
        Mat getNormals() const { return *normals; }
        Mat getAlbedo() const { return *albedo; }

    private:
        Size size;
        std::shared_ptr<Mat> final;
        std::shared_ptr<Mat> image;
        std::shared_ptr<Mat> depth;
        std::shared_ptr<Mat> normals;
        std::shared_ptr<Mat> albedo;
        std::shared_ptr<Mat> specular;
        std::shared_ptr<Mat> roughness;
        std::shared_ptr<Mat> passes;
        std::shared_ptr<Mat> steps;
    };
};