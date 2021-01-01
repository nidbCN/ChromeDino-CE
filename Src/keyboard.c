#include "universal.h"
#include "keyboard.h"

// get if jump button is hit
bool KB_getJumpBtnStatus() {
    return HAL_GPIO_ReadPin(BTN_R_GPIO_Port, BTN_R_Pin) ? true : false;
}

// get
bool KB_getRestartBtnStatus() {
    return HAL_GPIO_ReadPin(BTN_L_GPIO_Port, BTN_L_Pin) ? true : false;
}

// wait until jump button is hit
void KB_waitJumpBtnHit(uint8_t flushTime) {
    bool status = false;
    while (status == false) {
        status = KB_getJumpBtnStatus();
        HAL_Delay(flushTime);
    }
    return;
}

// wait until restart button is hit
void KB_waitRestartBtnHit(uint8_t flushTime) {
    bool status = false;
    while (status == false) {
        status = KB_getRestartBtnStatus();
        HAL_Delay(flushTime);
    }
    return;
}