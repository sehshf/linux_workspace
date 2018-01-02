/*
 * wheel.h
 *
 *  Created on: Oct 29, 2017
 *      Author: ses
 */

#ifndef _WHEEL_H_
#define _WHEEL_H_

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <pthread.h>
#include <sched.h>


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "dc_motors.h"
#include "speed_sensor.h"


/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
#define WHEEL_STEP_SPEED	20		// Wheel speed in step drive mode (speed between the steps)

// Wheel enumeration
enum
{
	LEFT_WHEEL,
	RIGHT_WHEEL,
	NUM_WHEEL
};


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
	uint8_T id;			// Wheel ID (left or right)
	int8_T 	direction;
	uint8_T motor;
	uint8_T sensor;
	uint8_T steps;		// Assigned number of steps when running in the step mode
} wheel_T;


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
void InitWheels(void);
void DriveWheel(wheel_T *wheel, int8_T direction, uint8_T speed);


#endif // _WHEEL_H_

// EOF: wheel.h


