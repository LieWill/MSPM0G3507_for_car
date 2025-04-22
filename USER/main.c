#include "ti_msp_dl_config.h"
#include "OLED.H"
#include <math.h>
#include "motor.h"
#include "pid.h"
#include <stdio.h>
#include "wit.h"
#include "timer.h"
#include "qei.h"

pid_distance distance = {0};

int main(void)
{
	SYSCFG_DL_init();
	// OLED_Init(WIT_INST);
	// OLED_ShowString(1, 1, "hello");
	qei_init();
	NVIC_EnableIRQ(BLUE_TOOTH_INST_INT_IRQN);
	NVIC_EnableIRQ(GPIOB_INT_IRQn);
	NVIC_EnableIRQ(GPIOA_INT_IRQn);
	NVIC_EnableIRQ(TIMER_INST_INT_IRQN);
	NVIC_EnableIRQ(WIT_uart_INST_INT_IRQN);
	DL_Timer_startCounter(TIMER_INST);
	motor_init(Motor_INST, Motor_INST);
	while (1)
	{
#if defined(VOFA)
		vofa_receive();
#endif
	}
}
