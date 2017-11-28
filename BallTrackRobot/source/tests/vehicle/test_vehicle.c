/*
 * test_vehicle.c
 *
 *  Created on: Sep 24, 2017
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

#include "wheel.h"
#include "vehicle_control.h"
#include "portable.h"



int main(int argc, char *argv[])
{
	uint8_T  speed;
	uint8_T  sharpness;
//	int32_T  leftSnsr;
//	uint16_T rpm;

	static wheel_T leftWheel  = {LEFT_WHEEL , FORWARD_DIRECTION};
	static wheel_T rightWheel = {RIGHT_WHEEL, FORWARD_DIRECTION};

	real32_T lowerSpeed;

	InitWheels();

	while(1)
    {
		printf("Enter speed:\n");
		scanf("%hhd", &speed);

//		printf("Enter sharpness:\n");
//		scanf("%hhd", &sharpness);

		for (int i = 0; i < 3; i++)
		{
			DriveWheel(&leftWheel, speed);
			DriveWheel(&rightWheel, speed);
			usleep(200000);
		}

//		rpm = ReadSpeedSnsr(leftSnsr);
//		printf("rpm = %d\n", rpm);
    }

	return PASSED;

} // END: main()

// EOF: test_vehicle .c

