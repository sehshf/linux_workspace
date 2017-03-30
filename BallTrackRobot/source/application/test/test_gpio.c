/*
 * test_gpio.c
 *
 *  Created on: Mar 29, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <stdio.h>
#include <unistd.h>

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "gpio.h"

int main(void)
{
	volatile uint32_T *mmapAdr;
	uint16_T Out1 = GPIO(21), In1 = GPIO(20);
	boolean_T b = TRUE;

	mmapAdr = MemMapGPIO();
	ConfigGPIO(mmapAdr, Out1, GPIO_OUT, 0);
	ConfigGPIO(mmapAdr, In1, GPIO_IN , 0);

	while(1)
    {
		SetGPIO(mmapAdr, Out1);
		b = ReadGPIO(mmapAdr, In1);
		printf("Toggle = %d\n", b);
		sleep(2);

		ClrGPIO(mmapAdr, Out1);
		b = ReadGPIO(mmapAdr, In1);
		printf("Toggle = %d\n", b);
		sleep(2);
    }

    return PASSED;
} // END: main()

// EOF: test_gpio.c
