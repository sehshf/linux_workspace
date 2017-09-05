/*
 * test_motor.c
 *
 *  Created on: Apr 11, 2017
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

#include "../../application/vehicle/speed_sensor.h"
#include "../../application/vehicle/wheel_drive.h"
#include "portable.h"



int main(int argc, char *argv[])
{
	uint8_T  speed;
	int8_T   direction;
	int32_T  leftSnsr;
	uint16_T rpm;

	motor_T motorLeft = {LEFT_MOTOR, 1, 0}, motorRight = {RIGHT_MOTOR, 1, 0};

	InitMotors();
	leftSnsr = InitSpeedSnsr(LEFT_WHEEL);

	while(1)
    {
		printf("Enter speed:\n");
		scanf("%hhd", &speed);

		printf("Enter direction:\n");
		scanf("%hhd", &direction);

		DriveMotor(&motorLeft , (int8_T)direction, (uint8_T)speed);
		DriveMotor(&motorRight, (int8_T)direction, (uint8_T)speed);

		rpm = ReadSpeedSnsr(leftSnsr);
		printf("rpm = %d\n", rpm);
    }

	return PASSED;

} // END: main()

// EOF: test_motor.c

