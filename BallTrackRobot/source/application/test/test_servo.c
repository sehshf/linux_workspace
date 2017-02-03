/*
 * test_servo.c
 *
 *  Created on: 20/10/2016
 *      Author: ses
 */

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <stdio.h>

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "portable.h"
#include "servo_motor.h"

int main(void)
{
	uint8_T motor;
	int16_T  degree;
	int16_T direction;

	InitServos();

	while(1)
    {

		printf("Enter motor\n");
		scanf("%hhu", &motor);

		printf("Enter degree:\n");
		scanf("%hd", &degree);

		//DriveServoAbs(motor, (int8_T)degree);

		printf("Enter direction:\n");
		scanf("%hd", &direction);
		DriveServoInc(motor, (int8_T)direction, (int8_T)degree);
    }

    return PASSED;
} // END: main()

// EOF: test_servo.c
