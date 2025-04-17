#ifndef __WIT_H__
#define __WIT_H__

#include "ti_msp_dl_config.h"
#include "REG.h"

#define WIT_ADD (0x50)

uint16_t wit_get_yaw(I2C_Regs *i2c_regs);
static inline float wit_to_float(uint16_t data) {
    return data / 32768.0f * 180.0f;
}

static inline uint16_t wit_to_uint16(float angle) {
    return angle / 180.0f * 32768.0f; 
}

#endif