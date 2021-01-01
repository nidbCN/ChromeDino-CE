
#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "universal.h"

bool RAND_setRandomInit();

uint8_t RAND_getRandomNumber_uint8(uint8_t from, uint8_t to);

uint16_t RAND_getRandomNumber_uint16(uint16_t from, uint16_t to);

uint32_t RAND_getRandomNumber_uint32(uint32_t from, uint32_t to);

uint64_t RAND_getRandomNumber_uint64(uint64_t from, uint64_t to);
#endif
