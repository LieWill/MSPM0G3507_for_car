/*
 * OLED.H
 *
 *  Created on: Mar 18, 2024
 *      Author: 123
 */

#ifndef INC_OLED_H_
#define INC_OLED_H_

#include "ti_msp_dl_config.h"

void OLED_Init(I2C_Regs *set);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_Printf(uint8_t line, uint8_t column, char *format, ...);
void OLED_SetCursor(uint8_t Y, uint8_t X);
void OLED_WriteData(uint8_t Data);

#endif /* INC_OLED_H_ */
