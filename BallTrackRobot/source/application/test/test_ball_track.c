/*
 * test_ball_track.c
 *
 *  Created on: Feb 9, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "portable.h"
#include "computer_vision.h"



int main(void)
{

	int numCont;
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* firstCont = NULL;
	CvMoments moment;

	int x = 0, y = 0;

	//minimum and maximum object area
	const int AREA_MIN = 20 * 20;
	const int AREA_MAX = 640 * 480 * 3 / 4;

	int area, lastArea;
	boolean_T dtcdFlag;

	printf("Start video capturing\n");
	CvCapture* capture =  cvCreateCameraCapture(0);

	cvNamedWindow("piWindow", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("piWindow", 400, 200);

//	cvNamedWindow("piWindow2", CV_WINDOW_AUTOSIZE);
//	cvMoveWindow("piWindow2", 1100, 200);

//	cvNamedWindow("cnt", CV_WINDOW_AUTOSIZE);
//	cvMoveWindow("piWindow2", 1100, 400);

	IplImage* img;
	IplImage* img2 = cvCreateImage(CvSize(640, 480), IPL_DEPTH_8U, 3);
	IplImage* imgTmp = cvCreateImage(CvSize(640, 480), IPL_DEPTH_8U, 1);
	IplImage* imgFild = cvCreateImage(CvSize(640, 480), IPL_DEPTH_8U, 1);

	cvCreateTrackbar("H1","cnt",&H_MIN,255,0);
	cvCreateTrackbar("H2","cnt",&H_MAX,255,0);
	cvCreateTrackbar("S1","cnt",&S_MIN,255,0);
	cvCreateTrackbar("S2","cnt",&S_MAX,255,0);
	cvCreateTrackbar("V1","cnt",&V_MIN,255,0);
	cvCreateTrackbar("V2","cnt",&V_MAX,255,0);

	IplConvKernel *erodeElement, *dilateElement;

	erodeElement  = cvCreateStructuringElementEx(3, 3, 0, 0, CV_SHAPE_RECT);;
	dilateElement = cvCreateStructuringElementEx(8, 8, 0, 0, CV_SHAPE_RECT);

	while(1)
	{

		lastArea  = 0;

		img = cvQueryFrame(capture);

		cvCvtColor(img, img2, CV_BGR2HSV);

		cvInRangeS(img2, cvScalar(H_MIN, S_MIN, V_MIN), cvScalar(H_MAX, S_MAX, V_MAX), imgTmp);

		cvErode (imgTmp, imgTmp, erodeElement , 2);
		cvDilate(imgTmp, imgTmp, dilateElement, 2);

		cvCopy(imgTmp, imgFild, NULL);

		numCont = cvFindContours(imgTmp, storage, &firstCont);

		if (numCont > 0)
		{
			for (; firstCont != NULL; firstCont = firstCont->h_next)
			{
				cvMoments(firstCont, &moment, 0);
				area = moment.m00;

				if (area > AREA_MIN && area < AREA_MAX && area > lastArea)
				{
					x = (int)(moment.m10 / moment.m00);
					y = (int)(moment.m01 / moment.m00);

					lastArea  = area;
					dtcdFlag = TRUE;
				}
				else
				{
					dtcdFlag = FALSE;
				}
			}
			if (dtcdFlag)
				cvCircle(img, CvPoint(x, y), 5, CV_RGB(255, 0, 0));
		}

		cvShowImage("piWindow" , img );
		//cvShowImage("piWindow2", imgFild);

		// wait for a key
		cvWaitKey(30);
	}

//		printf("Channel = %d, Size = %d, width = %d, height = %d, Depth = %d\n",
//				imgBall->nChannels, imgBall->nSize, imgBall->width, imgBall->height, imgBall->depth);

	cvReleaseStructuringElement(&erodeElement );
	cvReleaseStructuringElement(&dilateElement);

	cvReleaseCapture(&capture);

	return PASSED;

} // END: main()

// EOF: test_ball_detect.c


