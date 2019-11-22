#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat image = imread("./assets/notebook01.jpg", 1);
    CV_Assert(image.data);

    Mat dst_img(image.size(), CV_8UC3);

    Point2f pts_01[4] = {
        Point2f(0, 0), Point2f(image.cols, 0), Point2f(0, image.rows), Point2f(image.cols, image.rows)

    };
    Point2f pts_02[4] = {
        Point2f(20, 55), Point2f(215, 20), Point2f(197, 173), Point2f(430, 95)

    };

    Mat perspect_map = getPerspectiveTransform(pts_02,pts_01);
    warpPerspective(image,dst_img,perspect_map,image.size(),INTER_CUBIC);
    

    imshow("src_img", image);
    imshow("dst_img", dst_img);
    waitKey(0);
    return 0;
}
