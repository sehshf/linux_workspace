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
#define LEFT_WHEEL 			20		// GPIO pin number
#define RIGHT_WHEEL 		21		// GPIO pin number

#define SPEED_SENSOR_RES	20		// Sensor resolution: pulses/revolution



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
int32_T InitSpeedSnsr(uint8_T pin);

uint16_T ReadSpeedSnsr(int32_T fd);


#endif // _SPEED_SENSOR_H_

// EOF: speed_sensor.h
