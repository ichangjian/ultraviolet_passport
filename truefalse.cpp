#include "truefalse.h"
#include "log.h"

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
int tf_num = 0;

bool trueFalse(const unsigned char *image_data, int image_width, int image_height, int thresh)
{
    LOGI("TrueFalse version 0.2");
    try
    {
        if (tf_num++ > 5)
        {
            LOGE("please restart");
            return false;
        }

        LOGI("inter");
        Mat image(image_height, image_width, CV_8UC3, (void *)image_data);
        LOGI("cvt data");

        Mat hsv;
        // GaussianBlur(image,image,Size(11,11),0,0);
        cv::cvtColor(image, hsv, COLOR_BGR2HSV);
        Mat HSV[3];
        cv::split(hsv, HSV);
        LOGI("splt data");

        Mat tmpH1, tmpH2, tmpH3;
        //blue
        inRange(HSV[0], Scalar(92, 0.0, 0, 0), Scalar(155, 0.0, 0, 0), tmpH1);
        inRange(HSV[1], Scalar(43.0, 0.0, 0, 0), Scalar(255, 0.0, 0, 0), tmpH2);
        inRange(HSV[2], Scalar(46, 0.0, 0, 0), Scalar(255.0, 0.0, 0, 0), tmpH3);

        bitwise_and(tmpH3, tmpH2, tmpH2);
        bitwise_and(tmpH1, tmpH2, tmpH1);
        Mat blue = tmpH1.clone();
        LOGI("blue color");

        //black
        inRange(HSV[0], Scalar(0, 0.0, 0, 0), Scalar(180, 0.0, 0, 0), tmpH1);
        inRange(HSV[1], Scalar(0.0, 0.0, 0, 0), Scalar(255, 0.0, 0, 0), tmpH2);
        inRange(HSV[2], Scalar(0, 0.0, 0, 0), Scalar(46.0, 0.0, 0, 0), tmpH3);

        bitwise_and(tmpH3, tmpH2, tmpH2);
        bitwise_and(tmpH1, tmpH2, tmpH1);
        Mat black = tmpH1.clone();
        LOGI("black color");

        Mat bw = (black + blue) / 255;
        Scalar he = cv::sum(bw);
        float area = 100 - 100 * he[0] / (image.cols * image.rows);
        LOGI("ares %f", area);

        if (area > thresh)
        {
            return true;
        }

        return false;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        LOGE("crash");
        return false;
    }
}
