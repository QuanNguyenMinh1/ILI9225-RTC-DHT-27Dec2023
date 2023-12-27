/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "ILI9225.h"
#include "DHT.h"
#include "stdio.h"
#include "stdint.h"
#include <string.h>
#include "RTC.h"
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
I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN PV */
uint8_t second_present, min_present, hour_present, date_present, month_present, year_present;
uint8_t second_temp, min_temp, hour_temp, date_temp, month_temp, year_temp;
char temperature_string[100];
char humidity_string[100];
float Temperature;
float Humidity;
char str1[100];

char str2[100];

DHT_DataTypedef DHT11_Data;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_I2C2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
DHT_DataTypedef DHT11;
DateTime_t datetime;

void Read_DataDHT(void)
{
	DHT_GetData(&DHT11_Data);
	Temperature = DHT11_Data.Temperature;
	Humidity = DHT11_Data.Humidity;
}

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
  MX_SPI2_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
  lcd_init();
  fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_WHITE);
  draw_string(0, 50, COLOR_GREENYELLOW, 5, "HELLO");
  HAL_Delay(2500);
  fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_WHITE);
//  Read_DataDHT();
//
  // Cài đặt thời gian ban đầu
  datetime.second = 15;
  datetime.min = 44;
  datetime.hour = 12;
  datetime.day = 8;
  datetime.date = 58;
  datetime.month = 12;
  datetime.year = 23;
  RTC_WriteTime(&datetime);

  draw_string(20, 50, COLOR_GOLD, 5, "QMDP");
  HAL_Delay(2500);
  fill_rectangle(0, 0, 176, 220, COLOR_WHITE);
//  Read_DataDHT();
  draw_string(20, 20, COLOR_GOLD, 1, "TEMPERATURE");
  draw_string(20, 40, COLOR_GOLD, 1, "HUMIDITY");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		 RTC_ReadTime(&datetime);
		  second_temp = datetime.second;
		  min_temp = datetime.min;
		  hour_temp = datetime.hour;
		  date_temp = datetime.date;
		  month_temp = datetime.month;
		  year_temp = datetime.year;
		  sprintf(str1, "Time %.2d:%.2d:%.2d", datetime.hour, datetime.min, datetime.second);


		  if(second_temp != second_present)
		  {
			  fill_rectangle(140, 100, 160, 110, COLOR_WHITE);
			  second_present = second_temp;
		  }
		  draw_string(40, 100, COLOR_BLACK, 1, str1);

		  if(min_temp != min_present)
		  	  {
		  		  fill_rectangle(110, 100, 130, 110, COLOR_WHITE);
		  		  min_present = min_temp;
		  	  }
		  draw_string(40, 100, COLOR_BLACK, 1, str1);

		  if(hour_temp != hour_present)
		 	  	  {
		 	  		  fill_rectangle(85, 100, 105, 110, COLOR_WHITE);
		 	  		  hour_present = hour_temp;
		 	  	  }
		  draw_string(40, 100, COLOR_BLACK, 1, str1);

		  sprintf(str2,"Date %.2d/%.2d/%.2d",datetime.date,datetime.month,datetime.year );
//	// để sprintf ở đây cho nó chính xác, date, month, year lâu lắm
//		  //để sprintf ở đây để convert, lệnh in lên LCD nằm trong thư viện của LCD
		  if(date_temp != date_present)
		  	 	  	  {
		  	 	  		  fill_rectangle(85, 115, 105, 135, COLOR_WHITE);
		  	 	  		  date_present = date_temp;
		  	 	  	  }
		  	  draw_string(40, 120, COLOR_BLACK, 1, str2);

		  	if(month_temp != month_present)
		  		 	  	  {
		  		 	  		  fill_rectangle(110, 115, 130, 135, COLOR_WHITE);
		  		 	  		  month_present = month_temp;
		  		 	  	  }
		  		  draw_string(40, 120, COLOR_BLACK, 1, str2);

		  		if(year_temp != year_present)
		  			 	  	  {
		  			 	  		  fill_rectangle(135, 115, 160, 135, COLOR_WHITE);
		  			 	  		  year_present = year_temp;
		  			 	  	  }
		  			  draw_string(40, 120, COLOR_BLACK, 1, str2);


	      snprintf(temperature_string, 7, "%.2f", Temperature);
	      snprintf(humidity_string, 7, "%.2f", Humidity);
	      fill_rectangle(150, 20, 220, 50, COLOR_WHITE);
//          Read_DataDHT();
	      draw_string(20, 20, COLOR_GOLD, 1, "TEMPERATURE");
	      draw_string(20, 40, COLOR_GOLD, 1, "HUMIDITY");

	      draw_string(150, 20, COLOR_BLUE, 1, temperature_string);
		  draw_string(150, 40, COLOR_BLUE, 1, humidity_string);
//	  	  DHT_GetData(&dht11);
	  	  Read_DataDHT();
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
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7|CMD_Pin|CS_Pin|RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA7 CMD_Pin CS_Pin RST_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_7|CMD_Pin|CS_Pin|RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
