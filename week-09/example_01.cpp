#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    VideoCapture video;

    // read video
    video.open("./assets/ball.avi");

    // read video == false => error
    CV_Assert(video.isOpened());

    // frame define
    double frame_rate = video.get(CV_CAP_PROP_FPS);
    int delay = 1000 / frame_rate;
    int nofrm = 0;
    int width = video.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = video.get(CV_CAP_PROP_FRAME_HEIGHT);

    Mat sumImage(height, width, CV_32F);
    Mat grayImage(height, width, CV_8U);
    Mat frame;

    sumImage.setTo(0);
    int nFrameCount = 0;

    while (video.read(frame))
    {
        printf("nFrameCount=%d\n", nFrameCount);
        cvtColor(frame, grayImage, CV_BGR2GRAY);
        // (grayImage + sumImage) ++
        accumulate(grayImage, sumImage);

        imshow("grayImage", grayImage);
        char chKey = waitKey(33);
        if (chKey == 27) // Esc
            break;
        nFrameCount++;
    }
    // sumImage = 467 frame을 다 더한 것 / 467 frame
    sumImage /= (float)nFrameCount;
    sumImage.setTo(CV_8U);
    imshow("sumImage", sumImage);
    imwrite("ballavg.jpg", sumImage);

    return 0;
}
