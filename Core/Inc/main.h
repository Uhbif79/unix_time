/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define SIZE_BF 32
#define year_vis 31622400
#define year_ob 31536000
#define year_sr 31556926
#define month_sr 2592000
#define day_sr 86400
#define hour_sr 3600
#define min_sr 60
#define DWT_CONTROL *(volatile unsigned long *)0xE0001000
#define SCB_DEMCR   *(volatile unsigned long *)0xE000EDFC

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RS_Pin GPIO_PIN_3
#define RS_GPIO_Port GPIOB
#define E_Pin GPIO_PIN_4
#define E_GPIO_Port GPIOB
#define B4_Pin GPIO_PIN_5
#define B4_GPIO_Port GPIOB
#define B5_Pin GPIO_PIN_6
#define B5_GPIO_Port GPIOB
#define B6_Pin GPIO_PIN_8
#define B6_GPIO_Port GPIOB
#define B7_Pin GPIO_PIN_9
#define B7_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define    DWT_CYCCNT    *(volatile uint32_t*)0xE0001004
#define DWT_CONTROL *(volatile unsigned long *)0xE0001000
#define SCB_DEMCR   *(volatile unsigned long *)0xE000EDFC
#define  RS0 HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
#define  RS1 HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
#define  E0 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
#define  E1 HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
#define SIZE_BF 32
//#define MYUART huart1 // задефайнить USART
#define UART_RX_BUFFER_SIZE 128 // указать размер приёмного буфера

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
