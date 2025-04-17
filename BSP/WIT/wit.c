#include "wit.h"
uint16_t wit_get_yaw(I2C_Regs *i2c_regs)
{
    uint16_t res;
    DL_I2C_fillControllerTXFIFO(i2c_regs, &(char[]){Yaw}, 1);
    while (!(DL_I2C_getControllerStatus(i2c_regs) & DL_I2C_CONTROLLER_STATUS_IDLE));
    DL_I2C_startControllerTransfer(i2c_regs, WIT_ADD, DL_I2C_CONTROLLER_DIRECTION_TX, 1);
    while (DL_I2C_getControllerStatus(i2c_regs) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
    while (!(DL_I2C_getControllerStatus(i2c_regs) & DL_I2C_CONTROLLER_STATUS_IDLE));
    DL_I2C_flushControllerTXFIFO(i2c_regs);
    DL_I2C_startControllerTransfer(i2c_regs, WIT_ADD, DL_I2C_CONTROLLER_DIRECTION_RX, 1);
    while (DL_I2C_getControllerStatus(i2c_regs) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
    while (!(DL_I2C_getControllerStatus(i2c_regs) & DL_I2C_CONTROLLER_STATUS_IDLE));
    res = DL_I2C_receiveControllerData(i2c_regs) << 8;
    res = DL_I2C_receiveControllerData(i2c_regs);
    return res;
}