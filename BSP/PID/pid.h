#ifndef __PID_H__
#define __PID_H__

#include <stdint.h>

//#define SPEED_WITH_KI
#define WIT_WITH_KD

typedef struct{
	int real;
	int target;
	float kp;
	float kd;
#if defined(SPEED_WITH_KI)
	float ki;
	float accumulate;
#endif
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

typedef struct{
	uint16_t real;
	uint16_t target;
	uint16_t out;
#if defined (WIT_WITH_KD)
	uint16_t last_error;
	float kd;
#endif
	float kp;
}pid_wit;

void pid_run_speed(pid_speed *input);
void pid_run_rif(pid_rif *input);
void pid_run_wit(pid_wit *input);

#endif