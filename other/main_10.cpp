#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{

    Mat image = imread("./assets/input_04.jpg", IMREAD_COLOR);
    vector<Mat> bgr_vec;

    // split(from,to)
    split(image, bgr_vec);

    // imshow org_img
    imshow("org_img", image);

    // split image check
    imshow("Blue_Channel", bgr_vec[0]);
    imshow("Green_Channel", bgr_vec[1]);
    imshow("Red_Channel", bgr_vec[2]);

    Mat merge_img(image.rows, image.cols, CV_8UC3);
    Mat bgr_arr[] = {bgr_vec[0], bgr_vec[1], bgr_vec[2]};

    // merge(from,to)
    merge(bgr_arr, 3, merge_img);

    // merge image check
    imshow("merge_img", merge_img);

    waitKey(0);
    return 0;
}