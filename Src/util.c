#include "universal.h"
#include "util.h"
#include "graphicsE.h"
#include "gpio.h"
#include "random.h"

// LED 变换状态
void LED_toggle() {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

void GAME_InitScreen() {
    OLED_ClearScreen();                 // Clear OLED screen
    OLED_FillBlockAny(0, 6, RES_SIZE_16x16, RES_ID_16x16_DINO_1);
}

Dino *GAME_InitDino() {
    Dino *gameDino = (Dino *) malloc(sizeof(Dino));

    // Init the game dino object
    gameDino->isJumped = false;
    gameDino->jumpTime = 0;
    gameDino->flag = RES_ID_16x16_DINO_1;
    gameDino->y = 6;
    gameDino->lastDraw = 0;

    return gameDino;
}

void GAME_DrawGameOver() {
    OLED_FillBlockAny(0, 0, RES_SIZE_64x32, RES_ID_64x32_GAME);
    OLED_FillBlockAny(64, 4, RES_SIZE_64x32, RES_ID_64x32_OVER);
    OLED_FillBlockAny(16, 4, RES_SIZE_32x32, RES_ID_32x32_RESTART);
    OLED_FillBlockAny(90, 1, RES_SIZE_16x16, RES_ID_16x16_DINO_4);
    return;
}

// set dino status to jumped
Dino *GAME_SetDinoJump(Dino *gameDino) {
    if (gameDino->isJumped == false) {
        gameDino->isJumped = true;
        gameDino->flag = RES_ID_16x16_DINO_3;
        gameDino->jumpTime = HAL_GetTick();
    }
    return gameDino;
}

Dino *GAME_SetDinoNotJump(Dino *gameDino) {
    if (gameDino->isJumped == true) {
        gameDino->isJumped = false;
        gameDino->flag = RES_ID_16x16_DINO_1;
        gameDino->jumpTime = 0;
    }
    return gameDino;
}

// get the height of jumped dino
Dino *GAME_GetDinoHeight(Dino *gameDino) {
    if (gameDino->isJumped) {
        uint32_t time = HAL_GetTick() - gameDino->jumpTime;
        if ((time > 50 && time <= 100) || (time > 1100 && time <= 1150)) {
            gameDino->y = 5;
        } else if ((time > 100 && time <= 175) || (time > 1025 && time <= 1100)) {
            gameDino->y = 4;
        } else if ((time > 175 && time <= 275) || (time > 925 && time <= 1025)) {
            gameDino->y = 3;
        } else if ((time > 275 && time <= 425) || (time > 775 && time <= 925)) {
            gameDino->y = 2;
        } else if ((time > 425 && time <= 600) || (time > 600 && time <= 775)) {
            gameDino->y = 1;
        } else if (time > 1150) {
            if (gameDino->y == 6) {
                gameDino->isJumped = false;
            } else {
                gameDino->y = 6;
            }
        }
    }
    return gameDino;
}

// get the picture of dino
Dino *GAME_GetDinoFlag(Dino *gameDino) {
    if (gameDino->flag == RES_ID_16x16_DINO_1) {
        gameDino->flag = RES_ID_16x16_DINO_2;
    } else if (gameDino->flag == RES_ID_16x16_DINO_2) {
        gameDino->flag = RES_ID_16x16_DINO_1;
    }

    if (gameDino->isJumped == true) {
        gameDino->flag = RES_ID_16x16_DINO_3;
    }
    return gameDino;
}

// draw a dino on screen
Dino *GAME_DrawDino(Dino *gameDino) {
    uint8_t y = gameDino->y;

    // if the dino is in jump status
    if (gameDino->isJumped == true) {
        gameDino = GAME_GetDinoHeight(gameDino);
        // 判断是否有移动
        if (y > gameDino->y) {
            OLED_ClearBlockRow(0, y + 1, 16);
            OLED_ClearBlockAny(0, y, RES_SIZE_16x16);
            OLED_FillBlockAny(0, gameDino->y, RES_SIZE_16x16, gameDino->flag);
            gameDino->lastDraw = HAL_GetTick();
        } else if (y < gameDino->y) {
            OLED_ClearBlockRow(0, y, 16);
            OLED_FillBlockAny(0, gameDino->y, RES_SIZE_16x16, gameDino->flag);
            if (gameDino->y == 6) {
                gameDino = GAME_SetDinoNotJump(gameDino);
            }
            gameDino->lastDraw = HAL_GetTick();
        }
    } else if (GAME_GetDinoShouldDraw(gameDino)) {
        gameDino = GAME_GetDinoFlag(gameDino);
        OLED_ClearBlockRow(0, y + 1, 16);
        OLED_FillBlockAny(0, y, RES_SIZE_16x16, gameDino->flag);
        gameDino->lastDraw = HAL_GetTick();
    }

    return gameDino;
}


bool GAME_GetDinoShouldDraw(Dino *gameDino) {
    return
            (HAL_GetTick() - gameDino->lastDraw > 100)
            && (gameDino->isJumped != true)
            ? true : false;
}

// random make a cactus return new cactus or NULL
Cactus *GAME_GetCactusRand() {
    // 小于10为8x16，大于10为16x32
    // resource id table
    int8_t table[11] = {
            RES_ID_8x16_CACTUS_1, RES_ID_8x16_CACTUS_2, RES_ID_8x16_CACTUS_3, RES_ID_8x16_CACTUS_4,
            RES_ID_16x16_CACTUS_1, RES_ID_16x16_CACTUS_2, RES_ID_16x16_CACTUS_3,
            RES_ID_16x32_CACTUS_1, RES_ID_16x32_CACTUS_2, RES_ID_16x32_CACTUS_3, RES_ID_16x32_CACTUS_4
    };

    uint8_t randNum = GAME_GetRandomNumber_uint8(0, 12);
    Cactus *ret = NULL;
    if (randNum < 11) {
        ret = (Cactus *) malloc(sizeof(Cactus));
        ret->flag = table[randNum];
        ret->x = 127;
        if (randNum < 4) {
            ret->size = RES_SIZE_8x16;
            ret->width = 8;
            ret->height = 2;
        } else if (randNum < 7) {
            ret->size = RES_SIZE_16x16;
            ret->width = 16;
            ret->height = 2;
        } else {
            ret->size = RES_SIZE_16x32;
            ret->width = 16;
            ret->height = 4;
        }
        ret->y = 8 - ret->height;
    }
    return ret;
}

// draw a cactus no screen and clear the last cactus
Cactus *GAME_DrawCactus(Cactus *gameCactus) {
    // Fill block a cactus
    OLED_FillBlockAny(gameCactus->x, gameCactus->y, gameCactus->size, gameCactus->flag);

    if (gameCactus->x + gameCactus->width < 127) {
        for (uint8_t i = 0; i < 8 - gameCactus->y; ++i) {
            // clear old data
            OLED_ClearBlockRow(gameCactus->x + gameCactus->width, gameCactus->y + i, 2);
        }
    }

    if (gameCactus->height == 2) {
        HAL_Delay(2);
    }

    --(gameCactus->x);
    if (gameCactus->x < -gameCactus->width) {
        free(gameCactus);
        gameCactus = NULL;
    }
    return gameCactus;
}

// get the game status if it over
bool GAME_GetGameStatus(Dino *gameDino, Cactus *gameCactus) {
    bool ret = true;
    if (gameCactus->x <= 16 && gameCactus != NULL) {
        if ((gameDino->y + 2) > (8 - gameCactus->height))
            ret = false;
    }
    return ret;
}