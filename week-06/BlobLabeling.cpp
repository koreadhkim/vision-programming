//#include "StdAfx.h"

// refer to Professor Jin-soo Kim, if you have any question.
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "BlobLabeling.h"

CBlobLabeling::CBlobLabeling(void)
{
	m_nThreshold = 0;
	m_nBlobs = _DEF_MAX_BLOBS;
	long m_Image = NULL;
	m_recBlobs = NULL; //레이블링된 인덱스 저장
	long m_GrayImg = NULL;
	long m_colorImg = NULL;

}

CBlobLabeling::~CBlobLabeling(void)
{
	if (m_recBlobs != NULL)
	{
		delete m_recBlobs;
		m_recBlobs = NULL;//소멸
	}
}

void CBlobLabeling::SetParam(Mat grayImg, Mat image, Mat dstImg, int nThreshold)
{

	if (m_recBlobs != NULL)
	{
		delete m_recBlobs;//기존 레이블링 인덱스 제거

		m_recBlobs = NULL;//초기화
		m_nBlobs = _DEF_MAX_BLOBS;

	}

// 콜함수의 것 복제
	m_GrayImg = grayImg;
	m_Image = image;	
	m_colorImg = dstImg;

	m_nThreshold = nThreshold;
}

void CBlobLabeling::DoLabeling()
{
	m_nBlobs = Labeling(m_Image, m_nThreshold);//첫번째 인자의 이미지로 라벨링
	/*
	if (m_nBlobs >= 100) {
		m_nBlobs = 100;
	}
	*/

}

