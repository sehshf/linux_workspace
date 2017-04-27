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

#include "../motor_drive.h"
#include "portable.h"



int main(int argc, char *argv[])
{
	uint8_T  speed;
	int8_T direction;

	motor_T motorLeft = {LEFT_MOTOR, 1, 0};

	InitMotors();

	while(1)
    {
		printf("Enter speed:\n");
		scanf("%hhd", &speed);

		printf("Enter direction:\n");
		scanf("%hhd", &direction);

		DriveMotor(&motorLeft, (int8_T)direction, (uint8_T)speed);
    }

	return PASSED;

} // END: main()

// EOF: test_motor.c

