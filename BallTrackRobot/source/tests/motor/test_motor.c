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

#include "speed_sensor.h"
#include "dc_motors.h"
#include "portable.h"



int main(int argc, char *argv[])
{
	uint8_T  speed;
	int8_T   direction;

//	uint16_T rpm;

	static dcMotor_T motorLeft  = {{LEFT_MOTOR_CW  , LEFT_MOTOR_CCW}, 1, 0};
	static dcMotor_T motorRight = {{RIGHT_MOTOR_CCW, RIGHT_MOTOR_CW}, 1, 0};

	InitDCMotors();
	InitWheelSnsrs();

	while(1)
    {
		printf("Enter speed:\n");
		scanf("%hhd", &speed);

		printf("Enter direction:\n");
		scanf("%hhd", &direction);

		DriveDCMotor(&motorLeft , (int8_T)direction, (uint8_T)speed);
		DriveDCMotor(&motorRight, (int8_T)direction, (uint8_T)speed);

//		rpm = ReadSpeedSnsr(leftSnsr);
//		printf("rpm = %d\n", rpm);
    }

	return PASSED;

} // END: main()

// EOF: test_motor.c

