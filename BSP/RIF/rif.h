#ifndef __RIF_H__
#define __RIF_H__

#include "ti_msp_dl_config.h"

inline uint16_t rif_getValue()
{
    return RIF_PORT->DIN31_0;
}

#endif