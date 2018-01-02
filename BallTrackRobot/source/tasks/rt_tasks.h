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
#include <sys/mman.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "camera.h"
#include "servo.h"
#include "vehicle.h"
#include "portable.h"

/*
 * **************************************************
 * DEFINITIONS										*
 * **************************************************
 */
#define MAX_PRIO	(sched_get_priority_max(SCHED_FIFO))

// Task period as multiplication of the baserate
#define BASE_PERIOD			5		// 5   ms
#define CAMERA_TASK_RATE	10		// 50  ms
#define SERVO_TASK_RATE		10		// 50  ms
#define VEHICLE_TASK_RATE	24		// 120 ms

// Tasks enum should be ordered based on the tasks priorities
enum
{
	CAMERA_TASK,
	SERVO_TASK,
	VEHICLE_TASK,
	NUM_TASKS
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
	pthread_mutex_t mutex;
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
void SetAttribute(pthread_attr_t *attr);

void InitRTTasks(uint16_T period[NUM_TASKS]);

pf_T CreateRTTask(task_T task,
				  pthread_attr_t *attr,
				  int16_T prio,
				  struct sched_param *schedParam,
				  void *(*TaskRoutine) (void *),
				  void *threadArg
				 );

void *BaseRate(void *arg);

void *TaskRoutine(void *arg);

#endif // _RT_TASKS_H_

// EOF: rt_tasks.h
