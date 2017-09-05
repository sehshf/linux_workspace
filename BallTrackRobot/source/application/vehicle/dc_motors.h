/*
 * dc_motors.h
 *
 *  Created on: Sep 2, 2017
 *      Author: ses
 */

#ifndef _DC_MOTORS_H_
#define _DC_MOTORS_H_

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
#define MOTOR_CCW			0
#define MOTOR_CW		   	1

// DC motor IDs
#define LEFT_MOTOR_CCW		PWM_4
#define LEFT_MOTOR_CW		PWM_5
#define RIGHT_MOTOR_CCW 	PWM_6
#define RIGHT_MOTOR_CW 		PWM_7

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
	uint8_T id[2];
	int8_T  direction;
	uint8_T speed;
} dcMotor_T;


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
void InitDCMotors(void);

void DriveDCMotor(dcMotor_T *motor, int8_T direction, uint8_T speed);

#endif // _DC_MOTORS_H_

// EOF: dc_motors.h
