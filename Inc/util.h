#include <stdint.h>
#include <stdbool.h>

#define FLAG_DINO_STATUS_LEFT 0
#define FLAG_DINO_STATUS_RIGHT 1
#define FLAG_DINO_STATUS_STOP 2

typedef struct _dino
{
    bool isJumped;
    uint64_t jumpTime;
    uint8_t resource;
    uint8_t y;
} Dino;

// ��תLED��
void LED_toggle();
uint8_t GAME_getDinoFlag(uint16_t timeCnt, uint8_t *flag)