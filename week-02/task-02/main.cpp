#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int pxb_max = 0, pxb_min = 0, pyb_min = 0;
int xb_tmp = 0, yb_tmp = 0;

int pxr_max = 0, pxr_min = 0, pyr_min = 0;
int xr_tmp = 0, yr_tmp = 0;

int pxg_max = 0, pxg_min = 0, pyg_min = 0;
int xg_tmp = 0, yg_tmp = 0;

int pxy_max = 0, pxy_min = 0, pyy_min = 0;
int xy_tmp = 0, yy_tmp = 0;

int pxp_max = 0, pxp_min = 0, pyp_min = 0;
int xp_tmp = 0, yp_tmp = 0;

int main()
{
    int count = 0;
    Mat img = imread("./assets/input_01.jpg", 1);
    Point pt;

    //rows = 425 , cols = 300
    for (pt.x = 0; pt.x <= img.rows; pt.x++)
    {
        for (pt.y = 0; pt.y <= img.cols; pt.y++)
        {
            Vec3b Color = img.at<Vec3b>(pt.x, pt.y);

            //find blue_circle
            if (Color[0] >= 100 && Color[1] < 50 && Color[2] < 50)
            {
                if (count == 0)
                {
                    count = count + 1;
                    pxb_min = pt.x;
                    pyb_min = pt.y;
                }
                if (pxb_min < pt.x)
                {
                    pxb_max = pt.x;
                }
            }
            // find red_circle
            else if (Color[2] >= 100 && Color[0] < 50 && Color[1] < 50)
            {
                if (count == 1)
                {
                    count = count + 1;
                    pxr_min = pt.x;
                    pyr_min = pt.y;
                }
                if (pxr_min < pt.x)
                {
                    pxr_max = pt.x;
                }
            }
            // find green_circle
            else if (Color[1] >= 100 && Color[0] < 50 && Color[2] < 50)
            {
                if (count == 2)
                {
                    count = count + 1;
                    pxg_min = pt.x;
                    pyg_min = pt.y;
                }
                if (pxg_min < pt.x)
                {
                    pxg_max = pt.x;
                }
            }
            // find yellow_circle
            else if (Color[0] < 20 && Color[1] >= 100 && Color[2] >= 100)
            {
                if (count == 3)
                {
                    count = count + 1;
                    pxy_min = pt.x;
                    pyy_min = pt.y;
                }
                if (pxy_min < pt.x)
                {
                    pxy_max = pt.x;
                }
            }
            // find pink_circle
            if (Color[0] >= 200 && Color[1] < 150 && Color[2] >= 200)
            {
                if (count == 4)
                {
                    count = count + 1;
                    pxp_min = pt.x;
                    pyp_min = pt.y;
                }
                if (pxp_min < pt.x)
                {
                    pxp_max = pt.x;
                }
            }
        }
    }

    yb_tmp = round((pxb_min + pxb_max) / 2);
    xb_tmp = (pyb_min);

    yr_tmp = round((pxr_min + pxr_max) / 2);
    xr_tmp = (pyr_min);

    yg_tmp = round((pxg_min + pxg_max) / 2);
    xg_tmp = (pyg_min);

    yy_tmp = round((pxy_min + pxy_max) / 2);
    xy_tmp = (pyy_min);

    yp_tmp = round((pxp_min + pxp_max) / 2);
    xp_tmp = (pyp_min);

    //line(#img, Point(start_x,start_y), Point(end_x,end_y), line_color, line_fontsize)
    line(img, Point(xb_tmp, yb_tmp), Point(xr_tmp, yr_tmp), Scalar(0, 0, 0), 1);

    line(img, Point(xr_tmp, yr_tmp), Point(xg_tmp, yg_tmp), Scalar(0, 0, 0), 1);

    line(img, Point(xg_tmp, yg_tmp), Point(xy_tmp, yy_tmp), Scalar(0, 0, 0), 1);

    line(img, Point(xy_tmp, yy_tmp), Point(xp_tmp, yp_tmp), Scalar(0, 0, 0), 1);

    imshow("output", img);

    waitKey(0);

    return 0;
}