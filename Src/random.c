#include "random.h"

/*
 * Init the random functions, you should init it after use.
 * Arguments: /
 * Return: void
 */
bool RAND_SetRandomInit() {
    // Random a seed.
    uint32_t *seed_1 = (uint32_t *) malloc(4);
    uint32_t *seed_2 = (uint32_t *) malloc(4);
    uint32_t seed = (*seed_1) | (*seed_2);

    // Delete pointers.
    free(seed_1);
    free(seed_2);
    seed_1 = NULL;
    seed_2 = NULL;

    // Set rand() function seed.
    srand(seed);

    // Return init result.
    return seed != 0 ? true : false;
}

/*
 * Get the unsigned short (uint8_t) random number
 * Arguments: uint8_t range begin, uint8_t range end
 * Return: uint8_t random number
 */
uint8_t GAME_GetRandomNumber_uint8(uint8_t from, uint8_t to) {
    uint8_t size = to - from;
    uint8_t randNum = rand() % size;    // NOLINT(cert-msc30-c, cert-msc50-cpp)
    randNum += from;
    return randNum;
}

/*
 * Get the unsigned int (uint16_t) random number
 * Arguments: uint16_t range begin, uint8_t range end
 * Return: uint16_t random number
 */
uint16_t GAME_GetRandomNumber_uint16(uint16_t from, uint16_t to) {
    uint16_t size = to - from;
    uint16_t randNum = rand() % size;   // NOLINT(cert-msc30-c, cert-msc50-cpp)
    randNum += from;
    return randNum;
}

/*
 * Get the unsigned long (uint32_t) random number
 * Arguments: uint32_t range begin, uint32_t range end
 * Return: uint8_t random number
 */
uint32_t GAME_GetRandomNumber_uint32(uint32_t from, uint32_t to) {
    uint32_t size = to - from;
    uint32_t randNum = rand() % size;   // NOLINT(cert-msc30-c, cert-msc50-cpp)
    randNum += from;
    return randNum;
}

/*
 * Get the unsigned long long (uint64_t) random number
 * Arguments: uint64_t range begin, uint64_t range end
 * Return: uint64_t random number
 */
uint64_t GAME_GetRandomNumber_uint64(uint64_t from, uint64_t to) {
    uint32_t doubleSeed = HAL_GetTick();
    doubleSeed = (doubleSeed << 6);
    uint64_t size = to - from;
    uint64_t randNum = (rand() | doubleSeed) % size;    // NOLINT(cert-msc30-c, cert-msc50-cpp)
    randNum += from;
    return randNum;
}