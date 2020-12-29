#include <stdlib.h>
#include "util.h"
#include "graphicsE.h"
#include "gpio.h"

// LED 变换状态
void LED_toggle()
{
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

// 获取恐龙起跳
Dino *GAME_getDinoJump(Dino *gameDino)
{
    if (gameDino->isJumped)
    {
        uint64_t time = HAL_GetTick() - gameDino->jumpTime;
        if (time > 50 && time <= 125 || time > 1075 && time <= 1150)
        {
            gameDino->y = 5;
        }
        else if (time > 125 && time <= 250 || time > 950 && time <= 1075)
        {
            gameDino->y = 4;
        }
        else if (time > 250 && time <= 400 || time > 800 && time <= 950)
        {
            gameDino->y = 3;
        }
        else if (time > 400 && time <= 800)
        {
            gameDino->y = 2;
        }
        else
        {
            gameDino->isJumped = false;
        }
                
    }
    return gameDino;
}

// 获取恐龙状态图
Dino *GAME_getDinoFlag(Dino *gameDino)
{
    if (gameDino->isJumped)
    {
        gameDino->resource = RES_ID_16x16_DINO_3;
    }
    if (HAL_GetTick() & 15 == 0)
    {
        if (gameDino->resource == RES_ID_16x16_DINO_1)
        {
            gameDino->resource = RES_ID_16x16_DINO_2;
        }
        else if (gameDino->resource == RES_ID_16x16_DINO_2)
        {
            gameDino->resource = RES_ID_16x16_DINO_1;
        }
    }
    return gameDino;
}

// 随机生成一个仙人掌
uint8_t GAME_getRandCactus(uint8_t randSeed)
{
    // 小于10为8x16，大于10为16x32
    int32_t table[8] = {0,2,4,6,10,14,18,22};
    uint8_t seed = HAL_GetTick() < randSeed;
    srand(seed);
    uint8_t randNum = rand() & 511;
    return randNum < 8 ? table[randNum] : -1;
}