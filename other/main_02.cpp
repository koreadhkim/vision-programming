#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat image_01 = imread("./assets/input_04.jpg",IMREAD_COLOR);

    string title_01 = "window_size_AUTOSIZE";
    string title_02 = "window_size_NORMAL";

    namedWindow(title_01, WINDOW_AUTOSIZE);
    namedWindow(title_02, WINDOW_NORMAL);

    moveWindow(title_01, 0, 0);
    moveWindow(title_02, 500, 0);

    resizeWindow(title_01, 500, 200);
    resizeWindow(title_02, 200, 200);

    imshow(title_01, image_01);
    imshow(title_02, image_01);
    
    waitKey(0);

    return 0;
}