#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
    VideoCapture video;
    video.open("./assets/ball.avi");
    Mat bkgImage = imread("./assets/ballBkg.jpg", 0);
    CV_Assert(video.isOpened() || bkgImage.data);

    double frame_rate = video.get(CV_CAP_PROP_FPS);
    int delay = 1000 / frame_rate;
    int nofrm = 0;
    int width = video.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = video.get(CV_CAP_PROP_FRAME_HEIGHT);

    // 음수가 나올 수 있기 떄문에 32S 로 define
    Mat diffImage(height, width, CV_32S);
    Mat grayImage(height, width, CV_8U);

    int nFrameCount = 0;
    Mat frame;
    
    while (video.read(frame))
    {
        printf("nFrameCount=%d\n", nFrameCount);
        cvtColor(frame, grayImage, CV_BGR2GRAY);
        absdiff(grayImage, bkgImage, diffImage);
        
        imshow("diffImage", diffImage);
        char chKey = waitKey(33);
        if (chKey == 27) // Esc
            break;
        nFrameCount++;
    }
    return 0;
}