int CBlobLabeling::Labeling(Mat image, int nThreshold)
{
	if (image.channels() != 1) {
		cout << "labelling data must be 1-channel!!!" << endl;
		return 0;
	}

	int nNumber;
	int i, j;

	int nWidth = image.cols;
	int nHeight = image.rows;

	int* tmpBuf = new int[nWidth * nHeight]; // label number buf
	int* oriBuf = new int[nWidth * nHeight]; // ori value number buf

	for (j = 0; j<nHeight; j++) {
		uchar *ptr = (uchar *)image.data + j *image.step1();
		uchar *ptrOri = (uchar *)m_GrayImg.data + j *m_GrayImg.step1();
		for (i = 0; i<nWidth; i++) {
			tmpBuf[j*nWidth + i] = ptr[i];
			oriBuf[j*nWidth + i] = ptrOri[i];
		}
	}

	// 레이블링을 위한 포인트 초기화
	InitvPoint(nWidth, nHeight);

	// 레이블링
	nNumber = _Labeling(tmpBuf, oriBuf, nWidth, nHeight, nThreshold);

	if (nNumber != _DEF_MAX_BLOBS)		m_recBlobs = new CvRect[nNumber];

	//printf("nWidth=%d, nHeight=%d, nNumber=%d\n", nWidth, nHeight, nNumber);

	if (nNumber != 0)	DetectLabelingRegion(nNumber, tmpBuf, nWidth, nHeight);

	//삽입 정렬
	int si, sj, stemp;
	double mtemp, stdtemp, gxtemp, gytemp;
	for (si = 1; si <= nNumber; si++)
	{
		stemp = m_nBlobCount[si];
		mtemp = m_fMean[si - 1];
		stdtemp = m_fStd[si - 1];
		gxtemp = m_fcog_1[si - 1];
		gytemp = m_fcog_2[si - 1];
		m_vBTPoint[0].Left.x = m_vBPoint[si - 1].Left.x;
		m_vBTPoint[0].Left.y = m_vBPoint[si - 1].Left.y;
		m_vBTPoint[0].Right.x = m_vBPoint[si - 1].Right.x;
		m_vBTPoint[0].Right.y = m_vBPoint[si - 1].Right.y;
		m_vBTPoint[0].Top.x = m_vBPoint[si - 1].Top.x;
		m_vBTPoint[0].Top.y = m_vBPoint[si - 1].Top.y;
		m_vBTPoint[0].Bottom.x = m_vBPoint[si - 1].Bottom.x;
		m_vBTPoint[0].Bottom.y = m_vBPoint[si - 1].Bottom.y;

		//printf("m_vBTPoint[0].Top.x=%d, m_vBTPoint[0].Top.y=%d\n", m_vBTPoint[0].Top.x, m_vBTPoint[0].Top.y);

		for (sj = si - 1; sj >= 0 && m_nBlobCount[sj] < stemp; sj--) {
			m_nBlobCount[sj + 1] = m_nBlobCount[sj];
			m_fMean[sj] = m_fMean[sj - 1];
			m_fStd[sj] = m_fStd[sj - 1];
			m_fcog_1[sj] = m_fcog_1[sj - 1];
			m_fcog_2[sj] = m_fcog_2[sj - 1];
			m_vBPoint[sj].Left.x = m_vBPoint[sj - 1].Left.x;
			m_vBPoint[sj].Left.y = m_vBPoint[sj - 1].Left.y;
			m_vBPoint[sj].Right.x = m_vBPoint[sj - 1].Right.x;
			m_vBPoint[sj].Right.y = m_vBPoint[sj - 1].Right.y;
			m_vBPoint[sj].Top.x = m_vBPoint[sj - 1].Top.x;
			m_vBPoint[sj].Top.y = m_vBPoint[sj - 1].Top.y;
			m_vBPoint[sj].Bottom.x = m_vBPoint[sj - 1].Bottom.x;
			m_vBPoint[sj].Bottom.y = m_vBPoint[sj - 1].Bottom.y;

		}

		m_nBlobCount[sj + 1] = stemp;
		m_fMean[sj] = mtemp;
		m_fStd[sj] = stdtemp;
		m_fcog_1[sj] = gxtemp;
		m_fcog_2[sj] = gytemp;
		m_vBPoint[sj].Left.x = m_vBTPoint[0].Left.x;
		m_vBPoint[sj].Left.y = m_vBTPoint[0].Left.y;
		m_vBPoint[sj].Right.x = m_vBTPoint[0].Right.x;
		m_vBPoint[sj].Right.y = m_vBTPoint[0].Right.y;
		m_vBPoint[sj].Top.x = m_vBTPoint[0].Top.x;
		m_vBPoint[sj].Top.y = m_vBTPoint[0].Top.y;
		m_vBPoint[sj].Bottom.x = m_vBTPoint[0].Bottom.x;
		m_vBPoint[sj].Bottom.y = m_vBTPoint[0].Bottom.y;
	}

	
	m_colorImg = Scalar(0);

	int labelNum = 0;
	for (j = 0; j<nHeight; j++) {
		uchar *ptr = (uchar *)m_colorImg.data + j *m_colorImg.step1();
		for (i = 0; i<nWidth; i++) {
			labelNum = m_vPoint[j * nWidth + i].n_Obj; // Blob Index

			// 레이블링 객체의 개수를 30개 까지만 하도록 설정한 것임
			if (labelNum >= 30 || labelNum == 0) continue;

			//res = get_color(m_nBlobCount[labelNum]); //라벨링 번호별로 1~30까지 색
			res = get_color(labelNum); //라벨링 번호별로 1~30까지 색
			//ptr[i * 3 + 0] = res.val[0];
			//ptr[i * 3 + 1] = res.val[1];
			//ptr[i * 3 + 2] = res.val[2];

			image.at<uchar>(j, i) = 255;
			m_colorImg.at<Vec3b>(j, i) = Vec3b(res.val[0], res.val[1], res.val[2]);

			//printf("labelNum=%d-->(%5.2lf, %5.2lf, %5.2lf)-->%d \n", 
			//	labelNum, res.val[2], res.val[1], res.val[0], m_nBlobCount[labelNum]);
		}
	}

	// 포인트 메모리 해제
	DeletevPoint();

	/*
	for (j = 0; j<nHeight; j++)
	{
		uchar *ptr = (uchar *)image.data + j *image.step1();
		for (i = 0; i<nWidth; i++)
		{
			ptr[i] = tmpBuf[j*nWidth + i];
		}
	}
	*/

	delete tmpBuf;
	delete oriBuf;
	return nNumber;
}

