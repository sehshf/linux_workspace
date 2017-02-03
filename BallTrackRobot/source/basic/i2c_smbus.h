/*
 * i2c_smbus.h
 *
 *  Created on: 22/10/2016
 *      Author: ses
 */

#ifndef _I2C_SMBUS_H_
#define _I2C_SMBUS_H_

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>


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
#define I2C_FILE	"/dev/i2c-1"


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
int32_T AccessI2CBus(const char *fName, int32_T addr);

void SMBusWrite8(int32_T file, uint8_T reg, uint8_T val);

uint8_T SMBusRead8(int32_T file);


#endif // _I2C_SMBU_H_

// EOF: i2c_smbus.h

