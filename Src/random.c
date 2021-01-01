#include "random.h"

// Init the random functions, you should init it after use.
bool RAND_SetRandomInit() {
    // Random a seed.
    uint32_t *seed_1 = (uint32_t*)malloc(4);
    uint32_t *seed_2 = (uint32_t*)malloc(4);
    uint32_t seed = (*seed_1) | (*seed_2);

    // delete pointers.
    free(seed_1);
    free(seed_2);
    seed_1 = NULL;
    seed_2 = NULL;

    // Set rand() function seed.
    srand(seed);

    // Return init result.
    return seed != 0 ? true : false;
}

uint8_t GAME_GetRandomNumber_uint8(uint8_t from, uint8_t to) {
    uint8_t size = to - from;
    uint8_t randNum = rand() % size;
    randNum += from;
    return randNum;
}

uint16_t GAME_GetRandomNumber_uint16(uint16_t from, uint16_t to) {
    uint16_t size = to - from;
    uint16_t randNum = rand() % size;
    randNum += from;
    return randNum;
}

uint32_t GAME_GetRandomNumber_uint32(uint32_t from, uint32_t to) {
    uint32_t size = to - from;
    uint32_t randNum = rand() % size;
    randNum += from;
    return randNum;
}

uint64_t GAME_GetRandomNumber_uint64(uint64_t from, uint64_t to) {
    uint32_t doubleSeed = HAL_GetTick();
    doubleSeed = (doubleSeed << 6);
    uint64_t size = to - from;
    uint64_t randNum = (rand() | doubleSeed) % size;
    randNum += from;
    return randNum;
}