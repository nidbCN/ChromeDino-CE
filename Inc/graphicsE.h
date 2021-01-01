/*
 * A graphics library of 128 x 64 monochrome dot matrix OLED display
 * Created by Gaein nidb, https://www.gaein.cn
 * North Universal Of China
 */

#ifndef _GRAPHICS_EMBEDDED_H_
#define _GRAPHICS_EMBEDDED_H_


/*------宏定义------*/

/*------函数参数------*/

// 发送类别：指令
#define OLED_SEND_CMD (0x00)
// 发送类别：数据
#define OLED_SEND_DATA (0x40)

// 设置显示：关闭
#define OLED_DISPLAY_OFF (0)
// 设置显示：开启
#define OLED_DISPLAY_ON (1)



/*------函数声明------*/

/*------OLED相关------*/

// OLED 发送数据
// 注意：type为 OLED_SEND_DATA 或 OLED_SEND_CMD
void OLED_Send(uint8_t type, uint8_t *data, uint8_t size);

// OLED 设置显示开关
// 注意：option为 OLED_DISPLAY_ON 或 OLED_DISPLAY_OFF
void OLED_SetDisplay(uint8_t option);

// OLED设置初始化
void OLED_SetInit();

// 设置光标位置(x,y)
void OLED_SetPosition(uint8_t x, uint8_t y);
/*------填充相关------*/

// 从坐标(x,y)处向右下填充 width x 8 个像素大小的内容 res数组
// 注意：x为负数只渲染正数部分
void OLED_FillBlockRow(int8_t x, uint8_t y, uint8_t width, uint8_t *res);

// 从坐标(x,y)处向右下填充 RES_SIZE_AxB: AxB 个像素大小的内容 RES_CONTENT
void OLED_FillBlockAny(int8_t x, uint8_t y, uint8_t type, uint8_t res);

//  从坐标(x,y)处向右下填充4位数字
void OLED_FillBlockInt4(int8_t x, uint8_t y, uint16_t num);

// 从坐标(x,y)处向右下填充一个字符
void OLED_FillBlockChar(int8_t x, uint8_t y, uint8_t ch);

// 填充整块屏幕
void OLED_FillScreen();

/*------清除相关------*/

// 从坐标(x,y)处向右下清除 width x 8 个像素
void OLED_ClearBlockRow(uint8_t x, uint8_t y, uint8_t width);

// 从坐标(x,y)处向右下清除 width x height*8 个像素
// 注意：超出后不会清除反侧的
void OLED_ClearBlockCustom(uint8_t x, uint8_t y, uint8_t width, uint8_t height);

// 从坐标(x,y)处向右下清除 RES_SIZE_AxB: AxB 个像素
void OLED_ClearBlockAny(uint8_t x, uint8_t y, uint8_t type);

// 清除整块屏幕
void OLED_ClearScreen();

#endif
