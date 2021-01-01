/*
 * Some universal macro definition and header file
 * Created by Gaein nidb, https://www.gaein.cn
 * North Universal Of China
 */

#ifndef _UNIVERSAL_H_
#define _UNIVERSAL_H_

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
// 16x16 dino died
#define RES_ID_16x16_DINO_4 (6)
// 16x16 cactus1
#define RES_ID_16x16_CACTUS_1 (8)

#define RES_ID_16x16_CACTUS_2 (10)

#define RES_ID_16x16_CACTUS_3 (12)


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

// 代表游戏资源大小
#define RES_SIZE_8x16 (0)
#define RES_SIZE_16x16 (1)
#define RES_SIZE_16x32 (2)
#define RES_SIZE_32x32 (3)
#define RES_SIZE_64x32 (4)
#define RES_SIZE_64x64 (5)

// system lib include
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// stm32 lib include
#include "i2c.h"
#include "gpio.h"

#endif