/*
 * computer_vision.c
 *
 *  Created on: Feb 3, 2017
 *      Author: ses
 */


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "computer_vision.h"

/*
 * **************************************************
 * GLOBAL VARIABLES (extern)						*
 * **************************************************
 */



/*
 * **************************************************
 * FILE SCOPE VARIABLES (static)					*
 * **************************************************
 */



/*
 * **************************************************
 * LOCAL PROTOTYPES									*
 * **************************************************
 */



/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */

/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      INITSERVOS()
*      Initializing the servo motors.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Oct 2016
*  -------------------------------------------------------  *
*/
void BallFiltTune(IplImage *img, int32_T x, int32_T y)
{
	static IplImage* imgTmp = cvCreateImage(CvSize(CV_SIZE_W, CV_SIZE_H), IPL_DEPTH_8U, 3);

	static int32_T hsvArr[HSV_LEN + 1] = {30, 64, 86, 255, 34, 255};

	// Create image window
	cvNamedWindow("imgWindow", CV_WINDOW_AUTOSIZE);
	cvMoveWindow ("imgWindow", x, y);

	cvNamedWindow("ballWindow", CV_WINDOW_AUTOSIZE);
	cvMoveWindow ("ballWindow", x + CV_SIZE_W, y);

	cvNamedWindow("barWindow", CV_WINDOW_AUTOSIZE);
	cvMoveWindow ("barWindow", x + CV_SIZE_W, y + CV_SIZE_H);

	// Create track bars for the filter manual tuning
	cvCreateTrackbar("H1", "barWindow", &hsvArr[H_MIN], MAX_UINT8, 0);
	cvCreateTrackbar("H2", "barWindow", &hsvArr[H_MAX], MAX_UINT8, 0);
	cvCreateTrackbar("S1", "barWindow", &hsvArr[S_MIN], MAX_UINT8, 0);
	cvCreateTrackbar("S2", "barWindow", &hsvArr[S_MAX], MAX_UINT8, 0);
	cvCreateTrackbar("V1", "barWindow", &hsvArr[V_MIN], MAX_UINT8, 0);
	cvCreateTrackbar("V2", "barWindow", &hsvArr[V_MAX], MAX_UINT8, 0);

	// Covert image color to HSV color space
	cvCvtColor(img, imgTmp, CV_BGR2HSV);

	cvInRangeS(imgTmp, cvScalar(hsvArr[H_MIN], hsvArr[S_MIN], hsvArr[V_MIN]),
	                   cvScalar(hsvArr[H_MAX], hsvArr[S_MAX], hsvArr[V_MAX]), imgTmp);

	cvShowImage("imgWindow" , img );
	cvShowImage("ballWindow", imgTmp);

	// Wait for a key
	cvWaitKey(30);

} // END: BallFiltTune()





/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      PUBLICFUCTION()
*      What this function is doing.
*
*  Inputs:
*      x : Input
*
*  Outputs:
*      y : Return 0 when succeeded.
*
*  Author: Ehsan Shafiei
*  		   Aug 2016
*  -------------------------------------------------------  *
*/
//static type LocalFunction(type x)
//{
//    return y;
//} // END: LocalFunction()


// EOF: computer_vision.c


