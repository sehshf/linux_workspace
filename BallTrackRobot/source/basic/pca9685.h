/*
 * pca9685.h
 *
 *  Created on: 22/10/2016
 *      Author: ses
 */

#ifndef _PCA9685_H_
#define _PCA9685_H_

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "i2c_smbus.h"

/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
// Device specifics
#define PCA9685_ADDR		0x40
#define PCA9685_CLK			25000000
#define PCA9685_COUNT		4096		// 12 bit count

// PCA9685 registers
#define MODE1				0x00
#define MODE2				0x01

#define LED0_ON_L 			0x06
#define LED0_ON_H 			0x07
#define LED0_OFF_L 			0x08
#define LED0_OFF_H 			0x09

#define ALL_LED_ON_L		0xFA
#define ALL_LED_ON_H		0xFB
#define ALL_LED_OFF_L		0xFC
#define ALL_LED_OFF_H		0xFD
#define PRE_SCALE			0xFE

// Register bits
#define PCA9685_OUTDRV		0x04
#define PCA9685_ALLCALL 	0x01
#define PCA9685_SLEEP   	0x10

// Settings
#define PWM_COUNT_DELAY		41		// 1% of total count (4096)

// PWM outputs
enum
{
	PWM_0,
	PWM_1,
	PWM_2,
	PWM_3,
	PWM_4,
	PWM_5,
	PWM_6,
	PWM_7,
	PWM_8,
	PWM_9,
	PWM_10,
	PWM_11,
	PWM_12,
	PWM_13,
	PWM_14,
	PWM_15
};

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
#define PWM_FREQ 			50


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
void SetPCAPulse(uint8_T channel, uint16_T pulse);

void SetPCAPWM(uint8_T channel, uint8_T duty);

void InitPWMChannels(void);

#endif // _PCA9685_H_

// EOF: pca9685.h


