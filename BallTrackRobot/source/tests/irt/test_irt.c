/*
 * test_irt.c
 *
 *  Created on: 26/10/2016
 *      Author: ses
 */


/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <stdio.h>


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "portable.h"
#include "irt_sensor.h"

int main(void)
{
	real32_T temp;
	int8_T reg;

	InitIRTSnsr();

	printf("Reading temperature:\n");
	printf("Enter 'a' for ambient or 'o' for object:\n");

	scanf("%c", &reg);

	switch (reg)
	{
	case 'a':
		reg = TAMB_REG;
		break;

	case 'o':
		reg = TOBJ_REG;
		break;

	default:
		reg = TAMB_REG;
		printf("Ambient temperature:\n");
		break;
	}

	temp = ReadIRTSnsr(reg);

	printf("%f\n", temp);


    return PASSED;
} // END: main()


// EOF: test_irt.c
