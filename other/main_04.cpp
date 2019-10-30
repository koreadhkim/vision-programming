#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;


int main()
{
    Scalar blue(255,0,0), green(0,255,0), red(0,0,255), white(255,255,255), yellow(0,255,255);

    Mat image_01(400,600,CV_8UC3,white);
    Point pt_01(50,130),pt_02(200,300),pt_03(300,150),pt_04(400,50);
    Rect rect(pt_03,Size(200,150));

    // line(image_x,start_point,end_point_,color,thickness,lineType,shift)
    line(image_01,pt_01,pt_02,red);
    line(image_01,pt_03,pt_04,green,5);
    line(image_01,pt_03,pt_04,green,3,LINE_MAX,1);

    // rectangle
    rectangle(image_01,rect,blue,2);
    rectangle(image_01,rect,blue,CV_FILLED,LINE_MAX,1);
    rectangle(image_01,pt_01,pt_02,red,3);

    imshow("line and rectangle",image_01);


    // Check for shifted values
    // int shift_01 = input_x;
    // int shift_02 = shift_01 >> 1;
    // cout << shift_01 <<endl;
    // cout << shift_02 << endl;

    waitKey(0);

    return 0;
}