void CBlobLabeling::InsertionSort(int **ary, int max)
{
	int i, loc, nowNum, nowIdx;

	for (i = 1; i<max; i++)
	{
		loc = i - 1;

		nowNum = ary[i][1]; // 픽셀 갯수
		nowIdx = ary[i][0]; // 대응하는 인덱스

		while (loc >= 1 && nowNum>ary[loc][1])
		{
			ary[loc + 1][1] = ary[loc][1];
			ary[loc + 1][0] = ary[loc][0];
			loc--;
		}

		ary[loc + 1][1] = nowNum;
		ary[loc + 1][0] = nowIdx;
	}
}

void CBlobLabeling::ReleaseMem()
{
	DeletevPoint();
}

// m_vPoint 초기화 함수
void CBlobLabeling::InitvPoint(int nWidth, int nHeight)
{
	int nX, nY;

	m_vPoint = new Visited[nWidth * nHeight];

	for (nY = 0; nY < nHeight; nY++)
	{
		for (nX = 0; nX < nWidth; nX++)
		{
			m_vPoint[nY * nWidth + nX].n_Obj = 0;
			m_vPoint[nY * nWidth + nX].bVisitedFlag = false;
			m_vPoint[nY * nWidth + nX].ptReturnPoint.x = nX;
			m_vPoint[nY * nWidth + nX].ptReturnPoint.y = nY;
		}
	}

	//*m_nBlobCount = *new int[_DEF_MAX_LABEL]; // label number buf
	memset(m_nBlobCount, 0, _DEF_MAX_LABEL);
}

void CBlobLabeling::DeletevPoint()
{
	//for(int i=0; i<100; i++)
	//free(m_sortLabel[i]);

	delete m_vPoint;
	//delete m_vBPoint;
	//delete m_vBTPoint;
	//delete m_nBlobCount;
}

