#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "universal.h"

/*
 * Init the random functions, you should init it after use.
 * Arguments: /
 * Return: void
 */
bool RAND_SetRandomInit();

/*
 * Get the unsigned int (uint16_t) random number
 * Arguments: uint16_t range begin, uint8_t range end
 * Return: uint16_t random number
 */
uint8_t GAME_GetRandomNumber_uint8(uint8_t from, uint8_t to);

/*
 * Get the unsigned int (uint16_t) random number
 * Arguments: uint16_t range begin, uint8_t range end
 * Return: uint16_t random number
 */
uint16_t GAME_GetRandomNumber_uint16(uint16_t from, uint16_t to);

/*
 * Get the unsigned long (uint32_t) random number
 * Arguments: uint32_t range begin, uint32_t range end
 * Return: uint8_t random number
 */
uint32_t GAME_GetRandomNumber_uint32(uint32_t from, uint32_t to);

/*
 * Get the unsigned long long (uint64_t) random number
 * Arguments: uint64_t range begin, uint64_t range end
 * Return: uint64_t random number
 */
uint64_t GAME_GetRandomNumber_uint64(uint64_t from, uint64_t to);

#endif