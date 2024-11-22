/*
 * pid_controller.h
 *
 *  Created on: 22 мая 2023 г.
 *      Author: Kirs
 */

#ifndef INC_PID_CONTROLLER_H_
#define INC_PID_CONTROLLER_H_

#endif /* INC_PID_CONTROLLER_H_ */

#include "main.h"

typedef struct {

	float setpoint;
	float feedback;
	float err;
	float prevErr;
	float P;
	float I;
	float D;
	float Kp;
	float Ki;
	float Kd;
	float dt;
	float Out;
	float Outmax;
	float Outmin;

} PIDCONTROLLER;

void pid_controller_calculation(volatile PIDCONTROLLER *pid);
void pid_init(volatile PIDCONTROLLER *pid, float, float, float, float,
		float, float);
