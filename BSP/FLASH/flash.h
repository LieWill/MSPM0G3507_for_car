#ifndef __FLASH_H__
#define __FLASH_H__

#include <stdint.h>
#include <stdbool.h>

bool flash_init();
bool flash_write(uint16_t address, void *data, uint16_t length);
bool flash_read(uint16_t address, void *data, uint16_t length);

#endif