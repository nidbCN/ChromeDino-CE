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
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "util.h"
#include "graphicsE.h"
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

    // OLED codes must behind the I2C Init function
    OLED_SetInit();                     // Init OLED
    OLED_SetDisplay(OLED_DISPLAY_ON);   // Set OLED display to ON
    OLED_ClearScreen();                 // Clear OLED screen


    // New a cactus object
    Cactus *gameCactus = GAME_getCactusRand();

    // New a game dino object
    Dino *gameDino = (Dino *) malloc(sizeof(Dino));
    // Init the game dino object
    gameDino->isJumped = false;
    gameDino->jumpTime = 0;
    gameDino->flag = RES_ID_16x16_DINO_1;
    gameDino->y = 6;

    uint16_t score = 0;             // A var to record game scores
    uint64_t timer = HAL_GetTick(); // A var to record last loop end time

    uint8_t btnHasPressed = false;  // define a bool to record if button has pressed down
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (true) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */

        // button jump pressed
        if (HAL_GPIO_ReadPin(BTN_R_GPIO_Port, BTN_R_Pin) == GPIO_PIN_SET) {
            btnHasPressed = true;
            // set game dino status to jumped
            GAME_setDinoJump(gameDino);
            // set LED light
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
        } else {
            btnHasPressed = false;
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
        }

        if (gameCactus != NULL) {
            gameCactus = GAME_drawCactus(gameCactus);
            if (gameCactus == NULL) {
                ++score;
                OLED_FillBlockInt4(96, 0, score);
            }
        } else {
            uint64_t nowTime = HAL_GetTick();
            if (nowTime - timer > 1000) {
                // try to rand a cactus
                gameCactus = GAME_getCactusRand();
                timer = nowTime;
            }
        }

        gameDino = GAME_drawDino(gameDino);


        uint8_t nowTime = HAL_GetTick();
//        if ((nowTime - timer) < 30) {
//            HAL_Delay(30 - (nowTime - timer));
//        }

        if (GAME_getGameStatus(gameDino, gameCactus) == false) {
            OLED_ClearScreen();
            while (HAL_GPIO_ReadPin(BTN_L_GPIO_Port, BTN_L_Pin) != GPIO_PIN_SET) {
                OLED_FillBlockAny(0, 0, RES_SIZE_64x32, RES_ID_64x32_GAME);
                OLED_FillBlockAny(64, 4, RES_SIZE_64x32, RES_ID_64x32_OVER);
                OLED_FillBlockAny(16, 4, RES_SIZE_32x32, RES_ID_32x32_RESTART);
                OLED_FillBlockAny(90, 1, RES_SIZE_16x16, RES_ID_16x16_DINO_2);
                LED_toggle();
                HAL_Delay(100);
            }
            __set_FAULTMASK(1);//关闭总中断
            NVIC_SystemReset();//请求单片机重启

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
