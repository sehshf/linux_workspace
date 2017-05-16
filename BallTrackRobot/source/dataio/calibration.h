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
#include <errno.h>

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
