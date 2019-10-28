#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{

    Mat image_01 = imread("./assets/add1.jpg", 0);
    Mat image_02 = imread("./assets/add2.jpg", 0);

    Mat add_img_01 = 0.5 * image_01 + 0.7 * image_02;
    Mat add_img_02;

    double alpha = 0.6, beta = 0.7;

    // image_01 * alpha = 0.6% , image_02 * 1 - alpth = 0.4%
    addWeighted(image_01, alpha, image_02, 1 - alpha, 0, add_img_02);

    imshow("image_01.jpg", image_01);
    imshow("image_02.jpg", image_02);
    imshow("add_img_01.jpg", add_img_01);
    imshow("add_img_02.jpg", add_img_02);

    waitKey(0);
    return 0;
}
