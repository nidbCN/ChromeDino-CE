/*------头文件------*/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stm32f1xx_hal_i2c.h>
#include <i2c.h>
#include "graphicsE.h"
#include "gameRes.h"

/*------宏定义------*/

// 空数据
#define NULL_DATA (0x00)
// 填充数据
#define FILL_DATA (0xFF)
// 最大宽度
#define WIDTH_MAX (128)
// 最小宽度
#define HEIGHT_MAX (8)
// 发送数据超时设置(ms)
#define I2C_MEM_WRITE_TIMEOUT (10)

/*------函数定义------*/

/*------OLED相关------*/

// OLED 发送数据
// 注意：type为 OLED_SEND_DATA 或 OLED_SEND_CMD
void OLED_Send(uint8_t type, uint8_t *data, uint8_t size) {
    HAL_I2C_Mem_Write(&hi2c1, 0x78, type, I2C_MEMADD_SIZE_8BIT, data, size, I2C_MEM_WRITE_TIMEOUT);
}

// OLED 设置显示开关
// 注意：option为 OLED_DISPLAY_ON 或 OLED_DISPLAY_OFF
void OLED_SetDisplay(bool option) {
    uint8_t CMD_DataOn = {0X8D, 0X14, 0XAF};
    uint8_t CMD_DataOff = {0X8D, 0X10, 0XAE};
    uint8_t *CMD_Data = option ? CMD_DataOn : CMD_DataOff;
    OLED_Send(OLED_SEND_CMD, CMD_Data, 3);
}

// OLED设置初始化
void OLED_SetInit() {
    uint8_t CMD_Data[] = {
            0xAE, 0x00, 0x10, 0x40, 0xB0, 0x81, 0xFF, 0xA1,
            0xA6, 0xA8, 0x3F, 0xC8, 0xD3, 0x00, 0xD5, 0x80,
            0xD8, 0x05, 0xD9, 0xF1, 0xDA, 0x12, 0xD8, 0x30,
            0x8D, 0x14, 0xAF
    };

    OLED_Send(OLED_SEND_CMD, CMD_Data, 27);
}

// 设置光标位置(x,y)
void OLED_SetPosition(uint8_t x, uint8_t y) {
    uint8_t CMD_Data[3] = {
            (0xb0 + y),
            (((x & 0xf0) >> 4) | 0x10),
            (x & 0x0f),
    };
    OLED_Send(OLED_SEND_CMD, CMD_Data, 3);
}

// OLED设置开启

/*------填充相关------*/

// 从坐标(x,y)处向右下填充 width x 8 个像素大小的内容 res数组
// 注意：x为负数只渲染正数部分
void GAME_OLED_FillBlockRow(int8_t x, uint8_t y, uint8_t width, uint8_t *res) {
    uint8_t i = 0;
    // 跳过渲染x<0的部分
    if (x < 0) {
        i = -x;
        x = 0;
    }

    // 防止出界
    if (y < HEIGHT_MAX) {
        width = x + width > WIDTH_MAX ? WIDTH_MAX - x : width;
        OLED_SetPosition(x, y); // 设置光标
        OLED_Send(OLED_SEND_DATA, res, width - i);

    }
}

