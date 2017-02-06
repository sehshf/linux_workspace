/*
 * test_ball_detect.c
 *
 *  Created on: Feb 3, 2017
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
#include "computer_vision.h"



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

// EOF: test_ball_detect.c

