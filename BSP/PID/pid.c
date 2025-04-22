#include "pid.h"

void pid_run_speed(pid_speed *input)
{
		input->real = input->real * 0.2 + input->last_real * 0.8; //滤波；
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
//	if(input->out > 1000)
//			input->out = 1000;
//		else if(input->out < -1000)
//			input->out = -1000;
		//input->out = 100;
    input->last_error = error;
		input->last_real = input->real;
}

void pid_run_rif(pid_rif *input)
{
    int error = input->target - input->real;
    input->out = error * input->kp + (error - input->last_error) * input->kd;
    input->last_error = error;
}

void pid_run_distance(pid_distance *input)
{
    float error = input->target - input->real;
    input->out = error * input->kp + (error - input->last_error) * input->kd;
    input->last_error = error;
}

void pid_run_wit(pid_wit *input)
{
    int error = input->target - input->real;
#if defined(WIT_WITH_KD)
    input->out = error * input->kp + (error - input->last_error) * input->kd;
#else
    input->out = error * input->kp;
#endif
}