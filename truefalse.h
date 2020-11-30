#pragma once
#define LOCAPI extern "C"

/*
函数功能：识别紫外护照上的颜色信息判断真伪
函数参数：
    image_data:图像数据地址
    image_width:图像宽
    image_height:图像高
    thresh:颜色信息在整个图像上的占比
函数返回值：当识别为真是返回true，否则返回false
*/
LOCAPI bool trueFalse(const char *image_data, int image_width, int image_height, int thresh);