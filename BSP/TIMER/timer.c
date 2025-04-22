#include "timer.h"
#include "qei.h"
#include "wit.h"

#define VOFA
struct
{
	pid_speed left;
	pid_speed right;
	pid_speed *target;
	bool wit;
} speed = {.left = {0}, .right = {0}, .target = &speed.left, .wit = false};

pid_rif rif = {.target = 0x0180};

extern vofa bluetooth;

void TIMER_INST_IRQHandler(void)
{
	speed.left.real = qei_left_speed();
	speed.right.real = qei_right_speed();
	pid_run_speed(&speed.left);
	pid_run_speed(&speed.right);
	#if defined(VOFA)
	if(speed.wit == false)
	{
		vofa_add_value(&bluetooth, speed.target->real);
		vofa_add_value(&bluetooth, speed.target->target);
		vofa_add_value(&bluetooth, speed.target->out / 100);
		vofa_add_value(&bluetooth, wit_to_float(wit_get_yaw()));
	}
	else
	{
		vofa_add_value(&bluetooth, wit_to_float(wit_get_roll()));
		vofa_add_value(&bluetooth, wit_to_float(wit_get_pitch()));
		vofa_add_value(&bluetooth, wit_to_float(wit_get_yaw()));
	}
	vofa_transmitfloat(&bluetooth);
#endif
	pid_run_rif(&rif);
	motor_speed((int)speed.left.out, (int)speed.right.out); 
}