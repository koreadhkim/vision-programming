#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat image_01, image_02, image_03, image_04, image_05;

    image_01 = imread("./assets/input_02.png", IMREAD_UNCHANGED);
    image_02 = imread("./assets/input_02.png", IMREAD_GRAYSCALE);
    image_03 = imread("./assets/input_02.png", IMREAD_COLOR);
    image_04 = imread("./assets/input_02.png", IMREAD_ANYDEPTH);
    image_05 = imread("./assets/input_02.png", IMREAD_ANYCOLOR);

    imshow("image_01_IMREAD_UNCHANGED", image_01);
    imshow("image_02_IMREAD_GRAYSCALE", image_02);
    imshow("image_03_IMREAD_COLOR", image_03);
    imshow("image_04_IMREAD_ANYDEPTH", image_04);
    imshow("image_05_IMREAD_ANYCOLOR", image_05);

    waitKey(0);

    return 0;
}