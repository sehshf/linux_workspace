/*
 * pca9685.c
 *
 *  Created on: 22/10/2016
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "pca9685.h"


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
static uint16_T pcaFreq;

/*
 * **************************************************
 * LOCAL PROTOTYPES									*
 * **************************************************
 */
static void InitOnOffReg(void);
static void InitDeviceMode(void);
static void DeviceWakeUp(void);
static void SetupPCABoard(void);
static void SetPCAFreq(uint16_T freq);

/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      SETPCAPULSE()
*      Specify the pulse with starting delay and pulse width.
*
*  Inputs:
*      channel 	: The PWM channel on PCA9685
*      pulse	: Pulse width [ms]
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Aug 2016
*  -------------------------------------------------------  *
*/
void SetPCAPulse(uint8_T channel, uint16_T pulse)
{
	uint16_T onCnt, offCnt;

	onCnt  = PWM_COUNT_DELAY;
	offCnt = onCnt + pulse * pcaFreq * (PCA9685_COUNT - 1) / 1000 / 1000;

	SMBusWrite8(fd, LED0_ON_L  + 4 * channel, BYTE_L(onCnt ));
	SMBusWrite8(fd, LED0_ON_H  + 4 * channel, BYTE_H(onCnt ));
	SMBusWrite8(fd, LED0_OFF_L + 4 * channel, BYTE_L(offCnt));
	SMBusWrite8(fd, LED0_OFF_H + 4 * channel, BYTE_H(offCnt));

} // END: SetPCAPulse()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      SETPCAPWM()
*      Specify the PWM signal with duty cycle in percent.
*
*  Inputs:
*      channel 	: The PWM channel on PCA9685
*      duty		: Duty cycle [%]
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Apr 2017
*  -------------------------------------------------------  *
*/
void SetPCAPWM(uint8_T channel, uint8_T duty)
{
	uint16_T onCnt, offCnt;

	onCnt  = 0;
	offCnt = onCnt + (PCA9685_COUNT - 1) * duty / 100;

	SMBusWrite8(fd, LED0_ON_L  + 4 * channel, BYTE_L(onCnt ));
	SMBusWrite8(fd, LED0_ON_H  + 4 * channel, BYTE_H(onCnt ));
	SMBusWrite8(fd, LED0_OFF_L + 4 * channel, BYTE_L(offCnt));
	SMBusWrite8(fd, LED0_OFF_H + 4 * channel, BYTE_H(offCnt));

} // END: SetPCAPWM()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      INITPWMCHANNELS()
*      Initializing the PCA board to drive the motors.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Oct 2016, Sep 2017
*  -------------------------------------------------------  *
*/
void InitPWMChannels(void)
{
	static boolean_T isInit = FALSE;

	if (~isInit)
	{
		SetupPCABoard();
		SetPCAFreq(PWM_FREQ);
		isInit = TRUE;
	}

} // END: InitPWMChannels()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      INITONOFFREG()
*      Initialize the LED ON and OFF registers in PCA9685.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Oct 2016
*  -------------------------------------------------------  *
*/
static void InitOnOffReg(void)
{
    SMBusWrite8(fd, ALL_LED_ON_L , 0x00);
    SMBusWrite8(fd, ALL_LED_ON_H , 0x00);
    SMBusWrite8(fd, ALL_LED_OFF_L, 0x00);
    SMBusWrite8(fd, ALL_LED_OFF_H, 0x00);

} // END: InitOnOffReg()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      INITDEVICEMODE()
*      Initialize MODE1 and MODE2 of PCA9685.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Oct 2016
*  -------------------------------------------------------  *
*/
static void InitDeviceMode(void)
{
	SMBusWrite8(fd, MODE2 , PCA9685_OUTDRV);		// Default for MODE2
	SMBusWrite8(fd, MODE1 , PCA9685_ALLCALL);		// Normal mode
	usleep(500); 									// Wait for oscillator

} // END: InitDeviceMode()

/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      DEVICEWAKEUP()
*      Activate the PWM channels on PCA9685.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Oct 2016
*  -------------------------------------------------------  *
*/
static void DeviceWakeUp(void)
{
	uint8_T mode;

	mode = SMBusRead8(fd);		// Read MODE1

	SMBusWrite8(fd, MODE1, mode & ~PCA9685_SLEEP);

	usleep(500); 				// Wait for oscillator

} // END: DeviceWakeUp()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      SETUPPCABOARD()
*      Set up and initialize PCA9685.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Oct 2016
*  -------------------------------------------------------  *
*/
void SetupPCABoard(void)
{
	fd = AccessI2CBus((const char *)I2C_FILE, PCA9685_ADDR);
	InitOnOffReg();
	InitDeviceMode();
	DeviceWakeUp();

} // END: SetupPCABoard()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      SETPCAFREQ()
*      Set the PWN frequency of PCA9685.
*
*  Inputs:
*      freq : Frequency [Hz] from 45 to 1526
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Oct 2016
*  -------------------------------------------------------  *
*/
void SetPCAFreq(uint16_T freq)
{
	// Max: 1526 Hz
	// Min: 45   Hz

	uint8_T regVal, oldMode, newMode;

	oldMode = SMBusRead8(fd);						// Read MODE1

	newMode = (oldMode & 0x7F) | PCA9685_SLEEP;    	// Sleep mode
	SMBusWrite8(fd, MODE1, newMode);

	regVal = PCA9685_CLK / PCA9685_COUNT / freq - 1;
	SMBusWrite8(fd, PRE_SCALE, (uint8_T)regVal);	// Set the PWM frequency

	SMBusWrite8(fd, MODE1, oldMode);

	usleep(500);									// Wait for the oscillator

	SMBusWrite8(fd, MODE1, oldMode | 0x80);			// Restart all PWM channels

	pcaFreq = freq;									// Update the frequency

} // END: SetPCAFreq()


// EOF: pca9685.c

