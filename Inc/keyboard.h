#ifndef _KEYBOARD_H_
#define _KEY_BOARD_H

#include "universal.h"

bool KB_GetJumpBtnStatus();

bool KB_GetRestartBtnStatus();

void KB_WaitJumpBtnHit(uint8_t flushTime);

void KB_WaitRestartBtnHit(uint8_t flushTime);

#endif