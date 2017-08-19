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
#ifdef 	USE_MAP_ANON
#define _BSD_SOURCE
#endif
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

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
    targetObj_T ball;

    int32_T *addr, fd;

	fd = open("/dev/zero", O_RDWR);

	addr = (int32_T *)mmap((void *)PARAMS_ADDR, 256, PROT_WRITE | PROT_WRITE, MAP_PRIVATE, fd, 0);

	if (addr == MAP_FAILED)
		fprintf(stderr, "Mapping failed\n");

	InitParamAddr();
	InitParamVal();

	InitCamera();

	cvNamedWindow("piWindow", CV_WINDOW_AUTOSIZE);
	cvMoveWindow ("piWindow", 400, 200);

	IplImage *img, *imgFild;


	while(1)
	{
		img = cvQueryFrame(capture);

		imgFild = FiltBall(img);

		dtcdFlag = FindBall(imgFild, &ball);

		if (dtcdFlag)
			cvCircle(img, CvPoint(ball.x, ball.y), 5, CV_RGB(255, 0, 0));

		cvShowImage("piWindow" , img);

		// wait for a key
		cvWaitKey(30);
	}

	cvReleaseCapture(&capture);

	return PASSED;

} // END: main()

// EOF: test_ball_track.c


