/*
 * speed_sensor.h
 *
 *  Created on: May 20, 2017
 *      Author: ses
 */

#ifndef _SPEED_SENSOR_H_
#define _SPEED_SENSOR_H_

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <time.h>
#include <aio.h>


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "gpio.h"



/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
#define LEFT_SPEED_SENSOR_PIN 		21		// GPIO pin number
#define RIGHT_SPEED_SENSOR_PIN 		20		// GPIO pin number

#define SPEED_SENSOR_RES			20		// Sensor resolution: pulses/revolution
#define SPEED_STOP_TIME 			500		// Time to detect wheel stopped [ms]

// Speed sensors enumeration
enum
{
	LEFT_SPEED_SNSR,
	RIGHT_SPEED_SNSR,
	NUM_SPEED_SNSR
};

/*
 * **************************************************
 * MACROS											*
 * **************************************************
 */



/*
 * **************************************************
 * TYPE DEFINITIONS									*
 * **************************************************
 */



/*
 * **************************************************
 * External VARIABLES       						*
 * **************************************************
 */




/*
 * **************************************************
 * PROTOTYPES										*
 * **************************************************
 */
void InitSpeedSnsrs(void);

uint16_T ReadSpeedSnsr(uint8_T sensor);

boolean_T ReadSpeedPulse(uint8_T sensor);

#endif // _SPEED_SENSOR_H_

// EOF: speed_sensor.h
