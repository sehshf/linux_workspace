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
#include <stdlib.h>
#include <cv.h>
#include <highgui.h>
#include <opencv2/opencv.hpp>

#include <time.h>
#include <stdio.h>

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
enum
{
	H_MIN,
	H_MAX,
	S_MIN,
	S_MAX,
	V_MIN,
	V_MAX,
	HSV_LEN
};

// Ball detection method
enum
{
	FIND_CONTOUR,
	FIND_CIRCLES
};

// Ball location
typedef struct
{
    int32_T x;
    int32_T y;
} ballLoc_T;

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
void TuneBallFilt(IplImage *img, int32_T x, int32_T y);

IplImage *FiltBall(IplImage *img, int32_T *arr);

boolean_T FindBall(IplImage *img, ballLoc_T *loc, uint8_T method);

#endif // _COMPUTER_VISION_H_

// EOF: computer_vision.h

