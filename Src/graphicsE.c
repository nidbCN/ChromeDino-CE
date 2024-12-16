/*------Header files------*/
#include <string.h>
#include "universal.h"
#include "graphicsE.h"
#include "gameRes.h"

/*------Macro definition------*/

// Null data
#define NULL_DATA (0x00)
// Fill data
#define FILL_DATA (0xFF)
// The max width of screen
#define WIDTH_MAX (128)
// The max height of screen
#define HEIGHT_MAX (8)
// I2C data operate timeout(ms)
#define I2C_MEM_WRITE_TIMEOUT (50)

/*------Function definition------*/

/*------OLED related------*/

/*
 * Send data to OLED device.
 * Arguments: uint8_t type (macro OLED_SEND_DATA or OLED_SEND_CMD)
 *          , uint8_t *data (a pointer to the data you want send)
 *          , uint8_t size (length of your data, unit: element)
 * Return: void
 */
void OLED_Send(uint8_t type, uint8_t *data, uint8_t size) {
    HAL_I2C_Mem_Write(&hi2c1, 0x78, type, I2C_MEMADD_SIZE_8BIT, data, size, I2C_MEM_WRITE_TIMEOUT);
}

/*
 * OLED display switch.
 * Arguments: uint8_t option (macro OLED_DISPLAY_ON or OLED_DISPLAY_OFF)
 * Return: void
 */
void OLED_SetDisplay(uint8_t option) {
    // command on of oled screen.
    uint8_t CMD_DataOn[3] = {0X8D, 0X14, 0XAF};
    // command off of oled screen.
    uint8_t CMD_DataOff[3] = {0X8D, 0X10, 0XAE};
    uint8_t *CMD_Data = option ? CMD_DataOn : CMD_DataOff;
    OLED_Send(OLED_SEND_CMD, CMD_Data, 3);
}

/*
 * Init the OLED device
 * Arguments: /
 * Return: void
 */
void OLED_SetInit() {
    // command init of oled screen.
    uint8_t CMD_Data[] = {
            0xAE, 0x00, 0x10, 0x40, 0xB0, 0x81, 0xFF, 0xA1,
            0xA6, 0xA8, 0x3F, 0xC8, 0xD3, 0x00, 0xD5, 0x80,
            0xD8, 0x05, 0xD9, 0xF1, 0xDA, 0x12, 0xD8, 0x30,
            0x8D, 0x14, 0xAF
    };

    OLED_Send(OLED_SEND_CMD, CMD_Data, 27);
}

/*
 * Set cursor position on OLED screen.
 * Arguments: uint8_t x (x-coordinate), uint8_t y (y-coordinate)
 * Return: void
 */
void OLED_SetPosition(uint8_t x, uint8_t y) {
    // command set draw position of oled screen.x and y is position of screen.
    uint8_t CMD_Data[3] = {
            (0xb0 + y),
            (((x & 0xf0) >> 4) | 0x10),
            (x & 0x0f),
    };
    OLED_Send(OLED_SEND_CMD, CMD_Data, 3);
}

/*------Fill block ------*/

/*
 * Fill width x 8 pixels from (x, y) down to right.
 * Arguments: int8_t x (x-coordinate, it can be negative but only render the x>0 parts)
 *          , uint8_t y (y-coordinate)
 *          , uint8_t width (fill area width)
 *          , uint8_t *res (fill resource pointer)
 * Return: void
 */
void OLED_FillBlockRow(int8_t x, uint8_t y, uint8_t width, uint8_t *res) {
    uint8_t i = 0;
    uint8_t *renderRes = res;

    // ignore x<0
    if (x < 0) {
        i = -x;
        renderRes += i;
        x = 0;
    }

    // 防止出界
    if (y < HEIGHT_MAX) {
        width = x + width > WIDTH_MAX ? WIDTH_MAX - x : width;
        OLED_SetPosition(x, y);
        OLED_Send(OLED_SEND_DATA, renderRes, width - i);

    }
}

/*
 * Fill width RES_SIZE_AxB: AxB pixels from (x, y) down to right.
 * Arguments: int8_t x (x-coordinate, it can be negative but only render the x>0 parts)
 *          , uint8_t y (y-coordinate)
 *          , uint8_t type (macro RES_SIZE_AxB)
 *          , uint8_t res (macro RES_ID_AxB_C)
 * Return: void
 */
