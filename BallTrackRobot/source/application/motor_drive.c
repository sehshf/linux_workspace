/*
 * motor_drive.c
 *
 *  Created on: 22/10/2016
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "motor_drive.h"

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
static int8_T 	servoPos[NUM_SERVOS];	// Can vary from -90 to 90


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
*      INITMOTORS()
*      Initializing the PCA board to drive the motors.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Oct 2016
*  -------------------------------------------------------  *
*/
void InitMotors(void)
{
	SetupPCABoard();
	SetPCAFreq(50);		// 50 Hz

} // END: InitMotors()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      DRIVESERVOABS()
*      Drive the servo motors to an absolute position.
*
*  Inputs:
*      motor : Specifies the servo motor.
*      degree: Absolute position in degree -90 to 90
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Oct 2016
*  -------------------------------------------------------  *
*/
void DriveServoAbs(uint8_T motor, int8_T degree)
{
	uint16_T pulse;

	pulse = SERVO_PULSE_NEUT + degree * (SERVO_PULSE_MAX - SERVO_PULSE_MIN) / SERVO_POS_MAX / 2;	// pulse [ms]

	servoPos[motor] = degree;		// Update position

	SetPCAPulse(motor, pulse);

} // END: DriveServoAbs()

/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      DRIVESERVOINC()
*      Drive the servo motors with an incremental position degree.
*
*  Inputs:
*      motor 	: Specifies the servo motor.
*      direction: Rotation direction
*      degree	: Absolute position in degree -90 to 90
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Oct 2016
*  -------------------------------------------------------  *
*/
void DriveServoInc(uint8_T motor, int8_T direction, int8_T degree)
{
    servoPos[motor] = servoPos[motor] + direction * degree;
    servoPos[motor] = min(SERVO_POS_MAX, max(-SERVO_POS_MAX, servoPos[motor]));
    DriveServoAbs(motor, servoPos[motor]);

} // END: DriveServoInc()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      GETSERVOPOS()
*      Return the absolute position of the specified servo motor.
*
*  Inputs:
*      motor : Specifies the servo motor.
*
*  Outputs:
*      servoPos : Position.
*
*  Author: Ehsan Shafiei
*  		   Oct 2016
*  -------------------------------------------------------  *
*/
int8_T GetServoPos(uint8_T motor)
{
	return servoPos[motor];

} // END: GetServoPos()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      DRIVEMOTOR()
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
void DriveMotor(motor_T *motor, int8_T direction, uint8_T speed)
{
	if (direction != motor->direction)
	{
		if (direction > 0)
			SetPCAPWM(motor->id    , 0);
		else
			SetPCAPWM(motor->id + 1, 0);
		motor->speed = 0;
	}

	// If there is no speed encoder, this ensures the motor run
	if (speed > 0)
		speed = max(speed, MOTOR_MIN_SPEED);

	if (direction > 0)
		SetPCAPWM(motor->id + 1, speed);
	else
		SetPCAPWM(motor->id    , speed);

	motor->direction = direction;
	motor->speed = speed;

} // END: DriveMotor()


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


// EOF: motor_drive.c

