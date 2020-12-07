#include <jni.h>

#ifndef _Included_com_truefalse_sdk_upTrueFalse
#define _Included_com_truefalse_sdk_upTrueFalse
#ifdef __cplusplus
extern "C"
{
#endif
  /*
参数：
bitmap: Jave Bitmap 类型
返回值：
识别成功返回1，失败返回0
*/
  JNIEXPORT jint JNICALL Java_com_truefalse_sdk_upTrueFalse(JNIEnv *, jobject, jobject bitmap, jint thresh);

#ifdef __cplusplus
}
#endif
#endif
