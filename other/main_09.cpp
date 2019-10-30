#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{

    Mat ch_01(3, 4, CV_8U, Scalar(10));
    Mat ch_02(3, 4, CV_8U, Scalar(20));
    Mat ch_03(3, 4, CV_8U, Scalar(30));

    Mat bgr_arr[] = {ch_01, ch_02, ch_03};
    Mat bgr;

    // Channel Check
    cout << "ch_01" << endl
         << ch_01 << endl
         << endl;
    cout << "ch_02" << endl
         << ch_02 << endl
         << endl;
    cout << "ch_03" << endl
         << ch_03 << endl
         << endl;

    // merge ch_01~ch_03
    merge(bgr_arr, 3, bgr);

    // merge check
    cout << "BGR" << endl
         << bgr << endl
         << endl;

    vector<Mat> bgr_vec;

    // split bgr
    split(bgr, bgr_vec);

    // split channel check
    cout << "split_ch_01" << endl
         << bgr_vec[0] << endl
         << endl;
    cout << "split_ch_02" << endl
         << bgr_vec[1] << endl
         << endl;
    cout << "split_ch_03" << endl
         << bgr_vec[2] << endl
         << endl;

    waitKey(0);
    return 0;
}