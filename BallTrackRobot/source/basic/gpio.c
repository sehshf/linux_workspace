/*
 * gpio.c
 *
 *  Created on: Mar 29, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "gpio.h"


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



/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      MEMMAPGPIO()
*      Open "/dev/mem" file containing GPIO registers and
*      map it to memory.
*
*  Inputs:
*
*  Outputs:
*		pMap : returns starting address of mapping
*
*  Author: Ehsan Shafiei
*  		   Mar 2017
*  -------------------------------------------------------  *
*/
volatile uint32_T *MemMapGPIO(void)
{
	int32_T fd;
	void *pMap;

	// Open /dev/mem
	fd = open("/dev/mem", O_RDWR|O_SYNC);
	if (fd < 0)
	{
		fprintf(stderr, "Failed to open /dev/mem.\n");
		exit(EXIT_FAILURE);
	}
	pMap = mmap(NULL, MMAP_GPIO_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE_ADR);

	return (volatile uint32_T *)pMap;

} // END: MemMapGPIO()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      CONFIGGPIO()
*      Configure GPIO as input, output or an alternative.
*
*  Inputs:
*  		*mmapAdr : pointer to the GPIO mapped adress.
*  		gpio 	 : gpio number
*  		flag 	 : flag specifying the configuration type
*  		alt 	 : alternative type number
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Mar 2017
*  -------------------------------------------------------  *
*/
void ConfigGPIO(volatile uint32_T *mmapAdr, uint16_T gpio, uint16_T flag, uint16_T alt)
{
	// Clear the bit field. This also configures the GPIO as an input.
	*(mmapAdr + (gpio / 10)) &= ~(7 << ((gpio % 10) * 3));

	switch (flag)
	{
	case GPIO_IN:
		break;
	case GPIO_OUT:
		*(mmapAdr + (gpio / 10)) |=  (1 << ((gpio % 10) * 3));
		break;
	case GPIO_ALT:
		*(mmapAdr + (gpio / 10)) |=  ((alt <= 3 ? alt + 4 : alt == 4 ? 3 : 2) << ((gpio % 10) * 3));
		break;
	}
} // END: ConfigGPIO()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      MEMUNMAPGPIO()
*      Unmap the memory assigned to GPIO.
*
*  Inputs:
*  		*pMap : starting address of mapping returned by mmap()
*  		fd	  : memory mapped file descriptor
*
*  Outputs:*
*
*  Author: Ehsan Shafiei
*  		   Mar 2017
*  -------------------------------------------------------  *
*/
void MemUnMapGPIO(void *pMap, int32_T fd)
{
	munmap(pMap, MMAP_GPIO_SIZE);
	close(fd);

} // END: MemUnMapGPIO()

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

// EOF: gpio.c


