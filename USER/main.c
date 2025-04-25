#include "ti_msp_dl_config.h"

#include "OLED.H"
#include "motor.h"
#include "pid.h"
#include "wit.h"
#include "timer.h"
#include "qei.h"
//#include "vofa.h"
#include "flash.h"

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
	while (1)
	{
#if defined(VOFA)
		vofa_receive();
#endif
		//OLED_ShowNum(2, 1, (int)get_cpu_usage());
		//OLED_Printf(1, 1, "Yaw: %.1f  ", wit_to_float(wit_get_yaw()));
		//OLED_Printf(2, 1, "CPU: %.1f%%", get_cpu_usage());
		//OLED_Printf(3, 1, "rif %d", rif_getValue());
	}
}
