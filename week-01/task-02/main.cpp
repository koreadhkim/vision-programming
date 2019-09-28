#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{

	Mat image;

	image = imread("./assets/input.jpg", IMREAD_COLOR);

	if (image.empty())
	{
		cout << "Image_Error" << endl;
	}

	cout << "ROWS: " << image.rows << endl;
	cout << "COLS: " << image.cols << endl;
	Point pt;

	for (pt.y = 0; pt.y < image.rows; pt.y++)
	{
		for (pt.x = 0; pt.x < image.cols; pt.x++)
		{

			//Red_circle -> Blue_circle
			if (image.at<Vec3b>(pt.y, pt.x)[0] < 150 && image.at<Vec3b>(pt.y, pt.x)[1] < 150 && image.at<Vec3b>(pt.y, pt.x)[2] > 200)
				image.at<Vec3b>(pt.y, pt.x) = Vec3b(255, 0, 0);

			//Yellow_rhombus-> Red_rhombus
			if (image.at<Vec3b>(pt.y, pt.x)[0] < 150 && image.at<Vec3b>(pt.y, pt.x)[1] > 200 && image.at<Vec3b>(pt.y, pt.x)[2] > 200)
				image.at<Vec3b>(pt.y, pt.x) = Vec3b(0, 0, 255);

			//Green_triangle -> Yellow_triangle
			if (image.at<Vec3b>(pt.y, pt.x)[0] < 150 && image.at<Vec3b>(pt.y, pt.x)[1] > 200 && image.at<Vec3b>(pt.y, pt.x)[2] < 150)
				image.at<Vec3b>(pt.y, pt.x) = Vec3b(0, 255, 255);

			//Blue_rectangle -> Green_rectangle
			if (image.at<Vec3b>(pt.y, pt.x)[0] > 120 && image.at<Vec3b>(pt.y, pt.x)[0] != 255 && image.at<Vec3b>(pt.y, pt.x)[1] < 150 && image.at<Vec3b>(pt.y, pt.x)[2] < 150)
				image.at<Vec3b>(pt.y, pt.x) = Vec3b(0, 255, 0);
		}
	}

	imshow("output image", image);
	imwrite("./assets/out.jpg",image);
	waitKey(0);

	return 0;
}
