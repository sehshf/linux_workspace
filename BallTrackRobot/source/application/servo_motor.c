/*
 * servo_motor.c
 *
 *  Created on: 22/10/2016
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "servo_motor.h"

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
static int8_T 	servoPos[NUM_MOTORS];	// Can vary from -90 to 90


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
*      INITSERVOS()
*      Initializing the servo motors.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Oct 2016
*  -------------------------------------------------------  *
*/
void InitServos(void)
{
	SetupPCABoard();
	SetPCAFreq(50);		// 50 Hz
	DriveServoAbs(PAN_MOTOR , 0);
	DriveServoAbs(TILT_MOTOR, -45);

} // END: InitServos()


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

	SetPCAPWM(motor, pulse);

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


// EOF: servo_motor.c

