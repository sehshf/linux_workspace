/*
 * control.c
 *
 *  Created on: Apr 3, 2017
 *      Author: ses
 */

/*
 * **************************************************
 * APPLICATION INCLUDE FILES						*
 * **************************************************
 */
#include "control.h"

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
*      PIDCtl()
*      Initializing the servo motors.
*
*  Inputs:
*  		*pid: pointer to a PID structure
*     	r   : setpoint (reference) in percent
*     	y   : plant output in percent
*     	ts  : sampling time
*
*  Outputs:
*  	  	u: control command in percent
*
*  Author: Ehsan Shafiei
*  		   Apr 2017
*  -------------------------------------------------------  *
*/
uint16_T PIDCtl(pid_T *pid, uint16_T r, uint16_T y, real32_T ts)
{
	real32_T err, dy, v;

	real32_T P, I, D;

	uint16_T u;

	real32_T Kd1, Kd2, Ki, Kt, Tt;

	/* floating point error signal */
	err = (real32_T)(r - y);

	/* proportional part */
	P = pid->k * err;
//	printf("P = %f\n", P);

	/* derivative params */
	if (pid->td > 0)
	{
		Kd1 = pid->td / (pid->td + pid->n * ts);
		Kd2 = Kd1 * pid->k * pid->n;
	}
	else
	{
		Kd1 = 0;
		Kd2 = 0;
	}

	/* integral part */
	I = pid->I;
//	printf("I = %f\n", I);

	/* derivative parts */
	dy = (real32_T)(y - pid->y);						// floating point output difference
	D  = Kd1 * pid->D - Kd2 * dy;

	/* parallel PID */
	v = P + I + D;
//	printf("v = %f\n", v);
	u = SCALE(v, -pid->sc, pid->sc, pid->sc);
//	printf("u = %d\n", u);

	/* saturation filter */
	u = sat(u, 0, pid->sc);

	/* integrator params */
	if (pid->ti > 0)
	{
		Ki = pid->k * ts / (pid->ti);					// integrator gain

		/* anti-windup params */
		if (pid->td > 0.1 * pid->ti)
			Tt = sqrt((real32_T)(pid->ti * pid->td));	// anti-windup time
		else
			Tt = 0.3 * pid->ti;							// anti-windup time

		Kt = ts / Tt;									// anti-windup gain
	}
	else
	{
		Ki = 0;
		Kt = 0;
	}

	/* updates */
	pid->I = I + Ki * err + Kt * ((real32_T)UNSCALE(u, -pid->sc, pid->sc, pid->sc) - v);	// integrator update including anti-windup
	pid->y = y;
	pid->D = D;

	return u;

} // End: PIDCtrl()


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


// EOF: control.c

