/*
 * pid_controller.c
 *
 *  Created on: 22 мая 2023 г.
 *      Author: Kirs
 */

#include "pid_controller.h"
void pid_init(volatile PIDCONTROLLER *pid, float Kp, float Ki, float Kd,
		float Outmax, float Outmin, float dt) {
	pid->Kp = Kp;
	pid->Ki = Ki;
	pid->Kd = Kd;
	pid->Outmax = Outmax;
	pid->Outmin = Outmin;
	pid->dt = dt;
	pid->I = 0;

}

void pid_controller_calculation(volatile PIDCONTROLLER *pid) {

	pid->err = pid->setpoint - pid->feedback;

	// P составляющая
	pid->P = pid->err * pid->Kp;

	// I составляющая
	if (pid->Ki) {
		pid->I = pid->I + (pid->err + pid->Out - pid->I) * pid->dt;
	}
	// D составляющая
	pid->D = (pid->err - pid->prevErr) / pid->dt;

	pid->Out = pid->P + pid->I * pid->Ki + pid->D;

	if (pid->Out > pid->Outmax) {
		pid->Out = pid->Outmax;
	}
	else if (pid->Out < pid->Outmin) {
		pid->Out = pid->Outmin;
	}

	pid->prevErr = pid->err;
}
