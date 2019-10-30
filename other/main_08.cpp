#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat image_01 = imread("./assets/input_03.jpg", IMREAD_COLOR);
    CV_Assert(image_01.data);

    Mat x_axis, y_axis, xy_axis, rep_img, trans_img;

    // Vertical flip
    flip(image_01, x_axis, 0);
    // horizontal flip
    flip(image_01, y_axis, 1);
    // Horizontal and Vertical flip
    flip(image_01, xy_axis, -1);
    // repeat (x_1,y_2)
    repeat(image_01,1,2,rep_img);
    // transposition
    transpose(image_01,trans_img);

    imshow("input_03.jpg",image_01);
    imshow("Vertical_flip",x_axis);
    imshow("horizontal_flip",y_axis);
    imshow("Horizontal and Vertical flip",xy_axis);
    imshow("repeat",rep_img);
    imshow("transpose",trans_img);

    waitKey(0);

    return 0;
}