/*
 * camera.c
 *
 *  Created on: 26/04/2017
 *      Author: ses
 */


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "camera.h"


/*
 * **************************************************
 * LOCAL DECLARATIONS								*
 * **************************************************
 */



/*
 * **************************************************
 * GLOBAL VARIABLES (extern)						*
 * **************************************************
 */
cameraOutputs_T cameraOutputs = { .ballLoc = {.x = 0, .y = 0} };


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
void UpdateCameraOutputs(cameraOutputs_T *outputs);


/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      RUNCAMERA()
*      Run camera task.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*		   Apr 2017
*  -------------------------------------------------------  *
*/
void RunCamera(uint16_T period)
{
	static real32_T count = 0;

	cameraOutputs_T outputs;

	boolean_T 	dtcdFlag = FALSE;
	IplImage 	*img, *imgFild;
	int8_T 		nDtcn = 0;

	count++;
	if (count == period / baseTs)
	{
		count = 0;
		do
		{
			img = cvQueryFrame(capture);
		} while (img == NULL);

		imgFild = FiltBall(img);

		dtcdFlag = FindBall(imgFild, &(outputs.ballLoc));

		if (dtcdFlag)
			nDtcn = nDtcn + dtcdFlag;
		else
			nDtcn = 0;

		if (nDtcn > 1)
		{
			nDtcn = 0;
			// Update the component outputs
			UpdateCameraOutputs(&outputs);
		}
	}

} // END: RunCamera()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      UPDATECAMEAOUTPUTS()
*      Update the outputs of the "camera" component.
*
*  Inputs:
*      *outputs : Pointer to the output values
*
*  Author: Ehsan Shafiei
*  		   Apr 2017
*  -------------------------------------------------------  *
*/
void UpdateCameraOutputs(cameraOutputs_T *outputs)
{
	pthread_mutex_lock(task[CAMERA_TASK].mutex);
	cameraOutputs = *outputs;
	pthread_mutex_unlock(task[CAMERA_TASK].mutex);

} // END: UpdateCameraOutputs()

// EOF: camera.c
