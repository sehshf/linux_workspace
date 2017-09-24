/*
 * vehicle_control.c
 *
 *  Created on: 03/09/2017
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "vehicle_control.h"

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
static void DriveStraight(int8_T direction, uint8_T speed);
static void TurnVehicle(int8_T direction, uint8_T speed, int8_T side, uint8_T sharpness);


/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      VEHICLEPOSITIONCONTROL()
*      Control the vehicle position.
*
*  Inputs:
*  		vision: vision status
*  		pos	  : current position [%]
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Sep 2017
*  -------------------------------------------------------  *
*/
void VehiclePositionControl(boolean_T vision, real32_T pos)
{
	const static int32_T  POS_HYS = 2;


	static pid_T pid;

	pid.k 	 = 0.25;
	pid.ti 	 = 10;

	real32_T  u, ePos;
	uint8_T   speed = 0, direction = DRIVE_FORWARD;

	if (vision)
		ePos	= POSITION_SP - pos;
	else
		ePos = 0;


	if (abs(ePos) > POS_HYS)
//		speed = MOTORS_Kazim_C * abs(eAzim) + SPEED_BIAS;
	{
		u = PIDControl(&pid, POSITION_SP, pos, 0.04);

		if (GETSIGN(u) > 0)
			direction = DRIVE_FORWARD;
		else
			direction = DRIVE_BACKWARD;

		speed = abs(u);
	}
	else
	{
		speed = 0;
		pid.I = 0;
	}

	DriveStraight(direction, speed);

} // END: VehiclePositionControl()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      PUBLICFUCTION()
*      Drive vehicle straight.
*
*  Inputs:
*      direction: Drive direction (forward or rear)
*      speed	: Motor speed [%], range [MOTOR_MIN_SPEED 100]
*
*  Outputs:
*      y : Return 0 when succeeded.
*
*  Author: Ehsan Shafiei
*  		   Aug 2016
*  -------------------------------------------------------  *
*/
static void DriveStraight(int8_T direction, uint8_T speed)
{
	static dcMotor_T leftMotor  = {{LEFT_MOTOR_CW  , LEFT_MOTOR_CCW}, DRIVE_FORWARD, 0};
	static dcMotor_T rightMotor = {{RIGHT_MOTOR_CCW, RIGHT_MOTOR_CW}, DRIVE_FORWARD, 0};

	DriveDCMotor(&leftMotor , direction, speed);
	DriveDCMotor(&rightMotor, direction, speed);

} // END: DriveStraight()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      PUBLICFUCTION()
*      Drive vehicle straight.
*
*  Inputs:
*      direction: Drive direction (forward or rear)
*      speed	: Motor speed [%], range [MOTOR_MIN_SPEED 100]
*
*  Outputs:
*      y : Return 0 when succeeded.
*
*  Author: Ehsan Shafiei
*  		   Aug 2016
*  -------------------------------------------------------  *
*/
static void TurnVehicle(int8_T direction, uint8_T speed, int8_T side, uint8_T sharpness)
{
	static dcMotor_T leftMotor  = {{LEFT_MOTOR_CW  , LEFT_MOTOR_CCW}, DRIVE_FORWARD, 0};
	static dcMotor_T rightMotor = {{RIGHT_MOTOR_CCW, RIGHT_MOTOR_CW}, DRIVE_FORWARD, 0};

	real32_T lowerSpeed;

	lowerSpeed = (real32_T)speed * (100 - sharpness) / 100;

	if (lowerSpeed < MOTOR_MIN_SPEED)
		lowerSpeed = 0;

	if (side == TURN_RIGHT)
	{
		DriveDCMotor(&leftMotor , direction, speed);
		DriveDCMotor(&rightMotor, direction, (uint8_T)lowerSpeed);
	}
	else if (side == TURN_LEFT)
	{
		DriveDCMotor(&leftMotor , direction, (uint8_T)lowerSpeed);
		DriveDCMotor(&rightMotor, direction, speed);
	}
	else
		fprintf(stderr, "Wrong turn side.\n");

} // END: TurnVehicle()


// EOF: vehicle_control .c

