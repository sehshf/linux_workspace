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



/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */

/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      INITSPEEDSNSR()
*      Initializing speed sensor (rotary encoder).
*
*  Inputs:
*  		pin : GPIO pin for reading the sensor pulses
*
*  Outputs:
*  		fd  : SYSFS GPIO value file descriptor
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
int32_T InitSpeedSnsr(uint8_T pin)
{
	sysGPIO_T 	gpio;
	int32_T	  	fd;

	// Setting for the GPIO pin
	gpio.pin  		= pin;
	gpio.direction	= SYS_GPIO_IN;
	gpio.trigger 	= SYS_GPIO_FALLING;
	gpio.actvLow	= TRUE;

	// Apply the GPIO setting
	ConfigSysGPIO(&gpio);

	// Open GPIO port
	fd = OpenSysGPIO(pin);

	return fd;

} // END: InitSpeedSnsr()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      READSPEEDSNSR()
*      Calculating rpm from the speed sensor.
*
*  Inputs:
*      sensor : descriptor of the opened value file.
*
*  Outputs:
*      rpm : speed [rpm].
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
uint16_T ReadSpeedSnsr(int32_T sensor)
{
	int8_T	 gpioVal;
	uint16_T cnt = 0, rpm = 0;

	struct timespec tic, toc;

	real32_T dt;

	while (1)
	{
		// This is a blocking read
		gpioVal = ReadSysGPIO(sensor, WHEEL_STOP_TIME);

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
