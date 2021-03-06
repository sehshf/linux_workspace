/*
 * vehicle.h
 *
 *  Created on: 26/04/2017
 *      Author: ses
 */


#ifndef _VEHICLE_H_
#define _VEHICLE_H_

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
#include "camera.h"
#include "servo.h"
#include "params.h"
#include "vehicle_control.h"
#include "rt_tasks.h"

/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
typedef struct
{
	boolean_T	vision;
	real32_T 	vehPos;
	int8_T		panPos;
} vehicleInputs_T;


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
void InitVehicle(void);
void RunVehicle(uint16_T period);


#endif // _VEHICLE_H_

// EOF: vehicle.h

