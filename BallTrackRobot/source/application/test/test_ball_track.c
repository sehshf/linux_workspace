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
    boolean_T dtcdFlag = FALSE;
    ballLoc_T loc;

	printf("Start video capturing\n");
	CvCapture *capture =  cvCreateCameraCapture(0);

	cvNamedWindow("piWindow", CV_WINDOW_AUTOSIZE);
	cvMoveWindow ("piWindow", 400, 200);


	IplImage *img;
	IplImage *imgFild = cvCreateImage(CvSize(CV_SIZE_W, CV_SIZE_H), IPL_DEPTH_8U, 1);

	while(1)
	{
		img = cvQueryFrame(capture);

		cvCopy(img, imgFild, NULL);

		FiltBall(imgFild);

		dtcdFlag = FindBall(imgFild, &loc);

		if (dtcdFlag)
			cvCircle(img, CvPoint(loc.x, loc.y), 5, CV_RGB(255, 0, 0));

		cvShowImage("piWindow" , img );

		// wait for a key
		cvWaitKey(30);
	}

	cvReleaseCapture(&capture);

	return PASSED;

} // END: main()

// EOF: test_ball_track.c


