/*
 * irt_sensor.c
 *
 *  Created on: 26/10/2016
 *      Author: ses
 */


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "irt_sensor.h"


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
// File descriptor for I2C communication
static int32_T  fd;


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
*      INITIRTSNSR()
*      Initializing IR temperature sensor.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Oct 2016
*  -------------------------------------------------------  *
*/
void InitIRTSnsr(void)
{

	fd = AccessI2CBus((const char *)I2C_FILE, IRTSNSR_ADDR);

} // END: InitIRTSnsr()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      READIRTSNSR()
*      Reading IR temperature sensor.
*
*  Inputs:
*      reg : Device register; defined in irt_sensor.h
*
*  Outputs:
*      temp : temperature [°C].
*
*  Author: Ehsan Shafiei
*  		   Nov 2016
*  -------------------------------------------------------  *
*/
real32_T ReadIRTSnsr(uint8_T reg)
{
	real32_T temp;

	temp = wiringPiI2CReadReg16(fd, reg);

	temp = temp * IRT_RES - KELVIN_CON;

	return temp;

} // END: ReadIRTSnsr()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      LOCALFUCTION()
*      What this function is doing.
*
*  Inputs:
*      x : Input
*
*  Outputs:
*      y : Returns 0 when succeeded.
*
*  Author: Ehsan Shafiei
*  		   Aug 2016
*  -------------------------------------------------------  *
*/
//static type LocalFunction(type x)
//{
//    return y;
//} // END: LocalFunction()

// EOF: irt_sensor.c
