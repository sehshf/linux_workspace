/*
 * test_cam.c
 *
 *  Created on: 14/12/2016
 *      Author: ses
 */

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "portable.h"

static void * ThrdFcn(void *arg)
{
	//int8_T *str = (int8_T *const)arg;
	char *const rpiPhoto[] = {"raspistill", "-o", "test.jpg"};
	pid_t chldPid;

	switch (chldPid = fork())
	{
	case -1:
		fprintf(stderr, "fork() failed.\n");
		break;
	case 0:
		printf("Child PID = %ld created.\n", (long) getpid());
		execvp("/usr/bin/raspistill", rpiPhoto);
		break;
	default:
		wait(NULL);
		printf("Child terminated.\n");
		break;
	}

	return NULL;
}


int main(void)
{
	pthread_t t1;
	int32_T tmp;
	void *res;

	tmp = pthread_create(&t1, NULL, ThrdFcn, NULL);
	res = pthread_join(t1, &res);

	printf("Thread returned %ld\n", (int32_T) res);

    return PASSED;

} // END: main()


// EOF: test_cam.c
