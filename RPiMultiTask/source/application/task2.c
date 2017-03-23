/*
 * task2.c
 *
 *  Created on: 25/09/2016
 *      Author: ses
 */


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "task2.h"


/*
 * **************************************************
 * LOCAL DECLARATIONS								*
 * **************************************************
 */



/*
 * **************************************************
 * GLOBAL VARIABLES (extern)						*
 * **************************************************
 */



/*
 * **************************************************
 * FILE SCOPE VARIABLES (static)					*
 * **************************************************
 */



/*
 * **************************************************
 * LOCAL PROTOTYPES									*
 * **************************************************
 */



/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      EXECTASK2()
*      Execute the next step of task2.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*		   Sep 2016
*  -------------------------------------------------------  *
*/
void ExecTask2(void)
{
	static real32_T count = 0;

	count++;
	if (count == task[2].period / baseTs)
	{
		printf("task2 has run for %d seconds.\n", task[2].period);
		fflush(stdout);
		count = 0;
	}

	task[2].clock.clockTickL++;
	if (!task[2].clock.clockTickL)
	{
		task[2].clock.clockTickH++;
	}

} // END: ExecTask2()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      PUBLICFUCTION()
*      What this function is doing.
*
*  Inputs:
*      x : Input
*
*  Outputs:
*      y : Return 0 when succeeded.
*
*  Author: Ehsan Shafiei
*  		   Aug 2016
*  -------------------------------------------------------  *
*/
//static type LocalFunction(type x)
//{
//    return y;
//} // END: LocalFunction()

// EOF: task2.c
