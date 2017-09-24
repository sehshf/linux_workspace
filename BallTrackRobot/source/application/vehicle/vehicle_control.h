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
#include "dc_motors.h"
#include "control.h"


/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
#define POSITION_SP		10				// Vehicle position setpoint [%] (here is the percent of normalized ball area)
#define DRIVE_BACKWARD	0
#define DRIVE_FORWARD	1
#define TURN_RIGHT		2
#define TURN_LEFT 		3



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
void VehiclePositionControl(boolean_T vision, real32_T pos);


#endif // _VEHICLE_CONTROL_H_

// EOF: vehicle_control.h
