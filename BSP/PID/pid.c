#include "pid.h"

void pid_run_speed(pid_speed *input)
{
    int error = input->target - input->real;
#if defined(SPEED_WITH_KI)
		input->accumulate += error * input->ki;
		input->out += error * input->kp + (error - input->last_error) * input->kd + input->accumulate;
#else
    input->out += error * input->kp + (error - input->last_error) * input->kd;
#endif
    input->last_error = error;
}

void pid_run_rif(pid_rif *input)
{
    int error = input->target - input->real;
    input->out = error * input->kp + (error - input->last_error) * input->kd;
    input->last_error = error;
}

void pid_run_wit(pid_wit *input)
{
    int error = input->target - input->real;
#if defined (WIT_WITH_KD)
    input->out = error * input->kp + (error - input->last_error) * input->kd;
#else
    input->out = error * input->kp;
#endif
}