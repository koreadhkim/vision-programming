#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
    VideoCapture capture;
    capture.open("./assets/car.mp4");
    Mat accImage = imread("./assets/carbkg.jpg", 0);
    CV_Assert(capture.isOpened() || accImage.data);

    double frame_rate = capture.get(CV_CAP_PROP_FPS);
    int delay = 1000 / frame_rate;
    int nofrm = 0;
    int width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
    Mat diffImage(height, width, CV_32F);
    Mat grayImage(height, width, CV_8U);
    Mat maskImage(height, width, CV_8U);
    // accImage.convertTo(accImage, CV_32F);

    // 10% 반영. / alpth == 0.01 => 0.1% 반영
    double alpha = 0.01;
    int nFrameCount = 0;
    Mat frame;

    while (capture.read(frame))
    {
        printf("nFrameCount=%d\n", nFrameCount);
        cvtColor(frame, grayImage, CV_BGR2GRAY);
        grayImage.convertTo(grayImage, CV_32F);
        accImage.convertTo(accImage, CV_32F);
        absdiff(grayImage, accImage, diffImage);
        threshold(diffImage, maskImage, 20, 255, CV_THRESH_BINARY);
        // (x*alpha, y*(1-alpha))
        accumulateWeighted(grayImage, accImage, alpha);
        grayImage.convertTo(grayImage, CV_8U);
        accImage.convertTo(accImage, CV_8U);
        imshow("grayImage", grayImage);
        imshow("accImage", accImage);
        imshow("maskImage", maskImage);

        char chKey = waitKey(5);
        if (chKey == 27) // Esc
            break;
        nFrameCount++;
    }
    return 0;
}