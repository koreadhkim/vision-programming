#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    VideoCapture video;

    video.open("./assets/pipoball.avi");
    CV_Assert(video.isOpened());

    double frame_rate = video.get(CV_CAP_PROP_FPS);
    int delay = 1000 / frame_rate;

    Mat frame;

    while (video.read(frame))
    {

        int pxcnt = 0;

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
                    dstimg.at<Vec3b>(pt.y, pt.x) = Vec3b(0, 0, 255);
                    pxcnt++;
                    inball.x += pt.x;
                    inball.y += pt.y;
                }
                else
                {
                    dstimg.at<Vec3b>(pt.y, pt.x) = Vec3b(255, 255, 255);
                }
            }
        }
        if (pxcnt == 0)
            pxcnt = 1;

        inball.x /= pxcnt;
        inball.y /= pxcnt;

        // Point nofrm;
        // Point accpt[] ={};
        // float accptY[] = {0.};

        int radius = (int)(sqrt((double)pxcnt / 3.14));
        circle(dstimg, inball, radius, CV_RGB(255, 0, 0), 2);
        rectangle(dstimg, Point(inball.x - radius, inball.y - radius), Point(inball.x + radius, inball.y + radius), CV_RGB(0, 0, 0), 2);
        


        // // vector<Point> pointList;
        // // pointList.push_back(inball);

        // //cout << pointList.size() << endl;
        // // if(pointList.size() >=100){
        // for (int n = 0; n < 30; n++)

        //     {   vector<Point> pointList;
        //         pointList.push_back(inball);
        //         Point myPoint_01 = pointList[n];
                
        //         line(dstimg,inball,myPoint_01,CV_RGB(0,0,255),2);
        //         // cout << pointList <<endl;

        //     }
        
        // cout << newpoint <<endl;

        imshow("result_video", dstimg);
        // imshow("origin_video",frame);
    }
}
