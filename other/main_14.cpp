#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{

    Mat img_01 = imread("./assets/input_07.jpg", 1);

    CV_Assert(img_01.data);

    Scalar sum_value = sum(img_01) ;
    Scalar mean_value = mean(img_01) ;
    cout << "sum _value" << endl << sum_value<<endl;
    cout << "mean_value" << endl << mean_value<<endl;

    Mat mask(img_01.size(),CV_8U,Scalar(0));
    mask(Rect(20,40,70,70)).setTo(255);

    Mat mean,stddev;
    meanStdDev(img_01,mean,stddev,mask);
    cout<< "mean"<<endl<<mean<<endl;
    cout << "stddev"<<endl<<stddev<<endl;

    imshow("img_01.jpg",img_01);
    imshow("mask",mask);

    waitKey(0);
    return 0;
}