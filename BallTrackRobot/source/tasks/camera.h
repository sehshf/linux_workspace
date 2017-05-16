/*
 * camera.h
 *
 *  Created on: 26/04/2017
 *      Author: ses
 */


#ifndef _CAMERA_H_
#define _CAMERA_H_

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
#include "rt_tasks.h"
#include "computer_vision.h"

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
typedef struct
{
	ballLoc_T ballLoc;
} cameraOutputs_T;


/*
 * **************************************************
 * External VARIABLES       						*
 * **************************************************
 */
extern cameraOutputs_T cameraOutputs;



/*
 * **************************************************
 * PROTOTYPES										*
 * **************************************************
 */
void RunCamera(uint16_T period);


#endif // _CAMERA_H_

// EOF: camera.h
