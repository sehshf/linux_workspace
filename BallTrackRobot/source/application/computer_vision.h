/*
 * computer_vision.h
 *
 *  Created on: Feb 3, 2017
 *      Author: ses
 */

#ifndef _COMPUTER_VISION_H_
#define _COMPUTER_VISION_H_


/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <cv.h>
#include <highgui.h>
#include <opencv2/opencv.hpp>

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
#define CV_SIZE_W   640
#define CV_SIZE_H   480

//#define H_MIN	30
//#define H_MAX	64
//#define S_MIN	86
//#define S_MAX	255
//#define V_MIN	34
//#define V_MAX	255


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
// HSV filter
typedef enum
{
	H_MIN,
	H_MAX,
	S_MIN,
	S_MAX,
	V_MIN,
	V_MAX,
	HSV_LEN
} HSV_FILT;


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
void BallFiltTune(IplImage *img, int32_T x, int32_T y);


#endif // _COMPUTER_VISION_H_

// EOF: computer_vision.h

