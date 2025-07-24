/*
 * oled.c
 *
 *  Created on: Mar 18, 2024
 *      Author: 123
 */
#include "OLED.H"
#include "OLED_Font.h"
#include <stdio.h>
#include <stdarg.h>

#define OLED_ADDRESS 0x78

I2C_Regs *init = NULL;

static void I2C_WriteByte(uint8_t addr, uint8_t data) {	
    uint8_t gTxPacket[2] = {addr, data};  // 如果是数据模式，设置控制字节为0x40

    // 将数据填充到I2C控制器的TX FIFO中
    DL_I2C_fillControllerTXFIFO(init, &gTxPacket[0], 2);

    // 禁用TX FIFO触发中断
    DL_I2C_disableInterrupt(init, DL_I2C_INTERRUPT_CONTROLLER_TXFIFO_TRIGGER);

    // 等待I2C控制器空闲
    while (!(DL_I2C_getControllerStatus(init) & DL_I2C_CONTROLLER_STATUS_IDLE));

    // 启动I2C传输，目标地址为0x3C，方向为TX
    DL_I2C_startControllerTransfer(init, 0x3C, DL_I2C_CONTROLLER_DIRECTION_TX, 2);

    // 等待传输完成或出错
    //while ((gI2cControllerStatus != I2C_STATUS_TX_COMPLETE) && (gI2cControllerStatus != I2C_STATUS_ERROR));

    // 等待I2C总线空闲
    while (DL_I2C_getControllerStatus(init) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);

    // 等待I2C控制器空闲
    while (!(DL_I2C_getControllerStatus(init) & DL_I2C_CONTROLLER_STATUS_IDLE));
}

void OLED_SendCmd(uint8_t cmd)
{
//    uint8_t sendBuffer[2] = {0x00, cmd};
//		
//    DL_I2C_fillControllerTXFIFO(init, sendBuffer, 2);
//    while (!(DL_I2C_getControllerStatus(init) & DL_I2C_CONTROLLER_STATUS_IDLE));
//		
//    DL_I2C_startControllerTransfer(init, OLED_ADDRESS, DL_I2C_CONTROLLER_DIRECTION_TX, 2);
//    while (DL_I2C_getControllerStatus(init) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
//    while (!(DL_I2C_getControllerStatus(init) & DL_I2C_CONTROLLER_STATUS_IDLE));
//    DL_I2C_flushControllerTXFIFO(init);
	I2C_WriteByte(0x00, cmd);
}

void OLED_WriteData(uint8_t Data)
{
//    uint8_t sendBuffer[2] = {0x40, Data};
//		
//    DL_I2C_fillControllerTXFIFO(init, sendBuffer, 2);
//    while (!(DL_I2C_getControllerStatus(init) & DL_I2C_CONTROLLER_STATUS_IDLE));
//		
//    DL_I2C_startControllerTransfer(init, OLED_ADDRESS, DL_I2C_CONTROLLER_DIRECTION_TX, 2);
//    while (DL_I2C_getControllerStatus(init) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
//    while (!(DL_I2C_getControllerStatus(init) & DL_I2C_CONTROLLER_STATUS_IDLE));
//    DL_I2C_flushControllerTXFIFO(init);
	I2C_WriteByte(0x40, Data);
}

void OLED_SetCursor(uint8_t Y, uint8_t X)
{
    OLED_SendCmd(0xB0 | Y);                 // 设置Y位置
    OLED_SendCmd(0x10 | ((X & 0xF0) >> 4)); // 设置X位置高4位
    OLED_SendCmd(0x00 | (X & 0x0F));        // 设置X位置低4位
}

void OLED_Clear(void)
{
    uint8_t i, j;
    for (j = 0; j < 8; j++)
    {
        OLED_SetCursor(j, 0);
			
        for (i = 0; i < 128; i++)
        {
            OLED_WriteData(0x00);
        }
    }
}

