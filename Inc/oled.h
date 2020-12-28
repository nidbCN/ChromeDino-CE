#ifndef __OLED_H_
#define __OLED_H_

#include <stdint.h>
#include "i2c.h"

// 大号字符
#define CHAR_LG 16
// 小号字符
#define CHAR_SM 12
// 游戏字符小
#define CHAR_GAME_SM 6
// 游戏字符大
#define CHAR_GAME_LG 8

void WriteCmd(void);

//向设备写控制命令
void OLED_WR_CMD(uint8_t cmd);

//向设备写数据
void OLED_WR_DATA(uint8_t data);

//初始化oled屏幕
void OLED_Init(void);

//清屏
void OLED_Clear(void);

void OLED_ClearVertical(uint8_t x, uint8_t y, uint8_t height);

//清行
void OLED_ClearRow(uint8_t i);

//开启OLED显示
void OLED_Display_On(void);

//关闭OLED显示
void OLED_Display_Off(void);

//设置光标
void OLED_Set_Pos(uint8_t x, uint8_t y);

void OLED_On(void);

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size);

void OLED_ShowGame(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size);

//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x, uint8_t y, unsigned int num, uint8_t len, uint8_t size2);

//显示一个字符号串
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size);

//显示汉字
//hzk 用取模软件得出的数组
void OLED_ShowChinese(uint8_t x, uint8_t y, uint8_t no);

#endif
