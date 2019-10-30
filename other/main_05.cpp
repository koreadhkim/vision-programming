#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Scalar olive(128, 128, 0), violet(221, 160, 221), brown(42, 42, 165);
    Point pt_01(20, 100), pt_02(20, 200), pt_03(20, 250);

    Mat image_01(300, 500, CV_8UC3, Scalar(255, 255, 255));

    putText(image_01, "SIMPLEX", Point(20, 30), FONT_HERSHEY_SIMPLEX, 1, brown);
    putText(image_01, "DUPLEX", pt_01, FONT_HERSHEY_DUPLEX, 2, olive);
    putText(image_01, "TRIPLEX", pt_02, FONT_HERSHEY_TRIPLEX, 3, violet);
    putText(image_01, "ITALIC", pt_03, FONT_HERSHEY_PLAIN | FONT_ITALIC, 2, violet);

    imshow("putText", image_01);

    waitKey(0);

    return 0;
}