void OLED_FillBlockAny(int8_t x, uint8_t y, uint8_t type, uint8_t res) {
    uint8_t width = 0;
    uint8_t height = 0;
    
    // resource type
    switch (type) {
        case RES_SIZE_8x16:
            width = 8;
            height = 2;
            for (uint8_t i = 0; i < height; ++i) {
                OLED_FillBlockRow(x, y + i, width, RES_P8x16[res + i]);
            }
            break;
        case RES_SIZE_16x16:
            width = 16;
            height = 2;
            for (uint8_t i = 0; i < height; ++i) {
                OLED_FillBlockRow(x, y + i, width, RES_P16x16[res + i]);
            }
            break;
        case RES_SIZE_16x32:
            width = 16;
            height = 4;
            for (uint8_t i = 0; i < height; ++i) {
                OLED_FillBlockRow(x, y + i, width, RES_P16x32[res + i]);
            }
            break;
        case RES_SIZE_32x32:
            width = 32;
            height = 4;
            for (uint8_t i = 0; i < height; ++i) {
                OLED_FillBlockRow(x, y + i, width, RES_P32x32[res + i]);
            }
            break;
        case RES_SIZE_32x64:
            width = 32;
            height = 8;
            for (uint8_t i = 0; i < height; ++i) {
                OLED_FillBlockRow(x, y + i, width, RES_F32x64[res + i]);
            }
            break;

        case RES_SIZE_64x32:
            width = 64;
            height = 4;
            for (uint8_t i = 0; i < height; ++i) {
                OLED_FillBlockRow(x, y + i, width, RES_S64x32[res + i]);
            }
            break;
        case RES_SIZE_64x64:
            width = 64;
            height = 8;
            for (uint8_t i = 0; i < height; ++i) {
                OLED_FillBlockRow(x, y + i, width, RES_P64x64[res + i]);
            }
            break;
    }
}

/*
 * Fill 4-digits from (x, y) down to right.
 * Arguments: int8_t x (x-coordinate, it can be negative but only render the x>0 parts)
 *          , uint8_t y (y-coordinate)
 *          , uint16_t num (a number which will be filled)
 * Return: void
 */
void OLED_FillBlockInt4(int8_t x, uint8_t y, uint16_t num) {
    if (num < 10000) {
        // 乘方表
        uint16_t powTable[4] = {1000, 100, 10, 1};
        // 循环设置数字字符
        for (uint8_t i = 0; i < 4; ++i) {
            uint8_t ch = num / powTable[i];
            OLED_FillBlockChar(x + i * 8, y, RES_ID_8x16_NUM(ch));
            num %= powTable[i];
        }
    }
}

/*
 * Fill a 8x16 char from (x, y) down to right.
 * Arguments: int8_t x (x-coordinate, it can be negative but only render the x>0 parts)
 *          , uint8_t y (y-coordinate)
 *          , uint16_t ch (a char which will be filled)
 * Return: void
 */
void OLED_FillBlockChar(int8_t x, uint8_t y, uint8_t ch) {
    for (uint8_t i = 0; i < 2; ++i) {
        OLED_FillBlockRow(x, y + i, 8, RES_F8x16[ch + i]);
    }
}

/*
 * Fill all the OLED screen.
 * Arguments: /
 * Return: void
 */
void OLED_FillScreen() {
    uint8_t NULL_Data[WIDTH_MAX];
    memset(NULL_Data, FILL_DATA, WIDTH_MAX);
    for (int i = 0; i < HEIGHT_MAX; ++i) {
        OLED_FillBlockRow(0, i, WIDTH_MAX, NULL_Data);
    }

}

/*------清除相关------*/

// 从坐标(x,y)处向右下清除 width x 8 个像素
void OLED_ClearBlockRow(uint8_t x, uint8_t y, uint8_t width) {
    if (y < HEIGHT_MAX) {
        width = x + width > WIDTH_MAX ? WIDTH_MAX - x : width;
        uint8_t NULL_Data[width];
        memset(NULL_Data, NULL_DATA, width);
        OLED_SetPosition(x, y);
        OLED_Send(OLED_SEND_DATA, NULL_Data, width);
    }
}

// 从坐标(x,y)处向右下清除 width x height*8 个像素
// 注意：超出后不会清除反侧的
void OLED_ClearBlockCustom(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
    if (x < WIDTH_MAX) {
        // 防止出界
        height = y + height > HEIGHT_MAX ? HEIGHT_MAX - y : height;

        // 清空区域
        for (uint8_t i = 0; i < height; ++i) {
            OLED_ClearBlockRow(x, y + i, width);
        }
    }
}

// 从坐标(x,y)处向右下清除 RES_SIZE_AxB: AxB 个像素
void OLED_ClearBlockAny(uint8_t x, uint8_t y, uint8_t type) {
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
        OLED_ClearBlockCustom(x, y, width, height);
    }
}

// 清除整块屏幕
void OLED_ClearScreen() {
    OLED_ClearBlockCustom(0, 0, WIDTH_MAX, HEIGHT_MAX);
}