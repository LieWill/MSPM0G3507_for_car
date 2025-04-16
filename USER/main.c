/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti_msp_dl_config.h"
#include "OLED.H"
#include "vofa.h""

#define UART_BUFF_SIZE (20)

typedef struct
{
	uint8_t RxBuff[UART_BUFF_SIZE];
	bool complete;
	uint8_t size;
} uart;
uart rx = {.RxBuff = {0}, .size = 0, .complete = false};

volatile bool tranmit = false;

static void uart_transmit(char *word)
{
	for (uint8_t i = 0; word[i] != '\0'; i++)
		DL_UART_transmitDataBlocking(BLUE_TOOTH_INST, word[i]);
}

int main(void)
{   
	SYSCFG_DL_init();
	OLED_Init(OLED_INST);
	OLED_ShowString(1, 1, "hello");
	DL_TimerG_startCounter(Motor_INST);
	vofa bluetooth;
	vofa_set(&bluetooth, uart_transmit, NULL);
	//DL_TimerG_setCaptureCompareValue(Motor_INST, 0, DL_TIMER_CC_0_INDEX);
	//DL_TimerG_setCaptureCompareValue(Motor_INST, 0, DL_TIMER_CC_1_INDEX);
	
	NVIC_EnableIRQ(BLUE_TOOTH_INST_INT_IRQN);
	int n = 0;
   while (1) {
//		for(uint32_t i = 0; i < 1000; i++)
//		{
//			DL_TimerG_setCaptureCompareValue(Motor_INST, i, DL_TIMER_CC_0_INDEX);
//			DL_TimerG_setCaptureCompareValue(Motor_INST, i, DL_TIMER_CC_1_INDEX); 
			//delay_cycles(500000);
//			//uart_transmit("hello, this is mspm0g3507\n")
//		}7
		 //DL_UART_receiveData
		 //DL_UART_transmitDataBlocking(BLUE_TOOTH_INST, 'a');
//		 if(tranmit == true)
//		 {
//			 for(uint8_t i = 0; i < 50; i++)
//				DL_UART_transmitData(BLUE_TOOTH_INST, RxBuff[i]);
//			 tranmit = false;
//		 }
		 if(rx.complete)
		 {
			 rx.complete = false;
			 rx.RxBuff[rx.size] = 0;
			 uart_transmit(rx.RxBuff);
			 rx.size = 0;
		 }
		 delay_cycles(1000000);
		 vofa_printf(&bluetooth, "count = %d", n++);
   }
}

void BLUE_TOOTH_INST_IRQHandler (void)
{
	uint8_t i;
	switch(DL_UART_Main_getPendingInterrupt(BLUE_TOOTH_INST))
	{
	case DL_UART_IIDX_RX:
		rx.RxBuff[rx.size] = DL_UART_receiveData(BLUE_TOOTH_INST);
		if(rx.RxBuff[rx.size++] == '\n')
			rx.complete = true;
		break;
	default:
		break;
	}
}
