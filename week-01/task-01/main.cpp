#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	uchar data[] = { 100, 150, 150, 150, 150, 100, 100, 100, 100, 100, 100, 100,
		100, 100, 150, 150, 150, 100, 100, 100, 100, 100, 100, 100,
		100, 100, 250, 150, 150, 100, 100, 100, 100, 100, 100, 100,
		100, 100, 250, 250, 150, 100, 100, 100, 100, 100, 100, 100,
		100, 100, 250, 250, 250, 200, 120, 120, 120, 100, 100, 100,
		100, 100, 100, 100, 100, 200, 200, 120, 120, 100, 100, 100,
		100, 100, 100, 100, 100, 200, 200, 200, 120, 100, 100, 100,
		100, 100, 100, 100, 100, 100, 100, 100, 120, 120, 100, 100,
		100, 100, 100, 100, 100, 100, 100, 100, 120, 120, 120, 100,
		100, 100, 100, 100, 100, 100, 100, 100, 100, 120, 120, 120, };

	Mat example(10, 12, CV_8U, data);
	Point pt;
	cout << "data = " << example << endl;
    imshow("input", example);

	for (pt.x = 0; pt.x < example.rows; pt.x++)
	{
		for (pt.y = 0; pt.y < example.cols; pt.y++)
		{
			uchar val = example.at<uchar>(pt.x, pt.y);

			if (val == 250)
				example.at<uchar>(pt.x, pt.y) = 0;
			else if (val == 100)
				example.at<uchar>(pt.x, pt.y) = 255;
			else if (val == 120)
				example.at<uchar>(pt.x, pt.y) = 200;
			else if (val == 150)
				example.at<uchar>(pt.x, pt.y) = 100;
		}
	}

	cout << "output = " << example << endl;
	cout << "example.depth = " << example.depth() << endl;
	cout << "example.channels = " << example.channels() << endl;

	
	waitKey(0);

	return 0;
}