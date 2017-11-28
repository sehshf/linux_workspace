/*
 * vehicle_control.h
 *
 *  Created on: 02/09/2017
 *      Author: ses
 */

#ifndef _VEHICLE_CONTROL_H_
#define _VEHICLE_CONTROL_H_

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
#include "portable.h"
#include "wheel.h"
#include "servo_motors.h"
#include "control.h"


/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
#define POSITION_SP		10				// Vehicle position setpoint [%] (here is the percent of normalized ball area)
#define MOVE_RIGHT		0
#define MOVE_LEFT 		1
#define MOVE_STRAIGHT   2



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
	int8_T 	direction;	// Forward/Backward
	int8_T 	turn;		// Left/right
	uint8_T speed;
	uint8_T sharpness;	// Turning sharpness
} movement_T;

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
void VehiclePositionControl(boolean_T vision, real32_T pos, int8_T panPos);


#endif // _VEHICLE_CONTROL_H_

// EOF: vehicle_control.h
