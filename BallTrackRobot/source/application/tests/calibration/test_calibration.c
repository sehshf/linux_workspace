/*
 * test_calibration.c
 *
 *  Created on: May 5, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * SYSTEM INCLUDE FILES								*
 * **************************************************
 */
#ifdef 	USE_MAP_ANON
#define _BSD_SOURCE
#endif
#include <sys/mman.h>
#include <fcntl.h>

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "calibration.h"
#include "params.h"
#include "portable.h"

int main(int argc, char *argv[])
{
	int32_T *addr, fd;

	fd = open("/dev/zero", O_RDWR);

	addr = (int32_T *)mmap((void *)PARAMS_ADDR, 256, PROT_WRITE | PROT_WRITE, MAP_PRIVATE, fd, 0);

	if (addr == MAP_FAILED)
		fprintf(stderr, "Mapping failed\n");

	InitParamAddr();
	InitParamVal();

	printf("value = %f\n", MOTORS_Kpan_C);

	RunCalibration();

	printf("value = %f\n", MOTORS_Kpan_C);

	return PASSED;

} // END: main()

// EOF: test_calibration.c
