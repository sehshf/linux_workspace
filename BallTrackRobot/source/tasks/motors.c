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
void MotorHandler(motorsInputs_T *inputs);


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
	motorsInputs_T inputs;

	// Get the motors component inputs
	GetMotorsInputs(&inputs);

	// Handle motor tasks
	MotorHandler(&inputs);

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


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      MOTORHANDLER()
*      Handle motor tasks.
*
*  Inputs:
*      *inputs : Pointer to the input values
*
*  Author: Ehsan Shafiei
*  		   Aug 2017
*  -------------------------------------------------------  *
*/
void MotorHandler(motorsInputs_T *inputs)
{
	const static real32_T PAN_HYS = 2.0,  TILT_HYS = 2.0;
	const static real32_T PAN_SP  = 50.0, TILT_SP  = 50.0;

	const static int32_T  AZIMUTH_SP = 10, AZIMUTH_HYS = 2;

	const static int8_T SPEED_BIAS = 10;

	static motor_T leftMotor  = {LEFT_MOTOR , 1, 0};
	static motor_T rightMotor = {RIGHT_MOTOR, 1, 0};

	static pid_T pid;

	pid.k 	 = 0.01;
	pid.ti 	 = 0;
	pid.scale = 100;

	loc_T	 loc;
	int32_T  area, eAzim;
	real32_T ePan, eTilt;
	int8_T   panAngle, tiltAngle;
	int8_T  speed = 0;
	int8_T   direction = 1;

	if (inputs->ball.detcd)
	{
		// Calculate the position errors
		loc 	= BallLocation(inputs->ball.x, inputs->ball.y);
		ePan  	= PAN_SP  - loc.x;
		eTilt 	= TILT_SP - loc.y;

		area 	= BallArea(inputs->ball.area);
		eAzim	= AZIMUTH_SP - area;
	}
	else
	{
		ePan  = 0;
		eTilt = 0;
		eAzim = 0;
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

	if (abs(eAzim) > AZIMUTH_HYS)
//		speed = MOTORS_Kazim_C * abs(eAzim) + SPEED_BIAS;
	{
		speed = PIDCtl(&pid, AZIMUTH_SP, area, 0.04);
		direction = GETSIGN(speed);
		speed = SPEED_BIAS + abs(speed);
	}
	else
	{
		speed = 0;
		pid.I = 0;
	}

	// Movement direction
//	direction = GETSIGN(eAzim);

	// Drive pan and tilt motors
	DriveServoInc(PAN_MOTOR ,  GETSIGN(panAngle ), abs(panAngle ));
	DriveServoInc(TILT_MOTOR, -GETSIGN(tiltAngle), abs(tiltAngle));

	// Drive wheel motors
	DriveMotor(&leftMotor , direction, speed);
	DriveMotor(&rightMotor, direction, speed);


} // END: MotorHandler()


// EOF: motors.c
