#include "com_truefalse_sdk_upTrueFalse.h"
#include "../truefalse.h"
#include <iostream>
#include <vector>
#include <cstddef>
#include <android/log.h>
#include <android/bitmap.h>
#include <opencv2/opencv.hpp>
using namespace cv;
#ifdef _Included_com_truefalse_sdk_upTrueFalse
extern "C"
{
#define LOG_TAG "TrueFalse"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

  JNIEXPORT jint JNICALL Java_com_truefalse_sdk_upTrueFalse(JNIEnv *env, jobject, jobject bitmap, jint thresh)
  {
    AndroidBitmapInfo info;
    void *pixels = 0;
    cv::Mat dst;
    bool needUnPremultiplyAlpha = true;
    try
    {
      LOGI("nBitmapToMat");
      CV_Assert(AndroidBitmap_getInfo(env, bitmap, &info) >= 0);
      CV_Assert(info.format == ANDROID_BITMAP_FORMAT_RGBA_8888 ||
                info.format == ANDROID_BITMAP_FORMAT_RGB_565);
      CV_Assert(AndroidBitmap_lockPixels(env, bitmap, &pixels) >= 0);
      CV_Assert(pixels);
      dst.create(info.height, info.width, CV_8UC4);
      if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888)
      {
        LOGI("nBitmapToMat: RGBA_8888 -> CV_8UC4");
        Mat tmp(info.height, info.width, CV_8UC4, pixels);
        if (needUnPremultiplyAlpha)
          cvtColor(tmp, dst, cv::COLOR_RGBA2BGR);
        else
          tmp.copyTo(dst);
      }
      else
      {
        // info.format == ANDROID_BITMAP_FORMAT_RGB_565
        LOGI("nBitmapToMat: RGB_565 -> CV_8UC4");
        cv::Mat tmp(info.height, info.width, CV_8UC2, pixels);
        cvtColor(tmp, dst, cv::COLOR_BGR5552BGR);
      }
      AndroidBitmap_unlockPixels(env, bitmap);

      // imwrite("/sdcard/test0.jpg", dst);
      if (trueFalse(dst.data, dst.cols, dst.rows, (int)thresh))
        return 1;
      return 0;
    }
    catch (const cv::Exception &e)
    {
      AndroidBitmap_unlockPixels(env, bitmap);
      LOGI("nBitmapToMat caught cv::Exception: %s", e.what());
      jclass je = env->FindClass("org/opencv/core/CvException");
      if (!je)
        je = env->FindClass("java/lang/Exception");
      env->ThrowNew(je, e.what());
      return 0;
    }
    catch (...)
    {
      AndroidBitmap_unlockPixels(env, bitmap);
      LOGI("nBitmapToMat caught unknown exception (...)");
      jclass je = env->FindClass("java/lang/Exception");
      env->ThrowNew(je, "Unknown exception in JNI code {nBitmapToMat}");
      return 0;
    }
  }
}
#endif