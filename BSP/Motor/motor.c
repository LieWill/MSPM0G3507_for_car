#include "motor.h"

void motor_init()
{
    DL_GPIO_setPins(Motor_port, GPIO_LEFT1);
    DL_GPIO_setPins(Motor_port, GPIO_LEFT2);
    DL_GPIO_setPins(Motor_port, GPIO_RIGHT1);
    DL_GPIO_setPins(Motor_port, GPIO_RIGHT2);
    DL_Timer_startCounter(Motor_INST);
    DL_TimerG_setCaptureCompareValue(Motor_INST, 0, DL_TIMER_CC_0_INDEX);
    DL_TimerG_setCaptureCompareValue(Motor_INST, 0, DL_TIMER_CC_1_INDEX);
    DL_TimerG_setCaptureCompareValue(Motor_INST, 0, DL_TIMER_CC_0_INDEX);
    DL_TimerG_setCaptureCompareValue(Motor_INST, 0, DL_TIMER_CC_1_INDEX);
}

void motor_speed(int left, int right)
{
    if (right > 0)
    {
        DL_GPIO_setPins(Motor_port, GPIO_LEFT1);
        DL_GPIO_clearPins(Motor_port, GPIO_LEFT2);
        DL_TimerG_setCaptureCompareValue(Motor_INST, right, DL_TIMER_CC_0_INDEX);
    }
    else if (right < 0)
    {
        DL_GPIO_setPins(Motor_port, GPIO_LEFT2);
        DL_GPIO_clearPins(Motor_port, GPIO_LEFT1);
        DL_TimerG_setCaptureCompareValue(Motor_INST, -right, DL_TIMER_CC_0_INDEX);
    }
    else
    {
        DL_GPIO_setPins(Motor_port, GPIO_LEFT1);
        DL_GPIO_setPins(Motor_port, GPIO_LEFT2);
        DL_TimerG_setCaptureCompareValue(Motor_INST, 0, DL_TIMER_CC_0_INDEX);
    }
		
		if (left > 0)
    {
        DL_GPIO_setPins(Motor_port, GPIO_RIGHT1);
        DL_GPIO_clearPins(Motor_port, GPIO_RIGHT2);
        DL_TimerG_setCaptureCompareValue(Motor_INST, left, DL_TIMER_CC_1_INDEX);
    }
    else if (left < 0)
    {
        DL_GPIO_setPins(Motor_port, GPIO_RIGHT2);
        DL_GPIO_clearPins(Motor_port, GPIO_RIGHT1);
        DL_TimerG_setCaptureCompareValue(Motor_INST, -left, DL_TIMER_CC_1_INDEX);
    }
    else
    {
        DL_GPIO_setPins(Motor_port, GPIO_RIGHT1);
        DL_GPIO_setPins(Motor_port, GPIO_RIGHT2);
        DL_TimerG_setCaptureCompareValue(Motor_INST, 0, DL_TIMER_CC_1_INDEX);
    }
}