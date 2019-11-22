#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
uchar bilinear_value(Mat img, int x, int y)
{
    if (x >= img.cols - 1)
        x--;
    if (y >= img.rows - 1)
        y--;

    Point pt((int)x, (int)y);
    int A = img.at<uchar>(pt);
    int B = img.at<uchar>(pt + Point(0, 1));
    int C = img.at<uchar>(pt + Point(1, 0));
    int D = img.at<uchar>(pt + Point(1, 1));

    double alpth = y - pt.y;
    double beta = x - pt.x;

    int M1 = A + (int)cvRound(alpth * (B - A));
    int M2 = C + (int)cvRound(alpth * (D - C));
    int P = M1 + (int)cvRound(beta * (M2 - M1));
    return saturate_cast<uchar>(P);
};

void rotation(Mat img, Mat &dst, double dgree)
{
    double radian = dgree / 180 * CV_PI;
    double sin_value = sin(radian);
    double cos_value = cos(radian);

    Rect rect(Point(0, 0), img.size());
    dst = Mat(img.size(), img.type(), Scalar(0));

    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {

            double x = j * cos_value + 25*sin(2*CV_PI*i/180);
            double y = -j * sin_value + i * cos_value;

            if (rect.contains(Point2d(x, y)))
                dst.at<uchar>(i, j) = bilinear_value(img, x, y);
        }
    }
}
int main()
{
    Mat image = imread("./assets/lena.jpg", CV_8UC1);
    CV_Assert(image.data);

    Mat dst_img(image.size(), CV_8UC1);

    rotation(image,dst_img,0);
    imshow("src_img", image);
    imshow("dst_img", dst_img);
    waitKey(0);
    return 0;
}
