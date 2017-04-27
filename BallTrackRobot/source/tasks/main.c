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
#include <stdio.h>
#include <sys/mman.h>

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
	uint16_T period[NUM_TASKS] = {10, 10};

	uint32_T i;

	if (mlockall(MCL_CURRENT | MCL_FUTURE) < 0)
	{
		fprintf(stderr, "Error: mlockall failed - cannot lock application in memory\n");
		return FAILED;
	}

	// Initializations
	InitRTTasks(period);

	// Prepare tasks attributes
	if (pthread_attr_init(&attr) != 0)
	{
		fprintf(stderr, "pthread_attr_init failed\n");
		return FAILED;
	}

	if (pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED) != 0)
	{
		fprintf(stderr, "pthread_attr_setinheritsched failed\n");
		return FAILED;
	}

	if (pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0)
	{
		fprintf(stderr, "pthread_attr_setschedpolicy SCHED_FIFO failed\n");
		return FAILED;
	}

	for (i = 0; i < NUM_TASKS; i++)
	{
		CreateRTTask(task[i], attr, (int16_T) MAX_PRIO - i, schedParam, period[i], TaskRoutine, (uint32_T *)i);
	}

	// Base rate
	schedParam.sched_priority = MAX_PRIO + 1;

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
