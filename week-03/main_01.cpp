#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    //road_images
    Mat img_01 = imread("./assets/input_03.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    Mat img_02 = imread("./assets/input_03.jpg", CV_LOAD_IMAGE_COLOR);
    Point pt;

    CV_Assert(img_01.data);

    // window_size
    int w;

    // maxvalue_01,_02
    float maxvalue_01 = 0.0;
    float maxvalue_02 = 0.0;

    // width_01,_02
    int width_01 = 0, width_02 = 0;

    // pos_01,_02
    Point maxpos_01(0, 0), maxpos_02(0, 0);

    //search for window into img_01
    for (w = 20; w <= 30; w++)
    {
        for (pt.y = 0; pt.y < img_01.rows - w; pt.y++)
        {
            for (pt.x = 0; pt.x < img_01.cols - 3 * w; pt.x++)
            {
                Rect ract_01(pt.x, pt.y, w, w);
                Rect ract_02(pt.x + w, pt.y, w, w);
                Rect ract_03(pt.x + 2 * w, pt.y, w, w);

                Mat_<uchar> matrix_01(w, w);
                matrix_01 = (Mat)img_01(ract_01);
                // cout << "matrix_01_size" << matrix_01.size() << endl;
                // cout << "matrix_01" << matrix_01 << endl;

                Mat_<uchar> matrix_02(w, w);
                matrix_02 = (Mat)img_01(ract_02);
                // cout << "matrix_02_size" << matrix_02.size() << endl;
                // cout << "matrix_02" << matrix_02 << endl;

                Mat_<uchar> matrix_03(w, w);
                matrix_03 = (Mat)img_01(ract_03);
                // cout << "matrix_03_size" << matrix_03.size() << endl;
                // cout << "matrix_03" << matrix_03 << endl;

                Scalar val_01 = mean(matrix_01);
                Scalar val_02 = mean(255 - matrix_02);
                Scalar val_03 = mean(matrix_03);

                // matrix_average
                float matrix_avg = (((val_01[0] + val_02[0] + val_03[0]) / 3) / 255);
                // cout << matrix_avg<<endl;

                // if update for maxvalue_01,_02 and maxpos_01,_02
                if ((matrix_avg > maxvalue_01 || matrix_avg > maxvalue_02) && (abs(pt.x - maxpos_01.x) > 14) && (abs(pt.x - maxpos_02.x) > 14))
                {
                    if (maxvalue_02 > maxvalue_01)
                    {
                        cout << "update_maxvalue_01" << endl;
                        maxvalue_01 = matrix_avg;
                        width_01 = w;
                        maxpos_01 = Point(pt.x, pt.y);
                    }
                    else
                    {
                        cout << "update_maxvalue_02" << endl;
                        maxvalue_02 = matrix_avg;
                        width_02 = w;
                        maxpos_02 = Point(pt.x, pt.y);
                    }
                }
            }
        }
    }

    cout << width_01 << endl;
    cout << maxpos_01 << endl
         << endl
         << endl;
    cout << width_02 << endl;
    cout << maxpos_02 << endl
         << endl
         << endl;
    rectangle(img_02, Point(maxpos_01.x - 5, maxpos_01.y - 5), Point(maxpos_01.x + (w * 3) + 5, maxpos_01.y + w + 5), Scalar(0, 0, 255), 1);
    rectangle(img_02, Point(maxpos_02.x - 5, maxpos_02.y - 5), Point(maxpos_02.x + (w * 3) + 5, maxpos_02.y + w + 5), Scalar(255, 0, 0), 1);

    imshow("search_eye", img_02);
    waitKey(0);
    return 0;
}
