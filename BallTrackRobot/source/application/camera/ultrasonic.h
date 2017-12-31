/*
 * ultrasonic.h
 *
 *  Created on: Dec 30, 2017
 *      Author: ses
 */


#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

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
#include "portable.h"
#include "gpio.h"


/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
#define ULTRASONIC_TRIG_PIN		19
#define ULTRASONIC_ECHO_PIN		16

// Ultrasonic sensor enumeration
enum
{
	ULTRASONIC_TRIG,
	ULTRASONIC_ECHO,
	NUM_ULTRASONIC_PIN
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
void 	 InitUltrasonicSnsrs(void);
real32_T ReadDistance(void);


#endif // _ULTRASONIC_H_

// EOF: ultrasonic.h