// Size가 nWidth이고 nHeight인 DataBuf에서 
// nThreshold보다 작은 영역을 제외한 나머지를 blob으로 획득
int CBlobLabeling::_Labeling(int *DataBuf, int *oriBuf, int nWidth, int nHeight, int nThreshold)
{
	int Index = 0, num = 0;
	int nX, nY, k, l;
	int StartX, StartY, EndX, EndY;

	// Find connected components
	for (nY = 0; nY < nHeight; nY++)
	{
		for (nX = 0; nX < nWidth; nX++)
		{
			if (DataBuf[nY * nWidth + nX] == 255 && !(m_vPoint[nY * nWidth + nX].bVisitedFlag))		// Is this a new component?, 255 == Object
			{
				//if(nX==405 && nY==164)
				//	int a = 10;
				num++;

				DataBuf[nY * nWidth + nX] = num;
				m_vPoint[nY * nWidth + nX].n_Obj = num;

				StartX = nX, StartY = nY, EndX = nX, EndY = nY;

				__NRFIndNeighbor(DataBuf, nWidth, nHeight, nX, nY, &StartX, &StartY, &EndX, &EndY);


				if (__Area(DataBuf, StartX, StartY, EndX, EndY, nWidth, num) < nThreshold)
				{
					for (k = StartY; k <= EndY; k++)
					{
						for (l = StartX; l <= EndX; l++)
						{
							if (DataBuf[k * nWidth + l] == num) {
								DataBuf[k * nWidth + l] = 0;
								m_vPoint[k * nWidth + l].n_Obj = 0;
							}
						}
					}
					--num;
					//if(num > 250)
					//	return  0;
				}
			}
		}
	}

	//
	m_fMean = (double *)malloc(sizeof(double) *num);
	m_fStd = (double *)malloc(sizeof(double) *num);
	m_nLabelPixSum = (double *)malloc(sizeof(double) *num);
	m_fcog_1 = (double *)malloc(sizeof(double) *num);
	m_fcog_2 = (double *)malloc(sizeof(double) *num);
	m_nLabelPixSum_X = (double *)malloc(sizeof(double) *num);
	m_nLabelPixSum_Y = (double *)malloc(sizeof(double) *num);
	memset(m_fMean, 0., sizeof(double)*num); memset(m_fStd, 0., sizeof(double)*num); memset(m_nLabelPixSum, 0., sizeof(double)*num);
	memset(m_fcog_1, 0., sizeof(double)*num); memset(m_fcog_2, 0., sizeof(double)*num);
	memset(m_nLabelPixSum_X, 0., sizeof(double)*num); memset(m_nLabelPixSum_Y, 0., sizeof(double)*num);

	for (nY = 0; nY < nHeight; nY++) {
		for (nX = 0; nX < nWidth; nX++)
			m_nBlobCount[DataBuf[nY*nWidth + nX]]++;
	}

	for (k = 1; k <= num; k++)
		for (nY = 0; nY < nHeight; nY++)
		{
			for (nX = 0; nX < nWidth; nX++)
			{
				if (DataBuf[nY*nWidth + nX] == k)
				{
					m_nLabelPixSum[k - 1] += oriBuf[nY*nWidth + nX];
				}
			}
		}


	for (k = 1; k <= num; k++)
		m_fMean[k - 1] = m_nLabelPixSum[k - 1] / m_nBlobCount[k]; // each label avg 원 내부



	double diff = 0.;
	double tmp = 0.;
	for (k = 1; k <= num; k++)	// get std
	{
		for (nY = 0; nY < nHeight; nY++)
		{
			for (nX = 0; nX < nWidth; nX++)
			{
				if (DataBuf[nY*nWidth + nX] == k)
				{
					diff = ((double)oriBuf[nY*nWidth + nX] - m_fMean[k - 1]);
					tmp = pow(diff, 2);
					m_fStd[k - 1] = tmp;
				}
			}
		}
	}

	for (k = 0; k<num; k++)
		m_fStd[k] = sqrt(m_fStd[k] / (double)m_nBlobCount[k + 1]);

	for (k = 1; k <= num; k++)  // center of gravity
		for (nY = 0; nY < nHeight; nY++)
		{
			for (nX = 0; nX < nWidth; nX++)
			{
				if (DataBuf[nY*nWidth + nX] == k)
				{
					m_nLabelPixSum_X[k - 1] += nX;
					m_nLabelPixSum_Y[k - 1] += nY;
				}
			}
		}

	for (k = 1; k <= num; k++)
	{
		m_fcog_1[k - 1] = m_nLabelPixSum_X[k - 1] / m_nBlobCount[k];
		m_fcog_2[k - 1] = m_nLabelPixSum_Y[k - 1] / m_nBlobCount[k];
	}
	// Max Length
	m_vBPoint = new BlobPoint[num];
	for (k = 0; k<num; k++)			m_vBPoint[k].Left.x = m_vBPoint[k].Left.y = m_vBPoint[k].Right.x = m_vBPoint[k].Right.y = m_vBPoint[k].Top.x = m_vBPoint[k].Top.y = m_vBPoint[k].Bottom.x = m_vBPoint[k].Bottom.y = 0;

	m_vBTPoint = new BlobPoint[1];

	m_vBTPoint[0].Left.x = m_vBTPoint[0].Left.y = m_vBTPoint[0].Right.x = m_vBTPoint[0].Right.y = m_vBTPoint[0].Top.x = m_vBTPoint[0].Top.y = m_vBTPoint[0].Bottom.x = m_vBTPoint[0].Bottom.y = 0;




	return num;
}

