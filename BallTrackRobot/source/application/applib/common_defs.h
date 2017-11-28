/*
 * common_defs.h
 *
 *  Created on: Sep 5, 2017
 *      Author: ses
 */

#ifndef _COMMON_DEFS_H_
#define _COMMON_DEFS_H_

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
#define LEFT_SIDE 				0
#define RIGHT_SIDE 				1
#define FRONT_SIDE 				2
#define REAR_SIDE 				3

#define FORWARD_DIRECTION 		0
#define BACKWARD_DIRECTION 		1
#define LEFT_DIRECTION 			2
#define RIGHT_DIRECTION 		3


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
// Location
typedef struct
{
	real32_T x;
	real32_T y;
} loc_T;


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



#endif // _COMMON_DEFS_H_

// EOF: common_defs.h
