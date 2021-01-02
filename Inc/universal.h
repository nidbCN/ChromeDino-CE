/*
 * Some universal macro definition and header file
 * Created by Gaein nidb, https://www.gaein.cn
 * North Universal Of China
 */

#ifndef _UNIVERSAL_H_
#define _UNIVERSAL_H_

/*------8x16 resource------*/

// 8x16 small cactus 1
#define RES_ID_8x16_CACTUS_1 (0)
// 8x16 small cactus 2
#define RES_ID_8x16_CACTUS_2 (2)
// 8x16 small cactus 3
#define RES_ID_8x16_CACTUS_3 (4)
// 8x16 small cactus 4
#define RES_ID_8x16_CACTUS_4 (6)
// 8x16 font index table
#define RES_ID_8x16_NUM(n) (n*2)

/*------16x16 resource------*/

// 16x16 dino 1
#define RES_ID_16x16_DINO_1 (0)
// 16x16 dino 2
#define RES_ID_16x16_DINO_2 (2)
// 16x16 dino (static)
#define RES_ID_16x16_DINO_3 (4)
// 16x16 dino (died)
#define RES_ID_16x16_DINO_4 (6)

// 16x16 mid-size cactus 1
#define RES_ID_16x16_CACTUS_1 (8)
// 16x16 mid-size cactus 2
#define RES_ID_16x16_CACTUS_2 (10)
// 16x16 mid-size cactus 3
#define RES_ID_16x16_CACTUS_3 (12)

/*------16x32 resource------*/

// 16x32 big cactus 1
#define RES_ID_16x32_CACTUS_1 (0)
// 16x32 big cactus 2
#define RES_ID_16x32_CACTUS_2 (4)
// 16x32 big cactus 3
#define RES_ID_16x32_CACTUS_3 (8)
// 16x32 big cactus 4
#define RES_ID_16x32_CACTUS_4 (12)

/*------16x32 resource------*/

// 32x32 restart logo
#define RES_ID_32x32_RESTART (0)

/*------64x32 resource------*/

// 64x32 GAME string
#define RES_ID_64x32_GAME (0)
// 64x32 OVER string
#define RES_ID_64x32_OVER (4)

/*------32x64 resource------*/
// 32x64 font '0'
#define RES_ID_32x64_0 (0)
// 32x64 font '1'
#define RES_ID_32x64_1 (8)
// 32x64 font '2'
#define RES_ID_32x64_2 (16)
// 32x64 font '3'
#define RES_ID_32x64_3 (24)

/*------Resource size macro------*/
#define RES_SIZE_8x16 (0)
#define RES_SIZE_16x16 (1)
#define RES_SIZE_16x32 (2)
#define RES_SIZE_32x32 (3)
#define RES_SIZE_32x64 (4)
#define RES_SIZE_64x32 (5)
#define RES_SIZE_64x64 (6)

// System lib include
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// STM32 lib include
#include "i2c.h"
#include "gpio.h"

#endif