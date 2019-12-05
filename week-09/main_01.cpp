#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;


int main()
{
    VideoCapture video;
    video.open("./assets/car.mp4");
    Mat bkgimg = imread("./assets/carbkg.jpg", 0);
    CV_Assert(video.isOpened() || bkgimg.data);

    double frame_rate = video.get(CV_CAP_PROP_FPS);
    int delay = 1000 / frame_rate;
    int nofrm = 0;
    int width = video.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = video.get(CV_CAP_PROP_FRAME_HEIGHT);

    Mat diffImage(height, width, CV_32F);
    Mat grayImage(height, width, CV_8U);
    Mat maskImage(height, width, CV_8U);
    //accImage.convertTo(accImage, CV_32F);

    double alpha = 0.1;
    int nFrameCount = 0;
    Mat frame;
    maskImage.setTo(0);

    while (video.read(frame))
    {
        printf("nFrameCount=%d\n", nFrameCount);
        cvtColor(frame, grayImage, CV_BGR2GRAY);

        grayImage.convertTo(grayImage, CV_32F);
        bkgimg.convertTo(bkgimg, CV_32F);

        cvRunningAvg(grayImage,bkgimg)

        // // x - y = diffImage
        // absdiff(grayImage, accImage, diffImage);

        // // 20 >  => 255 (INV)
        // threshold(diffImage, maskImage, 20, 255,
        //           CV_THRESH_BINARY_INV);

        // maskImage.convertTo(maskImage, CV_8U);

        // // maskImage는 평균에 반영을 안한다.
        // accumulateWeighted(grayImage, accImage, alpha,
        //                    maskImage);

        // grayImage.convertTo(grayImage, CV_8U);
        // accImage.convertTo(accImage, CV_8U);

        imshow("grayImage", grayImage);
        imshow("maskImage", maskImage);
        imshow("accImage", accImage);

        char chKey = waitKey(5);

        if (chKey == 27) // Esc
            break;
        nFrameCount++;
    }

    return 0;
}

// int main()
// {
//     VideoCapture video;

//     // read video
//     video.open("./assets/car.mp4");

//     // read video == false => error
//     CV_Assert(video.isOpened());

//     // frame define
//     double frame_rate = video.get(CV_CAP_PROP_FPS);
//     int delay = 1000 / frame_rate;
//     int nofrm = 0;
//     int width = video.get(CV_CAP_PROP_FRAME_WIDTH);
//     int height = video.get(CV_CAP_PROP_FRAME_HEIGHT);

//     Mat sumImage(height, width, CV_32F);
//     Mat grayImage(height, width, CV_8U);
//     Mat frame;

//     sumImage.setTo(0);
//     int nFrameCount = 0;

//     while (video.read(frame))
//     {
//         printf("nFrameCount=%d\n", nFrameCount);
//         cvtColor(frame, grayImage, CV_BGR2GRAY);
//         // (grayImage + sumImage) ++
//         accumulate(grayImage, sumImage);

//         imshow("grayImage", grayImage);
//         char chKey = waitKey(33);
//         if (chKey == 27) // Esc
//             break;
//         nFrameCount++;
//     }
//     // sumImage = 467 frame을 다 더한 것 / 467 frame
//     sumImage /= (float)nFrameCount;
//     sumImage.setTo(CV_8U);
//     imshow("sumImage", sumImage);
//     imwrite("./assets/carbkg.jpg", grayImage);

//     return 0;
// }
