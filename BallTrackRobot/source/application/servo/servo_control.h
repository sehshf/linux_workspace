/*
 * servo_control.h
 *
 *  Created on: Sep 2, 2017
 *      Author: ses
 */

#ifndef _SERVO_CONTROL_H_
#define _SERVO_CONTROL_H_

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "params.h"
#include "common_defs.h"
#include "servo_motors.h"


/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
#define PAN_SP		50.0		// Pan  setpoint [%] (here is the percent of normalized window)
#define TILT_SP		50.0		// Tilt setpoint [%] (here is the percent of normalized window)

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
void ServoControl(boolean_T vision, loc_T loc);

#endif // _SERVO_CONTROL_H_

// EOF: servo_control.h
