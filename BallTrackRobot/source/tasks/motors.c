/*
 * motors.c
 *
 *  Created on: 26/04/2017
 *      Author: ses
 */


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "motors.h"


/*
 * **************************************************
 * LOCAL DECLARATIONS								*
 * **************************************************
 */



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
void GetMotorsInputs(motorsInputs_T *inputs);


/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      RUNMOTORS()
*      Run motors task.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*		   Apr 2017
*  -------------------------------------------------------  *
*/
void RunMotors (uint16_T period)
{
	motorsInputs_T motorsInputs;

	loc_T	 loc;
	real32_T ePan, eTilt;
	int8_T   panAngle, tiltAngle;

	// Get the motors component inputs
	GetMotorsInputs(&motorsInputs);

	if (motorsInputs.ball.detcd)
	{
		// Calculate the position errors
		loc 	= BallLocation(motorsInputs.ball.x, motorsInputs.ball.y);
		ePan  	= 50 - loc.x;
		eTilt 	= 50 - loc.y;
	}
	else
	{
		ePan  = 0;
		eTilt = 0;
	}

	// P control
	if (abs(ePan) > 1)
		panAngle  = MOTORS_Kpan_C  * ePan ;
	else
		panAngle = 0;

	if (abs(eTilt) > 1)
		tiltAngle = MOTORS_Ktilt_C * eTilt;
	else
		tiltAngle = 0;

	// Drive pan and tilt motors
	DriveServoInc(PAN_MOTOR ,  GETSIGN(panAngle ), abs(panAngle ));
	DriveServoInc(TILT_MOTOR, -GETSIGN(tiltAngle), abs(tiltAngle));

} // END: RunMotors()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      GETMOTORSINPUTS()
*      Get the inputs to the "motors" component.
*
*  Inputs:
*      *inputs : Pointer to the input values
*
*  Author: Ehsan Shafiei
*  		   Apr 2017
*  -------------------------------------------------------  *
*/
void GetMotorsInputs(motorsInputs_T *inputs)
{
	inputs->ball = cameraOutputs.ball;

} // END: GetMotorsInputs()

// EOF: motors.c
