#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

string title = "Trackbar_event";
Mat image_01, image_02;

void onChange(int value, void *userdata)
{

    int threshold = value;
    Point pt;

    for (int i = 0; i <= image_01.rows; i++)
    {
        for (int j = 0; j <= image_01.cols; j++)
        {
            uchar image_01_value = image_01.at<uchar>(j, i);

            if (image_01_value >= threshold)
            {
                image_02.at<uchar>(j, i) = 0;
            }
            else
            {
                image_02.at<uchar>(j, i) = 255;
            }
        }
    }

    imshow(title, image_02);
}

int main()
{
    // Initial trackbar value
    int pos_min = 0;

    // Max trackbar value
    int pos_max = 255;

    // read image_01/image_02
    image_01 = imread("./assets/input_01.jpg", IMREAD_GRAYSCALE);
    image_02 = Mat(image_01.cols, image_01.rows, CV_8UC1);

    namedWindow(title, WINDOW_AUTOSIZE);

    createTrackbar("Brightness", title, &pos_min, pos_max, onChange);

    waitKey(0);
    return 0;
}
