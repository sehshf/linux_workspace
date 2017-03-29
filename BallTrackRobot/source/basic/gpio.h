/*
 * gpio.h
 *
 *  Created on: Mar 29, 2017
 *      Author: ses
 */

#ifndef _GPIO_H_
#define _GPIO_H_

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "portable.h"

/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
enum {GPIO_IN ,
	  GPIO_OUT,
	  GPIO_ALT
	 };

#define MMAP_GPIO_SIZE   (4 * 1024)
#define PERI_BASE_ADR    0x3F000000    					// BCM2838 Peripheral starting address
#define GPIO_BASE_ADR    (PERI_BASE_ADR + 0x200000)    	// GPIO starting address
#define GPIO_SET			 7								// GPIO pin output set, IOs 0-31
#define GPIO_CLR			 10								// GPIO pin output clear, IOs 0-31
#define GPIO_LVL 			 13 							// GPIO Pin Level, IOs 0-31

/*
 * **************************************************
 * MACROS											*
 * **************************************************
 */



/*
 * **************************************************
 * TYPE DEFINITIONS									*
 * **************************************************
 */



/*
 * **************************************************
 * External VARIABLES       						*
 * **************************************************
 */




/*
 * **************************************************
 * PROTOTYPES										*
 * **************************************************
 */
volatile uint32_T *MemMapGPIO(void);
void ConfigGPIO(volatile uint32_T *mmapAdr, uint16_T gpio, uint16_T flag, uint16_T alt);
void MemUnMapGPIO(void *pMap, int32_T fd);
void SetGPIO(volatile uint32_T *mmapAdr, uint16_T gpio);
void ClrGPIO(volatile uint32_T *mmapAdr, uint16_T gpio);
boolean_T ReadGPIO(volatile uint32_T *mmapAdr, uint16_T gpio);


#endif // _GPIO_H_

// EOF: gpio.h
