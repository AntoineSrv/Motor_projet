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
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pwm.h"
#include "encoder.h"
#include "bouton.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ADC_BUF_SIZE 2
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t ADC_buffer[ADC_BUF_SIZE];

int counter =0;
int val[10];
int counter_val=0;
int moyenne_f=0;
int courant = 0;
int alpha_test = 500;
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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM14_Init();
  MX_TIM15_Init();
  MX_TIM16_Init();
  MX_TIM17_Init();
  MX_USART1_UART_Init();
  MX_USART4_UART_Init();
  MX_SPI1_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */

	HAL_ADCEx_Calibration_Start(&hadc1);
	/*if(HAL_OK != HAL_ADC_Start_DMA(&hadc1, ADC_buffer, ADC_BUF_SIZE)){
		Error_Handler();
	}
	 */
	HAL_TIM_Base_Start(&htim6);

	codeur_start();

	Motor_drv moteur1,moteur2;

	motor_Init(&moteur1,&moteur2);
	moteur1.sens = 1;
	moteur1.alpha = alpha_test;
	moteur1.update(moteur1);

	moteur1.pwm_start(moteur1.Timer_Backward,moteur1.Channel_Backward);
	moteur1.pwm_start(moteur1.Timer_Forward,moteur1.Channel_Forward);

	moteur2.sens = 1;
	moteur2.alpha = alpha_test;
	moteur2.update(moteur2);

	moteur2.pwm_start(moteur2.Timer_Backward,moteur2.Channel_Backward);
	moteur2.pwm_start(moteur2.Timer_Forward,moteur2.Channel_Forward);

	for (alpha_test; alpha_test<1000; alpha_test++){
		moteur1.alpha = alpha_test;
		moteur1.update(moteur1);
		moteur2.alpha = alpha_test;
		moteur2.update(moteur2);
		HAL_Delay(5);
	}

	for (alpha_test; alpha_test>0; alpha_test--){
		moteur1.alpha = alpha_test;
		moteur1.update(moteur1);
		moteur2.alpha = alpha_test;
		moteur2.update(moteur2);
		HAL_Delay(5);
	}

	moteur1.sens = 2;
	for (alpha_test; alpha_test<1000; alpha_test++){
		moteur1.alpha = alpha_test;
		moteur1.update(moteur1);
		moteur2.alpha = alpha_test;
		moteur2.update(moteur2);
		HAL_Delay(5);
	}


	moteur1.pwm_stop(moteur1.Timer_Backward,moteur1.Channel_Backward);
	moteur1.pwm_stop(moteur1.Timer_Forward,moteur1.Channel_Forward);
	moteur2.pwm_stop(moteur2.Timer_Backward,moteur2.Channel_Backward);
	moteur2.pwm_stop(moteur2.Timer_Forward,moteur2.Channel_Forward);
	/*
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
	__HAL_TIM_SetCompare(&htim16,TIM_CHANNEL_1,700);
	__HAL_TIM_SetCompare(&htim17,TIM_CHANNEL_1,0);
	HAL_Delay(2000);
	//	__HAL_TIM_SetCompare(&moteur1.Timer,moteur1.Channel_Backward,500);
	//	__HAL_TIM_SetCompare(&moteur1.Timer,moteur1.Channel_Forward,0);
	moteur1.alpha = 500;
	moteur1.update(moteur1);
	HAL_Delay(2000);
	//	__HAL_TIM_SetCompare(&moteur1.Timer,moteur1.Channel_Backward,0);
	//	__HAL_TIM_SetCompare(&moteur1.Timer,moteur1.Channel_Forward,0);
	moteur1.alpha = 0;
	moteur1.update(moteur1);
	HAL_Delay(2000);
	//	__HAL_TIM_SetCompare(&moteur1.Timer,moteur1.Channel_Backward,0);
	//	__HAL_TIM_SetCompare(&moteur1.Timer,moteur1.Channel_Forward,999);
	moteur1.alpha = 999;
	moteur1.sens = 2;
	moteur1.update(moteur1);
	HAL_Delay(2000);
	//pwm_stop_test();

	moteur1.pwm_stop(moteur1.Timer,moteur1.Channel_Backward);
	moteur1.pwm_stop(moteur1.Timer,moteur1.Channel_Forward);
	 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		ADC_Select_CH0();
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 1000);
		ADC_buffer[0] = HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop(&hadc1);

		HAL_Delay(10);

		ADC_Select_CH1();
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 1000);
		ADC_buffer[1] = HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop(&hadc1);
		counter ++;
		HAL_Delay(10);
		if (counter_val == 10){
			int temp=0;
			for (int i = 0 ; i<10;i++){
				temp += val[i];
			}
			moyenne_f = temp/10;
			courant = (moyenne_f - 2640)*10/25;
			counter_val=0;
		}
		val[counter_val]=ADC_buffer[0];
		counter_val++;


		/*if (counter == 500){
			moteur1.pwm_stop(moteur1.Timer,moteur1.Channel_Backward);
			moteur1.pwm_stop(moteur1.Timer,moteur1.Channel_Forward);

			HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);



		}
		if (counter == 1000){
			moteur1.pwm_start(moteur1.Timer,moteur1.Channel_Backward);
			moteur1.pwm_start(moteur1.Timer,moteur1.Channel_Forward);
			HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
			counter =0;
		}*/
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc){
	if(HAL_ADC_Stop_DMA(&hadc1)!= HAL_OK){
		Error_Handler();

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
