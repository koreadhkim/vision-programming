#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{

    Mat img_01(250, 250, CV_8U, Scalar(0));
    Mat img_02(250, 250, CV_8U, Scalar(0));
    Mat img_03, img_04, img_05, img_06;

    // Point center = img_01.size() / 2;
    circle(img_01, Point(round(img_01.cols / 2), round(img_01.rows / 2)), 80, Scalar(255), -1);
    rectangle(img_02, Point(0, 0), Point(125, 250), Scalar(255), -1);

    imshow("img_01", img_01);
    imshow("img_02", img_02);

    bitwise_or(img_01, img_02, img_03);
    bitwise_and(img_01, img_02, img_04);
    bitwise_not(img_01, img_05);

    imshow("bitwise_or", img_03);
    imshow("bitwise_and", img_04);
    imshow("bitwise_not", img_05);

    waitKey(0);
    return 0;
}