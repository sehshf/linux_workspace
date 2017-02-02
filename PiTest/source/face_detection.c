/*
 * face_detection.c
 *
 *  Created on: Jan 17, 2017
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
#include <math.h>
#include <time.h>
#include <cv.h>
#include <highgui.h>
#include <opencv2/opencv.hpp>

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
//#include "portable.h"


//char *faceCascadeFilename = "/home/pi/haarcascade_frontalface_alt.xml";
CvMemStorage* storage = cvCreateMemStorage(0);

// Detect and draw detected object boxes on image
// Presumes 2 Globals:
// Cascade is loaded by:
// cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
// AND that storage is allocated:
// CvMemStorage* storage = cvCreateMemStorage(0);
//
void detect_and_draw(IplImage* img)
{
	double scale = 1.3;
	CvHaarClassifierCascade* faceCascade;
//	static CvScalar colors[] = {
//	{{0,0,255}}, {{0,128,255}},{{0,255,255}},{{0,255,0}},
//	{{255,128,0}},{{255,255,0}},{{255,0,0}}, {{255,0,255}}
//	}; //Just some pretty colors to draw with
	// IMAGE PREPARATION:
	//
	IplImage* gray = cvCreateImage( cvSize(img->width,img->height), 8, 1);
	IplImage* small_img = cvCreateImage(
	cvSize( cvRound(img->width/scale), cvRound(img->height/scale)), 8, 1);
	cvCvtColor( img, gray, CV_BGR2GRAY );
	cvResize( gray, small_img, CV_INTER_LINEAR );
	cvEqualizeHist( small_img, small_img );
	// DETECT OBJECTS IF ANY
	//
	// load an image
	printf("Loading cascade file\n");
	faceCascade = (CvHaarClassifierCascade*)cvLoad("/home/pi/haarcascade_frontalface_alt.xml", NULL, NULL, NULL);
	if( !faceCascade ) {
		printf("Couldn't load Face detector\n");
		exit(1);
	}

	printf("face detection\n");
	cvClearMemStorage( storage );
	clock_t start = clock();
	CvSeq* objects = cvHaarDetectObjects(
										small_img,
										faceCascade,
										storage,
										1.1,
										2,
										0 /*CV_HAAR_DO_CANNY_PRUNING*/,
										cvSize(30, 30)
										);
	clock_t end = clock();
	double detectTime = (double)(end - start) / CLOCKS_PER_SEC * 1000;
	printf("detection time = %lf ms\n", detectTime);

	// LOOP THROUGH FOUND OBJECTS AND DRAW BOXES AROUND THEM
	//
	printf("Drawing rectangle: %d \n", objects->total);
	for(int i = 0; i < (objects ? objects->total : 0); i++ ) {
		CvRect* r = (CvRect*)cvGetSeqElem( objects, i );
		cvRectangle(
		img,
		cvPoint(r->x,r->y),
		cvPoint(r->x+r->width,r->y+r->height),
		cvScalar(0, 255, 255, 0)
		);
		printf("Face width = %d, height = %d\n", r->width, r->height);
	}

	cvReleaseImage( &gray );
	cvReleaseImage( &small_img );
}




int main(int argc, char *argv[])
{
	printf("Start video capturing\n");
	CvCapture* capture =  cvCreateCameraCapture(0);

	IplImage* img = cvQueryFrame(capture);
	img = cvQueryFrame(capture);

//	// save image
//	printf("Saving image\n");
//	cvSaveImage("capture_1.png", img, 0);

	// face detection
	detect_and_draw(img);

	// save image
	printf("Showing image\n");
	cvNamedWindow("piWindow", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("piWindow", 100, 100);
	cvShowImage("piWindow", img);

	// wait for a key
	cvWaitKey(0);

	cvReleaseCapture(&capture);

	//return PASSED;
	return 0;

} // END: main()

// EOF: face_detection.c
