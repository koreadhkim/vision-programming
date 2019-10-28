#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int peak[] = {};
int Th_01 = 0;

void calc_histo(Mat image, Mat &hist, int bins, int range_max = 256)
{
    int histSize[] = {bins};
    float range[] = {0, (float)range_max};
    int channels[] = {0};
    const float *ranges[] = {range};
    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);

    cout << histSize << endl;
}

void draw_histo(Mat hist, Mat &hist_img, Size size = Size(256, 200))
{
    hist_img = Mat(size, CV_8U, Scalar(255));

    float bin = (float)hist_img.cols / hist.rows;
    normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);

    for (int i = 0; i < hist.rows; i++)
    {
        float start_x = i * bin;
        float end_x = (i + 1) * bin;
        Point2f pt_01(start_x, 0);
        Point2f pt_02(end_x, hist.at<float>(i));

        if (pt_02.y > 0)
        {
            
            rectangle(hist_img, pt_01, pt_02, Scalar(0), -1);
        }
    }
    flip(hist_img, hist_img, 0);
}
int main()
{

    Mat image_01 = imread("./assets/cellimg2.jpg", 0);
    Mat image_02 = imread("./assets/cellimg2.jpg", 0);
    CV_Assert(!image_01.empty());

    Mat hist, hist_img_01;

    calc_histo(image_01, hist, 256);
    draw_histo(hist, hist_img_01);


    cout << image_01.size() << endl;
    imshow("hist_img_01", hist_img_01);
    imshow("image_01", image_01);
    imshow("image_02", image_02);

    waitKey(0);
    return 0;
}
