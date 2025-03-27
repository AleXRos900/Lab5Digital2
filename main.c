/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

volatile uint8_t Leds1 = 0;
volatile uint8_t Leds2 = 0;
volatile uint8_t EstadoCuentaR = 0;
volatile uint8_t Ganador = 0;

uint8_t digitToSegment[10] = {
    0x3F, // 0 -> a,b,c,d,e,f (0b00111111)
    0x06, // 1 -> b,c        (0b00000110)
    0x5B, // 2 -> a,b,d,e,g  (0b01011011)
    0x4F, // 3 -> a,b,c,d,g  (0b01001111)
    0x66, // 4 -> b,c,f,g    (0b01100110)
    0x6D, // 5 -> a,c,d,f,g  (0b01101101)
    0x7D, // 6 -> a,c,d,e,f,g(0b01111101)
    0x07, // 7 -> a,b,c      (0b00000111)
    0x7F, // 8 -> a,b,c,d,e,f,g (0b01111111)
    0x6F  // 9 -> a,b,c,d,f,g   (0b01101111)
};

void Numero(uint8_t digit);
void PrintLeds1();
void PrintLeds2();

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (EstadoCuentaR == 1)
	  {
		   Numero(5);
		   HAL_Delay(1000);
		   Numero(4);
		   HAL_Delay(1000);
		   Numero(3);
		   HAL_Delay(1000);
		   Numero(2);
		   HAL_Delay(1000);
		   Numero(1);
		   HAL_Delay(1000);
		   Numero(0);
		   EstadoCuentaR = 2;
	  }

	  if (EstadoCuentaR == 0)
	  	  {
	  		 if (Ganador == 0){Numero(0);}
	  		 if (Ganador == 1){Numero(1);}
	  		 if (Ganador == 2){Numero(2);}
	  	  }

	  PrintLeds1();
	  PrintLeds2();


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, SA_Pin|SB_Pin|SC_Pin|SD_Pin
                          |SE_Pin|SF_Pin|SG_Pin|LEDJ2_4_Pin
                          |LEDJ2_3_Pin|LEDJ2_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|LEDJ2_1_Pin|LEDJ1_4_Pin|LEDJ1_3_Pin
                          |LEDJ1_2_Pin|LEDJ1_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SA_Pin SB_Pin SC_Pin SD_Pin
                           SE_Pin SF_Pin SG_Pin LEDJ2_4_Pin
                           LEDJ2_3_Pin LEDJ2_2_Pin */
  GPIO_InitStruct.Pin = SA_Pin|SB_Pin|SC_Pin|SD_Pin
                          |SE_Pin|SF_Pin|SG_Pin|LEDJ2_4_Pin
                          |LEDJ2_3_Pin|LEDJ2_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin LEDJ2_1_Pin LEDJ1_4_Pin LEDJ1_3_Pin
                           LEDJ1_2_Pin LEDJ1_1_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|LEDJ2_1_Pin|LEDJ1_4_Pin|LEDJ1_3_Pin
                          |LEDJ1_2_Pin|LEDJ1_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : BOT1_Pin BOT2_Pin BOT3_Pin */
  GPIO_InitStruct.Pin = BOT1_Pin|BOT2_Pin|BOT3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	static uint32_t lastInterruptTick = 0;
	    uint32_t currentTick = HAL_GetTick();
	    if((currentTick - lastInterruptTick) < 100) // 50 ms de debounce
	    {
	        return; // Ignora interrupciones muy cercanas
	    }
	    lastInterruptTick = currentTick;


	if (GPIO_Pin == BOT1_Pin)
	{
		if (EstadoCuentaR == 0)
		{
			EstadoCuentaR = 1;
			Leds1 = 0;
			Leds2 = 0;
		}
	}
	if (GPIO_Pin == BOT2_Pin)
	{
		if (EstadoCuentaR == 2)
		{
			Leds1 = Leds1 + 1;
		}
	}

	if (GPIO_Pin == BOT3_Pin)
	{
		if (EstadoCuentaR == 2)
		{
			Leds2 = Leds2 + 1;
		}
	}


	if (Leds1 == 5) {Ganador = 1; EstadoCuentaR = 0;}
	if (Leds2 == 5) {Ganador = 2; EstadoCuentaR = 0;}

}


