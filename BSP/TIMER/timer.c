#include "timer.h"
#include "qei.h"
#include "wit.h"

#define VOFA
struct
{
	pid_speed left;
	pid_speed right;
	pid_speed *target;
	//float speed;
} speed = {.left = {0}, .right = {0}, .target = &speed.left};
float set_speed = 0;
pid_rif rif = {0};
pid_distance distance = {0};
pid_wit angle = {0};

extern enum {
	SPEED,
	RIF,
	ANGLE,
	DISTANCE
} cmd;

extern vofa bluetooth;

#if defined(CPU_USAGE)
static float cpu_counter = 0;
float get_cpu_usage()
{
	return cpu_counter * 100 / 40.0;
}
#endif

void TIMER_INST_IRQHandler(void)
{
	speed.left.real = qei_left_speed();
	speed.right.real = qei_right_speed();
	if(GPIOB->DIN31_0)
		rif.real = rif_to_value(GPIOB->DIN31_0);
	else
		rif.real = 0;
	pid_run_rif(&rif);
	speed.left.target = set_speed + rif.out;
	speed.right.target = set_speed - rif.out;
	pid_run_speed(&speed.left);
	pid_run_speed(&speed.right);
	distance.real += speed.right.real + speed.right.real;
	pid_run_distance(&distance);
	motor_speed(speed.left.out, speed.right.out);
#if defined(VOFA)
	switch (cmd)
	{
	case SPEED:
		vofa_add_value(&bluetooth, speed.left.real);
		vofa_add_value(&bluetooth, speed.right.real);
		vofa_add_value(&bluetooth, speed.left.target);
		break;
	case ANGLE:
		vofa_add_value(&bluetooth, wit_to_float(wit_get_roll()));
		vofa_add_value(&bluetooth, wit_to_float(wit_get_pitch()));
		vofa_add_value(&bluetooth, wit_to_float(wit_get_yaw()));
		break;
	case RIF:
		vofa_add_value(&bluetooth, rif.real);
		vofa_add_value(&bluetooth, rif.target);
		vofa_add_value(&bluetooth, GPIOB->DIN31_0);
		break;
	case DISTANCE:
		vofa_add_value(&bluetooth, distance.real);
		vofa_add_value(&bluetooth, distance.target);
		break;
	}
	vofa_transmitfloat(&bluetooth);
#endif
#if defined(CPU_USAGE)
	cpu_counter = TIMER_INST->COUNTERREGS.CTR;
#endif
}