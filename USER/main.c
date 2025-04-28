#include "ti_msp_dl_config.h"

#include "OLED.H"
#include "motor.h"
#include "pid.h"
#include "wit.h"
#include "timer.h"
#include "qei.h"
#include "vofa.h"
#include "flash.h"
#include "task.h"


int main(void)
{
	SYSCFG_DL_init();
	qei_init();
	motor_init(Motor_INST, Motor_INST);
	wit_init();
#if defined(VOFA)
	vofa_init();
#endif
	timer_init();
	OLED_Init(OLED_INST);
	OLED_ShowString(1, 1, "Question");
	task T = NO_QUESTION;
	task select = NO_QUESTION;
	
	while (1)
	{
		if (!DL_GPIO_readPins(Button_PORT, Button_P1_PIN))
		{
			delay_cycles(1000);
			if (!DL_GPIO_readPins(Button_PORT, Button_P1_PIN))
			{
				OLED_ShowNum(2, 1, select);
				while (!DL_GPIO_readPins(Button_PORT, Button_P1_PIN))
					;
				T = select;
				OLED_ShowNum(3, 1, T);
			}
		}
		if (!DL_GPIO_readPins(Button_PORT, Button_P2_PIN))
		{
			delay_cycles(1000);
			if (!DL_GPIO_readPins(Button_PORT, Button_P2_PIN))
			{
				while (!DL_GPIO_readPins(Button_PORT, Button_P2_PIN))
					;
				if(select >= QUESTION_4)
					select = QUESTION_1;
				else
					select++;
				OLED_ShowNum(2, 1, select);
			}
		}
		use_task(&T);
#if defined(VOFA)
		vofa_receive();
#endif
		// use_task(&T);
		// OLED_ShowNum(2, 1, (int)get_cpu_usage());
		// OLED_Printf(1, 1, "Yaw: %.1f  ", wit_to_float(wit_get_yaw()));
		// OLED_Printf(2, 1, "CPU: %.1f%%", get_cpu_usage());
		// OLED_Printf(3, 1, "rif %d", rif_getValue());
	}
}
