/*
 * tcpip.c
 *
 *  Created on: May 5, 2017
 *      Author: ses
 */


/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "tcpip.h"

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



/*
 * **************************************************
 * LOCAL PROTOTYPES									*
 * **************************************************
 */



/*
 * **************************************************
 * PUBLIC FUNCTIONS									*
 * **************************************************
 */
/**
*  -------------------------------------------------------  *
*  FUNCTION:
*      TCPSERVER()
*      Create a server socket and listen on a port.
*
*  Inputs:
*
*  Outputs:
*  	  	sfd: socket file description
*
*  Author: Ehsan Shafiei
*  		   May 2017
*  -------------------------------------------------------  *
*/
int32_T TCPServer(void)
{
	int32_T sfd, optval = 1;

    struct sockaddr_in sadr;

    // Create socket
    sfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sfd < 0)
    {
        fprintf(stderr, "Socket creation failed.\n");
    }

    // Set socket options
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
    	fprintf(stderr, "Socket set option failed.\n");
    }

    // Configure the socket
    sadr.sin_family		 = AF_INET;
    sadr.sin_addr.s_addr = INADDR_ANY;
    sadr.sin_port 		 = htons(SERVER_PORT);

    // Bind the socket
    if( bind(sfd, (struct sockaddr *)&sadr, sizeof(sadr)) < 0)
    {
        fprintf(stderr, "Socket binding failed.\n");
    }

    // Listen to the port
    if (listen(sfd, 5) < 0)
    {
    	fprintf(stderr, "Socket listening failed.\n");
    }
    else
    {
    	printf("start listening on port %d\n", SERVER_PORT);
    }

	return sfd;

}// END: TCPServer()



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


// EOF: tcpip.c
