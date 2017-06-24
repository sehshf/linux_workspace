/*
 * calibration.h
 *
 *  Created on: May 4, 2017
 *      Author: ses
 */

#ifndef _CALIBRATION_H_
#define _CALIBRATION_H_

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "portable.h"
#include "params.h"
#include "tcpip.h"


/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
// Calibration protocol
/*
 * | Start | Address | Flag | Length | Value | End |
 */
#define CAL_STRT_ID 		0x55
#define CAL_END_ID 			0x99
#define CAL_BUF_SIZE 		256
#define CAL_ADDR_BYTES		4		// Length of address in bytes
#define CAL_FIXED_BYTES		8		// NUmber of fixed bytes in protocol

// Protocol byte indices
#define CAL_START_IDX		0
#define CAL_ADDR_IDX		1
#define CAL_FLAG_IDX		5
#define CAL_LENGTH_IDX		6
#define CAL_VALUE_IDX		7

enum
{
	GET_PARAM,
	SET_PARAM,
	SAVE_PARAM
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
void RunCalibration(void);


#endif // _CALIBRATION_H_

// EOF: calibration.h
