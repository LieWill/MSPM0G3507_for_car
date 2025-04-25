#include "flash.h"

//const uint32_t EEPROM[4096] __attribute((used)) __attribute((at(0x00019000)))={0};

//bool flash_init()
//{

//}

//bool flash_write(uint16_t address, void *data, uint16_t length)
//{
//    if(address + length > 4096 * 4)
//        return false;
//    for(uint8_t i = 0; i < length; i++)
//        ((uint8_t*)EEPROM)[address + i] = ((uint8_t*)data)[i];
//    return true;
//}

//bool flash_read(uint16_t address, void *data, uint16_t length)
//{
//    if(address + length > 4096 * 4)
//        return false;
//    for(uint8_t i = 0; i < length; i++)
//        ((uint8_t*)data)[i] = ((uint8_t*)EEPROM)[address + i];
//    return true;
//}
