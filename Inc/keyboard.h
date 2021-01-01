#ifndef _KEYBOARD_H_
#define _KEY_BOARD_H

#include "universal.h"

bool KB_getJumpBtnStatus();

bool KB_getRestartBtnStatus();

void KB_waitJumpBtnHit(uint8_t flushTime);

void KB_waitRestartBtnHit(uint8_t flushTime);

#endif