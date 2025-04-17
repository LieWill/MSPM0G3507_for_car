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
#include <math.h>
#include "motor.h"
#include "pid.h"
#include <stdio.h>
#include "wit.h"

#define UART_BUFF_SIZE (20)

#define VOFA
struct
{
	pid_speed left;
	pid_speed right;
} speed = {0};

pid_rif rif = {.target = 0x0180};

#if defined(VOFA)
#include "vofa.h"
vofa bluetooth = {0};
typedef struct
{
	uint8_t RxBuff[UART_BUFF_SIZE];
	volatile bool complete;
	uint8_t size;
} uart;
uart rx = {.RxBuff = {0}, .size = 0, .complete = false};

void vofa_scanf()
{
	if (rx.complete == true)
	{
		rx.RxBuff[rx.size] = 0;
		for(int i = 0; rx.RxBuff[i] != 0; i++)
		{
			DL_UART_transmitDataBlocking(BLUE_TOOTH_INST, rx.RxBuff[i]);
		}
		switch (rx.RxBuff[0])
		{
		case 'S':
			switch (rx.RxBuff[1])
			{
			case 'L':
				switch (rx.RxBuff[2])
				{
				case 'T':
					sscanf((char *)&rx.RxBuff[3], "%d", &speed.left.target);
					break;
				case 'P':
					sscanf((char *)&rx.RxBuff[3], "%f", &speed.left.kp);
					break;
#if defined(SPEED_WITH_KI)
				case 'I':
					sscanf((char *)&rx.RxBuff[3], "%f", &speed.left.ki);
					break;
#endif
				case 'D':
					sscanf((char *)&rx.RxBuff[3], "%f", &speed.left.kd);
					break;
				}
				break;
			case 'R':
				break;
			}
			break;
		}
		rx.size = 0;
		rx.complete = false;
	}
}
#endif

int main(void)
{
	SYSCFG_DL_init();

	NVIC_EnableIRQ(BLUE_TOOTH_INST_INT_IRQN);
	NVIC_EnableIRQ(QEI_INT_IRQN);
	NVIC_EnableIRQ(TIMER_INST_INT_IRQN);
	
	DL_Timer_startCounter(TIMER_INST);
	motor_init(Motor_INST, Motor_INST);
	speed.left.target = 0;
	while (1)
	{
#if defined(VOFA)
		vofa_scanf();
#endif
		//delay_cycles(500000);
	}
}
void BLUE_TOOTH_INST_IRQHandler(void)
{

	switch (DL_UART_Main_getPendingInterrupt(BLUE_TOOTH_INST))
	{
	case DL_UART_IIDX_RX:
		//DL_UART_transmitDataBlocking(BLUE_TOOTH_INST, DL_UART_receiveData(BLUE_TOOTH_INST));
		rx.RxBuff[rx.size] = DL_UART_receiveData(BLUE_TOOTH_INST);
		if (rx.RxBuff[rx.size++] == '\n')
			rx.complete = true;
		break;
	default:
		break;
	}
}

void GROUP1_IRQHandler(void) // ���������жϺ���
{
	uint32_t gpioA = DL_GPIO_getEnabledInterruptStatus(QEI_PORT, QEI_EA1_PIN | QEI_EA2_PIN);
	if ((gpioA & QEI_EA1_PIN) != 0) // �����     A��������
	{
		if (DL_GPIO_readPins(QEI_PORT, QEI_EA2_PIN))
			speed.left.real++;
		else
			speed.left.real--;
		DL_GPIO_clearInterruptStatus(QEI_PORT, QEI_EA1_PIN);
	}
	//	else if ((gpioA & QEI_EA2_PIN) != 0) // �����     A��������
	//	{
	//		if ((gpioA & QEI_EA2_PIN) == QEI_EA2_PIN)
	//			speed.left.real++;
	//		else
	//			speed.left.real--; // B���½���
	//		DL_GPIO_clearInterruptStatus(QEI_PORT, QEI_EA2_PIN);
	//	}
}

void TIMER_INST_IRQHandler(void)
{
#if defined(VOFA)
	bluetooth.data[0].f_num = speed.left.real;
	bluetooth.data[1].f_num = speed.left.target;
	//	bluetooth.data[2].f_num = speed.left.kp;
	//	bluetooth.data[3].f_num = speed.left.kd;
	vofa_transmitfloat(&bluetooth, 2);
#endif
	pid_run_speed(&speed.left);
	pid_run_rif(&rif);
	motor_speed(speed.left.out, 0);
	speed.left.real = 0;
}
