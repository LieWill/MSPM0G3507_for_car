/*
 * 定时器模块头文件
 * 包含系统定时器初始化及 CPU 占用率计算接口。
 */
#ifndef __TIMER_H__
#define __TIMER_H__

#include "ti_msp_dl_config.h"
#include "vofa.h"
#include "rif.h"
#include "motor.h"
#include "pid.h"

#define CPU_USAGE

#if defined(CPU_USAGE)
float get_cpu_usage();
#endif

inline void timer_init(void)
{
    DL_Timer_startCounter(TIMER_INST);
    NVIC_EnableIRQ(TIMER_INST_INT_IRQN);
}

#endif