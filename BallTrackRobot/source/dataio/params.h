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
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

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
// Parameter file
#define paramFile 			"/home/pi/params"

// Calibration/tuning parameters memory address
#define PARAMS_ADDR 		0x20000000
#define PARAMS_SIZE			0x20

// Address steps for 8-byte and 16-byte data
#define WORD(x) 			((x) * 1)

/*
 * Calibration/Tuning parameters
 */
// "motors" component
#define MOTORS_Kpan_C 		*MOTORS_Kpan
#define MOTORS_Ktilt_C 		*MOTORS_Ktilt


// "camera" component
#define CAMERA_HSV_C		CAMERA_HSV		// array



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
 * Calibration/Tuning parameters
 */
// "motors" component
extern real32_T *MOTORS_Kpan;
extern real32_T *MOTORS_Ktilt;



// "camera" component
extern int32_T 	*CAMERA_HSV;


/*
 * **************************************************
 * PROTOTYPES										*
 * **************************************************
 */
void InitParamAddr(void);
void InitParamVal(void);

#endif // _PARAMS_H_

// EOF: params.h
