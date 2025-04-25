#include "wit.h"

static struct
{
	uint16_t roll;
	uint16_t pitch;
	uint16_t yaw;
} angle = {0};

#if defined(USING_I2C)
volatile uint16_t wit_get_yaw(I2C_Regs *i2c_regs)
{
	// volatile uint16_t res = 0;
	//    uint8_t yaw = Yaw;
	//    DL_I2C_fillControllerTXFIFO(i2c_regs, &yaw, 1);
	//    while (!(DL_I2C_getControllerStatus(i2c_regs) & DL_I2C_CONTROLLER_STATUS_IDLE));
	//
	//    DL_I2C_startControllerTransfer(i2c_regs, 0x50, DL_I2C_CONTROLLER_DIRECTION_TX, 2);
	//
	//    while (DL_I2C_getControllerStatus(i2c_regs) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
	//    while (!(DL_I2C_getControllerStatus(i2c_regs) & DL_I2C_CONTROLLER_STATUS_IDLE));
	//    //DL_I2C_flushControllerTXFIFO(i2c_regs);
	//
	//		delay_cycles(100);
	//    DL_I2C_startControllerTransfer(i2c_regs, 0x50, DL_I2C_CONTROLLER_DIRECTION_RX, 2);
	//	//DL_I2C_startControllerTransferAdvanced();
	//		while (!DL_I2C_isControllerRXFIFOEmpty(i2c_regs));
	//    res = DL_I2C_receiveControllerData(i2c_regs) << 8;
	//		while (!DL_I2C_isControllerRXFIFOEmpty(i2c_regs));
	//    res |= DL_I2C_receiveControllerData(i2c_regs);

	// DL_I2C_fillControllerTXFIFO(i2c_regs, &yaw, 1);
	// res = ReadReg(Yaw);
	// res |= ReadReg(Yaw+1) + 12;
	static uint16_t last;

	// while(Wit_rx.status != start);// && Wit_rx.buff.data.Sum == 0x55 + 0x53 + Wit_rx.buff.c[0] + Wit_rx.buff.c[1] + Wit_rx.buff.c[2]
	//+ Wit_rx.buff.c[3] + Wit_rx.buff.c[4] + Wit_rx.buff.c[5] + Wit_rx.buff.c[6] + Wit_rx.buff.c[7])
	last = y;
	return last;
}
#else
static struct
{
	uint8_t size;
	bool complete;
	enum
	{
		stop,
		check,
		start
	} status;
	union
	{
		uint8_t c[9];
		struct
		{
			uint16_t roll;
			uint16_t pitch;
			uint16_t yaw;
			uint16_t Version;
			uint8_t Sum;
		} data;
	} buff;
} Wit_rx = {0};

volatile uint16_t wit_get_yaw(void)
{
	return angle.yaw;
}

volatile uint16_t wit_get_roll(void)
{
	return angle.roll;
}

volatile uint16_t wit_get_pitch(void)
{
	return angle.pitch;
}

void BLUE_TOOTH_INST_IRQHandler()
{
	static uint8_t temp;
	switch (DL_UART_Main_getPendingInterrupt(BLUE_TOOTH_INST))
	{
	case DL_UART_IIDX_RX:
		do
		{
			temp = DL_UART_receiveData(BLUE_TOOTH_INST);
			switch (Wit_rx.status)
			{
			case stop:
				if (temp == 0x55)
					Wit_rx.status = check;
				break;
			case check:
				if (temp == 0x53)
					Wit_rx.status = start;
				else
					Wit_rx.status = stop;
				break;
			case start:

				if (Wit_rx.size > 8)
				{
					Wit_rx.size = 0;
					Wit_rx.status = stop;
					if (Wit_rx.buff.data.Sum == (uint8_t)(0x55 + 0x53 + Wit_rx.buff.c[0] + Wit_rx.buff.c[1] + Wit_rx.buff.c[2] + Wit_rx.buff.c[3] + Wit_rx.buff.c[4] + Wit_rx.buff.c[5] + Wit_rx.buff.c[6] + Wit_rx.buff.c[7]))
					{
						angle.yaw = Wit_rx.buff.data.yaw;
						angle.roll = Wit_rx.buff.data.roll;
						angle.pitch = Wit_rx.buff.data.pitch;
					}
				}
				else
					Wit_rx.buff.c[Wit_rx.size++] = temp;
				break;
			}
		} while (!DL_UART_isRXFIFOEmpty(BLUE_TOOTH_INST));
		break;
	default:
		break;
	}
}
#endif