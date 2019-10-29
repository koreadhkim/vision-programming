#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int peak[] = {};
int Th_01 = 0;
float inclination_value = 0.0;
float inclination[255] = {};
float inclination_pt_x[255] = {};

void calc_histo(Mat image, Mat &hist, int bins, int range_max = 256)
{
    int histSize[] = {
        bins};
    float range[] = {
        0,
        (float)range_max};
    int channels[] = {
        0};
    const float *ranges[] = {
        range};
    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
}

void draw_histo(Mat hist, Mat &hist_img, Size size = Size(256, 200))
{
    hist_img = Mat(size, CV_8U, Scalar(255));

    float bin = (float)hist_img.cols / hist.rows;
    normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);
    int count = 0;

    for (int i = 0; i < hist.rows; i++)
    {
        float start_x = i * bin;
        float end_x = (i + 1) * bin;
        Point2f pt_01(start_x, 0);
        Point2f pt_02(end_x, hist.at<float>(i));

        Point2f pt_03(start_x + 1, 0);
        Point2f pt_04(end_x, hist.at<float>(i + 1));

        if (pt_02.y > 0)
        {
                        cout<< count <<endl;

            if (i % 7 == 0)
            {
                inclination[count] = ((pt_04.y - pt_02.y) / (pt_03.x - pt_01.x));
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
            inclination_value = inclination[i];
            if (inclination_pt_x[i] > 50)
            {
                Th_01 = inclination_pt_x[i];
            }
        }
    }

    // cout << Th_01<<endl;
    flip(hist_img, hist_img, 0);
}
int main()
{

    Mat image_01 = imread("./assets/input_02.jpg", 0);
    Mat image_02(image_01.rows, image_01.cols, CV_8UC1);

    // check for image_size
    // cout << image_01.size()<<endl;
    // cout << image_02.size()<<endl;
    CV_Assert(!image_01.empty());

    Mat hist,
        hist_img_01;

    calc_histo(image_01, hist, 256);
    draw_histo(hist, hist_img_01);

    for (int i = 0; i <= image_01.rows; i++)
    {
        for (int j = 0; j <= image_01.cols; j++)
        {
            // cout <<Th_01<<endl;

            if (image_01.at<uchar>(i, j) >= Th_01)
            {
                image_02.at<uchar>(i, j) = 255;
            }
        }
    }

    cout << image_01.size() << endl;
    imshow("hist_img_01", hist_img_01);
    imshow("image_01", image_01);
    imshow("image_02", image_02);

    waitKey(0);
    return 0;
}





