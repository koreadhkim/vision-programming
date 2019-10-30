#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{

    Mat img_01 = imread("./assets/input_05.jpg", 0);
    Mat img_02 = imread("./assets/input_06.jpg", 0);
    Mat dif_img, test_01_dif, test_02_dif;

    CV_Assert(img_01.data && img_02.data);

    img_01.convertTo(img_01, CV_16S);
    img_02.convertTo(img_02, CV_16S);

    // Difference operation
    subtract(img_01, img_02, dif_img);

    // Check for negative values
    // cout << dif_img<<endl;

    // Absolute value
    test_01_dif = abs(dif_img);

    // Confirm conversion from negative to absolute.
    // cout << test_01_dif<<endl;

    test_01_dif.convertTo(test_01_dif, CV_8U);

    imshow("input_05.jpg", img_01);
    imshow("input_06.jpg", img_02);
    imshow("dif_img.jpg", test_01_dif);

    waitKey(0);
    return 0;
}