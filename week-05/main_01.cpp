#include <opencv2/opencv.hpp>
#include <iostream>
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

            if (i % 20 == 0)
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
// avg filtering 으로 변경. _(3x3 , 5x5, 7x7)
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

    Mat image_01 = imread("./assets/cellimg2.jpg", 0);
    Mat image_02(image_01.size(), CV_8U, Scalar(0));
    Mat image_03(image_01.size(), CV_8U, Scalar(0));
    Mat image_04(image_01.size(), CV_8U, Scalar(0));
    Mat image_05(image_01.size(), CV_8U, Scalar(0));
    Mat image_06(image_01.size(), CV_8U, Scalar(0));

    CV_Assert(!image_01.empty() || !image_02.empty() || !image_03.empty() || !image_04.empty() || !image_05.empty());

    Mat hist_01, hist_img_01;
    Mat hist_02, hist_img_02;
    Mat hist_03, hist_img_03;
    Mat hist_04, hist_img_04;
    Mat hist_05, hist_img_05;

    Mat avg_image_01, avg_image_02, avg_image_03, avg_image_04;

    init();

    // filtering 안하고 threshold 한거,
    calc_histo(image_01, hist_01, 256);
    draw_histo(hist_01, hist_img_01);
    threshold(image_01, image_02, Th_01, 255, THRESH_BINARY);

    cout << Th_01 << endl;

    init();

    // filtering (3x3 avg) threshold 한거,
    averageFilter(image_01, avg_image_01, 3);
    calc_histo(avg_image_01, hist_02, 256);
    draw_histo(hist_02, hist_img_02);
    cout << Th_01 << endl;
    threshold(avg_image_01, image_03, Th_01, 255, THRESH_BINARY);

    init();

    // filtering (5x5 avg) threshold 한거,
    averageFilter(image_01, avg_image_02, 5);
    calc_histo(avg_image_02, hist_03, 256);
    draw_histo(hist_03, hist_img_03);
    cout << Th_01 << endl;
    threshold(avg_image_02, image_04, Th_01, 255, THRESH_BINARY);

    init();

    // filtering (7x7 avg) threshold 한거,
    averageFilter(image_01, avg_image_03, 7);
    calc_histo(avg_image_03, hist_04, 256);
    draw_histo(hist_04, hist_img_04);
    cout << Th_01 << endl;
    threshold(avg_image_03, image_05, Th_01, 255, THRESH_BINARY);

    init();

    // filtering (11x11 avg) threshold 한거,
    averageFilter(image_01, avg_image_04, 11);
    calc_histo(avg_image_04, hist_05, 256);
    draw_histo(hist_05, hist_img_05);
    cout << Th_01 << endl;
    threshold(avg_image_04, image_06, Th_01, 255, THRESH_BINARY);

    imshow("hist_img_01", hist_img_01);
    imshow("hist_img_02_avg(3)", hist_img_02);
    imshow("hist_img_02_avg(5)", hist_img_03);
    imshow("hist_img_02_avg(7)", hist_img_04);
    imshow("hist_img_02_avg(11)", hist_img_05);

    imshow("none_filtering", image_02);
    imshow("avg(3)_image", image_03);
    imshow("avg(5)_image", image_04);
    imshow("avg(7)_image", image_05);
    imshow("avg(11)_image", image_06);


    waitKey(0);
    return 0;
}
