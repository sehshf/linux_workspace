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
CvCapture *capture;


/*
 * **************************************************
 * FILE SCOPE VARIABLES (static)					*
 * **************************************************
 */
// Minimum and maximum object area for the ball
static const int32_T AREA_MIN = 60 * 60;
static const int32_T AREA_MAX = 350 * 350;


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
*      INITCAMERA()
*      Initializing the camera.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Apr 2017
*  -------------------------------------------------------  *
*/
void InitCamera(void)
{
	system("sudo modprobe bcm2835-v4l2");
	usleep(50000);

	printf("Start video capturing\n");
	capture =  cvCreateCameraCapture(0);

} // END: InitCamera()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      EXITCAMERA()
*      Release camera capture.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Apr 2017
*  -------------------------------------------------------  *
*/
void ExitCamera(void)
{
	cvReleaseCapture(&capture);

} // END: ExitCamera()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      TUNEBALLFILT()
*      Tuning the tennis ball color filtering.
*
*  Inputs:
*       *img: Input image including a tennis ball
*          x: Horizontal location of the image window
           y: Vertical location of the image window
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Feb 2017
*  -------------------------------------------------------  *
*/
void TuneBallFilt(IplImage *img, int32_T x, int32_T y)
{
	static IplImage *imgTmp = cvCreateImage(CvSize(CV_SIZE_W, CV_SIZE_H), IPL_DEPTH_8U, 3);

	static int32_T hsvArr[] = {30, 64, 86, 255, 34, 255};

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

	// Filter the image within the HSV range
	cvInRangeS(imgTmp, cvScalar(hsvArr[H_MIN], hsvArr[S_MIN], hsvArr[V_MIN]),
	                   cvScalar(hsvArr[H_MAX], hsvArr[S_MAX], hsvArr[V_MAX]), imgTmp);

	// Show images
	cvShowImage("imgWindow" , img );
	cvShowImage("ballWindow", imgTmp);

	// Wait for a key
	cvWaitKey(30);

} // END: TuneBallFilt()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      FILTBALL()
*      Tennis ball color filtering. The input image is affected
*      by this function. If needed, make a copy before calling this.
*
*  Inputs:
*       *img: Input image including a tennis ball
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*          Feb 2017
*  -------------------------------------------------------  *
*/
IplImage *FiltBall(IplImage *img)
{
	static IplImage *imgTmp  = cvCreateImage(CvSize(CV_SIZE_W, CV_SIZE_H), IPL_DEPTH_8U, 3);
    static IplImage *imgFild = cvCreateImage(CvSize(CV_SIZE_W, CV_SIZE_H), IPL_DEPTH_8U, 1);

    // Covert image color to HSV color space
    cvCvtColor(img, imgTmp, CV_BGR2HSV);

    // Filter the image within the HSV range
    cvInRangeS( imgTmp,
    			cvScalar(CAMERA_HSV_C[H_MIN], CAMERA_HSV_C[S_MIN], CAMERA_HSV_C[V_MIN]),
                cvScalar(CAMERA_HSV_C[H_MAX], CAMERA_HSV_C[S_MAX], CAMERA_HSV_C[V_MAX]),
				imgFild
			  );

    return imgFild;

} // END: FiltBall()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      FINDBALL()
*      Find a tennis ball in a filtered binary image.
*
*  Inputs:
*       *img: Filtered image of a tennis ball
*       *loc: Pointer to a location struct. This function
*             retrieves the ball location from the input image.
*
*  Outputs:
*       find: Flag indicating if the ball is found.
*
*  Author: Ehsan Shafiei
*          Feb 2017
*  -------------------------------------------------------  *
*/
boolean_T FindBall(IplImage *img, targetObj_T *ball)
{
    static IplImage* imgTmp = cvCreateImage(CvSize(CV_SIZE_W, CV_SIZE_H), IPL_DEPTH_8U, 1);

    static int32_T         numCont;                             // number of contours
    static CvMemStorage    *storage = cvCreateMemStorage(0);    // storage block for contours
    static CvSeq           *firstCont = NULL;                   // first contour in a sequence
    static CvMoments       moment;                              // special and central moment

    int32_T     area, lastArea = 0;
    boolean_T   find = FALSE;

    cvCopy(img, imgTmp, NULL);

    numCont = cvFindContours(imgTmp, storage, &firstCont);

    if (numCont > 0)
    {
        for (; firstCont != NULL; firstCont = firstCont->h_next)
        {
            cvMoments(firstCont, &moment, 0);

            // Calculate the object area
            area = moment.m00;

            // Check if it can be the ball
            if (area > AREA_MIN && area < AREA_MAX && area > lastArea)
            {
                ball->x = (int32_T)(moment.m10 / moment.m00);
                ball->y = (int32_T)(moment.m01 / moment.m00);
                ball->area = area;

                lastArea  = area;
                find = TRUE;
            }
        }
    }

    return find;

} // END: FindBall()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      BALLAREA()
*      Filter the ball area signal.
*
*  Inputs:
*       area: Ball area raw signal
*
*  Outputs:
*       areaFilt: Filtered ball area. Simple moving average
*        		  filter applied.
*
*  Author: Ehsan Shafiei
*          Aug 2017
*  -------------------------------------------------------  *
*/
real32_T BallArea(int32_T area)
{
	real32_T areaNorm, areaFilt;
	static moveAvr_T areaObj = {.n = 10, .val = 0, .avr = 0};

	// Normalize the signal to 0-100%
	areaNorm    = (real32_T)(area - AREA_MIN) / (AREA_MAX - AREA_MIN) * 100;

	areaObj.val = areaNorm;

	SimpleMovingAverage(&areaObj);

	areaFilt = (real32_T)areaObj.avr;

	return areaFilt;
}


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


