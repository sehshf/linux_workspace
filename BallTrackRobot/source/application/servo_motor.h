/*
 * servo_motor.h
 *
 *  Created on: 22/10/2016
 *      Author: ses
 */

#ifndef _SERVO_MOTOR_H_
#define _SERVO_MOTOR_H_

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
#define SERVO_CCW			1		// Positive direction
#define SERVO_CW			-1		// Negative direction

// PWM channels where motors are connected to
#define PAN_MOTOR			0
#define TILT_MOTOR			1
#define NUM_MOTORS			2


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

void DriveServoAbs(uint8_T motor, int8_T degree);

void DriveServoInc(uint8_T motor, int8_T direction, int8_T degree);

int8_T GetServoPos(uint8_T motor);


#endif // _SERVO_MOTOR_H_

// EOF: servo_motor.h
