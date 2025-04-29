#include "timer.h"
#include "qei.h"
#include "wit.h"
#include "vofa.h"

struct
{
	pid_speed left;
	pid_speed right;
	pid_speed *target;
} speed = {.left = {.kp = 2.4, .kd = 21, .kf = 3, .kf2 = 5, .out = 0, .real = 0, .last_real = 0, .last_target = 0, .last_target2 = 0, .target = 0},
		   .right = {.kp = 2.4, .kd = 21, .kf = 3, .kf2 = 5, .out = 0, .real = 0, .last_real = 0, .last_target = 0, .last_target2 = 0, .target = 0},
		   .target = &speed.left};
float set_speed = 0;
pid_rif rif = {.out = 0, .kp = 2.4, .kd = 9.5, .last_error = 0, .target = 2};
pid_distance distance = {.kd = 0, .kp = 0.05, .last_error = 0, .real = 0, .out = 0, .target = 0, .last_error = 0};
pid_wit angle = {.kd = -1.6, .kp = -1.1, .last_error = 0, .last_real = 0, .ki = -0.001};
bool isBlack = false;

extern volatile uint8_t Bee;

extern enum {
	SPEED,
	RIF,
	ANGLE,
	DISTANCE
} cmd;

extern enum {
	INS,	  // 惯性导航
	TARCKING, // 循迹
	STOP,	  // 停
} status;

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
	if (GPIOB->DIN31_0 & 0xFFF)
	{
		isBlack = true;
		rif.real = rif_to_value(GPIOB->DIN31_0);
	}
	else
	{
		isBlack = false;
		rif.real = 0;
	}
	if (status == INS)
	{
		angle.real = ((union {
						 int16_t i;
						 uint16_t u;
					 })wit_get_yaw())
						 .i;
		pid_run_wit(&angle);
		distance.real += speed.left.real + speed.right.real;
		pid_run_distance(&distance);
		speed.left.target = distance.out - angle.out;
		speed.right.target = distance.out + angle.out;
	}
	else if (status == TARCKING)
	{
		pid_run_rif(&rif);
		speed.left.target = set_speed + rif.out;
		speed.right.target = set_speed - rif.out;
	}
	else if (status == STOP)
	{
		speed.left.target = 0;
		speed.right.target = 0;
	}
	pid_run_speed(&speed.left);
	pid_run_speed(&speed.right);
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
		vofa_add_value(&bluetooth, wit_to_float(angle.real));
		vofa_add_value(&bluetooth, wit_to_float(angle.target));
		vofa_add_value(&bluetooth, angle.out);
		break;
	case RIF:
		vofa_add_value(&bluetooth, rif.real);
		vofa_add_value(&bluetooth, rif.target);
		vofa_add_value(&bluetooth, GPIOB->DIN31_0 & 0xFFF);
		break;
	case DISTANCE:
		vofa_add_value(&bluetooth, distance.real);
		vofa_add_value(&bluetooth, distance.target);
		break;
	}
	vofa_transmitfloat(&bluetooth);
#endif
	if(Bee)
	{
		Bee--;
		DL_GPIO_setPins(buzzer_PORT, buzzer_PIN_12_PIN);
	}
	else
		DL_GPIO_clearPins(buzzer_PORT, buzzer_PIN_12_PIN);
#if defined(CPU_USAGE)
	cpu_counter = TIMER_INST->COUNTERREGS.CTR;
#endif
}