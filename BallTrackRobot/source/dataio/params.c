/*
 * params.c
 *
 *  Created on: Apr 27, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "params.h"


/*
 * **************************************************
 * GLOBAL VARIABLES (extern)						*
 * **************************************************
 */
// "motors" component calibration default values
struct MOTORS_TAG MOTORS_C = {
	.Kpan  = 0.04f,
	.Ktilt = 0.04f
	};

// "camera" component calibration default values
struct CAMERA_TAG CAMERA_C = {
	.hsv = {22, 50, 20, 255, 50, 255}
	};

// EOF: motors.c
