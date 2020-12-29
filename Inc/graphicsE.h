/* 
 * 嵌入式OLED图形库，适用于128x64单色点阵屏
 * By Gaein nidb , https://www.gaein.cn
 * 中北大学 | 大数据学院 2007040115李子康
 */
#include <stdint.h>
#ifndef _GRAPHICS_EMBEDDED_
#define _GRAPHICS_EMBEDDED_

/*------宏定义------*/

/*------8x16 资源------*/

// 8x16 小仙人掌1
#define RES_ID_8x16_CACTUS_1 (0)
// 8x16 小仙人掌2
#define RES_ID_8x16_CACTUS_2 (2)
// 8x16 小仙人掌3
#define RES_ID_8x16_CACTUS_3 (4)
// 8x16 小仙人掌4
#define RES_ID_8x16_CACTUS_4 (6)
// 8x16 字体索引表
#define RES_ID_8x16_NUM(n) (n*2)

/*------16x16 资源------*/

// 16x16 恐龙1
#define RES_ID_16x16_DINO_1 (0)
// 16x16 恐龙2
#define RES_ID_16x16_DINO_2 (2)
// 16x16 恐龙静态
#define RES_ID_16x16_DINO_3 (4)

/*------16x32 资源------*/

// 16x32 大仙人掌1
#define RES_ID_16x32_CACTUS_1 (0)
// 16x32 大仙人掌2
#define RES_ID_16x32_CACTUS_2 (4)
// 16x32 大仙人掌3
#define RES_ID_16x32_CACTUS_3 (8)
// 16x32 大仙人掌4
#define RES_ID_16x32_CACTUS_4 (12)

/*------16x32 资源------*/

// 32x32 重新开始
#define RES_ID_32x32_RESTART (0)

/*------64x32资源------*/

// 64x32 GAME字符串
#define RES_ID_64x32_GAME (0)
// 64x32 OVER字符串
#define RES_ID_64x32_OVER (4)

/*------64x64 资源------*/

// 64x64 4FC7838F-A9F9-4D3A-8643-FC23406DF6E9

#define RES_ID_64x64_4FC7838FA9F94D3A8643FC23406DF6E9 (0)

// 代表游戏资源大小
#define RES_SIZE_8x16 (0)
#define RES_SIZE_16x16 (1)
#define RES_SIZE_16x32 (2)
#define RES_SIZE_32x32 (3)
#define RES_SIZE_64x32 (4)
#define RES_SIZE_64x64 (5)

/*------函数声明------*/

/*------填充相关------*/

// 从坐标(x,y)处向右下填充 width x 8 个像素大小的内容 res数组
// 注意：x为负数只渲染正数部分
void GAME_OLED_FillBlockRow(int8_t x, uint8_t y, uint8_t width, uint8_t *res);

// 从坐标(x,y)处向右下填充 RES_SIZE_AxB: AxB 个像素大小的内容 RES_CONTENT
void GAME_OLED_FillBlockAny(int8_t x, uint8_t y, uint8_t type, uint8_t res);

void GAME_OLED_FillBlockInt4(int8_t x, uint8_t y, uint16_t num);

void GAME_OLED_FillBlockChar(int8_t x, uint8_t y, uint8_t type);

// 填充整块屏幕
void GAME_OLED_FillScreen();

/*------清除相关------*/

// 从坐标(x,y)处向右下清除 width x 8 个像素
void GAME_OLED_ClearBlockRow(uint8_t x, uint8_t y, uint8_t width);

// 从坐标(x,y)处向右下清除 width x height*8 个像素
// 注意：超出后不会清除反侧的
void GAME_OLED_ClearBlockCustom(uint8_t x, uint8_t y, uint8_t width, uint8_t height);

// 从坐标(x,y)处向右下清除 RES_SIZE_AxB: AxB 个像素
void GAME_OLED_ClearBlockAny(uint8_t x, uint8_t y, uint8_t type);

// 清除整块屏幕
void GAME_OLED_ClearScreen();

#endif
