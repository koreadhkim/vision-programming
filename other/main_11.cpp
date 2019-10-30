#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat m1(3, 6, CV_8U, Scalar(10));
    Mat m2(3, 6, CV_8U, Scalar(50));

    Mat m_add_01, m_add_02, m_sub, m_div_01, m_div_02;

    Mat mask(m1.size(), CV_8U, Scalar(0));
    // check m1,m2
    cout << "m1" << endl
         << m1 << endl
         << endl;
    cout << "m2" << endl
         << m2 << endl
         << endl;

    Rect rect(Point(3, 0), Size(3, 3));
    // Calculate only if nonzero
    mask(rect).setTo(1);
    cout << "mask" << endl
         << mask << endl
         << endl;

    // add for m1,m2 and check
    add(m1, m2, m_add_01);
    cout << "m_add_01" << endl
         << m_add_01 << endl
         << endl;

    // add for m1,m2 (mask) and check
    add(m1, m2, m_add_02, mask);
    cout << "m_add_02" << endl
         << m_add_02 << endl
         << endl;

    waitKey(0);
    return 0;
}