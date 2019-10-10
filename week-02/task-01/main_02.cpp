#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

string title = "Trackbar_event";
Mat img1, img2;

int main()
{

    img1 = imread("./assets/input1.jpg", IMREAD_GRAYSCALE);
    img2 = Mat(img1.rows, img1.cols, CV_8UC3);

    Point pt;

    for (pt.x = 0; pt.x <= img1.rows; pt.x++)
    {
        for (pt.y = 0; pt.y <= img1.cols; pt.y++)
        {
            
            if (img1.at<uchar>(pt.x, pt.y) >= 100&& img1.at<uchar>(pt.x, pt.y) <= 150)
                  img2.at<Vec3b>(pt.x, pt.y) = Vec3b(0, 255, 0);

            else if (img1.at<uchar>(pt.x, pt.y) >= 151 && img1.at<uchar>(pt.x, pt.y) <= 205)
                img2.at<Vec3b>(pt.x, pt.y) = Vec3b(255, 0, 0);

            else if (img1.at<uchar>(pt.x, pt.y) >= 206 && img1.at<uchar>(pt.x, pt.y) <= 237)
                img2.at<Vec3b>(pt.x, pt.y) = Vec3b(0, 0, 255);

            else if (img1.at<uchar>(pt.x, pt.y) >= 238 && img1.at<uchar>(pt.x, pt.y) <= 245)
                img2.at<Vec3b>(pt.x, pt.y) = Vec3b(0, 255, 255);

            else
                img2.at<Vec3b>(pt.x, pt.y) = Vec3b(255, 255, 255);
        }
    }

    imshow("output", img2);
    waitKey(0);
    return 0;
}
