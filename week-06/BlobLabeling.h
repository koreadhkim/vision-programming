#pragma once
#pragma once

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define _DEF_MAX_LABEL 10000
#define _DEF_MAX_BLOBS 1000000

struct BlobPoint
{
	Point Left;
	Point Right;
	Point Top;
	Point Bottom;
};

struct Visited
{
	bool bVisitedFlag;
	int n_Obj;
	Point ptReturnPoint;
};

class CBlobLabeling
{
public:
	CBlobLabeling(void);
	~CBlobLabeling(void);

public:
	Mat m_Image;
	Mat m_GrayImg;
	Mat m_colorImg;
	int m_nThreshold;
	Visited *m_vPoint;
	BlobPoint *m_vBPoint;
	BlobPoint *m_vBTPoint;
	int m_nBlobs;
	CvRect *m_recBlobs;

	int m_nBlobCount[_DEF_MAX_LABEL];
	int **m_sortLabel;

	double *m_nLabelPixSum;
	double *m_fMean;
	double *m_fStd;
	Scalar res;
	double *m_nLabelPixSum_X;
	double *m_nLabelPixSum_Y;
	double *m_fcog_1;
	double *m_fcog_2;

public:
	void SetParam(Mat grayImg, Mat image, Mat dstImg, int nThreshold);

	void DoLabeling();

	void ReleaseMem();

	void InsertionSort(int **, int);

private:
	int Labeling(Mat image, int nThreshold);

	void InitvPoint(int nWidth, int nHeight);
	void DeletevPoint();

	void DetectLabelingRegion(int nLabelNumber, int *DataBuf, int nWidth, int nHeight);
	Scalar get_color(int i);

	int _Labeling(int *labelBuf, int *oriBuf, int nWidth, int nHeight, int nThreshold);

	int __NRFIndNeighbor(int *DataBuf, int nWidth, int nHeight, int nPosX, int nPosY, int *StartX, int *StartY, int *EndX, int *EndY);
	int __Area(int *DataBuf, int StartX, int StartY, int EndX, int EndY, int nWidth, int nLevel);
};