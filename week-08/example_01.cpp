#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void respownCenter(Point *c)
{
    for (int i = 1; i < 30; i++)
    {
        c[i - 1] = c[i];
    }
}

int main()
{
    VideoCapture video;
    video.open("./assets/pipoball.avi");
    CV_Assert(video.isOpened());

    double frame_rate = video.get(CV_CAP_PROP_FPS);
    int delay = 1000 / frame_rate;

    Mat frame;

    Point center[30];
    int centerIndex = 0;

    while (video.read(frame))
    {
        float pxcnt = 0.;
        Point pt;
        Point inball(0, 0);

        if (waitKey(delay) >= 0)
            break;

        Mat dstimg(frame.size(), CV_8UC3);

        for (pt.y = 0; pt.y < frame.rows; pt.y++)
        {
            for (pt.x = 0; pt.x < frame.cols; pt.x++)
            {
                Vec3b val = frame.at<Vec3b>(pt.y, pt.x);

                float luma = 0.11 * (float)val[0] + 0.59 * (float)val[1] + 0.3 * (float)val[2];

                if (val[2] > 0.5 * luma && val[2] > 1.5 * val[0] && val[2] > 1.5 * val[1] && luma > 50.)
                {
                    dstimg.at<Vec3b>(pt.y, pt.x) = Vec3b(0, 255, 255);
                    pxcnt++;
                    inball.x += pt.x;
                    inball.y += pt.y;
                }
                else
                    dstimg.at<Vec3b>(pt.y, pt.x) = Vec3b(0, 0, 0);
            }
        }
        if (pxcnt == 0)
            pxcnt = 1;
        inball.x /= pxcnt;
        inball.y /= pxcnt;

        int radius = (int)(sqrt((double)pxcnt / 3.14));
        circle(dstimg, inball, radius, CV_RGB(255, 0, 0), 2);
        rectangle(dstimg, Point(inball.x - radius, inball.y - radius), Point(inball.x + radius, inball.y + radius), CV_RGB(255, 255, 255), 2);

        putText(dstimg, "targets", Point(inball.x - 4, inball.y + 4), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0), 1);

        if (centerIndex < 30)
        {
            center[centerIndex] = inball;
            centerIndex++;
        }
        else
        {
            respownCenter(center);
            center[29] = inball;
        }

        if (centerIndex > 2)
        {
            for (int i = 1; i < centerIndex - 1; i++)
            {
                line(dstimg, center[i - 1], center[i], Scalar(0, 255, 0), 2);
            }
        }

        imshow("result", dstimg);
        imshow("video_file_read", frame);
    }

    return 0;
}