// 从坐标(x,y)处向右下填充 RES_SIZE_AxB: AxB 个像素大小的内容 RES_CONTENT
void GAME_OLED_FillBlockAny(int8_t x, uint8_t y, uint8_t type, uint8_t res) {
    uint8_t width = 0;
    uint8_t height = 0;
    // 判断类型
    switch (type) {
        case RES_SIZE_8x16:
            width = 8;
            height = 2;
            for (uint8_t i = 0; i < height; ++i) {
                GAME_OLED_FillBlockRow(x, y + i, width, RES_P8x16[res + i]);
            }
            break;
        case RES_SIZE_16x16:
            width = 16;
            height = 2;
            for (uint8_t i = 0; i < height; ++i) {
                GAME_OLED_FillBlockRow(x, y + i, width, RES_P16x16[res + i]);
            }
            break;
        case RES_SIZE_16x32:
            width = 16;
            height = 4;
            for (uint8_t i = 0; i < height; ++i) {
                GAME_OLED_FillBlockRow(x, y + i, width, RES_P16x32[res + i]);
            }
            break;
        case RES_SIZE_32x32:
            width = 32;
            height = 4;
            for (uint8_t i = 0; i < height; ++i) {
                GAME_OLED_FillBlockRow(x, y + i, width, RES_P32x32[res + i]);
            }
            break;
        case RES_SIZE_64x32:
            width = 64;
            height = 4;
            for (uint8_t i = 0; i < height; ++i) {
                GAME_OLED_FillBlockRow(x, y + i, width, RES_S64x32[res + i]);
            }
            break;
        case RES_SIZE_64x64:
            width = 64;
            height = 8;
            for (uint8_t i = 0; i < height; ++i) {
                GAME_OLED_FillBlockRow(x, y + i, width, RES_P64x64[res + i]);
            }
            break;
    }
}

//  从坐标(x,y)处向右下填充4位数字
void GAME_OLED_FillBlockInt4(int8_t x, uint8_t y, uint16_t num) {
    // 乘方表
    uint16_t powTable[4] = {1000, 100, 10, 1};
    // 循环设置数字字符
    for (int i = 0; i < 4; i++) {
        uint8_t ch = RES_ID_8x16_NUM(num / powTable[i]); // 获取数字对于的表ID
        GAME_OLED_FillBlockChar(x + i * 8, y, ch);       // 显示数字
        num %= powTable[i];
    }
}

// 从坐标(x,y)处向右下填充一个字符
void GAME_OLED_FillBlockChar(int8_t x, uint8_t y, uint8_t ch) {
    for (int i = 0; i < 2; ++i) {
        GAME_OLED_FillBlockRow(x, y, 16, RES_F8x16[ch + i]);
    }
}

// 填充整块屏幕
void GAME_OLED_FillScreen() {
    uint8_t NULL_Data[WIDTH_MAX] = {0,};
    for (int i = 0; i < HEIGHT_MAX; ++i) {
        OLED_Set_Pos(0, i);
        OLED_Send(OLED_SEND_DATA, NULL_Data, WIDTH_MAX);
    }
}

/*------清除相关------*/

// 从坐标(x,y)处向右下清除 width x 8 个像素
void GAME_OLED_ClearBlockRow(uint8_t x, uint8_t y, uint8_t width) {
    if (y < HEIGHT_MAX) {
        width = x + width > WIDTH_MAX ? WIDTH_MAX - x : width;
        uint8_t NULL_Data[width];
        memset(NULL_Data, NULL_DATA, width);
        OLED_Set_Pos(x, y);
        OLED_Send(OLED_SEND_DATA, NULL_Data, width);
    }
}

// 从坐标(x,y)处向右下清除 width x height*8 个像素
// 注意：超出后不会清除反侧的
void GAME_OLED_ClearBlockCustom(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
    if (x < WIDTH_MAX) {
        // 防止出界
        height = y + height > HEIGHT_MAX ? HEIGHT_MAX - y : height;


        // 清空区域
        for (int i = 0; i < height; ++i) {
            GAME_OLED_ClearBlockRow(x, y + i, width);
        }
    }
}

// 从坐标(x,y)处向右下清除 RES_SIZE_AxB: AxB 个像素
void GAME_OLED_ClearBlockAny(uint8_t x, uint8_t y, uint8_t type) {
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
    if (width && height) {
        GAME_OLED_ClearBlockCustom(x, y, width, height);
    }
}

// 清除整块屏幕
void GAME_OLED_ClearScreen() {
    GAME_OLED_ClearBlockCustom(0, 0, WIDTH_MAX, HEIGHT_MAX);
}