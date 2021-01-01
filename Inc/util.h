#include <stdint.h>
#include <stdbool.h>

// define dino status flag
#define FLAG_DINO_STATUS_LEFT 0
#define FLAG_DINO_STATUS_RIGHT 1
#define FLAG_DINO_STATUS_STOP 2

// dino object struct
typedef struct _dino {
    bool isJumped;
    uint32_t jumpTime;
    uint8_t flag;
    uint8_t y;
    uint32_t lastDraw;
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

// convert LED to another status
void LED_toggle();

void GAME_CountDown();

void GAME_InitScreen();

Dino *GAME_InitDino();

void GAME_DrawGameOver();

// get dino height by object pointer game dino
Dino *GAME_GetDinoHeight(Dino *gameDino);

Dino *GAME_SetDinoNotJump(Dino *gameDino);

// get dino flag by object pointer game dino
Dino *GAME_GetDinoFlag(Dino *gameDino);

bool GAME_GetDinoShouldDraw(Dino *gameDino);

// draw a dino by object pointer dino
Dino *GAME_DrawDino(Dino *gameDino);

Dino *GAME_SetDinoJump(Dino *gameDino);

Cactus *GAME_GetCactusRand();

Cactus *GAME_DrawCactus(Cactus *gameCactus);

bool GAME_GetGameStatus(Dino *gameDino, Cactus *gameCactus);