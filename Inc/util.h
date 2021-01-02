#include <stdint.h>
#include <stdbool.h>

// Dino object struct.
typedef struct struct_dino {
    bool isJumped;      // Is jumped
    uint32_t jumpTime;  // Jump start time
    uint8_t flag;       // Flag of dino
    uint8_t y;          // y-coordinate of dino
    uint32_t lastDraw;  // Last draw time
} Dino;

// cactus object struct
typedef struct struct_cactus {
    uint8_t width;      // Width of cactus
    uint8_t height;     // Height of cactus
    uint8_t size;       // Size macro of cactus
    uint8_t flag;       // Flag macro of cactus
    int8_t x;           // x-coordinate of cactus
    uint8_t y;          // y-coordinate of cactus
} Cactus;

/*
 * Init the OLED screen for game.
 * Arguments: /
 * Return: void
 */
void GAME_InitScreen();

/*
 * Init a new dino.
 * Arguments: /
 * Return: Dino* (a new malloced dino)
 */
Dino *GAME_InitDino();

/*
 * Game count down three to zero.
 * Arguments: /
 * Return: void
 */
void GAME_CountDown();

/*
 * Draw the game over interface.
 * Arguments: /
 * Return: void
 */
void GAME_DrawGameOver();

/*
 * Draw a dino on screen.
 * Arguments: Dino* (input a dino you want to draw)
 * Return: Dino* (return a dino has been auto draw)
 */
Dino *GAME_DrawDino(Dino *gameDino);

/*
 * Draw a cactus, and make it left
 * Arguments: Cactus* (input a cactus which will be drawn)
 * Return: Cactus* (a cactus has been drawn)
 */
Cactus *GAME_DrawCactus(Cactus *gameCactus);

/*
 * Set dino status to jumped.
 * Arguments: Dino* (input dino pointer)
 * Return: Dino* (a dino has inited)
 */
Dino *GAME_SetDinoJump(Dino *gameDino);

/*
 * Set dino status to not jumped
 * argument: Dino* (input dino pointer)
 * return: Dino* (a dino has set to not jump)
 */
Dino *GAME_SetDinoNotJump(Dino *gameDino);

/*
 * Get the height of jumped dino
 * argument: Dino* (input dino pointer)
 * return: Dino* (a dino has set to not jump)
 */
Dino *GAME_GetDinoHeight(Dino *gameDino);

/*
 * Get the picture of dino.
 * Arguments: Dino* (input a dino)
 * Return: Dino* (return a dino which flag has been edit)
 * */
Dino *GAME_GetDinoFlag(Dino *gameDino);

/*
 * Get a dino if it should be drawn.
 * Arguments: Dino* (input a dino which you want to judge)
 * Return: bool (Should - true, Should not - false)
 */
bool GAME_GetDinoShouldDraw(Dino *gameDino);

/*
 * Get a random cactus.
 * Arguments: /
 * Return: Cactus* (a random cactus object)
 */
Cactus *GAME_GetCactusRand();

/*
 * Get game status, judge if it can be continued.
 * Arguments: Dino* (game used dino object pointer), Cactus (game used cactus object pointer)
 * Return: bool (continue - true, failed - false)
 */
bool GAME_GetGameStatus(Dino *gameDino, Cactus *gameCactus);