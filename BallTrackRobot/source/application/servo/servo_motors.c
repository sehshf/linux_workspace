/*
 * servo_motors.c
 *
 *  Created on: Sep 2, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "servo_motors.h"

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
static void DriveServoAbs(uint8_T motor, int8_T degree);


/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      INITSERVOS()
*      Initializing the servos.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Sep 2017
*  -------------------------------------------------------  *
*/
void InitServos(void)
{
	InitPWMChannels();

} // END: InitServos()


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
    uint8_T servo;

    switch (motor)
    {
    case PAN_MOTOR:
    	servo = PAN_SERVO;
    	break;
    case TILT_MOTOR:
    	servo = TILT_SERVO;
    	break;
    }

	servoPos[servo] = servoPos[servo] + direction * degree;
    servoPos[servo] = sat(servoPos[servo], -SERVO_POS_MAX, SERVO_POS_MAX);
    DriveServoAbs(motor, servoPos[servo]);

} // END: DriveServoInc()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      GETSERVOPOS()
*      Return the absolute position of the specified servo motor.
*
*  Inputs:
*      servo : Specifies the servo motor.
*
*  Outputs:
*      servoPos : Position.
*
*  Author: Ehsan Shafiei
*  		   Oct 2016
*  -------------------------------------------------------  *
*/
int8_T GetServoPos(uint8_T servo)
{
	return servoPos[servo];

} // END: GetServoPos()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
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
static void DriveServoAbs(uint8_T motor, int8_T degree)
{
	uint16_T pulse;
    uint8_T servo;

    switch (motor)
    {
    case PAN_MOTOR:
    	servo = PAN_SERVO;
    	break;
    case TILT_MOTOR:
    	servo = TILT_SERVO;
    	break;
    }

	pulse = SERVO_PULSE_NEUT + degree * (SERVO_PULSE_MAX - SERVO_PULSE_MIN) / SERVO_POS_MAX / 2;	// pulse [ms]

	servoPos[servo] = degree;		// Update position

	SetPCAPulse(motor, pulse);

} // END: DriveServoAbs()


// EOF: servo_motors.c

