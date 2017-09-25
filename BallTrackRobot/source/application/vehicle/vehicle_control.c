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
static void DriveVehicle(movement_T *move);


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
void VehiclePositionControl(boolean_T vision, real32_T pos, int8_T panPos)
{
	const static int32_T POS_HYS = 2;
	const static int8_t  PAN_HYS = 5;


	static pid_T pid;

	pid.k 	 = 0.5;
	pid.ti 	 = 10;

	real32_T  u, ePos;

	static movement_T move = { .direction = MOVE_FORWARD,
							   .side 	  = MOVE_STRAIGHT,
							   .speed 	  = 0,
							   .sharpness = 0 };

	if (vision)
		ePos	= POSITION_SP - pos;
	else
		ePos = 0;


	if (abs(ePos) > POS_HYS)
//		speed = MOTORS_Kazim_C * abs(eAzim) + SPEED_BIAS;
	{
		u = PIDControl(&pid, POSITION_SP, pos, 0.04);

		if (GETSIGN(u) > 0)
			move.direction = MOVE_FORWARD;
		else
			move.direction = MOVE_BACKWARD;

		if (panPos < -PAN_HYS)
		{
			if (GETSIGN(u) > 0)
				move.side = MOVE_RIGHT;
			else
				move.side = MOVE_LEFT;
		}
		else if (panPos > PAN_HYS)
		{
			if (GETSIGN(u) > 0)
				move.side = MOVE_LEFT;
			else
				move.side = MOVE_RIGHT;
		}
		else
		{
			move.side = MOVE_STRAIGHT;
		}

		move.speed = abs(u);

		move.sharpness = (int32_T)abs(panPos) * 100 / SERVO_POS_MAX;
	}
	else
	{
		move.speed = 0;
		pid.I = 0;
	}

	DriveVehicle(&move);

} // END: VehiclePositionControl()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
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
static void DriveVehicle(movement_T *move)
{
	static dcMotor_T leftMotor  = {{LEFT_MOTOR_CW  , LEFT_MOTOR_CCW}, MOVE_FORWARD, 0};
	static dcMotor_T rightMotor = {{RIGHT_MOTOR_CCW, RIGHT_MOTOR_CW}, MOVE_FORWARD, 0};

	real32_T lowerSpeed;

	lowerSpeed = (real32_T)move->speed * (100 - move->sharpness) / 100;

	if (lowerSpeed < MOTOR_MIN_SPEED)
		lowerSpeed = 0;

	if (move->side == MOVE_RIGHT)
	{
		DriveDCMotor(&leftMotor , move->direction, move->speed);
		DriveDCMotor(&rightMotor, move->direction, (uint8_T)lowerSpeed);
	}
	else if (move->side == MOVE_LEFT)
	{
		DriveDCMotor(&leftMotor , move->direction, (uint8_T)lowerSpeed);
		DriveDCMotor(&rightMotor, move->direction, move->speed);
	}
	else
	{
		DriveDCMotor(&leftMotor , move->direction, move->speed);
		DriveDCMotor(&rightMotor, move->direction, move->speed);
	}

} // END: DriveVehicle()


// EOF: vehicle_control .c

