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
