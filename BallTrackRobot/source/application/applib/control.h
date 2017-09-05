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
#include "signal_processing.h"


/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */


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
	real32_T y ;		// previous output  updated inside PIDCtl()
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
real32_T PIDControl(pid_T *pid, real32_T r, real32_T y, real32_T ts);

#endif // _CONTROL_H_

// EOF: servo_motor.h
