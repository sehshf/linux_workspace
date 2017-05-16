/*
 * params.c
 *
 *  Created on: Apr 27, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "params.h"


/*
 * **************************************************
 * GLOBAL VARIABLES (extern)						*
 * **************************************************
 */
/*
 * Calibration/Tuning parameters
 */
// "motors" component
real32_T *MOTORS_Kpan;
real32_T *MOTORS_Ktilt;

// "camera" component
int32_T  *CAMERA_HSV;


/*
 * **************************************************
 * FILE SCOPE VARIABLES (static)					*
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
*      INITPARAMADDR()
*      Initialize the memory address of the parameters
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
void InitParamAddr(void)
{
	// Array of memory addresses for parameters
	uint32_T *paramAddr = (uint32_T *)CAL_ADDR;
	uint32_T n = 0;

	MOTORS_Kpan  	= (real32_T *)&paramAddr[n];	n += WORD(1);		// 0x20000000
	MOTORS_Ktilt  	= (real32_T *)&paramAddr[n];	n += WORD(1);		// 0x20000004
	CAMERA_HSV 		= (int32_T  *)&paramAddr[n];	n += WORD(6);		// 0x20000008
	// 0x20000022

} // END: InitParamAddr()


/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      INITPARAMADDR()
*      Initialize the memory address of the parameters
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
void InitParamVal(void)
{
	// "motors" component
	*MOTORS_Kpan  	= 0.04f;
	*MOTORS_Ktilt  	= 0.04f;

	// "camera" component
	CAMERA_HSV[0] 	= 22;
	CAMERA_HSV[1] 	= 50;
	CAMERA_HSV[2] 	= 20;
	CAMERA_HSV[3] 	= 255;
	CAMERA_HSV[4] 	= 50;
	CAMERA_HSV[5] 	= 255;

} // END: InitParamVal()



// EOF: params.c
