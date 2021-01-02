/*
 * Some game util functions
 * Created by Gaein nidb, https://www.gaein.cn
 * North Universal Of China
 */

#include "universal.h"
#include "util.h"
#include "graphicsE.h"
#include "random.h"

/*
 * Init the OLED screen for game.
 * Arguments: /
 * Return: void
 */
void GAME_InitScreen() {
    OLED_ClearScreen();                 // Clear OLED screen.
    // Draw a game dino.
    OLED_FillBlockAny(0, 6, RES_SIZE_16x16, RES_ID_16x16_DINO_1);
}

/*
 * Init a new dino.
 * Arguments: /
 * Return: Dino* (a new malloced dino)
 */
Dino *GAME_InitDino() {
    // Malloc a new dino
    Dino *gameDino = (Dino *) malloc(sizeof(Dino));

    // Init the game dino object
    gameDino->isJumped = false;
    gameDino->jumpTime = 0;
    gameDino->flag = RES_ID_16x16_DINO_1;
    gameDino->y = 6;
    gameDino->lastDraw = 0;

    return gameDino;
}

/*
 * Game count down three to zero.
 * Arguments: /
 * Return: void
 */
void GAME_CountDown() {
    const uint8_t x = 48;
    const uint8_t y = 0;
    OLED_FillBlockAny(x, y, RES_SIZE_32x64, RES_ID_32x64_3);
    uint32_t startTime = HAL_GetTick();
    while (true) {
        HAL_Delay(1000);
        uint32_t time = HAL_GetTick() - startTime;
        if (time > 3000) {
            OLED_FillBlockAny(x, y, RES_SIZE_32x64, RES_ID_32x64_0);
            HAL_Delay(1000);
            break;
        } else if (time > 2000) {
            OLED_FillBlockAny(x, y, RES_SIZE_32x64, RES_ID_32x64_1);
        } else if (time > 1000) {
            OLED_FillBlockAny(x, y, RES_SIZE_32x64, RES_ID_32x64_2);
        }
    }
}

/*
 * Draw the game over interface.
 * Arguments: /
 * Return: void
 */
void GAME_DrawGameOver() {
    OLED_FillBlockAny(0, 0, RES_SIZE_64x32, RES_ID_64x32_GAME);
    OLED_FillBlockAny(64, 4, RES_SIZE_64x32, RES_ID_64x32_OVER);
    OLED_FillBlockAny(16, 4, RES_SIZE_32x32, RES_ID_32x32_RESTART);
    OLED_FillBlockAny(90, 1, RES_SIZE_16x16, RES_ID_16x16_DINO_4);
}

/*
 * Draw a dino on screen.
 * Arguments: Dino* (input a dino you want to draw)
 * Return: Dino* (return a dino has been auto draw)
 */
Dino *GAME_DrawDino(Dino *gameDino) {
    uint8_t y = gameDino->y;
    if (gameDino->flag != RES_ID_16x16_DINO_4) {

        // If the dino is in jump status
        if (gameDino->isJumped == true) {
            gameDino = GAME_GetDinoHeight(gameDino);

            // Judge if the game dino has move
            if (y > gameDino->y) {
                // Rise
                OLED_ClearBlockRow(0, y + 1, 16);
                OLED_ClearBlockAny(0, y, RES_SIZE_16x16);
                OLED_FillBlockAny(0, gameDino->y, RES_SIZE_16x16, gameDino->flag);
                gameDino->lastDraw = HAL_GetTick();
            } else if (y < gameDino->y) {
                // Down
                OLED_ClearBlockRow(0, y, 16);
                OLED_FillBlockAny(0, gameDino->y, RES_SIZE_16x16, gameDino->flag);
                gameDino->lastDraw = HAL_GetTick();
            }
        } else if (GAME_GetDinoShouldDraw(gameDino)) {
            gameDino = GAME_GetDinoFlag(gameDino);

            // Renew the dino picture(just 0,0 to 8,8)
            OLED_ClearBlockRow(0, y + 1, 16);
            OLED_FillBlockAny(0, y, RES_SIZE_16x16, gameDino->flag);
            gameDino->lastDraw = HAL_GetTick();
        }
    } else {
        OLED_ClearBlockRow(0, y, 16);
        OLED_FillBlockAny(0, y, RES_SIZE_16x16, gameDino->flag);
    }

    return gameDino;
}

/*
 * Draw a cactus, and make it left
 * Arguments: Cactus* (input a cactus which will be drawn)
 * Return: Cactus* (a cactus has been drawn)
 */
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

/*
 * Set dino status to jumped.
 * Arguments: Dino* (input dino pointer)
 * Return: Dino* (a dino has inited)
 */
Dino *GAME_SetDinoJump(Dino *gameDino) {
    if (gameDino->isJumped == false) {
        gameDino->isJumped = true;
        gameDino->flag = RES_ID_16x16_DINO_3;
        gameDino->jumpTime = HAL_GetTick();
    }
    return gameDino;
}

/*
 * Set dino status to not jumped
 * argument: Dino* (input dino pointer)
 * return: Dino* (a dino has set to not jump)
 */
Dino *GAME_SetDinoNotJump(Dino *gameDino) {
    if (gameDino->isJumped == true) {
        gameDino->isJumped = false;
        gameDino->flag = RES_ID_16x16_DINO_1;
        gameDino->jumpTime = 0;
    }
    return gameDino;
}

/*
 * Get the height of jumped dino
 * argument: Dino* (input dino pointer)
 * return: Dino* (a dino has set to not jump)
 */
Dino *GAME_GetDinoHeight(Dino *gameDino) {
    if (gameDino->isJumped) {
        uint32_t time = HAL_GetTick() - gameDino->jumpTime; // Get jumped time
        // Get time by y
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
            // End jump
            if (gameDino->y == 6) {
                gameDino = GAME_SetDinoNotJump(gameDino);
            } else {
                gameDino->y = 6;
            }
        }
    }
    return gameDino;
}

/*
 * Get the picture of dino.
 * Arguments: Dino* (input a dino)
 * Return: Dino* (return a dino which flag has been edit)
 * */
Dino *GAME_GetDinoFlag(Dino *gameDino) {
    // Get another res picture of dino
    if (gameDino->flag == RES_ID_16x16_DINO_1) {
        gameDino->flag = RES_ID_16x16_DINO_2;
    } else if (gameDino->flag == RES_ID_16x16_DINO_2) {
        gameDino->flag = RES_ID_16x16_DINO_1;
    }

    // If the game dino is jumped, return the jump picture
    if (gameDino->isJumped == true) {
        gameDino->flag = RES_ID_16x16_DINO_3;
    }
    return gameDino;
}

/*
 * Get a dino if it should be drawn.
 * Arguments: Dino* (input a dino which you want to judge)
 * Return: bool (Should - true, Should not - false)
 */
bool GAME_GetDinoShouldDraw(Dino *gameDino) {
    return
            (HAL_GetTick() - gameDino->lastDraw > 100)
            && (gameDino->isJumped != true)
            ? true : false;
}

/*
 * Get a random cactus.
 * Arguments: /
 * Return: Cactus* (a random cactus object)
 */
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

/*
 * Get game status, judge if it can be continued.
 * Arguments: Dino* (game used dino object pointer), Cactus (game used cactus object pointer)
 * Return: bool (continue - true, failed - false)
 */
bool GAME_GetGameStatus(Dino *gameDino, Cactus *gameCactus) {
    bool ret = true;
    if (gameCactus->x <= 16 && gameCactus != NULL) {
        if ((gameDino->y + 2) > (8 - gameCactus->height))
            ret = false;
    }
    return ret;
}