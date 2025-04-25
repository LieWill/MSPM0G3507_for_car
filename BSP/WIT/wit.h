#ifndef __WIT_H__
#define __WIT_H__

#include "ti_msp_dl_config.h"
#include "REG.h"

//#define USING_I2C

#if defined (USING_I2C)
#define WIT_ADD (0x50)
volatile uint16_t wit_get_yaw(I2C_Regs *i2c_regs);
#else
volatile uint16_t wit_get_yaw(void);
volatile uint16_t wit_get_roll(void);
volatile uint16_t wit_get_pitch(void);
#endif

inline void wit_init()
{
    NVIC_EnableIRQ(BLUE_TOOTH_INST_INT_IRQN);
}

inline float wit_to_float(uint16_t data) {
    return data / 32768.0f * 180.0f;
}

inline uint16_t wit_to_uint16(float angle) {
    return angle / 180.0f * 32768.0f; 
}

#endif