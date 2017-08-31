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
*      Initializing servo motors.
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
uint16_T PIDCtl(pid_T *pid, real32_T r, real32_T y, real32_T ts)
{
	real32_T e, dy;
	real32_T P, I, D;
	real32_T u, v;
	real32_T Kd1, Kd2, Ki, Kt, Tt;

	/* Error signal */
	e = (r - y);

	/* Proportional part */
	P = pid->k * e;

	/* Derivative params */
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

	/* Integral part */
	I = pid->I;

	/* Derivative parts */
	dy = (y - pid->y);						// floating point output difference
	D  = Kd1 * pid->D - Kd2 * dy;

	/* Parallel PID */
	v = P + I + D;

	/* Saturation filter */
	u = sat(v, 0, 100);

	/* Integrator params */
	if (pid->ti > 0)
	{
		Ki = pid->k * ts / (pid->ti);					// integrator gain

		/* Anti-windup params */
		if (pid->td > 0.1 * pid->ti)
			Tt = sqrt(pid->ti * pid->td);				// anti-windup time
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
	pid->I = I + Ki * e + Kt * (u - v);					// integrator update including anti-windup
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

