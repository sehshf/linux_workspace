/*
 * tasks.h
 *
 *  Created on: 27/08/2016
 *      Author: ses
 */

#ifndef _RT_TASKS_H_
#define _RT_TASKS_H_

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "portable.h"
#include "camera.h"
#include "motors.h"

/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
#define NUM_TASKS 	2
#define MAX_PRIO	(sched_get_priority_min(SCHED_FIFO) + NUM_TASKS)

// Tasks enum should be ordered based on the tasks priorities
enum
{
	CAMERA_TASK,
	MOTORS_TASK

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
typedef struct
{
	uint32_T clockTickL;
	uint32_T clockTickH;
} timing_T;

typedef struct
{
	sem_t 	  		sem;
	pthread_t 		thread;
	uint16_T  		period;	// Coefficient of the base period.
	pthread_mutex_t *mutex;
} task_T;

/*
 * **************************************************
 * External VARIABLES       						*
 * **************************************************
 */
extern task_T 	 task[NUM_TASKS];
extern real32_T  baseTs;


/*
 * **************************************************
 * PROTOTYPES										*
 * **************************************************
 */
void InitRTTasks(uint16_T period[NUM_TASKS]);

pf_T CreateRTTask(task_T task,
				  pthread_attr_t attr,
				  int16_T prio,
				  struct sched_param schedParam,
				  uint16_T period,
				  void *(*TaskRoutine) (void *),
				  void *threadArg
				 );

void *BaseRate(void *arg);

void *TaskRoutine(void *arg);

#endif // _RT_TASKS_H_

// EOF: rt_tasks.h
