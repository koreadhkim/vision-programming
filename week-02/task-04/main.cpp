#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int pxr_max = 0, pxr_min = 0, pyr_min = 0;
int xr_tmp = 0, yr_tmp = 0;

int pxg_max = 0, pxg_min = 0, pyg_min = 0;
int xg_tmp = 0, yg_tmp = 0;

int pxy_max = 0, pxy_min = 0, pyy_min = 0;
int xy_tmp = 0, yy_tmp = 0;

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

            // find red_circle
            if (Color[2] >= 100 && Color[0] < 50 && Color[1] < 50)
            {
                if (count == 0)
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
                if (count == 1)
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
                if (count == 2)
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
        }
    }

    // The center coordinate of each circle
    yr_tmp = round((pxr_min + pxr_max) / 2);
    xr_tmp = (pyr_min);

    yg_tmp = round((pxg_min + pxg_max) / 2);
    xg_tmp = (pyg_min);

    yy_tmp = round((pxy_min + pxy_max) / 2);
    xy_tmp = (pyy_min);

    // The radius of each circle * x
    int Sun = (pxr_max - yr_tmp) * 5;
    int Earth = (pxg_max - yg_tmp) * 3;
    int Moon = (pxy_max - yy_tmp) * 1.2;

    //circle(#img, Point(start_x,start_y), radius, line_color, line_fontsize)
    circle(img, Point(xr_tmp, yr_tmp), Sun, Scalar(0, 0, 0), 1);
    circle(img, Point(xg_tmp, yg_tmp), Earth, Scalar(0, 0, 0), 1);
    circle(img, Point(xy_tmp, yy_tmp), Moon, Scalar(0, 0, 0), 1);

    //Letter in the circle
    int font = FONT_HERSHEY_COMPLEX;
    putText(img, "Sun", Point(xr_tmp - Sun, yr_tmp - Sun), font, 0.5, Scalar(0, 0, 0));
    putText(img, "Earth", Point(xg_tmp - Earth, yg_tmp - Earth), font, 0.5, Scalar(0, 0, 0));
    putText(img, "Moon", Point(xy_tmp - Moon, yy_tmp - Moon), font, 0.5, Scalar(0, 0, 0));

    imshow("output", img);

    waitKey(0);

    return 0;
}