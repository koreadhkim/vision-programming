#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat image_01(300, 400, CV_8U, Scalar(255));
    Mat image_02(300, 400, CV_8U, Scalar(100));

    string title_01 = "white_window";
    string title_02 = "gray_window";

    // window_autosize = matrix 크기에 맞춰 생성(창크기 변경 불가능)
    namedWindow(title_01, WINDOW_AUTOSIZE);
    namedWindow(title_02, WINDOW_NORMAL);
    moveWindow(title_01, 100, 200);
    moveWindow(title_02, 300, 200);

    imshow(title_01, image_01);
    imshow(title_02, image_02);

    waitKey(0);

    destroyAllWindows();
    return 0;
}