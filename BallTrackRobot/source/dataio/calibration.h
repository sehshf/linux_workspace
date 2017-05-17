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


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "portable.h"
#include "tcpip.h"


/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
// Calibration protocol
/*
 * | Start | Address | Length | Value | End |
 */
#define CAL_STRT_ID 		0x55
#define CAL_END_ID 			0x99
#define CAL_BUF_SIZE 		256
#define GET_FLAG			0
#define SET_FLAG			1
#define CAL_ADDR_BYTES		4		// Length of address in bytes
#define CAL_FIXED_BYTES		8		// NUmber of fixed bytes in protocol

// Protocol byte indices
#define CAL_START_IDX		0
#define CAL_ADDR_IDX		1
#define CAL_FLAG_IDX		5
#define CAL_LENGTH_IDX		6
#define CAL_VALUE_IDX		7



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
