#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{

    Mat img1;
    img1 = imread("./assets/input1.jpg", CV_LOAD_IMAGE_COLOR);

    Mat img2(img1.rows, img1.cols, CV_8UC3);

    cout << img1.channels() << endl; // 3channel image
    cout << img1.size() << endl;     // img1.size = 653 x 529

    Point pt;

    for (pt.x = 0; pt.x <= img2.rows; pt.x++)
    {
        for (pt.y = 0; pt.y <= img2.cols; pt.y++)
        {
            if (100 < img1.at<Vec3b>(pt.x, pt.y)[0] && img1.at<Vec3b>(pt.x, pt.y)[0] <= 155)
                img2.at<Vec3b>(pt.x, pt.y) = Vec3b(0, 255, 0);

            else if (155 <= img1.at<Vec3b>(pt.x, pt.y)[0] && img1.at<Vec3b>(pt.x, pt.y)[0] <= 180)
                img2.at<Vec3b>(pt.x, pt.y) = Vec3b(255, 0, 0);

            else if (200 < img1.at<Vec3b>(pt.x, pt.y)[0] && img1.at<Vec3b>(pt.x, pt.y)[0] < 240)
                img2.at<Vec3b>(pt.x, pt.y) = Vec3b(0, 0, 255);

            else if (235 < img1.at<Vec3b>(pt.x, pt.y)[0] && img1.at<Vec3b>(pt.x, pt.y)[0] <= 245)
                img2.at<Vec3b>(pt.x, pt.y) = Vec3b(0, 255, 255);

            else
                img2.at<Vec3b>(pt.x, pt.y) = Vec3b(255, 255, 255);
        }
    }

    imshow("output1", img1);
    imshow("output2", img2);

    waitKey(0);
    return 0;
}