/*
 * 定时器模块源文件
 * 在定时器中断中执行 PID 闭环控制算法、读取传感器状态并驱动电机。
 */
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
	// 1. 读取左右电机正交编码器，获取当前实际速度
	speed.left.real = qei_left_speed();
	speed.right.real = qei_right_speed();
	// 2. 读取红外灰度传感器阵列，判断是否压到黑线，并计算位置特征值
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
	
	// 3. 根据当前系统工作模式执行不同的上层闭环控制策略
	if (status == INS)
	{
		// 惯性导航模式：读取并转换偏航角 (Yaw)
		angle.real = ((union {
						 int16_t i;
						 uint16_t u;
					 })wit_get_yaw())
						 .i;
		pid_run_wit(&angle);  // 执行角度/姿态 PID 闭环

		// 累加左右轮速度作为里程计，并执行距离 PID 闭环
		distance.real += speed.left.real + speed.right.real;
		pid_run_distance(&distance);

		// 根据距离和角度的 PID 输出值，计算左右轮的目标速度（差速控制）
		speed.left.target = distance.out - angle.out;
		speed.right.target = distance.out + angle.out;
	}
	else if (status == TARCKING)
	{
		// 黑线循迹模式：执行红外传感器巡线 PID 闭环
		pid_run_rif(&rif);
		// 基础设定速度加上巡线 PID 输出作为转向补偿
		speed.left.target = set_speed + rif.out;
		speed.right.target = set_speed - rif.out;
	}
	else if (status == STOP)
	{
		// 停止模式：目标速度归零
		speed.left.target = 0;
		speed.right.target = 0;
	}

	// 4. 执行底层的速度环 PID 计算
	pid_run_speed(&speed.left);
	pid_run_speed(&speed.right);
	
	// 5. 将计算出的最终控制量（PWM占空比）输出到电机驱动硬件
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