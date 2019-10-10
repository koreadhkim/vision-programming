#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

string title = "Trackbar_event";
Mat img1, img2;

void onChange(int value, void *userdata)
{

    int threshold = value;
    Point pt;

    for (pt.x = 0; pt.x <= img1.rows; pt.x++)
    {
        for (pt.y = 0; pt.y <= img1.cols; pt.y++)
        {
            uchar val = img1.at<uchar>(pt.x, pt.y);
        
            if (val <= threshold){
                img2.at<uchar>(pt.x, pt.y) = uchar(255);
                cout<<threshold-val<<endl;

            }
            else
                img2.at<uchar>(pt.x, pt.y) = uchar(0);
        }
    }
    
    imshow("Brightness", img2);
}

int main()
{

    int pos_min = 0;
    int pos_max = 255;
    img1 = imread("./assets/input1.jpg", IMREAD_GRAYSCALE);
    img2 = Mat(img1.rows, img1.cols, CV_8UC3);

    namedWindow(title, WINDOW_AUTOSIZE);

    createTrackbar("Brightness", title, &pos_min, pos_max, onChange);

    imshow(title, img1);

    waitKey(0);
    return 0;
}
