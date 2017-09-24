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
*      direction: Rotation direction
*      speed	: Motor speed [%], range [MOTOR_MIN_SPEED 100]
*
*  Outputs:
*      servoPos : Position.
*
*  Author: Ehsan Shafiei
*  		   Apr 2017
*  -------------------------------------------------------  *
*/
void DriveDCMotor(dcMotor_T *motor, int8_T direction, uint8_T speed)
{
	if (direction != motor->direction)
	{
		SetPCAPWM(motor->id[motor->direction], 0);
		motor->speed = 0;
	}

	// If there is no speed encoder, this ensures the motor run
	if (speed > 0)
		speed = max(speed, MOTOR_MIN_SPEED);

	SetPCAPWM(motor->id[direction], speed);

	motor->direction = direction;
	motor->speed 	 = speed;

} // END: DriveDCMotor()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      PUBLICFUCTION()
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

