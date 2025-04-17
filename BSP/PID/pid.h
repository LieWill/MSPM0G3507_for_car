#ifndef __PID_H__
#define __PID_H__

#include <stdint.h>

typedef struct{
	int real;
	int target;
	float kp;
	float ki;
	float kd;
	int out;
	int last_error;
}pid_speed;

typedef struct{
	uint16_t real;
	uint16_t target;
	uint16_t out;
	uint16_t last_error;
	float kp;
	float kd;
}pid_rif;

void pid_run_speed(pid_speed *input);
void pid_run_rif(pid_rif *input);

#endif