#include <opencv2/opencv.hpp>
#include <iostream>
#include "truefalse.h"
#include "log.h"
using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    string file(argv[1]);
    Mat image = imread(file);
    std::cout << trueFalse(image.data, image.cols, image.rows, 15);
}
