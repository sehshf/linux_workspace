/*
 * control.h
 *
 *  Created on: Apr 3, 2017
 *      Author: ses
 */

#ifndef _CONTROL_H_
#define _CONTROL_H_

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <stdio.h>
#include <math.h>

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
// Scale to and unscale from [0 factor]
#define SCALE(  x, xmin, xmax, factor)		((factor) * ((x) - (xmin)) / ((xmax) - (xmin)))
#define UNSCALE(x, xmin, xmax, factor)		((x) * ((xmax) - (xmin)) / (factor) + (xmin))


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
// PID gains for ideal form implementation
typedef struct
{
	real32_T k ;		// PID gain
	real32_T ti;		// integration time
	real32_T td;		// derivative time
	uint16_T n ;		// derivative filter factor
	real32_T I ; 		// integrator state updated inside PIDCtl()
	real32_T D ;		// derivative state updated inside PIDCtl()
	uint16_T y ;		// previous output  updated inside PIDCtl()
	uint16_T scale;		// normalizing scale factor
} pid_T;


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
uint16_T PIDCtl(pid_T *pid, uint16_T r, uint16_T y, real32_T ts);

#endif // _CONTROL_H_

// EOF: servo_motor.h
