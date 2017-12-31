/*
 * test_ultrasonic.c
 *
 *  Created on: Dec 30, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "../../application/camera/ultrasonic.h"


int main(int argc, char *argv[])
{
	real32_T x;

	InitUltrasonicSnsrs();
	sleep(1);

	x = ReadDistance();

	printf("x = %f\n", x);

	return PASSED;

} // END: main()

// EOF: test_ultrasonic.c
