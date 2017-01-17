/*
 * main.c
 *
 *  Created on: Jan 17, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <stdio.h>
#include <unistd.h>

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "portable.h"

int main()
{
	for (int32_T i = 0; i < 3; i++)
	{
		printf("Hello Ehsan\n");
		sleep(3);
	}

	return PASSED;

} // END: main()

// EOF: main.c
