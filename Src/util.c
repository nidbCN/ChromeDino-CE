#include <stdlib.h>
#include "util.h"
#include "graphicsE.h"
#include "gpio.h"

// LED 变换状态
void LED_toggle() {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

// set dino status to jumped
Dino *GAME_setDinoJump(Dino *gameDino) {
    if (gameDino->isJumped == false) {
        gameDino->isJumped = true;
        gameDino->flag = RES_ID_16x16_DINO_3;
        gameDino->jumpTime = HAL_GetTick();
    }
    return gameDino;
}

// get the height of jumped dino
Dino *GAME_getDinoHeight(Dino *gameDino) {
    if (gameDino->isJumped) {
        uint64_t time = HAL_GetTick() - gameDino->jumpTime;
        if ((time > 50 && time <= 100) || (time > 1275 && time <= 1300)) {
            gameDino->y = 5;
        } else if ((time > 100 && time <= 175) || (time > 1200 && time <= 1275)) {
            gameDino->y = 4;
        } else if ((time > 175 && time <= 300) || (time > 1075 && time <= 1200)) {
            gameDino->y = 3;
        } else if ((time > 300 && time <= 475) || (time > 925 && time <= 1075)) {
            gameDino->y = 2;
        } else if ((time > 475 && time <= 700) || (time > 700 && time <= 925)) {
            gameDino->y = 1;
        } else if (time > 1300) {
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
Dino *GAME_getDinoFlag(Dino *gameDino) {
    if ((HAL_GetTick() & 127) == 0) {
        if (gameDino->flag == RES_ID_16x16_DINO_1) {
            gameDino->flag = RES_ID_16x16_DINO_2;
        } else if (gameDino->flag == RES_ID_16x16_DINO_2) {
            gameDino->flag = RES_ID_16x16_DINO_1;
        } else if (gameDino->isJumped == false) {
            gameDino->flag = RES_ID_16x16_DINO_1;
        }
    }
    return gameDino;
}

// draw a dino on screen
Dino *GAME_drawDino(Dino *gameDino) {
    uint8_t y = gameDino->y;

    // if the dino is in jump status
    if (gameDino->isJumped == true) {
        gameDino = GAME_getDinoHeight(gameDino);
        // 判断是否有移动
        if (y > gameDino->y) {
            OLED_ClearBlockAny(0, y, RES_SIZE_16x16);
            OLED_FillBlockAny(0, gameDino->y, RES_SIZE_16x16, gameDino->flag);
        } else if (y < gameDino->y) {
            OLED_ClearBlockAny(0, gameDino->y - 2, RES_SIZE_16x16);
            OLED_FillBlockAny(0, gameDino->y, RES_SIZE_16x16, gameDino->flag);
        }
    } else {
        uint8_t flag = gameDino->flag;
        gameDino = GAME_getDinoFlag(gameDino);
        if (flag != gameDino->flag) {
            OLED_ClearBlockAny(0, y, RES_SIZE_16x16);
            OLED_FillBlockAny(0, y, RES_SIZE_16x16, flag);
        }
    }
    return gameDino;
}

// random make a cactus return new cactus or NULL
Cactus *GAME_getCactusRand(uint8_t randSeed) {
    // 小于10为8x16，大于10为16x32
    int32_t table[8] = {0, 2, 4, 6, 0, 4, 8, 12};
    uint8_t seed = (HAL_GetTick() << randSeed);
    srand(seed);
    uint8_t randNum = rand() & 4095;
    Cactus *ret = NULL;
    if (randNum < 8) {
        ret = (Cactus *) malloc(sizeof(Cactus));
        ret->flag = table[randNum];
        ret->x = 127;
        ret->size = randNum < 4 ? RES_SIZE_8x16 : RES_SIZE_16x32;
        ret->width = randNum < 4 ? 8 : 16;
        ret->height = randNum < 4 ? 2 : 4;
        ret->y = 8 - ret->height;
    }
    return ret;
}

// draw a cactus no screen and clear the last cactus
Cactus *GAME_drawCactus(Cactus *gameCactus) {
    // Fill block a cactus
    OLED_FillBlockAny(gameCactus->x, gameCactus->y, gameCactus->size, gameCactus->flag);

    if (gameCactus->x + gameCactus->width < 127) {

        for (uint8_t i = 0; i < 8 - gameCactus->y; ++i) {
            // clear old data
            OLED_ClearBlockRow(gameCactus->x + gameCactus->width, gameCactus->y + i, 1);
        }
    }

    --(gameCactus->x);
    if (gameCactus->x < -gameCactus->width) {
        free(gameCactus);
        gameCactus = NULL;
    }
    return gameCactus;
}

// get the game status if it over
bool GAME_getGameStatus(Dino *gameDino, Cactus *gameCactus) {
    bool ret = true;
    if (gameCactus->x <= 16 && gameCactus != NULL) {
        if ((gameDino->y + 2) >= (8 - gameCactus->height))
            ret = false;
    }
    return ret;
}