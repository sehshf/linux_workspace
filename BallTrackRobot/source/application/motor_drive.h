/*
 * motor_drive.h
 *
 *  Created on: 22/10/2016
 *      Author: ses
 */

#ifndef _MOTORS_DRIVE_H_
#define _MOTORS_DRIVE_H_

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

#define MOTOR_CCW			1
#define MOTOR_CW		   -1

#define PAN_MOTOR 			0
#define TILT_MOTOR 			1
#define LEFT_MOTOR			4
// number 5 is reserved for LEFT_MOTOR direction
#define RIGHT_MOTOR 		6
// number 7 is reserved for RIGHT_MOTOR direction

#define MOTOR_MIN_SPEED		10		// The minimum speed [%] required to start the rotation

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
	uint8_T id;
	int8_T  direction;
	uint8_T speed;
} motor_T;


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
void InitMotors(void);

void DriveServoAbs(uint8_T motor, int8_T degree);

void DriveServoInc(uint8_T motor, int8_T direction, int8_T degree);

int8_T GetServoPos(uint8_T motor);

void DriveMotor(motor_T *motor, int8_T direction, uint8_T speed);

#endif // _SERVO_MOTOR_H_

// EOF: motor_drive.h
