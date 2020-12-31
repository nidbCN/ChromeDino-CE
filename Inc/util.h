#include <stdint.h>
#include <stdbool.h>

#define FLAG_DINO_STATUS_LEFT 0
#define FLAG_DINO_STATUS_RIGHT 1
#define FLAG_DINO_STATUS_STOP 2

// dino object struct
typedef struct _dino {
    bool isJumped;
    uint64_t jumpTime;
    uint8_t flag;
    uint8_t y;
} Dino;

// cactus object struct
typedef struct _cactus {
    uint8_t width;
    uint8_t height;
    uint8_t size;
    uint8_t flag;
    int8_t x;
    uint8_t y;
} Cactus;

void LED_toggle();

Dino *GAME_getDinoHeight(Dino *gameDino);

Dino *GAME_getDinoFlag(Dino *gameDino);

Dino *GAME_drawDino(Dino *gameDino);

Dino *GAME_setDinoJump(Dino *gameDino);

Cactus *GAME_getCactusRand();

Cactus *GAME_drawCactus(Cactus *gameCactus);

bool GAME_getGameStatus(Dino *gameDino, Cactus *gameCactus);
