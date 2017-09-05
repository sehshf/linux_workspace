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
#include <unistd.h>
#include <cv.h>
#include <highgui.h>
#include <opencv2/opencv.hpp>
#include <time.h>


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "portable.h"
#include "common_defs.h"
#include "params.h"
#include "signal_processing.h"


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
};

// Target Object
typedef struct
{
	boolean_T detcd;
	int32_T area;
	int32_T x;
    int32_T y;
} targetObj_T;


/*
 * **************************************************
 * External VARIABLES       						*
 * **************************************************
 */
extern CvCapture *capture;



/*
 * **************************************************
 * PROTOTYPES										*
 * **************************************************
 */
void InitCamera(void);
void ExitCamera(void);

void TuneBallFilt(IplImage *img, int32_T x, int32_T y);

IplImage *FiltBall(IplImage *img);

void FindBall(IplImage *img, targetObj_T *ball);

real32_T BallArea(int32_T area);

loc_T BallLocation(int32_T x, int32_T y);

#endif // _COMPUTER_VISION_H_

// EOF: computer_vision.h

