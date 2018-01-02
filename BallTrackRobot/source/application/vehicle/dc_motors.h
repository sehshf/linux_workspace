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
#include "common_defs.h"
#include "pca9685.h"
#include "speed_sensor.h"


/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
// DC motor channels
#define LEFT_MOTOR_CW		PWM_4
#define LEFT_MOTOR_CCW		PWM_5
#define RIGHT_MOTOR_CCW 	PWM_6
#define RIGHT_MOTOR_CW 		PWM_7

// Voltage range
#define MOTOR_MIN_V			3
#define MOTOR_MAX_V			6
#define MOTOR_BAT_V			15	// Battery voltage

#define MOTOR_MIN_SPEED		20	// (100 * MOTOR_MIN_V / MOTOR_BAT_V)
#define MOTOR_MAX_SPEED		40	// (100 * MOTOR_MAX_V / MOTOR_BAT_V)


// DC motors enumeration
enum
{
	LEFT_DCMOTOR,
	RIGHT_DCMOTOR,
	NUM_DCMOTOR
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

void DriveDCMotor(uint8_T motor, int8_T direction, uint8_T speed);

#endif // _DC_MOTORS_H_

// EOF: dc_motors.h
