#ifndef _KEY_BOARD_H_
#define _KEY_BOARD_H

#include "universal.h"

/*
 * Get if jump button is hit
 * Arguments: /
 * Return: bool is the button was pressed
 */
bool KB_GetJumpBtnStatus();

/*
 * Get if restart button is hit
 * Arguments: /
 * Return: bool is the button was pressed
 */
bool KB_GetRestartBtnStatus();

/*
 * Wait until jump button was pressed
 * Arguments: uint8_t flush time between each loop
 * Return: void
 */
void KB_WaitJumpBtnHit(uint8_t flushTime);

/*
 * Wait until restart button was pressed
 * Arguments: uint8_t flush time between each loop
 * Return: void
 */
void KB_WaitRestartBtnHit(uint8_t flushTime);

#endif