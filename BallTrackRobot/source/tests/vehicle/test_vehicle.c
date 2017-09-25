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

#include "speed_sensor.h"
#include "vehicle_control.h"
#include "portable.h"



int main(int argc, char *argv[])
{
	uint8_T  speed;
	uint8_T  sharpness;
//	int32_T  leftSnsr;
//	uint16_T rpm;

	static dcMotor_T motorLeft  = {{LEFT_MOTOR_CW  , LEFT_MOTOR_CCW}, 1, 0};
	static dcMotor_T motorRight = {{RIGHT_MOTOR_CCW, RIGHT_MOTOR_CW}, 1, 0};

	real32_T lowerSpeed;

	InitDCMotors();
//	leftSnsr = InitSpeedSnsr(LEFT_WHEEL);

	while(1)
    {
		printf("Enter speed:\n");
		scanf("%hhd", &speed);

		printf("Enter sharpness:\n");
		scanf("%hhd", &sharpness);

		lowerSpeed = (real32_T)speed * (100 - sharpness) / 100;

		if (lowerSpeed < MOTOR_MIN_SPEED)
			lowerSpeed = 0;

		DriveDCMotor(&motorLeft , (int8_T)MOVE_BACKWARD, (uint8_T)speed);
		DriveDCMotor(&motorRight, (int8_T)MOVE_BACKWARD, (uint8_T)lowerSpeed);

//		rpm = ReadSpeedSnsr(leftSnsr);
//		printf("rpm = %d\n", rpm);
    }

	return PASSED;

} // END: main()

// EOF: test_vehicle .c

