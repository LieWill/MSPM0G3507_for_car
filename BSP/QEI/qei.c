#include "qei.h"
#include "pid.h"

static int left_speed = 0;
static int right_speed = 0;

void qei_init(void)
{
	NVIC_EnableIRQ(QEI_INT_IRQN);
}

void GROUP1_IRQHandler(void) // ���������жϺ���
{
	uint32_t qei = DL_GPIO_getEnabledInterruptStatus(QEI_PORT, QEI_EA1_PIN | QEI_EB1_PIN);
	if ((qei & QEI_EA1_PIN) != 0) // �����     A��������
	{
		if (DL_GPIO_readPins(QEI_PORT, QEI_EA2_PIN))
			right_speed--;
		else
			right_speed++;
		DL_GPIO_clearInterruptStatus(QEI_PORT, QEI_EA1_PIN);
	}
	if ((qei & QEI_EB1_PIN) != 0) // �����     A��������
	{
		if (DL_GPIO_readPins(QEI_PORT, QEI_EB2_PIN))
			left_speed--;
		else
			left_speed++;
		DL_GPIO_clearInterruptStatus(QEI_PORT, QEI_EB1_PIN);
	}
}

int qei_left_speed()
{
	int res = left_speed;
	left_speed = 0;
	return res;
}

int qei_right_speed()
{
	int res = right_speed;
	right_speed = 0;
	return res;
}