void Numero(uint8_t digit)
{

    if (digit > 9) return;
    uint8_t pattern = digitToSegment[digit];

    HAL_GPIO_WritePin(SA_GPIO_Port, SA_Pin, (pattern & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(SB_GPIO_Port, SB_Pin, (pattern & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(SC_GPIO_Port, SC_Pin, (pattern & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(SD_GPIO_Port, SD_Pin, (pattern & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(SE_GPIO_Port, SE_Pin, (pattern & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(SF_GPIO_Port, SF_Pin, (pattern & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(SG_GPIO_Port, SG_Pin, (pattern & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void PrintLeds1()
{

	switch (Leds1)
	{
	case 0:
		HAL_GPIO_WritePin(LEDJ1_1_GPIO_Port, LEDJ1_1_Pin, 0);
		HAL_GPIO_WritePin(LEDJ1_2_GPIO_Port, LEDJ1_2_Pin, 0);
		HAL_GPIO_WritePin(LEDJ1_3_GPIO_Port, LEDJ1_3_Pin, 0);
		HAL_GPIO_WritePin(LEDJ1_4_GPIO_Port, LEDJ1_4_Pin, 0);
	break;


	case 1:
		HAL_GPIO_WritePin(LEDJ1_1_GPIO_Port, LEDJ1_1_Pin, 1);
		HAL_GPIO_WritePin(LEDJ1_2_GPIO_Port, LEDJ1_2_Pin, 0);
		HAL_GPIO_WritePin(LEDJ1_3_GPIO_Port, LEDJ1_3_Pin, 0);
		HAL_GPIO_WritePin(LEDJ1_4_GPIO_Port, LEDJ1_4_Pin, 0);
	break;

	case 2:
		HAL_GPIO_WritePin(LEDJ1_1_GPIO_Port, LEDJ1_1_Pin, 0);
		HAL_GPIO_WritePin(LEDJ1_2_GPIO_Port, LEDJ1_2_Pin, 1);
		HAL_GPIO_WritePin(LEDJ1_3_GPIO_Port, LEDJ1_3_Pin, 0);
		HAL_GPIO_WritePin(LEDJ1_4_GPIO_Port, LEDJ1_4_Pin, 0);
	break;

	case 3:
		HAL_GPIO_WritePin(LEDJ1_1_GPIO_Port, LEDJ1_1_Pin, 0);
		HAL_GPIO_WritePin(LEDJ1_2_GPIO_Port, LEDJ1_2_Pin, 0);
		HAL_GPIO_WritePin(LEDJ1_3_GPIO_Port, LEDJ1_3_Pin, 1);
		HAL_GPIO_WritePin(LEDJ1_4_GPIO_Port, LEDJ1_4_Pin, 0);
	break;

	case 4:
		HAL_GPIO_WritePin(LEDJ1_1_GPIO_Port, LEDJ1_1_Pin, 0);
		HAL_GPIO_WritePin(LEDJ1_2_GPIO_Port, LEDJ1_2_Pin, 0);
		HAL_GPIO_WritePin(LEDJ1_3_GPIO_Port, LEDJ1_3_Pin, 0);
		HAL_GPIO_WritePin(LEDJ1_4_GPIO_Port, LEDJ1_4_Pin, 1);
	break;

	case 5:
		HAL_GPIO_WritePin(LEDJ1_1_GPIO_Port, LEDJ1_1_Pin, 1);
		HAL_GPIO_WritePin(LEDJ1_2_GPIO_Port, LEDJ1_2_Pin, 1);
		HAL_GPIO_WritePin(LEDJ1_3_GPIO_Port, LEDJ1_3_Pin, 1);
		HAL_GPIO_WritePin(LEDJ1_4_GPIO_Port, LEDJ1_4_Pin, 1);
	break;
	}

}

void PrintLeds2()
{

	switch (Leds2)
	{
		case 0:
			HAL_GPIO_WritePin(LEDJ2_1_GPIO_Port, LEDJ2_1_Pin, 0);
			HAL_GPIO_WritePin(LEDJ2_2_GPIO_Port, LEDJ2_2_Pin, 0);
			HAL_GPIO_WritePin(LEDJ2_3_GPIO_Port, LEDJ2_3_Pin, 0);
			HAL_GPIO_WritePin(LEDJ2_4_GPIO_Port, LEDJ2_4_Pin, 0);
		break;


		case 1:
			HAL_GPIO_WritePin(LEDJ2_1_GPIO_Port, LEDJ2_1_Pin, 1);
			HAL_GPIO_WritePin(LEDJ2_2_GPIO_Port, LEDJ2_2_Pin, 0);
			HAL_GPIO_WritePin(LEDJ2_3_GPIO_Port, LEDJ2_3_Pin, 0);
			HAL_GPIO_WritePin(LEDJ2_4_GPIO_Port, LEDJ2_4_Pin, 0);
		break;

		case 2:
			HAL_GPIO_WritePin(LEDJ2_1_GPIO_Port, LEDJ2_1_Pin, 0);
			HAL_GPIO_WritePin(LEDJ2_2_GPIO_Port, LEDJ2_2_Pin, 1);
			HAL_GPIO_WritePin(LEDJ2_3_GPIO_Port, LEDJ2_3_Pin, 0);
			HAL_GPIO_WritePin(LEDJ2_4_GPIO_Port, LEDJ2_4_Pin, 0);
		break;

		case 3:
			HAL_GPIO_WritePin(LEDJ2_1_GPIO_Port, LEDJ2_1_Pin, 0);
			HAL_GPIO_WritePin(LEDJ2_2_GPIO_Port, LEDJ2_2_Pin, 0);
			HAL_GPIO_WritePin(LEDJ2_3_GPIO_Port, LEDJ2_3_Pin, 1);
			HAL_GPIO_WritePin(LEDJ2_4_GPIO_Port, LEDJ2_4_Pin, 0);
		break;

		case 4:
			HAL_GPIO_WritePin(LEDJ2_1_GPIO_Port, LEDJ2_1_Pin, 0);
			HAL_GPIO_WritePin(LEDJ2_2_GPIO_Port, LEDJ2_2_Pin, 0);
			HAL_GPIO_WritePin(LEDJ2_3_GPIO_Port, LEDJ2_3_Pin, 0);
			HAL_GPIO_WritePin(LEDJ2_4_GPIO_Port, LEDJ2_4_Pin, 1);
		break;

		case 5:
			HAL_GPIO_WritePin(LEDJ2_1_GPIO_Port, LEDJ2_1_Pin, 1);
			HAL_GPIO_WritePin(LEDJ2_2_GPIO_Port, LEDJ2_2_Pin, 1);
			HAL_GPIO_WritePin(LEDJ2_3_GPIO_Port, LEDJ2_3_Pin, 1);
			HAL_GPIO_WritePin(LEDJ2_4_GPIO_Port, LEDJ2_4_Pin, 1);
		break;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
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
