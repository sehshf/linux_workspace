/*
 * params.h
 *
 *  Created on: Apr 27, 2017
 *      Author: ses
 */

#ifndef _PARAMS_H_
#define _PARAMS_H_

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "portable.h"


/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */



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
// "motors" component calibration parameters
struct MOTORS_TAG
{
	real32_T Kpan ;
	real32_T Ktilt;
};

extern struct MOTORS_TAG MOTORS_C;


// "camera" component calibration parameters
struct CAMERA_TAG
{
	int32_T hsv[6];
};

extern struct CAMERA_TAG CAMERA_C;

#endif // _PARAMS_H_

// EOF: params.h
