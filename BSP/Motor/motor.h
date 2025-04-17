#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "ti_msp_dl_config.h"

#define Motor_port MOTOR_PORT
#define GPIO_LEFT1 MOTOR_AIN1_PIN
#define GPIO_LEFT2 MOTOR_AIN2_PIN
#define GPIO_RIGHT1 MOTOR_BIN1_PIN
#define GPIO_RIGHT2 MOTOR_BIN2_PIN

void motor_init();
void motor_speed(int left, int right);

#endif