#include <stdint.h>
#include <stdbool.h>

#define FLAG_DINO_STATUS_LEFT 0
#define FLAG_DINO_STATUS_RIGHT 1
#define FLAG_DINO_STATUS_STOP 2

typedef struct _dino {
    bool isJumped;
    uint64_t jumpTime;
    uint8_t flag;
    uint8_t y;
} Dino;

void LED_toggle();

Dino *GAME_getDinoHeight(Dino *gameDino);

Dino *GAME_getDinoFlag(Dino *gameDino);

Dino *GAME_drawDino(Dino *gameDino);

Dino *GAME_setDinoJump(Dino *gameDino);

uint8_t GAME_getRandCactus(uint8_t randSeed);