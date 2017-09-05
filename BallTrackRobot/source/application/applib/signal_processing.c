/*
 * signal_processing.c
 *
 *  Created on: Aug 18, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "applib/signal_processing.h"

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
*      SIMPLEMOVINGAVERAGE()
*      Implement simple moving average algorithm.
*
*  Inputs:
*  		*avrObj: Pointer to moving average struct
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Aug 2017
*  -------------------------------------------------------  *
*/
void SimpleMovingAverage(moveAvr_T *avrObj)
{
	uint32_T i;
	real64_T sum = 0;

	// Update array
	for (i = 0; i < avrObj->n - 1; i++)
		avrObj->array[i] = avrObj->array[i + 1];
	avrObj->array[avrObj->n - 1] = avrObj->val;

	// Calculate average
	for (i = 0; i < avrObj->n; i++)
		sum += avrObj->array[i];
	avrObj->avr = sum / avrObj->n;

} // END: SimpleMovingAverage()





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


// EOF: signal_processing.c


