/*------头文件------*/
#include "oled.h"
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

/*------函数定义------*/

/*------填充相关------*/

// 从坐标(x,y)处向右下填充 width x 8 个像素大小的内容 res数组
// 注意：x为负数只渲染正数部分
void GAME_OLED_FillBlockRow(int8_t x, uint8_t y, uint8_t width, uint8_t *res)
{
    uint8_t i = x < 0 ? -x : 0; // 跳过 x < 0 的部分
    // 防止出界
    if (y < HEIGHT_MAX)
    {
        width = x + width > WIDTH_MAX ? WIDTH_MAX - x : x;
        OLED_Set_Pos(x, y); // 设置光标
        while (i < width)   // 渲染置顶宽度的数据
        {
            OLED_WR_DATA(res[i]);
            ++i;
        }
    }
}

// 从坐标(x,y)处向右下填充 RES_SIZE_AxB: AxB 个像素大小的内容 RES_CONTENT
void GAME_OLED_FillBlockAny(int8_t x, uint8_t y, uint8_t type, uint8_t res)
{
    uint8_t width = 0;
    uint8_t height = 0;
    // 判断类型
    switch (type)
    {
    case RES_SIZE_8x16:
        width = 8;
        height = 2;
        for (uint8_t i = 0; i < height; ++i)
        {
            GAME_OLED_FillBlockRow(x, y + i, width, RES_G8x16[res + i]);
        }
        break;
    case RES_SIZE_16x16:
        width = 16;
        height = 2;
        for (uint8_t i = 0; i < height; ++i)
        {
            GAME_OLED_FillBlockRow(x, y + i, width, RES_G16x16[res + i]);
        }
        break;
    case RES_SIZE_16x32:
        width = 16;
        height = 4;
        for (uint8_t i = 0; i < height; ++i)
        {
            GAME_OLED_FillBlockRow(x, y + i, width, RES_G16x32[res + i]);
        }
        break;
    case RES_SIZE_32x32:
        width = 32;
        height = 4;
        for (uint8_t i = 0; i < height; ++i)
        {
            GAME_OLED_FillBlockRow(x, y + i, width, RES_G32x32[res + i]);
        }
        break;
    case RES_SIZE_64x32:
        width = 64;
        height = 4;
        for (uint8_t i = 0; i < height; ++i)
        {
            GAME_OLED_FillBlockRow(x, y + i, width, RES_G64x32[res + i]);
        }
        break;
    case RES_SIZE_64x64:
        width = 64;
        height = 8;
        for (uint8_t i = 0; i < height; ++i)
        {
            GAME_OLED_FillBlockRow(x, y + i, width, RES_G64x64[res + i]);
        }
        break;
    }
}

//  从坐标(x,y)处向右下填充4位数字
void GAME_OLED_FillBlockInt4(int8_t x, uint8_t y, uint16_t num)
{
    // 乘方表
    uint8_t powTable[4] = {1000, 100, 10, 1};
    // 循环设置数字字符
    for (int i = 0; i < 4; i++)
    {
        uint8_t ch = RES_ID_8x16_NUM[num / powTable[i]]; // 获取数字对于的表ID
        GAME_OLED_FillBlockChar(x + i * 8, y, ch);       // 显示数字
        num %= powTable[i];
    }
}

// 从坐标(x,y)处向右下填充一个字符
void GAME_OLED_FillBlockChar(int8_t x, uint8_t y, uint8_t ch)
{
    if (y < HEIGHT_MAX)
    {
        uint8_t i = x < 0 ? -x : 0;
        while (i < 2)
        {
            for (int j = 0; j < 8 && x + j < WIDTH_MAX; ++j)
            {
                OLED_Set_Pos(x, y + j);
                OLED_WR_DATA(RES_F8x16[ch][j]);
            }
            ++i;
        }
    }
}

// 填充整块屏幕
void GAME_OLED_FillScreen()
{
    for (int i = 0; i < HEIGHT_MAX; ++i)
    {
        for (int j = 0; j < WIDTH_MAX; ++j)
        {
            OLED_Set_Pos(i, j);
            OLED_WR_DATA(FILL_DATA);
        }
    }
}

/*------清除相关------*/

// 从坐标(x,y)处向右下清除 width x 8 个像素
void GAME_OLED_ClearBlockRow(uint8_t x, uint8_t y, uint8_t width)
{
    if (y < HEIGHT_MAX)
    {
        width = x + width > WIDTH_MAX ? WIDTH_MAX - x : x;
        OLED_Set_Pos(x, y);
        uint8_t count = width * 8;
        for (uint8_t i = 0; i < count; i++)
        {
            OLED_WR_DATA(NULL_DATA);
        }
    }
}

// 从坐标(x,y)处向右下清除 width x height*8 个像素
// 注意：超出后不会清除反侧的
void GAME_OLED_ClearBlockCustom(uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
    // 防止出界
    height = y + height > HEIGHT_MAX ? HEIGHT_MAX - y : height;

    // 清空区域
    for (int i = 0; i < height; ++i)
    {
        GAME_OLED_ClearBlockRow(x, y, width);
    }
}

// 从坐标(x,y)处向右下清除 RES_SIZE_AxB: AxB 个像素
void GAME_OLED_ClearBlockAny(uint8_t x, uint8_t y, uint8_t type)
{
    uint8_t width = 0;
    uint8_t height = 0;

    // 通过type设置清除的大小
    switch (type)
    {
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
    if (width && height)
    {
        GAME_OLED_ClearBlockCustom(x, y, width, height);
    }
}

// 清除整块屏幕
void GAME_OLED_ClearScreen()
{
    GAME_OLED_ClearBlockCustom(0, 0, WIDTH_MAX, HEIGHT_MAX);
}