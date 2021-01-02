#include "universal.h"
#include "keyboard.h"

/*
 * Get if jump button is hit
 * arguments: /
 * return: bool is the button was pressed
 */
bool KB_GetJumpBtnStatus() {
    return HAL_GPIO_ReadPin(BTN_R_GPIO_Port, BTN_R_Pin) ? true : false;
}

/*
 * Get if restart button is hit
 * arguments: /
 * return: bool is the button was pressed
 */
bool KB_GetRestartBtnStatus() {
    return HAL_GPIO_ReadPin(BTN_L_GPIO_Port, BTN_L_Pin) ? true : false;
}

/*
 * Wait until jump button was pressed
 * arguments: uint8_t flush time between each loop
 * return: void
 */
void KB_WaitJumpBtnHit(uint8_t flushTime) {
    bool status = false;    // Define a var to record status.
    while (status == false) {
        status = KB_GetJumpBtnStatus();
        HAL_Delay(flushTime);
    }
    return;
}

/*
 * Wait until restart button was pressed
 * arguments: uint8_t flush time between each loop
 * return: void
 */
void KB_WaitRestartBtnHit(uint8_t flushTime) {
    bool status = false;
    while (status == false) {
        status = KB_GetRestartBtnStatus();
        HAL_Delay(flushTime);
    }
    return;
}