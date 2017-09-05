/*
 * test_ball_detect.c
 *
 *  Created on: Feb 3, 2017
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

#include "../../camera/computer_vision.h"
/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "portable.h"



int main(void)
{

	printf("Start video capturing\n");
	CvCapture* capture =  cvCreateCameraCapture(0);

	IplImage* img;

	while (1)
	{

		img = cvQueryFrame(capture);

		BallFiltTune(img, 400, 200);
	}

//		printf("Channel = %d, Size = %d, width = %d, height = %d, Depth = %d\n",
//				imgBall->nChannels, imgBall->nSize, imgBall->width, imgBall->height, imgBall->depth);

	cvReleaseCapture(&capture);

	return PASSED;

} // END: main()

// EOF: test_ball_detect.c

