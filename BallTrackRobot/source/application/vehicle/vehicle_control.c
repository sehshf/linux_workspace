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
*  		panPos: Pan servo position in degree -90 to 90
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Sep 2017
*  -------------------------------------------------------  *
*/
void VehiclePositionControl(boolean_T vision, real32_T pos, int8_T panPos)
{
	const static int32_T 	POS_HYS = 5;
	const static int8_T  	PAN_HYS = 30;
	const static real32_T 	BACKWARD_RDCN = 0.5;
	const static real32_T	Kp = 0.8;


//	static pid_T pid;
//
//	pid.k 	 = 0.5;
//	pid.ti 	 = 5;

	real32_T  u, ePos;

	static movement_T move = { .direction = FORWARD_DIRECTION,
							   .turn 	  = MOVE_STRAIGHT,
							   .speed 	  = 0,
							   .sharpness = 0 };

	if (vision)
	{
		ePos	= POSITION_SP - pos;
		printf("pos = %f\n", pos);
	}
	else
		ePos = 0;

	if (abs(ePos) > POS_HYS)
	{
//		u = PIDControl(&pid, POSITION_SP, pos, 0.1);
		u = Kp * ePos;

		if (GETSIGN(u) > 0)
		{
			move.direction = FORWARD_DIRECTION;
		}
		else
		{
			move.direction = BACKWARD_DIRECTION;
			u = 0.5 * u;	// Lower speed on backward
		}

//		if (panPos < -PAN_HYS)
//		{
//			if (GETSIGN(u) > 0)
//				move.turn = MOVE_RIGHT;
//			else
//				move.turn = MOVE_LEFT;
//
//		}
//		else if (panPos > PAN_HYS)
//		{
//			if (GETSIGN(u) > 0)
//				move.turn = MOVE_LEFT;
//			else
//				move.turn = MOVE_RIGHT;
//		}
//		else
//		{
//			move.turn 		= MOVE_STRAIGHT;
//		}

		if (abs(panPos) > PAN_HYS)
			move.sharpness = (int32_T)(abs(panPos) - PAN_HYS) * 100 / SERVO_POS_MAX;
		else
			move.sharpness 	= 0;

		move.speed = abs(u);


//		printf("turn = %d, pan = %d, sharp = %u\n", move.turn, panPos, move.sharpness);
//		printf("speed = %d\n", move.speed);
	}
	else
	{
		move.speed = 0;
//		pid.I = 0;
	}

	DriveVehicle(&move);

} // END: VehiclePositionControl()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      DRIVEVEHICLE()
*      Drive vehicle with the specified direction,
*      side, speed and sharpness of the turn.
*
*  Inputs:
*      *move : *pointer to the movement object
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Sep 2017
*  -------------------------------------------------------  *
*/
static void DriveVehicle(movement_T *move)
{
	static wheel_T leftWheel  = {LEFT_WHEEL , FORWARD_DIRECTION, 0};
	static wheel_T rightWheel = {RIGHT_WHEEL, FORWARD_DIRECTION, 0};

	real32_T lowerSpeed;

	// Lower speed of the wheel associated with the turning side
	lowerSpeed = (real32_T)move->speed * (100 - move->sharpness) / 100;

//	printf("speedHigh = %u, sharp = %u\n", move->speed, move->sharpness);

	if (move->turn == MOVE_RIGHT)
	{
		DriveWheel(&leftWheel , move->direction, move->speed);
		DriveWheel(&rightWheel, move->direction, (uint8_T)lowerSpeed);
	}
	else if (move->turn == MOVE_LEFT)
	{
		DriveWheel(&leftWheel , move->direction, (uint8_T)lowerSpeed);
		DriveWheel(&rightWheel, move->direction, move->speed);
	}
	else
	{
		DriveWheel(&leftWheel , move->direction, move->speed);
		DriveWheel(&rightWheel, move->direction, move->speed);
	}

} // END: DriveVehicle()


// EOF: vehicle_control .c

