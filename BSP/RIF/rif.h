#ifndef __RIF_H__
#define __RIF_H__

#include "ti_msp_dl_config.h"

inline uint16_t rif_getValue()
{
    return GPIOB->DIN31_0 & 0xFF;
}
int rif_to_value(uint16_t value);

#endif