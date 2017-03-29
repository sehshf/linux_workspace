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
	uint16_T gpio = 21;

	mmapAdr = MemMapGPIO();
	ConfigGPIO(mmapAdr, gpio, GPIO_OUT, 0);

	while(1)
    {
		SetGPIO(mmapAdr, gpio);
		sleep(3);

		ClrGPIO(mmapAdr, gpio);
		sleep(3);
    }

    return PASSED;
} // END: main()

// EOF: test_gpio.c
