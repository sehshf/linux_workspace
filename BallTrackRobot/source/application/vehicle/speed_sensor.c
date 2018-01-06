/*
 * speed_sensor.c
 *
 *  Created on: May 20, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "../vehicle/speed_sensor.h"


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
// File descriptor for speed sensors
static int32_T fdSpeedSnsr[NUM_SPEED_SNSR];


/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */

/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      INITSPEEDSNSRS()
*      Initializing speed sensors (rotary encoder).
*
*  Inputs:
*  		*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
void InitSpeedSnsrs(void)
{
	sysGPIO_T gpio;

	/* Initialize left speed sensor */

	// Setting for the GPIO pin
	gpio.pin  		= LEFT_SPEED_SENSOR_PIN;
	gpio.direction	= SYS_GPIO_IN;
	gpio.trigger 	= SYS_GPIO_BOTH;
	gpio.actvLow	= FALSE;

	// Apply the GPIO setting
	ConfigSysGPIO(&gpio);

	// Open GPIO port
	fdSpeedSnsr[LEFT_SPEED_SNSR] = OpenSysGPIO(LEFT_SPEED_SENSOR_PIN);


	/* Initialize right speed sensor */

	// Setting for the GPIO pin
	gpio.pin  		= RIGHT_SPEED_SENSOR_PIN;
	gpio.direction	= SYS_GPIO_IN;
	gpio.trigger 	= SYS_GPIO_BOTH;
	gpio.actvLow	= FALSE;

	// Apply the GPIO setting
	ConfigSysGPIO(&gpio);

	// Open GPIO port
	fdSpeedSnsr[RIGHT_SPEED_SNSR] = OpenSysGPIO(LEFT_SPEED_SENSOR_PIN);

} // END: InitSpeedSnsrs()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      READSPEEDSNSR()
*      Calculating rpm from the speed sensor.
*
*  Inputs:
*      sensor : speed sensor (left or right).
*
*  Outputs:
*      rpm : speed [rpm].
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
uint16_T ReadSpeedSnsr(uint8_T sensor)
{
	int8_T	 gpioVal;
	uint16_T cnt = 0, rpm = 0;

	struct timespec tic, toc;

	real32_T dt;

	while (1)
	{
		// This is a blocking read
		gpioVal = ReadSysGPIO(fdSpeedSnsr[sensor], SPEED_STOP_TIME);

		if (gpioVal == TRUE)
			cnt++;
		else if (gpioVal == -1)		// timeout
		{
			return 0;				// Speed is zeros
		}

		// Calculate the speed after a complete revolution
		switch (cnt)
		{
		case 1:
			clock_gettime(CLOCK_REALTIME, &tic);
			break;
		case SPEED_SENSOR_RES + 1:
			clock_gettime(CLOCK_REALTIME, &toc);
			cnt = 0;
			dt = (float)(toc.tv_sec + toc.tv_nsec * 1e-9 - tic.tv_sec - tic.tv_nsec * 1e-9);
			rpm = 60 / dt;
			return rpm;
			break;
		}
	}

} // END: ReadSpeedSnsr()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      READSPEEDPULSE()
*      Reading one complete encoder pulse.
*
*  Inputs:
*      sensor : descriptor of the opened value file.
*
*  Outputs:
*      pulse : returns the read status.
*
*  Author: Ehsan Shafiei
*  		   Oct 2017
*  -------------------------------------------------------  *
*/
boolean_T ReadSpeedPulse(uint8_T sensor)
{
	boolean_T pulse = FALSE;

	// This is a blocking read
	if (ReadSysGPIO(fdSpeedSnsr[sensor], SPEED_STOP_TIME) != -1)
		pulse = TRUE;
	else
		pulse = FALSE;

	return pulse;

} // END: ReadSpeedPulse()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      LOCALFUCTION()
*      What this function is doing.
*
*  Inputs:
*      x : Input
*
*  Outputs:
*      y : Returns 0 when succeeded.
*
*  Author: Ehsan Shafiei
*  		   Aug 2016
*  -------------------------------------------------------  *
*/
//static type LocalFunction(type x)
//{
//    return y;
//} // END: LocalFunction()

// EOF: speed_sensor.c
