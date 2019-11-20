#include <opencv2/opencv.hpp>
#include <iostream>
#include "BlobLabeling.h"
using namespace cv;
using namespace std;

int peak[] = {};
int Th_01 = 0;
float inclination_value = 0.0;
float inclination[255] = {};
float inclination_pt_x[255] = {};
float inclination_before_value[255] = {};

void calc_histo(Mat image, Mat &hist, int bins, int range_max = 256)
{
    int histSize[] = {bins};
    float range[] = {0, (float)range_max};
    int channels[] = {0};
    const float *ranges[] = {range};
    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);

    // cout << histSize << endl;
}

void draw_histo(Mat hist, Mat &hist_img, Size size = Size(256, 200))
{
    cout << "hello" << endl;
    hist_img = Mat(size, CV_8U, Scalar(255));
    int count = 0;

    float bin = (float)hist_img.cols / hist.rows;
    normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);

    for (int i = 0; i < hist.rows; i++)
    {
        float start_x = i * bin;
        float end_x = (i + 1) * bin;

        Point2f pt_01(start_x, 0);
        Point2f pt_02(end_x, hist.at<float>(i));
        Point2f pt_03(start_x + 1, 0);
        Point2f pt_04(end_x, hist.at<float>(i + 1));

        if (pt_02.y >= 0)
        {
            inclination_before_value[i] = pt_02.y;

            if (i % 25 == 0)
            {
                inclination[count] = ((pt_04.y - inclination_before_value[i - 15]) / (pt_03.x - pt_01.x - 15));
                inclination_pt_x[count] = pt_01.x;
            }
            rectangle(hist_img, pt_01, pt_02, Scalar(0), -1);
            count++;
        }
    }

    int floatCnt = sizeof(inclination) / sizeof(inclination[0]);

    for (int i = 0; i < floatCnt; i++)
    {
        if (inclination_value < inclination[i])
        {
            inclination_value = inclination_pt_x[i];
            Th_01 = inclination_pt_x[i];
            cout << inclination_pt_x[i] << endl;
        }
    }
    flip(hist_img, hist_img, 0);
}

void averageFilter(Mat img, Mat &dst, int size)
{
    cout << "hello averagefilter" << endl;
    dst = Mat(img.size(), CV_8U, Scalar(0));

    for (int i = 0; i <= img.rows; i++)
    {
        for (int j = 0; j <= img.cols; j++)
        {
            int x = j - size;
            int y = i - size;

            Point pt_01 = Point(x, y);
            Point pt_02 = pt_01 + (Point)Size(size, size);

            if (pt_01.x < 0)
                pt_01.x = 0;
            if (pt_01.y < 0)
                pt_01.y = 0;
            if (pt_02.x > img.cols)
                pt_02.x = img.cols;
            if (pt_02.y > img.rows)
                pt_02.y = img.rows;

            Rect mask_rect(pt_01, pt_02);
            Mat mask = img(mask_rect);
            dst.at<uchar>(i, j) = (uchar)mean(mask)[0];
        }
    }
}

void init()
{
    int floatCnt = sizeof(inclination) / sizeof(inclination[0]);
    for (int i = 0; i <= floatCnt; i++)
    {

        inclination_pt_x[i] = 0;
        inclination_pt_x[i] = 0;
        inclination_before_value[i] = 0;
        inclination[i] = 0;
        inclination_value = 0.0;
    }
}
int main()
{
    char strp[10] = "A";
    char stp[10];

    Mat srcImage = imread("./assets/coins.jpg", IMREAD_GRAYSCALE);
    Mat gauss_img(srcImage.size(), CV_8UC1);
    Mat binimg(srcImage.size(), CV_8UC1);
    Mat mopimg1(srcImage.size(), CV_8UC1);
    Mat mopimg2(srcImage.size(), CV_8UC1);
    Mat dstImage(srcImage.size(), CV_8UC3, Scalar(0, 0, 0));

    CV_Assert(!srcImage.empty());

    // gaussian kernel define
    Size size(13, 13);
    double sigmaX = 0.3 * ((size.width - 1) * 0.5 - 1) + 0.8;
    double sigmaY = 0.3 * ((size.height - 1) * 0.5 - 1) + 0.8;
    GaussianBlur(srcImage, gauss_img, size, sigmaX, sigmaY);

    Mat hist_01, hist_img_01;

    init();

    calc_histo(gauss_img, hist_01, 256);
    draw_histo(hist_01, hist_img_01);
    threshold(gauss_img, binimg, Th_01, 255, THRESH_BINARY);

    Matx<uchar, 3, 3> mask;
    mask << 1, 1, 1,
        1, 1, 1,
        1, 1, 1;

    // morphologyEx(binimg, mopimg1, MORPH_CLOSE, mask, Point(-1, -1), 2);
    morphologyEx(binimg, mopimg2, MORPH_OPEN, mask, Point(-1, -1), 2);
    cvtColor(mopimg2, dstImage, CV_GRAY2BGR);
    cvtColor(srcImage, srcImage, CV_GRAY2BGR);

    CBlobLabeling resLab;
    resLab.SetParam(mopimg2, mopimg2, dstImage, Th_01);
    resLab.DoLabeling();

    Point pt;
    for (int i = 0; i < resLab.m_nBlobs; i++)
    {
        pt = Point((int)resLab.m_fcog_1[i], (int)resLab.m_fcog_2[i]);
        stp[0] = strp[0] + i;
        stp[1] = 0;
        putText(srcImage, stp, cvPoint(pt.x, pt.y), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);
    }

    // imshow("src_Image", srcImage);
    imshow("hist_img_02_avg(13)", hist_img_01);
    imshow("gaussian_img", gauss_img);
    imshow("bin_img", binimg);

    // imshow("close_img", mopimg1);
    imshow("open_img", mopimg2);
    imshow("dst_img", dstImage);
    imshow("src_image",srcImage);

    waitKey(0);
    return 0;
}
