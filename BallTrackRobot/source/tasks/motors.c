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
	static real32_T count = 0;

	motorsInputs_T motorsInputs;

	real32_T ePan, eTilt;
	int8_T   panAngle, tiltAngle;

	// Get the motors component inputs
	GetMotorsInputs(&motorsInputs);

	count++;
	if (count == period / baseTs)
	{
		count = 0;

		// Calculate the position errors
		ePan  = CV_SIZE_W / 2 - motorsInputs.ballLoc.x;
		eTilt = CV_SIZE_H / 2 - motorsInputs.ballLoc.y;

		// P control
		panAngle  = MOTORS_C.Kpan * ePan ;
		tiltAngle = MOTORS_C.Ktilt * eTilt;

		// Drive pan and tilt motors
		DriveServoInc(PAN_MOTOR ,  GETSIGN(panAngle ), abs(panAngle ));
		DriveServoInc(TILT_MOTOR, -GETSIGN(tiltAngle), abs(tiltAngle));
	}

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
	inputs->ballLoc = cameraOutputs.ballLoc;

} // END: GetMotorsInputs()

// EOF: motors.c
