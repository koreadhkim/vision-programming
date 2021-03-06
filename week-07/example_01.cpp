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

void affine_transform(Mat img, Mat &dst, Mat map, Size size)
{

    dst = Mat(img.size(), img.type(), Scalar(0));
    Rect rect(Point(0, 0), img.size());

    Mat inv_map;

    invertAffineTransform(map, inv_map);

    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            Point3d ji(j, i, 1);
            Mat xy = inv_map * (Mat)ji;
            Point2d pt = (Point2d)xy;

            if (rect.contains(pt))
                dst.at<uchar>(i, j) = bilinear_value(img, pt.x, pt.y);
        }
    }
}
int main()
{
    Mat image = imread("./assets/affine_test3.jpg", 0);
    CV_Assert(image.data);

    Point2f pt_01[3] = {Point2f(10, 200), Point2f(200, 150), Point2f(300, 300)};
    Point2f pt_02[3] = {Point2f(10, 10), Point2f(250, 10), Point2f(300, 300)};
    Point center(200, 100);

    double angle = 30.0;
    double scale = 1;

    Mat aff_map = getAffineTransform(pt_01, pt_02);
    Mat rot_map = getRotationMatrix2D(center, angle, scale);
    Mat dst_01, dst_02, dst_03, dst_04;

    affine_transform(image, dst_01, aff_map, image.size());
    affine_transform(image, dst_02, rot_map, image.size());

    warpAffine(image, dst_03, aff_map, image.size(), INTER_LINEAR);
    warpAffine(image, dst_04, rot_map, image.size(), INTER_LINEAR);

    cvtColor(image, image, CV_GRAY2BGR);
    cvtColor(dst_01, dst_01, CV_GRAY2BGR);
    cvtColor(dst_02, dst_02, CV_GRAY2BGR);
    cvtColor(dst_03, dst_03, CV_GRAY2BGR);
    cvtColor(dst_04, dst_04, CV_GRAY2BGR);

    for (int i = 0; i < 3; i++)
    {
        circle(image, pt_01[i], 3, Scalar(0, 0, 255), 2);
        circle(dst_01, pt_02[i], 3, Scalar(0, 0, 255), 2);
    }

    imshow("image", image);
    imshow("dst_01", dst_01);
    imshow("dst_02", dst_02);
    imshow("dst_03", dst_03);
    imshow("dst_04", dst_04);

    waitKey(0);
    return 0;
}
