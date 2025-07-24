#include "vofa.h"
#include <ti_msp_dl_config.h>
#include "pid.h"
#include <stdio.h>
#include "wit.h"

extern struct
{
	pid_speed left;
	pid_speed right;
	pid_speed *target;
} speed;
extern pid_rif rif;
extern pid_distance distance;
extern pid_wit angle;
extern float set_speed;

static bool both = false;

enum
{
	SPEED,
	RIF,
	ANGLE,
	DISTANCE
} cmd = ANGLE;

extern enum {
	INS,	  // 转
	TARCKING, // 循迹
	STOP,	  // 停
} status;

#define UART_BUFF_SIZE (20)
struct
{
	uint8_t RxBuff[UART_BUFF_SIZE];
	volatile bool complete;
	uint8_t size;
} rx = {.RxBuff = {0}, .size = 0, .complete = false};

vofa bluetooth = {0};

void vofa_transmitfloat(vofa *temp)
{
	for (uint8_t i = 0; i < temp->tx_num; i++)
	{
		for (uint8_t j = 0; j < 4; j++)
			DL_UART_transmitDataBlocking(WIT_uart_INST, temp->data[i].c[j]);
	}
	for (uint8_t i = 0; i < 4; i++)
		DL_UART_transmitDataBlocking(WIT_uart_INST, ((uint8_t[]){0x00, 0x00, 0x80, 0x7F})[i]);
	temp->tx_num = 0;
}

bool vofa_add_value(vofa *temp, float value)
{
	if (temp->tx_num <= VOFA_TX_VALUE_MAX)
	{
		temp->data[temp->tx_num++].f_num = value;
		return true;
	}
	else
		return false;
}

void vofa_receive()
{
	if (rx.complete == true)
	{
		float angle_temp = 0;
		switch (rx.RxBuff[0])
		{
		case 'S':
			switch (rx.RxBuff[1])
			{
			case 'T':
				sscanf((char *)&rx.RxBuff[2], "%f", &set_speed);
				//					sscanf((char *)&rx.RxBuff[2], "%f", &speed.right.target);
				break;
			case 'L':
				switch (rx.RxBuff[2])
				{
				case 'P':
					sscanf((char *)&rx.RxBuff[3], "%f", &speed.left.kp);
					break;
#if defined(SPEED_WITH_KI)
				case 'I':
					sscanf((char *)&rx.RxBuff[3], "%f", &speed.left.ki);
					break;
#endif
#if defined(SPEED_WITH_feedforward)
				case 'F':
					sscanf((char *)&rx.RxBuff[3], "%f", &speed.left.kf);
					break;
#if defined(SPEED_WITH_Second_order_feedforward)
				case '2':
					if (rx.RxBuff[3] == 'F')
						sscanf((char *)&rx.RxBuff[4], "%f", &speed.left.kf2);
					break;
#endif
#endif
				case 'D':
					sscanf((char *)&rx.RxBuff[3], "%f", &speed.left.kd);
					break;
				}
				break;
			case 'R':
				switch (rx.RxBuff[2])
				{
				case 'P':
					sscanf((char *)&rx.RxBuff[3], "%f", &speed.right.kp);
					break;
#if defined(SPEED_WITH_KI)
				case 'I':
					sscanf((char *)&rx.RxBuff[3], "%f", &speed.right.ki);
					break;
#endif
#if defined(SPEED_WITH_feedforward)
				case 'F':
					sscanf((char *)&rx.RxBuff[3], "%f", &speed.right.kf);
					break;
#if defined(SPEED_WITH_Second_order_feedforward)
				case '2':
					if (rx.RxBuff[3] == 'F')
						sscanf((char *)&rx.RxBuff[4], "%f", &speed.right.kf2);
					break;
#endif
#endif
				case 'D':
					sscanf((char *)&rx.RxBuff[3], "%f", &speed.right.kd);
					break;
				}
				break;
			}
			break;
		case 'R':
			switch (rx.RxBuff[1])
			{
			case 'P':
				sscanf((char *)&rx.RxBuff[2], "%f", &rif.kp);
				break;
			case 'D':
				sscanf((char *)&rx.RxBuff[2], "%f", &rif.kd);
				break;
			}
			break;
		case 'A':
			switch (rx.RxBuff[1])
			{
			case 'P':
				sscanf((char *)&rx.RxBuff[2], "%f", &angle.kp);
				break;
#if defined(WIT_WITH_KD)
			case 'D':
				sscanf((char *)&rx.RxBuff[2], "%f", &angle.kd);
				break;
#endif
			case 'T':
				sscanf((char *)&rx.RxBuff[2], "%f", &angle_temp);
				angle.target = wit_to_int16(angle_temp);
				break;
			}
			break;
		case 'D':
			switch (rx.RxBuff[1])
			{
			case 'P':
				sscanf((char *)&rx.RxBuff[2], "%f", &distance.kp);
				break;
			case 'D':
				sscanf((char *)&rx.RxBuff[2], "%f", &distance.kd);
				break;
			case 'T':
				sscanf((char *)&rx.RxBuff[2], "%f", &distance.target);
				break;
			}
			break;
		case 'T':
			switch (rx.RxBuff[1])
			{
			case 'S':
				cmd = SPEED;
				break;
			case 'R':
				cmd = RIF;
				status = TARCKING;
				break;
			case 'D':
				cmd = DISTANCE;
				break;
			case 'A':
				angle.target = wit_get_yaw();
				status = INS;
				cmd = ANGLE;
				break;
			}
			break;
		case 'O':
			if (rx.RxBuff[1] == 'P')
			{
				speed.left.target = 0;
				speed.right.target = 0;
				angle.kp = 0;
				angle.kd = 0;
			}
			break;
		}
		rx.size = 0;
		rx.complete = false;
	}
}

void WIT_uart_INST_IRQHandler(void)
{

	switch (DL_UART_Main_getPendingInterrupt(WIT_uart_INST))
	{
	case DL_UART_IIDX_RX:
		do
		{
			rx.RxBuff[rx.size] = DL_UART_receiveData(WIT_uart_INST);
			if (rx.RxBuff[rx.size++] == '\n')
				rx.complete = true;
		} while (!DL_UART_isRXFIFOEmpty(WIT_uart_INST));
		break;
	default:
		break;
	}
}
