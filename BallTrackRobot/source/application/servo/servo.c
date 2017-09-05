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
static void ServoHandler(servoInputs_T *inputs);


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

	// Get the servo component inputs
	GetServoInputs(&inputs);

	// Handle servo tasks
	ServoHandler(&inputs);

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
static void ServoHandler(servoInputs_T *inputs)
{
	ServoControl(inputs->vision, inputs->loc);

} // END: ServoHandler()


// EOF: servo.c

