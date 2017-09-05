/*
 * sginal_processing.h
 *
 *  Created on: Aug 18, 2017
 *      Author: ses
 */

#ifndef _SIGNAL_PROCESSING_H_
#define _SIGNAL_PROCESSING_H_

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <string.h>
#include <stdio.h>

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "portable.h"


/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
#define MAX_AVERAGE_LENGTH	10

#define NORMAL100	(200 * ((x) - (xmin)) / ((xmax) - (xmin)) - 100)	// Normalizing to [-100 100]
#define UNORMAL100	(100 * ((x) - (xmin)) / ((xmax) - (xmin)))			// Normalizing to [0 100]


/*
 * **************************************************
 * MACROS											*
 * **************************************************
 */



/*
 * **************************************************
 * TYPE DEFINITIONS									*
 * **************************************************
 */
typedef struct
{
	uint32_T n;								// averaging window
	real64_T val;							// recent value
	real64_T avr;							// average value
	real64_T array[MAX_AVERAGE_LENGTH];		// value array
} moveAvr_T;


/*
 * **************************************************
 * External VARIABLES       						*
 * **************************************************
 */




/*
 * **************************************************
 * PROTOTYPES										*
 * **************************************************
 */
void SimpleMovingAverage(moveAvr_T *avrObj);


#endif // _SIGNAL_PROCESSING_H_

// EOF: signal_processing.h
