/*
 * tasks.c
 *
 *  Created on: 27/08/2016
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "rt_tasks.h"


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
task_T 	  task[NUM_TASKS];
real32_T  baseTs;	// Base rate sample time


/*
 * **************************************************
 * FILE SCOPE VARIABLES (static)					*
 * **************************************************
 */
struct timespec basePeriod;


/*
 * **************************************************
 * LOCAL PROTOTYPES									*
 * **************************************************
 */
// Array of tasks function calls.
// Should appear in the same order as of tasks enum
void (*pTaskFcn[NUM_TASKS])(uint16_T period) = { RunCamera,
												 RunMotors };


/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      INITRTTASK()
*      Initialize real-time tasks.
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   Sep 2016
*  -------------------------------------------------------  *
*/
void InitRTTasks(uint16_T period[NUM_TASKS])
{
	int32_T i;
	basePeriod.tv_sec  = 0U;
	basePeriod.tv_nsec = 10000000U; // 10 ms

	baseTs = basePeriod.tv_sec + basePeriod.tv_nsec / 1000 / 1000 / 1000;

	for (i = 0; i < NUM_TASKS; i++)
	{
		task[i].period = period[i];
		pthread_mutex_init(task[i].mutex, NULL);
	}

	InitCamera();

} // END: InitRTTask()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      CREATERTTASK()
*      Create a real-time task.
*
*  Inputs:
*      *task 		: Pointer to a task structure
*      *attr		: Pointer to a ask attribute
*      prio	   		: Task priority
*      schedParam   : Scheduling parameters
*      TaskRoutine 	: Task function
*      threadArg    : Task argument
*
*  Outputs:
*	   Return 0 when succeeded.
*
*  Author: Ehsan Shafiei
*  		   Sep 2016
*  -------------------------------------------------------  *
*/
pf_T CreateRTTask(task_T task,
				  pthread_attr_t attr,
				  int16_T prio,
				  struct sched_param schedParam,
				  uint16_T period,
				  void *(*TaskRoutine) (void *),
				  void *threadArg
				 )
{
	sem_init(&task.sem, 0, 0);

	task.period = period;

	schedParam.sched_priority = prio;

	if (pthread_attr_setschedparam(&attr, &schedParam) != 0)
	{
		fprintf(stderr, "pthread_attr_setschedparam failed for task %u.\n", task.period);
		return FAILED;
	}

	if (pthread_create(&task.thread, &attr, TaskRoutine, threadArg) != 0)
	{
		fprintf(stderr, "cannot start the real-time task\n");
		return FAILED;
	}

	return PASSED;

} // END: CreateRTTask()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      BASERATE()
*      The base task period.
*
*  Inputs:
*
*  Outputs:
*
*
*  Author: Ehsan Shafiei
*  		   Sep 2016
*
*  -------------------------------------------------------  *
*/
void *BaseRate(void *arg)
{
	struct timespec now, next;

	boolean_T taskFlag[NUM_TASKS];
	int32_T   taskCounter[NUM_TASKS];
	int32_T   semVal, i;

	clock_gettime(CLOCK_MONOTONIC, &next);

	// Main loop, running until all the threads are terminated
	while (1)
	{
		// Set tasks flags
		for (i = 0; i < NUM_TASKS; i++)
		{
			if (taskCounter[i])
			{
				if (taskFlag[i])
				{
					// Sampling too fast
					fprintf(stderr, "Overrun, task%d did not run.\n", i);
					return NULL;
				}

				taskFlag[i] = TRUE;
			}
		}

		for (i = 0; i < NUM_TASKS; i++)
		{
			// Check tasks period
			taskCounter[i]++;
			if (taskCounter[i] == task[i].period)
			{
				taskCounter[i] = 0;
			}
		}

		for (i = 0; i < NUM_TASKS; i++)
		{
			// Trigger tasks
			if (taskFlag[i])
			{
				taskFlag[i] = FALSE;
				sem_getvalue(&task[i].sem, &semVal);
				if (semVal)
				{
					printf("Task%d overrun.\n", i);
					break;
				}

				sem_post(&task[i].sem);
			}
		}

		do
		{
			next.tv_sec  += basePeriod.tv_sec;
			next.tv_nsec += basePeriod.tv_nsec;
			if (next.tv_nsec >= 1000000000)
			{
				next.tv_sec++;
				next.tv_nsec -= 1000000000;
			}

			clock_gettime(CLOCK_MONOTONIC, &now);

			if (now.tv_sec > next.tv_sec ||	(now.tv_sec == next.tv_sec && now.tv_nsec > next.tv_nsec))
			{
				uint32_T usec = (now.tv_sec - next.tv_sec) * 1000000 + (now.tv_nsec - next.tv_nsec) / 1000;
				fprintf(stderr, "Base rate (0.01s) overrun by %u us\n", usec);
				next = now;
				continue;
			}
		} while (0);

		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next, NULL);
	}

	return NULL;

} // END: BaseRate()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      TASKROUTINE()
*      Task1 periodic call.
*
*  Inputs:
*
*  Outputs:
*
*
*  Author: Ehsan Shafiei
*  		   Sep 2016
*
*  -------------------------------------------------------  *
*/
void *TaskRoutine(void *arg)
{
	while (1)
	{
		sem_wait(&task[(uint32_T)arg].sem);
		pTaskFcn[(uint32_T)arg](task[(uint32_T)arg].period);
	}

	return NULL;
} // END: *TaskRoutine()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      PUBLICFUCTION()
*      What this function is doing.
*
*  Inputs:
*      x : Input
*
*  Outputs:
*      y : Return 0 when succeeded.
*
*  Author: Ehsan Shafiei
*  		   Aug 2016
*  -------------------------------------------------------  *
*/
//static type LocalFunction(type x)
//{
//    return y;
//} // END: LocalFunction()

// EOF: rt_tasks.c
