#ifndef __QEI_H__
#define __QEI_H__

#include "ti_msp_dl_config.h"

void qei_init(void);
int qei_left_speed();
int qei_right_speed();

#endif