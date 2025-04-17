#include "pid.h"

void pid_run_speed(pid_speed *input)
{
    int error = input->target - input->real;
    input->out += error * input->kp + (error - input->last_error) * input->kd;
    input->last_error = error;
}

void pid_run_rif(pid_rif *input)
{
    int error = input->target - input->real;
    input->out = error * input->kp + (error - input->last_error) * input->kd;
    input->last_error = error;
}