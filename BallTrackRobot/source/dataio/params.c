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
	int32_T *addr, fd;

	// Memory map for parameters
	fd 	 = open("/dev/zero", O_RDWR);
	addr = (int32_T *)mmap((void *)PARAMS_ADDR, 256, PROT_WRITE | PROT_WRITE, MAP_PRIVATE, fd, 0);

	if (addr == MAP_FAILED)
		fprintf(stderr, "Mapping failed\n");

	// Array of memory addresses for parameters
	uint32_T *paramAddr = (uint32_T *)PARAMS_ADDR;
	uint32_T n = 0;

	// Add new parameter to the bottom of the list
	MOTORS_Kpan  	= (real32_T *)&paramAddr[n];	n += WORD(1);		// 0x20000000
	MOTORS_Ktilt  	= (real32_T *)&paramAddr[n];	n += WORD(1);		// 0x20000004
	CAMERA_HSV		= (int32_T  *)&paramAddr[n];	n += WORD(6);		// 0x20000008
	// 0x20000020

} // END: InitParamAddr()


/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      INITPARAMVAL()
*      Default values for the parameters
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
	*MOTORS_Kpan  	= 0.14f;
	*MOTORS_Ktilt  	= 0.13f;

	// "camera" component
	CAMERA_HSV[0] 	= 30;
	CAMERA_HSV[1] 	= 64;
	CAMERA_HSV[2] 	= 86;
	CAMERA_HSV[3] 	= 255;
	CAMERA_HSV[4] 	= 34;
	CAMERA_HSV[5] 	= 255;

	FILE *fd;
	char *dest = (char *)PARAMS_ADDR;
	char src[PARAMS_SIZE];

	// check if the parameter file exists
	if (access(paramFile, F_OK) < 0)
	{
		printf("%s does not exist.\n", paramFile);
		return;
	}

	// Open the parameter files
	fd = fopen(paramFile, "r");
	if (fd == NULL)
		fprintf(stderr, "Failed to open the parameter file\n");


	// Read the parameters value
	if (fread(src, 1, PARAMS_SIZE, fd) != PARAMS_SIZE)
		fprintf(stderr, "Failed to read the parameter file\n");

	// Copy the parameter values into a specific memory area
	memcpy(dest, src, PARAMS_SIZE);

	fclose(fd);

} // END: InitParamVal()



// EOF: params.c
