/*
 * main.c
 *
 *  Created on: Apr 5, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "portable.h"
#include "computer_vision.h"


int main(int argc, char *argv[])
{
	boolean_T dtcdFlag = FALSE;
	ballLoc_T loc;
	IplImage *img, *imgFild;

	clock_t tic, toc;
	real32_T dt;

	int8_T  buf1[256], buf2[256], *str1, *str2, *dispNum;
	int8_T  disp[2];
	int32_T len, i;

	system("sudo modprobe bcm2835-v4l2");
	usleep(50000);

	FILE *fp = popen("xauth list $DISPLAY", "r");
	fgets(buf1, 255, fp);
	pclose(fp);

	str1 = strchr(buf1, ':');
	str2 = strchr(buf1, ' ');

	len = strlen(str1) - strlen(str2) - 1;

	for (i = 0; i < len; i++)
		disp[i] = str1[i + 1];

	dispNum = strrchr(buf1, ' ');

	memset(buf2, 0, sizeof(buf2));
	strcpy(buf2, "DISPLAY=:");
	strcat(buf2, disp);
	strcat(buf2, "; export DISPLAY");
	system(buf2);

	memset(buf2, 0, sizeof(buf2));
	strcpy(buf2, "xauth add $DISPLAY . ");
	strcat(buf2, dispNum + 1);
	system(buf2);

	printf("Start video capturing\n");
	CvCapture *capture =  cvCreateCameraCapture(0);

	cvNamedWindow("piWindow", CV_WINDOW_AUTOSIZE);
	cvMoveWindow ("piWindow", 400, 500);

	cvNamedWindow("filtWindow", CV_WINDOW_AUTOSIZE);
	cvMoveWindow ("filtWindow", 1100, 500);

	int32_T hsv[6];

	tic = clock();
	toc = clock();
	dt = (real32_T)(toc - tic) / CLOCKS_PER_SEC;


//	for (i = 0; i < 6; i++)
//		hsv[i] = atoi(argv[i + 1]);

	while(1)
	{
		img = cvQueryFrame(capture);

		img = cvQueryFrame(capture);

		imgFild = FiltBall(img, &hsv[0]);

		dtcdFlag = FindBall(imgFild, &loc, FIND_CONTOUR);

		if (dtcdFlag)
		{
			cvCircle(img, CvPoint(loc.x, loc.y), 5, CV_RGB(255, 0, 0));

//			printf("x = %d, y = %d\n", loc.x, loc.y);
		}


		cvShowImage("piWindow"  , img);
		cvShowImage("filtWindow", imgFild);

		// wait for a key
		cvWaitKey(30);
	}

	cvReleaseCapture(&capture);

	return PASSED;

} // END: main()

// EOF: main.c
