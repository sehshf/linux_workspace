/*
 * main.c
 *
 *  Created on: 22/08/2016
 *      Author: ses
 */

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
#include "portable.h"
#include "rt_tasks.h"

int main()
{
	pthread_t baseRateThread;
	pthread_attr_t attr;
	struct sched_param schedParam;

	// Task period as multiplication of the baserate
	uint16_T period[NUM_TASKS] = {CAMERA_TASK_RATE, MOTORS_TASK_RATE};

	uint32_T i;

	// Initializations
	InitRTTasks(period);

	// Prepare tasks attributes
	SetAttribute(&attr);

	// Real-time tasks
	for (i = 0; i < NUM_TASKS; i++)
	{
		CreateRTTask(task[i], &attr, (int16_T)MAX_PRIO - i, &schedParam, TaskRoutine, (uint32_T *)i);
	}

	// Base rate
	schedParam.__sched_priority = MAX_PRIO + 1;

	if (pthread_attr_setschedparam(&attr, &schedParam) != 0)
	{
		fprintf(stderr, "pthread_attr_setschedparam failed for base rate\n");
		return FAILED;
	}

	if (pthread_create(&baseRateThread, &attr, BaseRate, NULL) != 0)
	{
		fprintf(stderr, "cannot start the real-time task\n");
		return FAILED;
	}

	pthread_attr_destroy(&attr);

	// Wait for threads to finish
	pthread_join(baseRateThread, NULL);

	for (i = 0; i < NUM_TASKS; i++)
		pthread_join(task[i].thread, NULL);

	return PASSED;

} // END: main()

// EOF: main.c
