/*
 * wheel.c
 *
 *  Created on: Oct 29, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "wheel.h"


/*
 * **************************************************
 * LOCAL DECLARATIONS								*
 * **************************************************
 */


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
static pthread_t 		thread[NUM_WHEEL];						// Thread array for running in the step mode
static pthread_attr_t 	attr[NUM_WHEEL];						// threads attributes
static uint16_T  		steps[NUM_WHEEL] = {0, 0};				// Number of steps driven by the wheel
static boolean_T 		isRun[NUM_WHEEL] = {FALSE, FALSE};		// Running status of the threads

const static uint16_T 	maxSteps = 5;

/*
 * **************************************************
 * LOCAL PROTOTYPES									*
 * **************************************************
 */
static uint8_T SetMotor(uint8_T wheelID);
static uint8_T SetSensor(uint8_T wheelID);
static void InitStepDrive(void);
static void StepDrive(wheel_T *wheel);
static void *StepCounter(void *arg);


/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      INITWHEELS()
*      Initialize wheel motor and sensor.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*		   Apr 2017
*  -------------------------------------------------------  *
*/
void InitWheels(void)
{
	InitDCMotors();
	InitSpeedSnsrs();
	InitStepDrive();

} // END: InitWheels()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      DRIVEWHEEL()
*      Drive the wheel with the specified direction
*      and speed.
*
*  Inputs:
*      wheel    : Specifies the wheel.
*      direction: Rotation direction
*      speed	: Wheel speed [%], range [0 100]
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Oct 2017
*  -------------------------------------------------------  *
*/
void DriveWheel(wheel_T *wheel, int8_T direction, uint8_T speed)
{
	// Set the corresponding motor and sensor
	wheel->motor  = SetMotor( wheel->id);
	wheel->sensor = SetSensor(wheel->id);

	// Stop the motors first, when the direction reversed
	if (direction != wheel->direction)
		DriveDCMotor(wheel->motor, direction, 0);

	wheel->direction = direction;

	if (speed <= WHEEL_STEP_THD && speed > 0)	// Stepper drive mode
	{
		DriveDCMotor(wheel->motor, direction, WHEEL_STEP_THD);
//		wheel->steps = speed * maxSteps / WHEEL_STEP_THD;
//
//		if (isRun[wheel->id] == FALSE)
//		{
//			steps[wheel->id] = 0;
//			isRun[wheel->id] = TRUE;
//			StepDrive(wheel);
//		}
//		else if (wheel->steps <= steps[wheel->id])
//		{
//			DriveDCMotor(wheel->motor, direction, 0);
//			pthread_cancel(thread[wheel->id]);	// cancel the thread created for step-drive
//			isRun[wheel->id] = FALSE;
//			steps[wheel->id] = 0;
//		}
	}
	else	// Normal drive mode
	{
		if (isRun[wheel->id] == TRUE)
		{
			pthread_cancel(thread[wheel->id]);	// cancel the thread created for step-drive
			isRun[wheel->id] = FALSE;
			steps[wheel->id] = 0;
		}
		DriveDCMotor(wheel->motor, direction, speed);
	}

} // END: DriveWheel()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      SETMOTOR()
*      Set the corresponding wheel motor.
*
*  Inputs:
*      wheelID : Wheel ID
*
*  Outputs:
*  	   motor: motor ID
*
*  Author: Ehsan Shafiei
*  		   Nov 2017
*  -------------------------------------------------------  *
*/
static uint8_T SetMotor(uint8_T wheelID)
{
	uint8_T motor;

	// This can be replaced by a table or map!
	if (wheelID == LEFT_WHEEL)
		motor = LEFT_DCMOTOR;
	else
		motor = RIGHT_DCMOTOR;

	return motor;

} // END: SetMotor()

/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      SETSENSOR()
*      Set the corresponding wheel sensor.
*
*  Inputs:
*      wheelID: Wheel ID
*
*  Outputs:
*  	   sensor: sensor ID
*
*  Author: Ehsan Shafiei
*  		   Nov 2017
*  -------------------------------------------------------  *
*/
static uint8_T SetSensor(uint8_T wheelID)
{
	uint8_T sensor;

	// This can be replaced by a table or map!
	if (wheelID == LEFT_WHEEL)
		sensor = LEFT_SPEED_SNSR;
	else
		sensor = RIGHT_SPEED_SNSR;

	return sensor;

} // END: SetSensor()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      INITSTEPDRIVE()
*      Initialize the thread attributes for step drive
*      function.
*
*  Inputs:
*
*  Author: Ehsan Shafiei
*  		   Dec 2017
*  -------------------------------------------------------  *
*/
static void InitStepDrive(void)
{
	struct sched_param schedParam;

	int32_T i;

	for (i = 0; i < NUM_WHEEL; i++)
	{
		pthread_attr_init(&attr[i]);
		pthread_attr_setinheritsched(&attr[i], PTHREAD_EXPLICIT_SCHED);
		pthread_attr_setschedpolicy(&attr[i], SCHED_FIFO);

		schedParam.__sched_priority = sched_get_priority_max(SCHED_FIFO) - i - 10;

		pthread_attr_setschedparam(&attr[i], &schedParam);
	}

} // END: InitStepDrive()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      STEPDRIVE()
*      Drive the DC motor step-by-step. Each step is
*      as long as an encoder angel resolution.
*
*  Inputs:
*      *wheel: Pointer to wheel object
*
*  Author: Ehsan Shafiei
*  		   Nov 2017
*  -------------------------------------------------------  *
*/
static void StepDrive(wheel_T *wheel)
{
	pthread_create(&thread[wheel->id], &attr[wheel->id], StepCounter, (void *)wheel);

	/* drive the motor with specified step speed the motor
	 * will be stopped by the thread function when it
	 * ran with the requested number of steps
	 */
	DriveDCMotor(wheel->motor, wheel->direction, WHEEL_STEP_SPEED);

} // END: StepDrive()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      STEPCOUNTER()
*      Thread specific function that counts the number of
*      steps that the motor driven and stops the motor
*      after specified number of steps.
*
*  Inputs:
*      *arg : Descriptor of the opened value file.
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Oct 2017
*  -------------------------------------------------------  *
*/
static void *StepCounter(void *arg)
{
	wheel_T *wheel = (wheel_T *)arg;

	int32_T i, maxStep = wheel->steps, id = wheel->id;
	uint8_T motor = wheel->motor, sensor = wheel->sensor;
	int8_T direction = wheel->direction;

	for (i = 0; i < maxStep; i++)
	{
		// Blocking read
		if (ReadSpeedPulse(sensor))
			steps[id]++;
	}
	DriveDCMotor(motor, direction, 0);

	return NULL;

} // END: StepCounter()


// EOF: wheel.c