// Blob labeling해서 얻어진 결과의 rec을 얻어냄 
void CBlobLabeling::DetectLabelingRegion(int nLabelNumber, int *DataBuf, int nWidth, int nHeight)
{
	int nX, nY;
	int nLabelIndex;

	bool bFirstFlag[100000] = { 0, };

	for (nY = 1; nY < nHeight - 1; nY++)
	{
		for (nX = 1; nX < nWidth - 1; nX++)
		{
			nLabelIndex = DataBuf[nY * nWidth + nX];

			if (nLabelIndex != 0)	// Is this a new component?, 255 == Object
			{
				if (bFirstFlag[nLabelIndex] == false)
				{
					m_recBlobs[nLabelIndex - 1].x = nX;
					m_recBlobs[nLabelIndex - 1].y = nY;
					m_recBlobs[nLabelIndex - 1].width = 0;
					m_recBlobs[nLabelIndex - 1].height = 0;

					bFirstFlag[nLabelIndex] = true;

					//교정jsk 2014.9.12 (초기화로 삽입함)
					m_vBPoint[nLabelIndex - 1].Top.x = nX;
					m_vBPoint[nLabelIndex - 1].Left.x = nX;
					m_vBPoint[nLabelIndex - 1].Right.x = nX;
					m_vBPoint[nLabelIndex - 1].Bottom.x = nX;

					m_vBPoint[nLabelIndex - 1].Top.y = nY;
					m_vBPoint[nLabelIndex - 1].Left.y = nY;
					m_vBPoint[nLabelIndex - 1].Right.y = nY;
					m_vBPoint[nLabelIndex - 1].Bottom.y = nY;
				}
				else
				{

					int left = m_recBlobs[nLabelIndex - 1].x;
					int right = left + m_recBlobs[nLabelIndex - 1].width;
					int top = m_recBlobs[nLabelIndex - 1].y;
					int bottom = top + m_recBlobs[nLabelIndex - 1].height;

					/*
					if(nLabelNumber >= 3) {
					//printf("(nX=%d, nY=%d) : left=%d, right=%d, top=%d, bottom=%d\n", nX, nY, left, right, top, bottom);
					//printf("m_recBlobs[%d].x=%d, y=%d, width=%d, height=%d\n",nLabelIndex-1, left, top, right-left, bottom-top);
					printf("(nX=%d, nY=%d) top=%d,left=%d:TOP(%d,%d),LEFT(%d,%d),RIGHT(%d,%d),BOT(%d,%d)\n", nX, nY, top, left,
					m_vBPoint[nLabelIndex - 1].Top.x, m_vBPoint[nLabelIndex - 1].Top.y,
					m_vBPoint[nLabelIndex - 1].Left.x, m_vBPoint[nLabelIndex - 1].Left.y,
					m_vBPoint[nLabelIndex - 1].Right.x, m_vBPoint[nLabelIndex - 1].Right.y,
					m_vBPoint[nLabelIndex - 1].Bottom.x, m_vBPoint[nLabelIndex - 1].Bottom.y);
					}
					*/

					if (left >= nX)
					{
						left = nX;
						m_vBPoint[nLabelIndex - 1].Left.x = nX;
						m_vBPoint[nLabelIndex - 1].Left.y = nY;

						//printf("L==>left_nX=%d\n", nX);
					}

					if (right <= nX)
					{
						right = nX;
						m_vBPoint[nLabelIndex - 1].Right.x = nX;
						m_vBPoint[nLabelIndex - 1].Right.y = nY;

						//						//printf("right_nX=%d\n", nX);
					}

					if (top >= nY)
					{
						top = nY;
						m_vBPoint[nLabelIndex - 1].Top.x = nX;
						m_vBPoint[nLabelIndex - 1].Top.y = nY;

						//printf("T==>top_nY=%d\n", nY);
					}

					if (bottom <= nY)
					{
						bottom = nY;
						m_vBPoint[nLabelIndex - 1].Bottom.x = nX;
						m_vBPoint[nLabelIndex - 1].Bottom.y = nY;

						//						//printf("bot_nY=%d\n", nY);
					}

					m_recBlobs[nLabelIndex - 1].x = left;
					m_recBlobs[nLabelIndex - 1].y = top;
					m_recBlobs[nLabelIndex - 1].width = right - left;
					m_recBlobs[nLabelIndex - 1].height = bottom - top;

				}
			}
		}
	}
}

