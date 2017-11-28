/*
 * dc_motors.c
 *
 *  Created on: Sep 2, 2017
 *      Author: ses
 */



/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "dc_motors.h"

/*
 * **************************************************
 * GLOBAL VARIABLES (extern)						*
 * **************************************************
 */



/*
 * **************************************************
 * FILE SCOPE VARIABLES (static)					*
 * **************************************************
 */


/*
 * **************************************************
 * LOCAL PROTOTYPES									*
 * **************************************************
 */



/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      INITDCMOTORS()
*      Initialize DC motors and sensors.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Sep 2017
*  -------------------------------------------------------  *
*/
void InitDCMotors(void)
{
	InitPWMChannels();

} // END: InitDCMotors()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      DRIVEDCMOTOR()
*      Drive the DC motor with the specified direction
*      and speed.
*
*  Inputs:
*      motor    : Specifies the DC motor.
*      direction: Movement direction
*      speed	: Motor speed [%], range [MOTOR_MIN_SPEED 100]
*
*  Outputs:
*      servoPos : Position.
*
*  Author: Ehsan Shafiei
*  		   Nov 2017
*  -------------------------------------------------------  *
*/
void DriveDCMotor(uint8_T motor, int8_T direction, uint8_T speed)
{
	uint8_T channel;

	// This can be replaced by a table or map!
	if (motor == LEFT_DCMOTOR)
		if (direction == FORWARD_DIRECTION)
			channel = LEFT_MOTOR_CCW;
		else
			channel = LEFT_MOTOR_CW;
	else
		if (direction == FORWARD_DIRECTION)
			channel = RIGHT_MOTOR_CW;
		else
			channel = RIGHT_MOTOR_CCW;

	SetPCAPWM(channel, speed);

} // END: DriveDCMotor()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      LOCALFUCTION()
*      What this function is doing.
*
*  Inputs:
*      x : Input
*
*  Outputs:
*      y : Return 0 when succeeded.
*
*  Author: Ehsan Shafiei
*  		   Aug 2016
*  -------------------------------------------------------  *
*/
//static type LocalFunction(type x)
//{
//    return y;
//} // END: LocalFunction()


// EOF: dc_motors.c

