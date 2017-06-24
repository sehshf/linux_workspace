/*
 * calibration.c
 *
 *  Created on: May 4, 2017
 *      Author: ses
 */


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "calibration.h"

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
// Data buffer for calibration
uint8_T calBuf[CAL_BUF_SIZE];


/*
 * **************************************************
 * LOCAL PROTOTYPES									*
 * **************************************************
 */
static void CalHandler (int32_T sock);
static void GetParamVal(int32_T sock);
static void SetParamVal(int32_T sock);
static void SaveParams (int32_T sock);

/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      RUNCALIBRATION()
*      Start parameter calibration using TCP/IP server
*
*  Inputs:
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
void RunCalibration(void)
{
    int32_T  	sfd, sock;
    socklen_t 	addrLen;

    struct sockaddr addr;

    // Start TCP/IP server
    sfd = TCPServer();

    addrLen = sizeof(addr);
    while ((sock = accept(sfd, &addr, &addrLen)) >= 0)
    {
    	memset(calBuf, 0, CAL_BUF_SIZE);

    	if (recv(sock, calBuf, CAL_BUF_SIZE, 0) < 0)
    	{
    		fprintf(stderr, "Socket calibration receive failed.\n");
    		break;
    	}
    	else
    	{
    		CalHandler(sock);
    	}
    }

} // END: RunCalibration()


/*
 * **************************************************
 * LOCAL FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      CALHANdLER()
*      Handle calibration request from TCP client
*
*  Inputs:
*		sock: Socket handle
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
static void CalHandler(int32_T sock)
{
	// Get starting byte 0
	if (calBuf[CAL_START_IDX] != CAL_STRT_ID)
	{
		fprintf(stderr, "Calibration start ID is not valid.\n");
		return;
	}

	// Identify calibration request flag
	switch (calBuf[CAL_FLAG_IDX])
	{
	case GET_PARAM:
		GetParamVal(sock);
		break;
	case SET_PARAM:
		SetParamVal(sock);
		 break;
	case SAVE_PARAM:
		SaveParams(sock);
	}
} // END: CalHandler()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      GETPARAMVAL()
*      Unpack calibration raw data based on the protocol
*      and set the value of the corresponding parameter.
*
*  Inputs:
*  		sock: Socket handle
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
static void GetParamVal(int32_T sock)
{
	uint32_T addr;
	uint8_T	 len, packSize, buf[CAL_BUF_SIZE];

	// Get data (value) length
	// from byte 5
	len 	 = calBuf[CAL_LENGTH_IDX];
	packSize = CAL_FIXED_BYTES + len;

	if (calBuf[packSize - 1] != CAL_END_ID)
	{
		fprintf(stderr, "Calibration end ID is not valid.\n");
		return;
	}

	// Get the parameter address
	memcpy(&addr, &calBuf[1], CAL_ADDR_BYTES);
	printf("address = 0x%x\n", addr);

	/**************************************/
	/* Start Packing data */

	// Put start ID
	buf[CAL_START_IDX] = CAL_STRT_ID;

	// Put the parameter address
	memcpy(&buf[CAL_ADDR_IDX], &calBuf[CAL_ADDR_IDX], CAL_ADDR_BYTES);

	// Put request flag
	buf[CAL_FLAG_IDX] = GET_PARAM;

	// Put data length
	buf[CAL_LENGTH_IDX] = len;

	// Put parameter value
	memcpy(&buf[CAL_VALUE_IDX], (uint32_T *)addr, len);

	// Put end ID
	buf[packSize - 1] = CAL_END_ID;

	/* End packing data */
	/**************************************/

	// Send the packet
	send(sock, buf, packSize, 0);

} // END: GetParamVal()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      SETPARAMVAL()
*      Unpack calibration raw data based on the protocol
*      and set the value of the corresponding parameter.
*
*  Inputs:
*  		sock: Socket handle
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
static void SetParamVal(int32_T sock)
{
	uint32_T addr;
	uint8_T  len, packSize;

	// Get data (value) length
	// from byte 5
	len 	 = calBuf[CAL_LENGTH_IDX];
	packSize = CAL_FIXED_BYTES + len;

	if (calBuf[packSize - 1] != CAL_END_ID)
	{
		fprintf(stderr, "Calibration end ID is not valid.\n");
		return;
	}

	// Get the parameter address
	// from bytes 1 to 4
	memcpy(&addr, &calBuf[CAL_ADDR_IDX], CAL_ADDR_BYTES);

	// Update parameter value
	// from bytes 5 to 5 + len
	memcpy((uint32_T *)addr, &calBuf[CAL_VALUE_IDX], len);

	GetParamVal(sock);

} // END: SetParamVal()


/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      SAVEPARAMS()
*      Save the calibration parameter values in a file.
*
*  Inputs:
*  		sock: Socket handle
*
*  Outputs:
*
*  Author: Ehsan Shafiei
*  		   June 2017
*  -------------------------------------------------------  *
*/
static void SaveParams(int32_T sock)
{
	FILE *fd;
	char *p = (char *)PARAMS_ADDR;

	// Open the parameter file
	fd = fopen(paramFile, "w");
	if (fd == NULL)
		fprintf(stderr, "Failed to open the parameter file\n");


	// Write the parameter values from the specified
	// memory address into the parameter file
	if (fwrite(p, 1, PARAMS_SIZE, fd) == PARAMS_SIZE)
		printf("parameters were written to %s\n", paramFile);
	else
		fprintf(stderr, "Failed to write the parameter file\n");

	fclose(fd);

} // END: SaveParams()


// EOF: calibration.c