// Blob Labeling을 실제 행하는 function
// 2000년 정보처리학회에 실린 논문 참조
int CBlobLabeling::__NRFIndNeighbor(int *DataBuf, int nWidth, int nHeight, int nPosX, int nPosY, int *StartX, int *StartY, int *EndX, int *EndY)
{
	Point CurrentPoint;

	CurrentPoint.x = nPosX;
	CurrentPoint.y = nPosY;

	m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].bVisitedFlag = true;
	m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].ptReturnPoint.x = nPosX;
	m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].ptReturnPoint.y = nPosY;

	while (1)
	{
		if ((CurrentPoint.x != 0) && (DataBuf[CurrentPoint.y * nWidth + CurrentPoint.x - 1] == 255))   // -X 방향
		{
			if (m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x - 1].bVisitedFlag == false)
			{
				DataBuf[CurrentPoint.y  * nWidth + CurrentPoint.x - 1] = DataBuf[CurrentPoint.y * nWidth + CurrentPoint.x];	// If so, mark it
				m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x - 1].bVisitedFlag = true;
				m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x - 1].ptReturnPoint = CurrentPoint;
				m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x - 1].n_Obj = m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].n_Obj;

				CurrentPoint.x--;

				if (CurrentPoint.x <= 0)
					CurrentPoint.x = 0;

				if (*StartX >= CurrentPoint.x)
					*StartX = CurrentPoint.x;

				continue;
			}
		}

		if ((CurrentPoint.x != nWidth - 1) && (DataBuf[CurrentPoint.y * nWidth + CurrentPoint.x + 1] == 255))   // +X 방향
		{
			if (m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x + 1].bVisitedFlag == false)
			{
				DataBuf[CurrentPoint.y * nWidth + CurrentPoint.x + 1] = DataBuf[CurrentPoint.y * nWidth + CurrentPoint.x];	// If so, mark it
				m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x + 1].bVisitedFlag = true;
				m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x + 1].ptReturnPoint = CurrentPoint;
				m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x + 1].n_Obj = m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].n_Obj;

				CurrentPoint.x++;

				if (CurrentPoint.x >= nWidth - 1)
					CurrentPoint.x = nWidth - 1;

				if (*EndX <= CurrentPoint.x)
					*EndX = CurrentPoint.x;

				continue;
			}
		}

		if ((CurrentPoint.y != 0) && (DataBuf[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x] == 255))   // -Y 방향
		{
			if (m_vPoint[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x].bVisitedFlag == false)
			{
				DataBuf[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x] = DataBuf[CurrentPoint.y * nWidth + CurrentPoint.x];	// If so, mark it
				m_vPoint[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x].bVisitedFlag = true;
				m_vPoint[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x].ptReturnPoint = CurrentPoint;
				m_vPoint[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x].n_Obj = m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].n_Obj;

				CurrentPoint.y--;

				if (CurrentPoint.y <= 0)
					CurrentPoint.y = 0;

				if (*StartY >= CurrentPoint.y)
					*StartY = CurrentPoint.y;

				continue;
			}
		}

		if ((CurrentPoint.y != nHeight - 1) && (DataBuf[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x] == 255))   // +Y 방향
		{
			if (m_vPoint[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x].bVisitedFlag == false)
			{
				DataBuf[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x] = DataBuf[CurrentPoint.y * nWidth + CurrentPoint.x];	// If so, mark it
				m_vPoint[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x].bVisitedFlag = true;
				m_vPoint[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x].ptReturnPoint = CurrentPoint;
				m_vPoint[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x].n_Obj = m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].n_Obj;

				CurrentPoint.y++;

				if (CurrentPoint.y >= nHeight - 1)
					CurrentPoint.y = nHeight - 1;

				if (*EndY <= CurrentPoint.y)
					*EndY = CurrentPoint.y;

				continue;
			}
		}
		/************************************************************************/
		/* 4->8방향으로 확장
		/************************************************************************/
		if ((CurrentPoint.x != 0) && (CurrentPoint.y != 0) && (DataBuf[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x - 1] == 255))   // -Y 방향
		{
			if (m_vPoint[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x - 1].bVisitedFlag == false)
			{
				DataBuf[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x - 1] = DataBuf[CurrentPoint.y * nWidth + CurrentPoint.x];	// If so, mark it
				m_vPoint[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x - 1].bVisitedFlag = true;
				m_vPoint[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x - 1].ptReturnPoint = CurrentPoint;
				m_vPoint[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x - 1].n_Obj = m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].n_Obj;

				CurrentPoint.y--;
				CurrentPoint.x--;

				if (CurrentPoint.y <= 0)
					CurrentPoint.y = 0;

				if (CurrentPoint.x <= 0)
					CurrentPoint.x = 0;

				if (*StartY >= CurrentPoint.y)
					*StartY = CurrentPoint.y;

				if (*StartX >= CurrentPoint.x)
					*StartX = CurrentPoint.x;

				continue;
			}
		}

		if ((CurrentPoint.x != nWidth - 1) && (CurrentPoint.y != 0) && (DataBuf[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x + 1] == 255))   // -Y 방향
		{
			if (m_vPoint[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x + 1].bVisitedFlag == false)
			{
				DataBuf[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x + 1] = DataBuf[CurrentPoint.y * nWidth + CurrentPoint.x];	// If so, mark it
				m_vPoint[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x + 1].bVisitedFlag = true;
				m_vPoint[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x + 1].ptReturnPoint = CurrentPoint;
				m_vPoint[(CurrentPoint.y - 1) * nWidth + CurrentPoint.x + 1].n_Obj = m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].n_Obj;

				CurrentPoint.y--;
				CurrentPoint.x++;

				if (CurrentPoint.x >= nWidth - 1)
					CurrentPoint.x = nWidth - 1;

				if (CurrentPoint.y <= 0)
					CurrentPoint.y = 0;

				if (*StartY >= CurrentPoint.y)
					*StartY = CurrentPoint.y;

				if (*EndX <= CurrentPoint.x)
					*EndX = CurrentPoint.x;

				continue;
			}
		}

		if ((CurrentPoint.x != 0) && (CurrentPoint.y != nHeight - 1) && (DataBuf[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x - 1] == 255))   // -Y 방향
		{
			if (m_vPoint[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x - 1].bVisitedFlag == false)
			{
				DataBuf[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x - 1] = DataBuf[CurrentPoint.y * nWidth + CurrentPoint.x];	// If so, mark it
				m_vPoint[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x - 1].bVisitedFlag = true;
				m_vPoint[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x - 1].ptReturnPoint = CurrentPoint;
				m_vPoint[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x - 1].n_Obj = m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].n_Obj;

				CurrentPoint.y++;
				CurrentPoint.x--;

				if (CurrentPoint.y >= nHeight - 1)
					CurrentPoint.y = nHeight - 1;

				if (CurrentPoint.x <= 0)
					CurrentPoint.x = 0;

				if (*EndY <= CurrentPoint.y)
					*EndY = CurrentPoint.y;

				if (*StartX >= CurrentPoint.x)
					*StartX = CurrentPoint.x;

				continue;
			}
		}

		if ((CurrentPoint.x != nWidth - 1) && (CurrentPoint.y != nHeight - 1) && (DataBuf[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x + 1] == 255))   // -Y 방향
		{
			if (m_vPoint[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x + 1].bVisitedFlag == false)
			{
				DataBuf[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x + 1] = DataBuf[CurrentPoint.y * nWidth + CurrentPoint.x];	// If so, mark it
				m_vPoint[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x + 1].bVisitedFlag = true;
				m_vPoint[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x + 1].ptReturnPoint = CurrentPoint;
				m_vPoint[(CurrentPoint.y + 1) * nWidth + CurrentPoint.x + 1].n_Obj = m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].n_Obj;

				CurrentPoint.y++;
				CurrentPoint.x++;

				if (CurrentPoint.y >= nHeight - 1)
					CurrentPoint.y = nHeight - 1;

				if (CurrentPoint.x >= nWidth - 1)
					CurrentPoint.x = nWidth - 1;

				if (*EndY <= CurrentPoint.y)
					*EndY = CurrentPoint.y;

				if (*EndX <= CurrentPoint.x)
					*EndX = CurrentPoint.x;

				continue;
			}
		}

		if ((CurrentPoint.x == m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].ptReturnPoint.x)
			&& (CurrentPoint.y == m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].ptReturnPoint.y))
		{
			break;
		}
		else
		{
			CurrentPoint = m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].ptReturnPoint;
		}
	}

	return 0;
}

