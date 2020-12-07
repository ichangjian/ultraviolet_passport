#include "com_truefalse_sdk_upTrueFalse.h"
#include "../truefalse.h"
#include <iostream>
#include <vector>
#include <cstddef>
#include <android/log.h>

#ifdef _Included_com_truefalse_sdk_upTrueFalse
extern "C"
{
#define LOG_TAG "TrueFalse"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
  JNIEXPORT jint JNICALL Java_com_truefalse_sdk_upTrueFalse(JNIEnv *env, jobject, jobjectArray rgb_data, jint thresh)
  {
    jarray jniarray;
    int rows = env->GetArrayLength(rgb_data);
    LOGI("image height %d", rows);

    jniarray = (jcharArray)env->GetObjectArrayElement(rgb_data, 0);
    int cols = env->GetArrayLength(jniarray);
    LOGI("image width %d", cols);

    std::vector<std::vector<unsigned char> > image_data;
    for (size_t i = 0; i < rows; i++)
    {
      jniarray = (jcharArray)env->GetObjectArrayElement(rgb_data, i);
      unsigned short *rowdata = env->GetCharArrayElements((jcharArray)jniarray, 0);

      std::vector<unsigned char> row_data;
      for (jint j = 0; j < cols; j++)
      {
        row_data.push_back((unsigned char)rowdata[j]);
      }
      image_data.push_back(row_data);
    }

    LOGI("copyed image data");
    if (trueFalse((unsigned char*)image_data.data(), rows, cols, (int)thresh))
      return 1;
    return 0;
  }
}
#endif