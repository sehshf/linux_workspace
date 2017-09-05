/*
 * servo_control.c
 *
 *  Created on: Sep 2, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "servo_control.h"

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
*      SERVOCONTROL()
*      Servo control of the pan and tilt structure.
*
*  Inputs:
*      vision: vision status
*      loc	 : Current servo position
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Sep 2017
*  -------------------------------------------------------  *
*/
void ServoControl(boolean_T vision, loc_T loc)
{
	const static real32_T PAN_HYS = 2.0,  TILT_HYS = 2.0;

	real32_T ePan, eTilt;
	int8_T   panAngle, tiltAngle;

	if (vision)
	{
		// Calculate the position errors
		ePan  	= PAN_SP  - loc.x;
		eTilt 	= TILT_SP - loc.y;
	}
	else
	{
		ePan  = 0;
		eTilt = 0;
	}

	// P control loops
	if (abs(ePan) > PAN_HYS)
		panAngle  = MOTORS_Kpan_C  * ePan ;
	else
		panAngle = 0;

	if (abs(eTilt) > TILT_HYS)
		tiltAngle = MOTORS_Ktilt_C * eTilt;
	else
		tiltAngle = 0;

	// Drive pan and tilt servos
	DriveServoInc(PAN_MOTOR ,  GETSIGN(panAngle ), abs(panAngle ));
	DriveServoInc(TILT_MOTOR, -GETSIGN(tiltAngle), abs(tiltAngle));

} // END: ServoControl()



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


// EOF: servo_control.c


