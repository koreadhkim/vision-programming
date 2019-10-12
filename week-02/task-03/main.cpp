#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int pxr_max = 0, pxr_min = 0, pyr_max = 0;
int xr_tmp = 0, yr_tmp = 0;

int pxg_max = 0, pxg_min = 0, pyg_min = 0;
int xg_tmp = 0, yg_tmp = 0;

int pxy_max = 0, pxy_min = 0, pyy_max = 0;
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

            // find red_circle_edge
            if (Color[2] >= 100 && Color[0] < 50 && Color[1] < 50)
            {
                if (count == 0)
                {
                    count = count + 1;
                    pxr_min = pt.x;
                }

                if (pyr_max < pt.y)
                {
                    pyr_max = pt.y;
                }
            }
            // find green_circle_edge
            else if (Color[1] >= 100 && Color[0] < 50 && Color[2] < 50)
            {
                if (count == 1)
                {
                    count = count + 1;
                    pxg_min = pt.x;
                    pyg_min = pt.y;
                }

                if (pt.y < pyg_min)
                    pyg_min = pt.y;

                if (pxg_min < pt.x)
                {
                    pxg_max = pt.x;
                }
            }
            // find yellow_circle_edge
            else if (Color[0] < 20 && Color[1] >= 100 && Color[2] >= 100)
            {
                if (count == 2)
                {
                    count = count + 1;
                    pxy_min = pt.x;
                }

                if (pyy_max < pt.y)
                {
                    pyy_max = pt.y;
                }
            }
            // find pink_circle_edge
            if (Color[0] >= 200 && Color[1] < 150 && Color[2] >= 200)
            {
                if (count == 3)
                {
                    count = count + 1;
                    pxp_min = pt.x;
                    pyp_min = pt.y;
                }

                if (pt.y < pyp_min)
                    pyp_min = pt.y;

                if (pxp_min < pt.x)
                {
                    pxp_max = pt.x;
                }
            }
        }
    }

    rectangle(img, Point(pyr_max, pxr_min), Point(pyg_min, pxg_max), Scalar(0, 0, 0), 1);

    rectangle(img, Point(pyy_max, pxy_min), Point(pyp_min, pxp_max), Scalar(0, 0, 0), 1);

    imshow("output", img);

    waitKey(0);

    return 0;
}