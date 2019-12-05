#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void respownCenter(Point *c)
{
    for (int i = 1; i < 30; i++)
    {
        c[i - 1] = c[i];
    }
}

int main()
{
    VideoCapture video_01, video_02;
    video_01.open("./assets/pipoball.avi");
    video_02.open("./assets/GLOBAL.mp4");
    CV_Assert(video_01.isOpened() || video_02.isOpened());

    double frame_rate = video_01.get(CV_CAP_PROP_FPS);
    int delay = 1000 / frame_rate;

    Mat frame_01, frame_02;
    int nofrm = 0;
    Point2f srcQuad[4], dstQuad[4];

    while (true)
    {
        if (!video_01.read(frame_01))
            break;
        if (!video_02.read(frame_02))
        {
            video_02.open("globe.avi");
            video_02.read(frame_02);
        }

        if (waitKey(delay) >= 0)
            break;

        float pxcnt = 0.;
        Point pt;
        Point inball(0, 0);

        Mat dstimg(frame_01.size(), CV_8UC3);

        for (pt.y = 0; pt.y < frame_01.rows; pt.y++)
        {
            for (pt.x = 0; pt.x < frame_01.cols; pt.x++)
            {
                Vec3b val = frame_01.at<Vec3b>(pt.y, pt.x);

                float luma = 0.11 * (float)val[0] + 0.59 * (float)val[1] + 0.3 * (float)val[2];

                if (val[2] > 0.5 * luma && val[2] > 1.5 * val[0] && val[2] > 1.5 * val[1] && luma > 50.)
                {
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

        dstQuad[0] = Point(inball.x - radius, inball.y - radius);
        dstQuad[1] = Point(inball.x + radius, inball.y - radius);
        dstQuad[2] = Point(inball.x - radius, inball.y + radius);
        dstQuad[3] = Point(inball.x + radius, inball.y + radius);

        srcQuad[0] = Point(0, 0);
        srcQuad[1] = Point(frame_02.cols, 0);
        srcQuad[2] = Point(0, frame_02.rows);
        srcQuad[3] = Point(frame_02.cols, frame_02.rows);

        Mat matrix = getPerspectiveTransform(srcQuad, dstQuad);
        warpPerspective(frame_02, dstimg, matrix, frame_01.size());

        imshow("result", dstimg);
        imshow("global", frame_02);
        imshow("pipball", frame_01);
    }

    return 0;
}
