/*
 * RIF (Reflectance Infrared Sensor) 模块源文件
 * 实现灰度传感器数据的处理和特征提取（计算黑线位置）。
 */
#include "rif.h"

int rif_to_value(uint16_t value)
{
  uint8_t i = 1;
  uint8_t j = 10;
  for (; i < 10; i++)
  {
    if ((value & (1 << i)))
      break;
  }
  for (; j > i; j--)
  {
    if ((value & (1 << j)))
      break;
  }
  return i + j - 11;
}