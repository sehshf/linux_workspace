/*
 * servo_motors.h
 *
 *  Created on: Sep 2, 2017
 *      Author: ses
 */

#ifndef _SERVO_MOTORS_H_
#define _SERVO_MOTORS_H_

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
#include "pca9685.h"


/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
// Pulse defines in ms
#define SERVO_PULSE_NEUT	1500
#define SERVO_PULSE_MIN		600
#define SERVO_PULSE_MAX		2400


#define SERVO_POS_MAX		90
#define SERVO_POS_MIN	   -90
#define NUM_SERVOS 			2

#define PAN_MOTOR 			PWM_0
#define TILT_MOTOR 			PWM_1

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
void InitServos(void);

void DriveServoInc(uint8_T motor, int8_T direction, int8_T degree);

int8_T GetServoPos(uint8_T motor);


#endif // _SERVO_MOTORS_H_

// EOF: servo_motors.h
