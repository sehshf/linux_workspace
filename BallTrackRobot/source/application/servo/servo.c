/*
 * servo.c
 *
 *  Created on: Sep 2, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "servo.h"


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
servoOutputs_T servoOutputs = {.panPos = 0, .tiltPos = 0};


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
static void GetServoInputs(servoInputs_T *inputs);
static void UpdateServoOutputs(servoOutputs_T *outputs);
static void ServoHandler(servoInputs_T *inputs, servoOutputs_T *outputs);


/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      RUNSERVOS()
*      Run servo task.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*		   Apr 2017
*  -------------------------------------------------------  *
*/
void RunServos(uint16_T period)
{
	servoInputs_T inputs;
	static servoOutputs_T outputs;

	// Get the servo component inputs
	GetServoInputs(&inputs);

	// Handle servo tasks
	ServoHandler(&inputs, &outputs);

	// Update the component outputs
	UpdateServoOutputs(&outputs);

} // END: RunServos()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      GETSERVOINPUTS()
*      Get the inputs to the "servo" component.
*
*  Inputs:
*      *inputs : Pointer to the input values
*
*  Author: Ehsan Shafiei
*  		   Apr 2017
*  -------------------------------------------------------  *
*/
static void GetServoInputs(servoInputs_T *inputs)
{
	inputs->vision = cameraOutputs.ball.detcd;
	inputs->loc	   = BallLocation(cameraOutputs.ball.x, cameraOutputs.ball.y);

} // END: GetServoInputs()


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
static void UpdateServoOutputs(servoOutputs_T *outputs)
{
	pthread_mutex_lock(&(task[CAMERA_TASK].mutex));
	servoOutputs = *outputs;
	pthread_mutex_unlock(&(task[CAMERA_TASK].mutex));

} // END: UpdateCameraOutputs()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      SERVOHANDLER()
*      Handle servo tasks.
*
*  Inputs:
*      *inputs : Pointer to the input values
*
*  Author: Ehsan Shafiei
*  		   Aug 2017
*  -------------------------------------------------------  *
*/
static void ServoHandler(servoInputs_T *inputs, servoOutputs_T *outputs)
{
	ServoControl(inputs->vision, inputs->loc);

	outputs->panPos  = GetServoPos(PAN_SERVO );
	outputs->tiltPos = GetServoPos(TILT_SERVO);

} // END: ServoHandler()


// EOF: servo.c

