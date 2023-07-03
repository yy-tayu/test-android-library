//
// Created by tayu on 2023/4/19.
//

#include "nativecv.h"
#include <fstream>
#include "opencv2/opencv.hpp"
#include "log.h"
#define LOG_TAG "NativeCV"

bool NativeCV::blendImage(cv::Mat img1, float alpha1, cv::Mat img2, float alpha2, cv::Mat& dest) {
    if (img1.size() != img2.size() || img1.channels() != img2.channels()) {
        ALOGE( "blend image size or channles not same");
        return false;
    }
    cv::addWeighted(img1, alpha1, img2, alpha2, 0.0, dest);
    return true;
}

void NativeCV::saveImageToFile(std::string file_path, std::string file_name, cv::Mat img) {
    if (file_path.back() != '/')
    {
        file_path += "/";
    }
    ALOGE( "saveImageToFile %s %s" ,file_path.c_str(), file_name.c_str());
    ALOGE( "save Mat cols %d, rows %d, is empty %d" , img.cols, img.rows, img.empty());
    cv::imwrite(file_path+file_name, img);
}

void NativeCV::convertColorSpace(const cv::Mat &img, cv::Mat &dest, int type) {
    cvtColor(img, dest, type);
}

bool NativeCV::openUYVYImage(std::string file_path, std::string file_name, int width, int height, cv::Mat& ret) {
    if (file_path.back() != '/')
    {
        file_path += "/";
    }
    std::string full_path = file_path + file_name;
    std::ifstream file_stream(full_path, std::ios::binary);

    if (!file_stream) {
        ALOGE("Error: Unable to open file %s", full_path.c_str());
        return false;
    }

    int frame_size = width * height * 2; // UYVY format has 2 bytes per pixel
    std::vector<unsigned char> buffer(frame_size);
    file_stream.read(reinterpret_cast<char*>(buffer.data()), frame_size);
    if (file_stream.gcount() != frame_size) {
        ALOGE("Error: Unable to read the entire file %s", full_path.c_str());
        return false;
    }

    cv::Mat raw_image(height, width, CV_8UC2, buffer.data());
    return true;
}

bool NativeCV::openUYVYImageToRGBAImage(std::string file_path, std::string file_name, int width,
                                           int height, cv::Mat& ret) {
    cv::Mat uyvy_image;
    if(!openUYVYImage(file_path, file_name, width, height, uyvy_image))
    {
        return false;
    }
    convertColorSpace(uyvy_image, ret, cv::COLOR_YUV2BGR_UYVY);
    return true;
}

void NativeCV::cutImage(const cv::Mat& img, cv::Mat& out_img, const cv::Rect& roi) {
    cv::Mat roi_mat = img(roi);
    roi_mat.copyTo(out_img);
}

void NativeCV::resizeImage(cv::Mat& img, cv::Mat& dest) {
    cv::resize(img, dest, cv::Size(dest.cols, dest.rows));
}

void NativeCV::encodeImageToFile(cv::Mat &img, std::string file_name, std::string path) {
    // 定义压缩参数
    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
    compression_params.push_back(90);

    cv::cvtColor(img,img,COLOR_BGRA2BGR);

    // 压缩图像
    std::vector<uchar> compressed_image;
    cv::imencode(".jpg", img, compressed_image, compression_params);

    // 打开文件
    std::ofstream out_file(path + "/" + file_name, std::ios::binary);

    // 将压缩后的数据写入文件
    out_file.write((char*)compressed_image.data(), compressed_image.size());

    // 立即刷新输出流，将所有数据写入磁盘
    out_file.flush();
    out_file.close();
}

