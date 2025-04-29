#ifndef __PID_H__
#define __PID_H__

#include <stdint.h>

// #define SPEED_WITH_KI
#define SPEED_WITH_feedforward				// 前馈
#define SPEED_WITH_Second_order_feedforward // 二阶前馈
#define WIT_WITH_KD

typedef struct
{
	float real;
	float last_real;
	float target;
#if defined(SPEED_WITH_feedforward)
	float last_target;
	float kf;
#if defined(SPEED_WITH_Second_order_feedforward)
	float last_target2;
	float kf2;
#endif
#endif
	float kp;
	float kd;
#if defined(SPEED_WITH_KI)
	float ki;
	float accumulate;
#endif
	float out;
	float last_error;
} pid_speed;

typedef struct
{
	float real;
	float last_real;
	float target;
	float out;
	float last_error;
	float kp;
	float kd;
} pid_rif;

typedef struct
{
	float real;
	float target;
	float kp;
	float kd;
	float last_error;
	float out;
	float limit;
} pid_distance;

typedef struct
{
	int16_t real;
	int16_t target;
	float out;
	int16_t last_real;
#if defined(WIT_WITH_KD)
	int16_t last_error;
	float kd;
#endif
	float kp;
	float ki;
	float accumulate;
} pid_wit;

void pid_run_speed(pid_speed *input);
void pid_run_rif(pid_rif *input);
void pid_run_distance(pid_distance *input);
void pid_run_wit(pid_wit *input);

#endif