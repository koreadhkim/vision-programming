#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int pxb_max = 0, pyb_max = 0;
int pxb_min = 255, pyb_min = 255;
int xb_tmp = 0, yb_tmp = 0;

int pxr_max = 0, pyr_max = 0;
int pxr_min = 255, pyr_min = 255;
int xr_tmp = 0, yr_tmp = 0;

int pxg_max = 0, pyg_max = 0;
int pxg_min = 255, pyg_min = 255;
int xg_tmp = 0, yg_tmp = 0;

int pxy_max = 0, pyy_max = 0;
int pxy_min = 255, pyy_min = 255;
int xy_tmp = 0, yy_tmp = 0;

int pxp_max = 0, pyp_max = 0;
int pxp_min = 255, pyp_min = 255;
int xp_tmp = 0, yp_tmp = 0;

int main()
{
    int count = 0;
    Mat img = imread("./assets/hwfig3-2.jpg", 1);
    Point pt;
    //rows = 425 , cols = 300
    for (pt.x = 0; pt.x <= img.rows; pt.x++)
    {
        for (pt.y = 0; pt.y <= img.cols; pt.y++)
        {
            Vec3b Color = img.at<Vec3b>(pt.x, pt.y);
            if (Color[0] >= 100 && Color[1] < 50 && Color[2] < 50)
            {
                if (pxb_max < pt.y)
                    pxb_max = pt.y;
                if (pxb_min > pt.y)
                    pxb_min = pt.y;

                if (pyb_min > pt.x)
                    pyb_min = pt.x;
                if (pyb_max < pt.x)
                    pyb_max = pt.x;
            }
            if (Color[2] >= 100 && Color[0] < 50 && Color[1] < 50)
            {
                if (pxr_max < pt.y)
                    pxr_max = pt.y;
                if (pxr_min > pt.y)
                    pxr_min = pt.y;

                if (pyr_min > pt.x)
                    pyr_min = pt.x;
                if (pyr_max < pt.x)
                    pyr_max = pt.x;
            }

            if (Color[1] >= 100 && Color[0] < 50 && Color[2] < 50)
            {
                if (pxg_max < pt.y)
                    pxg_max = pt.y;
                if (pxg_min > pt.y)
                    pxg_min = pt.y;

                if (pyg_min > pt.x)
                    pyg_min = pt.x;
                if (pyg_max < pt.x)
                    pyg_max = pt.x;
            }

            if (Color[0] < 20 && Color[1] >= 100 && Color[2] >= 100)
            {
                if (pxy_max < pt.y)
                    pxy_max = pt.y;
                if (pxy_min > pt.y)
                    pxy_min = pt.y;

                if (pyy_min > pt.x)
                    pyy_min = pt.x;
                if (pyy_max < pt.x)
                    pyy_max = pt.x;
            }

            if (Color[0] >= 200 && Color[1] < 150 && Color[2] >= 200)
            {
                if (pxp_max < pt.y)
                    pxp_max = pt.y;
                if (pxp_min > pt.y)
                    pxp_min = pt.y;

                if (pyp_min > pt.x)
                    pyp_min = pt.x;
                if (pyp_max < pt.x)
                    pyp_max = pt.x;
            }
        }
    }

    xb_tmp = (pxb_max + pxb_min) / 2;

    yb_tmp = (pyb_max + pyb_min) / 2;

    xr_tmp = (pxr_max + pxr_min) / 2;

    yr_tmp = (pyr_max + pyr_min) / 2;

    xg_tmp = (pxg_max + pxg_min) / 2;

    yg_tmp = (pyg_max + pyg_min) / 2;

    xy_tmp = (pxy_max + pxy_min) / 2;

    yy_tmp = (pyy_max + pyy_min) / 2;

    xp_tmp = (pxp_max + pxp_min) / 2;

    yp_tmp = pyp_max - 10;

    line(img, Point(xb_tmp, yb_tmp), Point(xr_tmp, yr_tmp), Scalar(0, 0, 0), 1);

    line(img, Point(xr_tmp, yr_tmp), Point(xg_tmp, yg_tmp), Scalar(0, 0, 0), 1);

    line(img, Point(xg_tmp, yg_tmp), Point(xy_tmp, yy_tmp), Scalar(0, 0, 0), 1);

    line(img, Point(xy_tmp, yy_tmp), Point(xp_tmp, yp_tmp), Scalar(0, 0, 0), 1);

    imshow("img", img);

    waitKey(0);

    return 0;
}