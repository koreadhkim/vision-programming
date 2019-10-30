#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
// Image to hold the image, Image to contain the separated image [3]
    Mat image_01 , img[3];

    // read image
    image_01 = imread("./assets/bhpark.jpg",IMREAD_COLOR);

    // image.size()
    cout << image_01.size()<<endl;

    // image.depth()
    cout << image_01.depth()<<endl;

    // image channels
    cout << image_01.channels()<<endl;

    // image file size
    cout << image_01.elemSize()*image_01.rows*image_01.cols<<endl;
    
    // Image splite 
    split(image_01,img);

    imwrite("./assets/blue_bhpark.jpg",img[0]);
    imwrite("./assets/green_bhpark.jpg",img[1]);
    imwrite("./assets/red_bhpark.jpg",img[2]);

    Mat image_02, image_03, image_04;

    image_02 = imread("./assets/blue_bhpark.jpg",IMREAD_COLOR);
    image_03 = imread("./assets/green_bhpark.jpg",IMREAD_COLOR);
    image_04 = imread("./assets/red_bhpark.jpg",IMREAD_COLOR);

    imshow("blue_bhpark.jpg", image_02);
    imshow("green_bhpark.jpg", image_03);
    imshow("red_bhpark.jpg", image_04);

	waitKey(0);

	return 0;
}