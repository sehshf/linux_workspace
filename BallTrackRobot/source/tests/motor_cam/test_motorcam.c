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

#include "../../application/vehicle/vehicle_control.h"
#include "portable.h"
#include "../../camera/computer_vision.h"
#include "../../application/vehicle/speed_sensor.h"


#define AREA_SETPOINT		10
#define KP					0.25
#define BIAS				10


int main(int argc, char *argv[])
{
	int32_T *addr, fd;

	boolean_T dtcdFlag = FALSE;
	targetObj_T ball;
	IplImage *img, *imgFild;

	real32_T areaFilt = 0;

	int8_T nDtcn = 0, nCapt = 0;

	motor_T leftMotor = {LEFT_MOTOR, 1, 0}, rightMotor = {RIGHT_MOTOR, 1, 0};

	int8_T   direction = 1;
	uint8_T  speed = 0;
	int32_T  err = 0, leftSnsr, rightSnsr;
	uint16_T leftRPM, rightRPM;

	fd = open("/dev/zero", O_RDWR);

	addr = (int32_T *)mmap((void *)PARAMS_ADDR, 256, PROT_WRITE | PROT_WRITE, MAP_PRIVATE, fd, 0);

	if (addr == MAP_FAILED)
		fprintf(stderr, "Mapping failed\n");

	InitParamAddr();
	InitParamVal();



//	clock_t tic, toc;
//	real32_T dt;

	InitMotors();
	leftSnsr  = InitSpeedSnsr(LEFT_WHEEL );
	rightSnsr = InitSpeedSnsr(RIGHT_WHEEL);

	InitCamera();

	while(1)
	{
//		tic = clock();

		img = cvQueryFrame(capture);

		if (img == NULL)
			continue;

		imgFild = FiltBall(img);

		dtcdFlag = FindBall(imgFild, &ball);
//		toc = clock();
//		dt = (real32_T)(toc - tic) / CLOCKS_PER_SEC;

		if (dtcdFlag)
		{
			nDtcn++;
		}
		else
		{
			nDtcn = 0;
			nCapt++;
		}

		if (nDtcn > 0)
		{
			nDtcn = 0;
			nCapt = 0;

			areaFilt = BallArea(ball.area);
			err   	 = AREA_SETPOINT - areaFilt;

			if (abs(err) > 2)
				speed = KP * abs(err) + BIAS;
			else
				speed = 0;

			direction 	= GETSIGN(err);

//			printf("areaFilt = %f, speed = %d\n", areaFilt, speed);

			DriveMotor(&leftMotor , direction, speed);
			DriveMotor(&rightMotor, direction, speed);

//			leftRPM  = ReadSpeedSnsr(leftSnsr );
//			rightRPM = ReadSpeedSnsr(rightSnsr);
//
//			if (leftRPM == 0 || rightRPM == 0)
//			{
//				// Wheel stuck
//				if (speed > MOTOR_MIN_SPEED)
//				{
//					DriveMotor(&leftMotor , 1, 0);
//					DriveMotor(&rightMotor, 1, 0);
//					sleep(5);
//				}
//			}
		}
		else if (nCapt > 20)
		{
//			printf("nCapt = %d\n", nCapt);
			nCapt = 0;
			DriveMotor(&leftMotor , 1, 0);
			DriveMotor(&rightMotor, 1, 0);
		}
	}

	ExitCamera();

	return PASSED;

} // END: main()

// EOF: test_servocam.c
