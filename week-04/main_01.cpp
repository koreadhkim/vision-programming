#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int peak[] = {};
int Th_01 = 0;
int Th_02 = 0;
int Th_03 = 0;

void calc_histo(Mat image, Mat &hist, int bins, int range_max = 256)
{
    int histSize[] = {bins};
    float range[] = {0, (float)range_max};
    int channels[] = {0};
    const float *ranges[] = {range};
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

        if (pt_02.y > 0)
        {
            // cout << pt_02.y<<endl;
            if (pt_02.y > 70)
            {

                cout << "hello" << endl;
                cout << pt_02.x << endl;
                peak[count] = pt_02.x;
                count = count + 1;
            }

            rectangle(hist_img, pt_01, pt_02, Scalar(0), -1);
        }
    }
    cout <<"peak_01" <<peak[0] <<endl<< "peak_02" <<endl<<peak[1] <<"peak_03"<<endl<< peak[2]<<"peak_04" <<endl<< peak[3] << endl;
    Th_01 = (peak[0] + peak[1]) / 2;
    Th_02 = (peak[1] + peak[2]) / 2;
    Th_03 = (peak[2] + peak[3]) / 2;

    flip(hist_img, hist_img, 0);
}
int main()
{

    Mat image_01 = imread("./assets/input_03.jpg", 0);
    Mat image_02(image_01.rows, image_01.cols, CV_8UC3);
    
    // check for image_size
    // cout << image_01.size()<<endl;
    // cout << image_02.size()<<endl;
    CV_Assert(!image_01.empty());

    Mat hist, hist_img_01;

    calc_histo(image_01, hist, 256);
    draw_histo(hist, hist_img_01);

    for (int i = 0; i <= image_01.rows; i++)
    {
        for (int j = 0; j <= image_01.cols; j++)
        {
            // cout <<Th_01<<endl;

            if (image_01.at<uchar>(i, j) < Th_01)
            {
                image_02.at<Vec3b>(i, j) = Vec3b(255, 0, 0);
            }

            else if (image_01.at<uchar>(i, j) > Th_01 && image_01.at<uchar>(i, j) < Th_02)
            {
                image_02.at<Vec3b>(i, j) = Vec3b(0, 255, 0);
            }
            else if (image_01.at<uchar>(i, j) > Th_02 && image_01.at<uchar>(i, j) < Th_03)
            {
                image_02.at<Vec3b>(i, j) = Vec3b(0, 0, 255);
            }
            else
            {
                image_02.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
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
