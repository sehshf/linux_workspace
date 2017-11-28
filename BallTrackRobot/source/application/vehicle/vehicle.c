/*
 * vehicle.c
 *
 *  Created on: 26/04/2017
 *      Author: ses
 */


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "vehicle.h"


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
static void GetVehicleInputs(vehicleInputs_T *inputs);
static void VehicleHandler(vehicleInputs_T *inputs);


/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      INITVEHICLE()
*      Run vehicle task.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*		   Apr 2017
*  -------------------------------------------------------  *
*/
void InitVehicle(void)
{
	InitWheels();

} // END: InitVehicle()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      RUNVEHICLE()
*      Run vehicle task.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*		   Apr 2017
*  -------------------------------------------------------  *
*/
void RunVehicle(uint16_T period)
{
	vehicleInputs_T inputs;

	// Get the vehicle component inputs
	GetVehicleInputs(&inputs);

	// Handle vehicle tasks
	VehicleHandler(&inputs);

} // END: RunVehicle()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      GETVEHICLEINPUTS()
*      Get the inputs to the "vehicle" component.
*
*  Inputs:
*      *inputs : Pointer to the input values
*
*  Author: Ehsan Shafiei
*  		   Apr 2017
*  -------------------------------------------------------  *
*/
static void GetVehicleInputs(vehicleInputs_T *inputs)
{
	inputs->vision = cameraOutputs.ball.detcd;
	inputs->vehPos = BallArea(cameraOutputs.ball.area);
	inputs->panPos = servoOutputs.panPos;

} // END: GetVehicleInputs()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      VEHICLEHANDLER()
*      Handle vehicle functions.
*
*  Inputs:
*      *inputs : Pointer to the input values
*
*  Author: Ehsan Shafiei
*  		   Aug 2017
*  -------------------------------------------------------  *
*/
static void VehicleHandler(vehicleInputs_T *inputs)
{
	VehiclePositionControl(inputs->vision, inputs->vehPos, inputs->panPos);

} // END: VehicleHandler()


// EOF: vehicle.c
