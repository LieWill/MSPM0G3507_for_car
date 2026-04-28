/*
 * VOFA+ 上位机通信模块头文件
 * 提供与 VOFA+ 上位机的数据打包、发送，以及在线调参指令的接收解析接口。
 */
#ifndef __VOFA_H__
#define __VOFA_H__

#include <stdint.h>
#include <stdbool.h>
#include "ti_msp_dl_config.h"

#define VOFA_TX_VALUE_MAX 10
#define VOFA //不定义就是不使用VOFA

typedef struct
{
	union
	{
		float f_num;
		uint8_t c[4];
	} data[VOFA_TX_VALUE_MAX];
	uint16_t tx_num;
} vofa;

void vofa_transmitfloat(vofa *temp);
bool vofa_add_value(vofa *temp, float value);
void vofa_receive();
inline void vofa_init()
{
	NVIC_EnableIRQ(WIT_uart_INST_INT_IRQN);
}

#endif