void OLED_Init(I2C_Regs *set)
{
    init = set;
    
    OLED_SendCmd(0xAE); // 关闭显示
    OLED_SendCmd(0xD5); // 设置显示时钟分频比/振荡器频率
    OLED_SendCmd(0x80);
    OLED_SendCmd(0xA8); // 设置多路复用率
    OLED_SendCmd(0x3F);
    OLED_SendCmd(0xD3); // 设置显示偏移
    OLED_SendCmd(0x00);
    OLED_SendCmd(0x40); // 设置显示开始行
    OLED_SendCmd(0xA1); // 设置左右方向，0xA1正常 0xA0左右反置
    OLED_SendCmd(0xC8); // 设置上下方向，0xC8正常 0xC0上下反置
    OLED_SendCmd(0xDA); // 设置COM引脚硬件配置
    OLED_SendCmd(0x12);
    OLED_SendCmd(0x81); // 设置对比度控制
    OLED_SendCmd(0xCF);
    OLED_SendCmd(0xD9); // 设置预充电周期
    OLED_SendCmd(0xF1);
    OLED_SendCmd(0xDB); // 设置VCOMH取消选择级别
    OLED_SendCmd(0x30);
    OLED_SendCmd(0xA4); // 设置整个显示打开/关闭
    OLED_SendCmd(0xA6); // 设置正常/倒转显示
    OLED_SendCmd(0x8D); // 设置充电泵
    OLED_SendCmd(0x14);
    OLED_SendCmd(0xAF); // 开启显示
    OLED_Clear();       // OLED清屏
}

/**
 * @brief  OLED显示一个字符
 * @param  Line 行位置，范围：1-4
 * @param  Column 列位置，范围：1-16
 * @param  Char 要显示的一个字符，范围：ASCII可见字符
 * @retval 无
 */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{
    uint8_t i;
    OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8); // 设置光标位置在上半部分
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(OLED_F8x16[Char - ' '][i]); // 显示上半部分内容
    }
    OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8); // 设置光标位置在下半部分
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]); // 显示下半部分内容
    }
}

/**
 * @brief  OLED显示字符串
 * @param  Line 起始行位置，范围：1-4
 * @param  Column 起始列位置，范围：1-16
 * @param  String 要显示的字符串，范围：ASCII可见字符
 * @retval 无
 */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i++)
    {
        OLED_ShowChar(Line, Column + i, String[i]);
    }
}

/**
 * @brief  OLED次方函数
 * @retval 返回值等于X的Y次方
 */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;
    while (Y--)
    {
        Result *= X;
    }
    return Result;
}

/**
 * @brief  OLED显示数字（十进制，正数）
 * @param  Line 起始行位置，范围：1-4
 * @param  Column 起始列位置，范围：1-16
 * @param  Number 要显示的数字，范围：0-4294967295
 * @param  Length 要显示数字的长度，范围：1-10
 * @retval 无
 */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number)
{
		uint8_t Length = 0;
		for (uint32_t i = Number; i > 0; i /= 10, Length++);
		if(!Number)
			Length = 1;
    for (uint8_t i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
    }
}

/**
 * @brief  OLED显示数字（十进制，带符号数）
 * @param  Line 起始行位置，范围：1-4
 * @param  Column 起始列位置，范围：1-16
 * @param  Number 要显示的数字，范围：-2147483648-2147483647
 * @param  Length 要显示数字的长度，范围：1-10
 * @retval 无
 */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
    uint8_t i;
    uint32_t Number1;
    if (Number >= 0)
    {
        OLED_ShowChar(Line, Column, '+');
        Number1 = Number;
    }
    else
    {
        OLED_ShowChar(Line, Column, '-');
        Number1 = -Number;
    }
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
    }
}

/**
 * @brief  OLED显示数字（十六进制，正数）
 * @param  Line 起始行位置，范围：1-4
 * @param  Column 起始列位置，范围：1-16
 * @param  Number 要显示的数字，范围：0-0xFFFFFFFF
 * @param  Length 要显示数字的长度，范围：1-8
 * @retval 无
 */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    uint8_t i, SingleNumber;
    for (i = 0; i < Length; i++)
    {
        SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
        if (SingleNumber < 10)
        {
            OLED_ShowChar(Line, Column + i, SingleNumber + '0');
        }
        else
        {
            OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
        }
    }
}

/**
 * @brief  OLED显示数字（二进制，正数）
 * @param  Line 起始行位置，范围：1-4
 * @param  Column 起始列位置，范围：1-16
 * @param  Number 要显示的数字，范围：0-1111 1111 1111 1111
 * @param  Length 要显示数字的长度，范围：1-16
 * @retval 无
 */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
    }
}

#define MAX_STR 20

void OLED_Printf(uint8_t line, uint8_t column, char *format, ...)
{
    char str[MAX_STR] = {0};
    va_list arg;
    va_start(arg, format);
    vsprintf(str, format, arg);
    va_end(arg);
    OLED_ShowString(line, column, str);
}