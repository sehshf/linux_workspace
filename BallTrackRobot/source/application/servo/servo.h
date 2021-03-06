/*
 * servo.h
 *
 *  Created on: Sep 2, 2017
 *      Author: ses
 */

#ifndef _SERVO_H_
#define _SERVO_H_

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
#include "servo_control.h"
#include "params.h"
#include "rt_tasks.h"

/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
typedef struct
{
	boolean_T 	vision;
	loc_T 		loc;
} servoInputs_T;

typedef struct
{
	int8_T panPos;
	int8_T tiltPos;
} servoOutputs_T;


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
extern servoOutputs_T servoOutputs;



/*
 * **************************************************
 * PROTOTYPES										*
 * **************************************************
 */
void RunServos(uint16_T period);


#endif // _SERVO_H_

// EOF: servo.h
