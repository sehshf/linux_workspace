/*
 * ultrasonic.c
 *
 *  Created on: Dec 30, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "ultrasonic.h"

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
// File descriptor for ultrasonic sensor
static int32_T fdUltrasonicSnsr[NUM_ULTRASONIC_PIN];


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
*      INITULTRASONICSNSRS()
*      Initializing ultrasonic sensor.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Dec 2017
*  -------------------------------------------------------  *
*/
void InitUltrasonicSnsrs(void)
{
	sysGPIO_T gpio;

	// Setting for the trigger pin
	gpio.pin  		= ULTRASONIC_TRIG_PIN;
	gpio.direction	= SYS_GPIO_OUT;
	gpio.trigger 	= SYS_GPIO_NONE;
	gpio.actvLow	= FALSE;

	// Apply the GPIO setting
	ConfigSysGPIO(&gpio);

	// Open GPIO port
	fdUltrasonicSnsr[ULTRASONIC_TRIG] = OpenSysGPIO(ULTRASONIC_TRIG_PIN);

	// Setting for the trigger pin
	gpio.pin  		= ULTRASONIC_ECHO_PIN;
	gpio.direction	= SYS_GPIO_IN;
	gpio.trigger 	= SYS_GPIO_BOTH;
	gpio.actvLow	= FALSE;

	// Apply the GPIO setting
	ConfigSysGPIO(&gpio);

	// Open GPIO port
	fdUltrasonicSnsr[ULTRASONIC_ECHO] = OpenSysGPIO(ULTRASONIC_ECHO_PIN);

} // END: InitUltrasonicSnsrs()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      READDISTANCE()
*      Calculates object distance using ultrasonic sensor.
*
*  Inputs:
*
*  Outputs:
*  		x : distance [cm]
*
*  Author: Ehsan Shafiei
*  		   Dec 2017
*  -------------------------------------------------------  *
*/
real32_T ReadDistance(void)
{
	const static real32_T SOUND_SPEED = 0.034; // [cm/us]

	int8_T gpioVal;

	struct timespec tic, toc;

	real32_T dt, x = 0;

	// Apply trigger pulse
	WriteSysGPIO(fdUltrasonicSnsr[ULTRASONIC_TRIG], TRUE);
	usleep(10);
	WriteSysGPIO(fdUltrasonicSnsr[ULTRASONIC_TRIG], FALSE);

	// Detect rising edge of the echo pulse
	gpioVal = ReadSysGPIO(fdUltrasonicSnsr[ULTRASONIC_ECHO], 1);
	if (gpioVal == TRUE)
	{
		clock_gettime(CLOCK_REALTIME, &tic);
	}
	else
	{
		fprintf(stderr, "Failed to read the rising edge of ultrasonic echo pin.\n");
	}

	// Detect falling edge of the echo pulse
	gpioVal = ReadSysGPIO(fdUltrasonicSnsr[ULTRASONIC_ECHO], 10);
	if (gpioVal == FALSE)
	{
		clock_gettime(CLOCK_REALTIME, &toc);
	}
	else
	{
		fprintf(stderr, "Failed to read the falling edge of ultrasonic echo pin.\n");
	}

	// Calculate echo pulse duration
	dt = (real32_T)(toc.tv_sec * 1e6 + toc.tv_nsec * 1e-3 - tic.tv_sec * 1e6 - tic.tv_nsec * 1e-3);	// [us]

	// Calculate distance
	x = 0.5 * dt * SOUND_SPEED;

	return x;

} // END: ReadDistance()


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
//static void DriveVehicle(movement_T *move)
//{
//
//
//} // END: DriveVehicle()


// EOF: ultrasonic .c


