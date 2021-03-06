/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "universal.h"
#include "util.h"
#include "keyboard.h"
#include "graphicsE.h"
#include "random.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//uint8_t axis = 0;
//uint16_t score = 14;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    /* USER CODE BEGIN 1 */

    // Try to init random 10 times.
    for (int i = 0; i < 10; ++i) {
        if (RAND_SetRandomInit()) {
            break;  // Random init success.
        }
    }
    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */
    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_I2C1_Init();
    /* USER CODE BEGIN 2 */

    // Attention: OLED codes must behind the I2C Init function.
    OLED_SetInit();                     // Init OLED.
    OLED_SetDisplay(OLED_DISPLAY_ON);   // Set OLED display to ON.

    // New a cactus object.
    Cactus *gameCactus = GAME_GetCactusRand();

    // New a game dino object.
    Dino *gameDino = GAME_InitDino();

    uint16_t score = 0;             // Define a var to record game scores.
    uint32_t timer = HAL_GetTick(); // Define a var to record last loop end time.
    // Define a var to record random interval number.
    uint16_t interval = GAME_GetRandomNumber_uint16(500, 1000);

    // Clear the screen.
    OLED_ClearScreen();
    // Start count down(three to zero).
    GAME_CountDown();
    // Init the OLED screen.
    GAME_InitScreen();
    OLED_FillBlockInt4(96, 0, 0);   // Init the score with zero.
    // Define a bool var to record if button has pressed down(lock).
    uint8_t btnHasPressed = false;
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    // Operation loop
    while (true) {
        /* USER CODE END WHILE */
        /* USER CODE BEGIN 3 */

        gameDino = GAME_DrawDino(gameDino); // Draw the dino

        // Jump button was pressed.
        if (KB_GetJumpBtnStatus() == true) {
            btnHasPressed = true;       // Lock the button.
            GAME_SetDinoJump(gameDino); // Set game dino status to jumped.
            // Set LED On.
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
        } else {
            btnHasPressed = false;      // Unlock the button.
            // Set Light Off
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
        }

        // Try to draw a cactus.
        if (gameCactus != NULL) {
            uint8_t plusScore = gameCactus->height * 2;     // Define a var to record the score.
            gameCactus = GAME_DrawCactus(gameCactus);       // Draw the cactus.
            if (gameCactus == NULL) {
                score += plusScore;                               // Calculate the new score.
                OLED_FillBlockInt4(96, 0, score);           // Display the new score.
            }
        } else {
            // Get now time.
            uint32_t nowTime = HAL_GetTick();
            if (nowTime - timer > interval) {
                // Try to rand a cactus interval.
                gameCactus = GAME_GetCactusRand();
                interval = GAME_GetRandomNumber_uint16(1000, 1500);     // Set new interval.
                timer = nowTime;                                                 // Renew timer
            }
        }

        // Game over
        if (GAME_GetGameStatus(gameDino, gameCactus) == false) {
//            OLED_ClearBlockAny(0, 6, RES_SIZE_16x16);
//            OLED_FillBlockAny(0, 6, RES_SIZE_16x16, RES_ID_16x16_DINO_4);
            gameDino->flag = RES_ID_16x16_DINO_4;
            GAME_DrawDino(gameDino);

            HAL_Delay(600);
            OLED_ClearScreen();         // Clear screen
            GAME_DrawGameOver();        // Draw game over interface

            KB_WaitRestartBtnHit(200);     // Wait for restart button pressed
            __set_FAULTMASK(1);            // Turn off total interrupt
            NVIC_SystemReset();                     // Request MCU restart
        }
    }

    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
        // Light the LED
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
        HAL_Delay(5000);            // Delay 5s
        __set_FAULTMASK(1);      // Turn off total interrupt
        NVIC_SystemReset();               // Request MCU restart
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
