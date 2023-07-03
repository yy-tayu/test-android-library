//
// Created by tayu on 2023/4/18.
//

#include "nativecv.h"
#include "jni_cvcommon.h"
#include <fstream>
#include <string>
#include "log.h"
#define LOG_TAG "jni_jnativecv"


extern "C"
JNIEXPORT jboolean JNICALL
Java_com_fotric_jdenali_cv_JNativeCV_openUYVYFileToRGBA(JNIEnv *env, jobject thiz,
                                                        jstring file_path, jstring file_name,
                                                        jint width, jint height, jobject ret) {
    std::string path = env->GetStringUTFChars(file_path, 0);
    std::string name = env->GetStringUTFChars(file_name, 0);
    cv::Mat ret_mat = jImageToMat(env, ret);
    return NativeCV::openUYVYImageToRGBAImage(path, name, width, height, ret_mat);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fotric_jdenali_cv_JNativeCV_convertColorSpace(JNIEnv *env, jobject thiz, jobject src, jobject dest, jint type) {
    cv::Mat src_mat = jImageToMat(env, src);
    cv::Mat dest_mat = jImageToMat(env, dest);
    NativeCV::convertColorSpace(src_mat, dest_mat, type);
    return ;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_fotric_jdenali_cv_JNativeCV_blendImages(JNIEnv *env, jobject thiz, jobject image1,
                                                 float alpha1, jobject image2, float alpha2, jobject dest) {
    cv::Mat rgb_mat1 = jImageToMat(env, image1);
    cv::Mat rgb_mat2 = jImageToMat(env, image2);
    cv::Mat dest_mat = jImageToMat(env, dest);
    return NativeCV::blendImage(rgb_mat1, alpha1, rgb_mat2, alpha2, dest_mat);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fotric_jdenali_cv_JNativeCV_cvSaveImages(JNIEnv *env, jobject thiz, jobject image,
                                                jstring file_path, jstring file_name) {
    cv::Mat rgb_mat1 = jImageToMat(env, image);
    std::string path = env->GetStringUTFChars(file_path, 0);
    std::string name = env->GetStringUTFChars(file_name, 0);
    NativeCV::saveImageToFile(path, name, rgb_mat1);
    return;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fotric_jdenali_cv_JNativeCV_cutImage(JNIEnv *env, jobject thiz,
                                              jobject src, jobject dest,
                                              jobject rect) {
    cv::Mat src_mat = jImageToMat(env, src);
    cv::Mat dest_mat = jImageToMat(env, dest);
    cv::Rect roi = jRectToCvRect(env, rect);
    NativeCV::cutImage(src_mat, dest_mat, roi);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_fotric_jdenali_cv_JNativeCV_convertUYVYStreamToRGBA(JNIEnv *env, jobject thiz, jobject src,
                                                             jobject dest, jobject rect) {
    cv::Mat src_mat = jImageToMat(env, src);
    cv::Mat dest_mat = jImageToMat(env, dest);
    cv::Mat bgra_mat;
    NativeCV::convertColorSpace(src_mat, bgra_mat, COLOR_YUV2BGRA_UYVY);
    if (rect != nullptr) {
        cv::Rect roi = jRectToCvRect(env, rect);
        if (bgra_mat.cols > roi.width && bgra_mat.rows > roi.height) {
            cv::Mat output_mat;
//            ALOGE("cutImage");
            NativeCV::cutImage(bgra_mat, output_mat, roi);
            NativeCV::resizeImage(output_mat, dest_mat);
            return;
        }
    }
    if (src_mat.rows == dest_mat.rows || src_mat.cols == dest_mat.cols)
    {
        bgra_mat.copyTo(dest_mat);
    } else
    {
//        ALOGE("resizeImage %d*%d to %d*%d", bgra_mat.rows,bgra_mat.cols,dest_mat.rows,dest_mat.cols);
        NativeCV::resizeImage(bgra_mat, dest_mat);
    }
    return ;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_fotric_jdenali_cv_JNativeCV_resize(JNIEnv *env, jobject thiz, jobject src,
                                            jobject dest) {
//    ALOGE("Java_com_fotric_jdenali_cv_JNativeCV_resize");
    cv::Mat src_mat = jImageToMat(env, src);
    cv::Mat dest_mat = jImageToMat(env, dest);
    NativeCV::resizeImage(src_mat, dest_mat);
    return ;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fotric_jdenali_cv_JNativeCV_ofstreamSaveImages(JNIEnv *env, jobject thiz, jobject image,
                                                            jstring file_path, jstring file_name) {
    // Convert jstring to std::string
    const char *file_path_cstr = env->GetStringUTFChars(file_path, nullptr);
    const char *file_name_cstr = env->GetStringUTFChars(file_name, nullptr);

    std::string file_path_str(file_path_cstr);
    std::string file_name_str(file_name_cstr);

    env->ReleaseStringUTFChars(file_path, file_path_cstr);
    env->ReleaseStringUTFChars(file_name, file_name_cstr);

    std::string output_path = file_path_str + "/" + file_name_str;

    // Get the ptr field from the JImage object
    jclass image_class = env->GetObjectClass(image);
    jmethodID mid_getData = env->GetMethodID(image_class, "getData", "()Ljava/nio/ByteBuffer;");
    jobject data_object = env->CallObjectMethod(image, mid_getData);

    // Get the byte buffer direct address.
    void* buffer = env->GetDirectBufferAddress(data_object);
    jlong buffer_capacity = env->GetDirectBufferCapacity(data_object);

    if (buffer == NULL) {
    return; // buffer not direct, or JNI access to direct buffers not supported, or buffer has been disposed
    }

    // Save the ptr content to a file
    std::ofstream output_file(output_path, std::ios::binary);
    output_file.write(static_cast<char *>(buffer), buffer_capacity);
    output_file.close();
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_fotric_jdenali_cv_JNativeCV_openUYVYFile(JNIEnv *env, jobject thiz, jstring file_path,
                                                  jstring file_name, jint width, jint height, jobject ret) {
    std::string path = env->GetStringUTFChars(file_path, 0);
    std::string name = env->GetStringUTFChars(file_name, 0);
    cv::Mat ret_mat = jImageToMat(env, ret);
    return NativeCV::openUYVYImage(path, name, width, height, ret_mat);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fotric_jdenali_cv_JNativeCV_encodeSaveImages(JNIEnv *env, jobject thiz, jobject image,
                                                      jstring file_path, jstring file_name) {
    const char *c_file_path = env->GetStringUTFChars(file_path, nullptr);
    const char *c_file_name = env->GetStringUTFChars(file_name, nullptr);

    cv::Mat src_mat = jImageToMat(env, image);
    NativeCV::encodeImageToFile(src_mat, c_file_name, c_file_path);

    env->ReleaseStringUTFChars(file_path, c_file_path);
    env->ReleaseStringUTFChars(file_name, c_file_name);
}