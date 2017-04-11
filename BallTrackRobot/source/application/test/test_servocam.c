/*
 * test_servocam.c
 *
 *  Created on: Apr 2, 2017
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
#include <time.h>

#include "../motor.h"
/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "portable.h"
#include "computer_vision.h"
#include "control.h"


int main(int argc, char *argv[])
{
	real32_T Kpan = 0.04, Ktilt = 0.04, ePan, eTilt;
	int8_T  panAngle, tiltAngle;

	boolean_T dtcdFlag = FALSE;
	ballLoc_T loc;
	IplImage *img, *imgFild;

	int8_T nDtcn = 0;

	clock_t tic, toc;
	real32_T dt;

	system("sudo modprobe bcm2835-v4l2");
	usleep(50000);

	InitServos();
	DriveServoAbs(PAN_MOTOR ,   0);
	DriveServoAbs(TILT_MOTOR, -45);

	printf("Start video capturing\n");
	CvCapture *capture =  cvCreateCameraCapture(0);

	while(1)
	{
//		tic = clock();
		img = cvQueryFrame(capture);

		if (img == NULL)
			continue;

		imgFild = FiltBall(img);

		dtcdFlag = FindBall(imgFild, &loc);
//		toc = clock();
//		dt = (real32_T)(toc - tic) / CLOCKS_PER_SEC;

		if (dtcdFlag)
			nDtcn = nDtcn + dtcdFlag;
		else
			nDtcn = 0;

		if (nDtcn > 1)
		{
			nDtcn = 0;

			ePan  = CV_SIZE_W / 2 - loc.x;
			eTilt = CV_SIZE_H / 2 - loc.y;

			// P control
			panAngle  = Kpan  * ePan ;
			tiltAngle = Ktilt * eTilt;

			DriveServoInc(PAN_MOTOR ,  GETSIGN(panAngle) , abs(panAngle) );
			DriveServoInc(TILT_MOTOR, -GETSIGN(tiltAngle), abs(tiltAngle));
		}
	}

	cvReleaseCapture(&capture);

	return PASSED;

} // END: main()

// EOF: test_servocam.c
