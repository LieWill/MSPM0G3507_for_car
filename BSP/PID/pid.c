#include "pid.h"

void pid_run_speed(pid_speed *input)
{
	input->real = input->real * 0.2 + input->last_real * 0.8; // 滤波；
	float error = input->target - input->real;
#if defined(SPEED_WITH_KI)
	input->accumulate += error * input->ki;
	input->out += error * input->kp + (error - input->last_error) * input->kd + input->accumulate;
#else
	input->out += error * input->kp + (error - input->last_error) * input->kd;
#endif
#if defined(SPEED_WITH_feedforward)
#if defined(SPEED_WITH_Second_order_feedforward)
	input->out += ((input->target - input->last_target) - (input->last_target - input->last_target2)) * input->kf2;
	input->last_target2 = input->last_target;
#endif
	input->out += (input->target - input->last_target) * input->kf;
	input->last_target = input->target;
#endif
	input->last_error = error;
	input->last_real = input->real;
}

void pid_run_rif(pid_rif *input)
{
	input->real = input->real * 0.6 + input->last_real * 0.4;
	int error = input->target - input->real;
	input->out = error * input->kp + (error - input->last_error) * input->kd;
	input->last_error = error;
	input->last_real = input->real;
}

void pid_run_distance(pid_distance *input)
{
	float error = input->target - input->real;
	input->out = error * input->kp + (error - input->last_error) * input->kd;
	if (input->out > input->limit)
		input->out = input->limit;
	else if (input->out < -input->limit)
		input->out = -input->limit;
	input->last_error = error;
}

void pid_run_wit(pid_wit *input)
{
	int16_t error = (input->target - input->real);
	error = error * 0.3 + input->last_error * 0.7;
	if (error > 100 || error < -100)
		input->accumulate += error * input->ki;
	if (input->accumulate > 0 && error > 0)
		input->accumulate = 0;
	else if (input->accumulate < 0 && error < 0)
		input->accumulate = 0;
	if (input->accumulate > 20)
		input->accumulate = 20;
	else if (input->accumulate < -20)
		input->accumulate = -20;
	error /= 400;
#if defined(WIT_WITH_KD)
	input->out = error * input->kp + (error - input->last_error) * input->kd + input->accumulate * 0.1;
	input->last_error = error;
	if (input->out > 30)
		input->out = 30;
	else if (input->out < -30)
		input->out = -30;
#else
	input->out = error * input->kp;
#endif
}