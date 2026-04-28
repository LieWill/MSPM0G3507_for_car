/*
 * VOFA+ 上位机通信模块源文件
 * 实现串口数据发送帧封装（JustFloat 协议）与调参字符串解析（动态修改 PID 参数等）。
 */
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

// 使用 VOFA+ 的 JustFloat 协议发送打包好的浮点数据队列 (尾部追加帧尾)
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

// 将需要上传并在上位机绘制波形的数据压入发送队列
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

// 解析来自 VOFA+ 上位机的字符串调参指令
void vofa_receive()
{
	if (rx.complete == true)
	{
		float angle_temp = 0;
		switch (rx.RxBuff[0])
		{
		case 'S': // 速度相关指令 (Speed)，例如 SLPxxx 表示左轮 kp
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
		case 'R': // 灰度循迹相关指令 (RIF)
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
		case 'A': // 角度/姿态相关指令 (Angle)
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
		case 'D': // 距离/里程相关指令 (Distance)
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
		case 'T': // 状态机/显示模式切换指令 (Toggle)
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

// 串口接收中断，用于逐字节接收上位机发来的以换行符 '\n' 结尾的调参命令
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