// 영역중 실제 blob의 칼라를 가진 영역의 크기를 획득
int CBlobLabeling::__Area(int *DataBuf, int StartX, int StartY, int EndX, int EndY, int nWidth, int nLevel)
{
	int nArea = 0;
	int nX, nY;

	for (nY = StartY; nY <= EndY; nY++)
		for (nX = StartX; nX <= EndX; nX++)
			if (DataBuf[nY * nWidth + nX] == nLevel)
				++nArea;
	return nArea;
}


Scalar CBlobLabeling::get_color(int i)
{
	switch (i)
	{
	case 0:
		res = CV_RGB(50, 0, 0);
		break;
	case 1:
		res = CV_RGB(50, 50, 0);
		break;
	case 2:
		res = CV_RGB(50, 100, 0);
		break;
	case 3:
		res = CV_RGB(50, 150, 0);
		break;
	case 4:
		res = CV_RGB(50, 200, 0);
		break;
	case 5:
		res = CV_RGB(50, 50, 50);
		break;
	case 6:
		res = CV_RGB(250, 50, 100);
		break;
	case 7:
		res = CV_RGB(50, 50, 150);
		break;
	case 8:
		res = CV_RGB(50, 50, 200);
		break;
	case 9:
		res = CV_RGB(50, 50, 250);
		break;
	case 10:
		res = CV_RGB(50, 0, 50);
		break;
	case 11:
		res = CV_RGB(50, 100, 50);
		break;
	case 12:
		res = CV_RGB(50, 150, 50);
		break;
	case 13:
		res = CV_RGB(50, 200, 50);
		break;
	case 14:
		res = CV_RGB(50, 250, 50);
		break;
	case 15:
		res = CV_RGB(100, 0, 0);
		break;
	case 16:
		res = CV_RGB(150, 0, 0);
		break;
	case 17:
		res = CV_RGB(200, 0, 0);
		break;
	case 18:
		res = CV_RGB(100, 50, 0);
		break;
	case 19:
		res = CV_RGB(100, 100, 0);
		break;
	case 20:
		res = CV_RGB(100, 150, 0);
		break;
	case 21:
		res = CV_RGB(100, 200, 0);
		break;
	case 22:
		res = CV_RGB(100, 250, 0);
		break;
	case 23:
		res = CV_RGB(250, 50, 100);
		break;
	case 24:
		res = CV_RGB(100, 100, 100);
		break;
	case 25:
		res = CV_RGB(100, 200, 50);
		break;
	case 26:
		res = CV_RGB(150, 100, 200);
		break;
	case 27:
		res = CV_RGB(150, 100, 100);
		break;
	case 28:
		res = CV_RGB(200, 50, 50);
		break;
	case 29:
		res = CV_RGB(200, 100, 0);
		break;
	}

	return res;
}
