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
static void AssignSysGPIOPin(uint8_T pin);

static void AssignSysGPIODirection(uint8_T pin, uint8_T direction);

static void AssignSysGPIOTrigger(uint8_T pin, uint8_T trigger);

static void AssignSysGPIOActvLow(uint8_T pin, boolean_T state);



/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */

/******************* DIRECT GPIO ********************/

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
*  Outputs:
*
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



/******************** SYSFS GPIO ********************/

/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      CONFIGSYSGPIO()
*      Configure GPIO through SYSFS files.
*
*  Inputs:
*  		*sysGPIO : GPIO struct.
*
*  Outputs:
*
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
void ConfigSysGPIO(sysGPIO_T *sysGPIO)
{
	// Assign the pin
	AssignSysGPIOPin(sysGPIO->pin);

	// Assign direction
	AssignSysGPIODirection(sysGPIO->pin, sysGPIO->direction);

	// Assign trigger
	AssignSysGPIOTrigger(sysGPIO->pin, sysGPIO->trigger);

	// Assign active_low
	AssignSysGPIOActvLow(sysGPIO->pin, sysGPIO->actvLow);

} // END: ConfigSysGPIO()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      OPENSYSGPIO()
*      Open SYSFS GPIO value file for read/write.
*
*  Inputs:
*  		pin : GPIO number
*
*  Outputs:
*		fd  : SYSFS GPIO value file descriptor
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
int32_T OpenSysGPIO(uint8_T pin)
{
	char	str[50];
	int32_T	fd;

	// Open value file
	sprintf(str, SYS_GPIO_VALUE, pin);
	fd = open(str, O_RDWR);
	if (fd < 0)
	{
		fprintf(stderr, "Failed to open GPIO value file.\n");
		exit(EXIT_FAILURE);
	}

	return fd;

} // END: OpenSysGPIO()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      READSYSGPIO()
*      Read GPIO from SYSFS value file.
*
*  Inputs:
*  		fd : descriptor of the opened value file.
*
*  Outputs:
*  		retVal : pin value (state)
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
int8_T ReadSysGPIO(int32_T fd)
{
	char	 buf;
	int32_T	 retPoll;
	int8_T	 retVal;
	pollFd_T fds;

	fds.fd 	   = fd;
	fds.events = POLLPRI;

	retPoll = poll(&fds, 1, SYS_GPIO_TIMEOUT);
	if (retPoll < 0)
	{
		fprintf(stderr, "Failed to poll GPIO value file.\n");
		exit(EXIT_FAILURE);
	}

	if (retPoll == 0)
	{
		retVal = -1;
	}
	else
	{
		lseek(fd, 0, SEEK_SET);
		read (fd, &buf, 1);

		if (buf == SYS_GPIO_HIGH)
			retVal = TRUE;
		else if (buf == SYS_GPIO_LOW)
			retVal = FALSE;
		else
			exit(EXIT_FAILURE);
	}

	return retVal;

} // END: ReadSysGPIO()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      ASSIGNSYSGPIOPIN()
*      Export SYSFS file of the GPIO pin.
*
*  Inputs:
*      pin : GPIO number
*
*  Outputs:
*
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
static void AssignSysGPIOPin(uint8_T pin)
{
	int32_T fd;
	char 	str[2];

	// Open "/sys/class/gpio/export"
	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Failed to open /sys/class/gpio/export.\n");
		exit(EXIT_FAILURE);
	}
	sprintf(str, "%d", pin);
	write(fd, str, sizeof(str));
	close(fd);

} // END: AssignSysGPIOPin()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      ASSIGNSYSGPIODIRECTION()
*      Assign input/output pin direction.
*
*  Inputs:
*  		pin 	  : GPIO number
*  		direction : IO direction (defined value)
*
*  Outputs:
*
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
static void AssignSysGPIODirection(uint8_T pin, uint8_T direction)
{
	int32_T fd;
	char str[50];

	sprintf(str, SYS_GPIO_DIRECTION, pin);

	fd = open(str, O_WRONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Failed to open GPIO direction file.\n");
		exit(EXIT_FAILURE);
	}

	switch (direction)
	{
	case SYS_GPIO_IN:
		write(fd, "in", strlen("in"));
		break;

	case SYS_GPIO_OUT:
		write(fd, "out", strlen("out"));
		break;
	}

	close(fd);

} // END: AssignSysGPIODirection()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      ASSIGNSYSGPIOTRIGGER()
*      Configure the trigger mode of the GPIO as
*      "none", "rising", "falling", or "both".
*
*  Inputs:
*  		pin 	: GPIO number
*  		trigger : trigger mode (defined value)
*
*  Outputs:
*
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
static void AssignSysGPIOTrigger(uint8_T pin, uint8_T trigger)
{
	int32_T fd;
	char str[50];

	sprintf(str, SYS_GPIO_EDGE, pin);

	fd = open(str, O_WRONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Failed to open GPIO edge file.\n");
		exit(EXIT_FAILURE);
	}

	switch (trigger)
	{
	case SYS_GPIO_NONE:
		write(fd, "none", strlen("none"));
		break;

	case SYS_GPIO_RISING:
		write(fd, "rising", strlen("rising"));
		break;

	case SYS_GPIO_FALLING:
		write(fd, "falling", strlen("falling"));
		break;

	case SYS_GPIO_BOTH:
		write(fd, "both", strlen("both"));
		break;
	}

	close(fd);

} // END: AssignSysGPIOTrigger()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      ASSIGNSYSGPIOACTIVELOW()
*      Set the active low status of the GPIO.
*
*  Inputs:
*  		pin   : GPIO number
*  		state : active low status
*
*  Outputs:

*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
static void AssignSysGPIOActvLow(uint8_T pin, boolean_T state)
{
	int32_T fd;
	char str[50];

	sprintf(str, SYS_GPIO_ACTIVELOW, pin);

	fd = open(str, O_WRONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Failed to open GPIO active_low file.\n");
		exit(EXIT_FAILURE);
	}

	switch (state)
	{
	case TRUE:
		write(fd, "1", strlen("1"));
		break;

	case FALSE:
		write(fd, "0", strlen("0"));
		break;
	}

	close(fd);

} // END: AssignSysGPIOActvLow()


// EOF: gpio.c


