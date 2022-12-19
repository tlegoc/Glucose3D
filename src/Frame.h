#pragma once

#include <opencv2/core.hpp>

using namespace cv;

namespace Glucose
{

    struct Frame
    {

    public:
        Frame() = delete;
        Frame(int width, int height);
        Frame(Size size);
        void setSize(int width, int height) { setSize(Size(width, height)); }
        void setSize(Size size) { this->size = size; }
        Size getSize() const { return this->size; }

        std::mutex depth_mutex;
        void writeDepth(const Size pos, const Mat values);
        std::mutex threads_mutex;
        void writeThreads(const Size pos, const Mat values);
        std::mutex normals_mutex;
        void writeNormals(const Size pos, const Mat values);
        std::mutex albedo_mutex;
        void writeAlbedo(const Size pos, const Mat values);
        std::mutex specular_mutex;
        void writeSpecular(const Size pos, const Mat values);
        std::mutex roughness_mutex;
        void writeRoughness(const Size pos, const Mat values);
        std::mutex passes_mutex;
        void writePasses(const Size pos, const Mat values);
        std::mutex steps_mutex;
        void writeSteps(const Size pos, const Mat values);


        Mat getFinal() const { return *final; }
        Mat getDepth() const { return *depth; }
        Mat getThreads() const { return *threads; }
        Mat getNormals() const { return *normals; }
        Mat getAlbedo() const { return *albedo; }
        Mat getSpecular() const { return *specular; }
        Mat getRoughness() const { return *roughness; }
        Mat getPasses() const { return *passes; }
        Mat getSteps() const { return *steps; }


    private:
        Size size;
        std::shared_ptr<Mat> final;
        std::shared_ptr<Mat> depth;
        std::shared_ptr<Mat> threads;
        std::shared_ptr<Mat> normals;
        std::shared_ptr<Mat> albedo;
        std::shared_ptr<Mat> specular;
        std::shared_ptr<Mat> roughness;
        std::shared_ptr<Mat> passes;
        std::shared_ptr<Mat> steps;
    };
};