#include "util.h"
#include "gpio.h"

void LED_toggle() {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

uint8_t GAME_jump(uint16_t time) {
    // 0400 - 0600
    // 0250 - 0400
    // 0125 - 0250:125
    // 0050 - 0125:75
    // 0000 - 0050:50
    uint8_t y = 6;
    if (time >50 && time <= 125 ) {
        y = 5;
    } else if (time > 125 && time <= 250) {
        y = 4;
    } else if (time > 250 && time <= 400) {
        y = 3;
    } else if (time > 400 && time <= 600) {
        y = 2;
    }
    return y;
}