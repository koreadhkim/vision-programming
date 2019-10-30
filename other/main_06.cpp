#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Scalar orange(0,165,255), blue(255,0,0), magenta(255,0,255);
    Mat image_01(300,500,CV_8UC3,Scalar(255,255,255));


    Point center = Point(round(image_01.cols/2),round(image_01.rows/2));

    // Check center value
    cout << image_01.size()<<endl;
    cout << center <<endl;
    
    Point pt_01(70,50), pt_02(350,220);

    circle(image_01,center,100,blue);
    circle(image_01,pt_01,80,orange,2);
    circle(image_01,pt_02,60,magenta,-1);

    int font = FONT_HERSHEY_COMPLEX;
    
    // putText(image_01,"input_text",start_point,font_style,font_size,color,font_weight)
    putText(image_01,"center_blue",center,font,1.2,blue);
    putText(image_01,"pt_01_orange",pt_01,font,0.8,orange);
    
    // Creates black shadows.
    putText(image_01,"pt_02_magenta",pt_02+Point(2,2),font,0.5,Scalar(0,0,0),2);
    putText(image_01,"pt_02_magenta",pt_02,font,0.5,magenta,1);

    // Check point addition
    cout << pt_02 + Point(2,2)<<endl;

    imshow("draw_circle", image_01);

    waitKey(0);

    return 0;
}