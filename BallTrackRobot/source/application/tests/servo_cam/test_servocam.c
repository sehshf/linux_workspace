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
#ifdef 	USE_MAP_ANON
#define _BSD_SOURCE
#endif
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "motor_drive.h"
#include "portable.h"
#include "computer_vision.h"
#include "control.h"


int main(int argc, char *argv[])
{
	int32_T *addr, fd;

	fd = open("/dev/zero", O_RDWR);

	addr = (int32_T *)mmap((void *)PARAMS_ADDR, 256, PROT_WRITE | PROT_WRITE, MAP_PRIVATE, fd, 0);

	if (addr == MAP_FAILED)
		fprintf(stderr, "Mapping failed\n");

	InitParamAddr();
	InitParamVal();

	const real32_T Kpan = 0.14, Ktilt = 0.13;
	real32_T ePan, eTilt;
	int8_T   panAngle, tiltAngle;
	loc_T	 loc;

	targetObj_T ball;
	IplImage *img, *imgFild;

	clock_t tic, toc;
	real32_T dt;

	InitMotors();
	DriveServoAbs(PAN_MOTOR ,   0);
	DriveServoAbs(TILT_MOTOR, -45);

	InitCamera();

	while(1)
	{
		tic = clock();

		img = cvQueryFrame(capture);

		if (img == NULL)
			continue;

		imgFild = FiltBall(img);

		FindBall(imgFild, &ball);

		if (ball.detcd)
		{
			loc 	= BallLocation(ball.x, ball.y);
			ePan  	= 50 - loc.x;
			eTilt 	= 50 - loc.y;

//			tic = clock();
//			printf("(%f, %f)\n", ePan, eTilt);
//			toc = clock();
//			dt = (real32_T)(toc - tic) / CLOCKS_PER_SEC;
//			printf("dt = %f\n", dt);
		}
		else
		{
			ePan  = 0;
			eTilt = 0;
		}
		// P control
		if (abs(ePan) > 2)
			panAngle  = Kpan  * ePan ;
		else
			panAngle = 0;

		if (abs(eTilt) > 2)
			tiltAngle = Ktilt * eTilt;
		else
			tiltAngle = 0;

		DriveServoInc(PAN_MOTOR ,  GETSIGN(panAngle) , abs(panAngle) );
		DriveServoInc(TILT_MOTOR, -GETSIGN(tiltAngle), abs(tiltAngle));

		usleep(10000);
	}

	ExitCamera();

	return PASSED;

} // END: main()

// EOF: test_servocam.c
