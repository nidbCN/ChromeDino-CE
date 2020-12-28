//
// Created by Gaein on 2020/12/27.
// 游戏操作相关函数
//

#include "oled.h"

// 宏定义
#define NULL_DATA (0x00)
#define FILL_DATA (0xFF)
#define WIDTH_MAX (128)
#define HEIGHT_MAX (8)

// 游戏资源大小
#define RES_SIZE_8x16 (0)
#define RES_SIZE_16x16 (1)
#define RES_SIZE_16x32 (2)
#define RES_SIZE_32x32 (3)

#define RES_NULL_8x16 0
#define RES_CACTUS_8x16 1

#define RES_NULL_16x16 0
#define RES_DINO1_16x16 2
#define RES_DINO2_16x16 4
#define RES_CACTUS_16x16 6

void GAME_OLED_FullFill() {
    for (int i = 0; i < HEIGHT_MAX; ++i) {
        for (int j = 0; j < WIDTH_MAX; ++j) {
            OLED_Set_Pos(i, j);
            OLED_WR_DATA(FILL_DATA);
        }
    }
}

// 从坐标(x,y)处向右下清除 width x height*8 个像素
// 注意超出后不会清除反侧的
void GAME_OLED_ClearBlockCustom(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
    // 防止出界
    height = y + height > HEIGHT_MAX ? HEIGHT_MAX - y : height;
    width = x + width > WIDTH_MAX ? WIDTH_MAX - x : x;

    // 清空区域
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            OLED_Set_Pos(x, y);         // 设置光标
            OLED_WR_DATA(NULL_DATA);    // 写入空数据
        }
    }
}

// 从坐标(x,y)处向右下清除 1 x height*8 个像素
void GAME_OLED_ClearVertical(uint8_t x, uint8_t y, uint8_t height) {
    for (int i = 0; i < height; ++i) {
        OLED_Set_Pos(x, y);

    }
    GAME_OLED_ClearBlockCustom(x, y, 1, height);
}

void GAME_OLED_ClearBlock(uint8_t x, uint8_t y, uint8_t type) {
    uint8_t width = 0;
    uint8_t height = 0;

    // 通过type设置清除的大小
    switch (type) {
        case RES_SIZE_8x16:
            width = 8;
            height = 2;
            break;
        case RES_SIZE_16x16:
            width = 16;
            height = 2;
            break;
        case RES_SIZE_16x32:
            width = 16;
            height = 4;
            break;
        case RES_SIZE_32x32:
            width = 32;
            height = 4;
            break;
    }

    // 有数据时进行清除
    if (width&&height) {
        GAME_OLED_ClearBlockCustom(x, y, width, height);
    }
}