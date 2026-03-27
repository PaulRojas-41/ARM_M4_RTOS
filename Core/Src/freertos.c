/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include <string.h>

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
#define RXBUFFERSIZE 10
/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* Exported functions ------------------------------------------------------- */
/* Size of Transmission buffer */
#define TXBUFFERSIZE                      (COUNTOF(aTxBuffer) - 1)
/* Size of Reception buffer */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t rx_buffer[4];

/* USER CODE END Variables */
/* Definitions for led_blink */
osThreadId_t led_blinkHandle;
const osThreadAttr_t led_blink_attributes = {
  .name = "led_blink",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal7,
};
/* Definitions for usart2_tx */
osThreadId_t usart2_txHandle;
const osThreadAttr_t usart2_tx_attributes = {
  .name = "usart2_tx",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh2,
};
/* Definitions for usart2_rx */
osThreadId_t usart2_rxHandle;
const osThreadAttr_t usart2_rx_attributes = {
  .name = "usart2_rx",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime1,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void led_blink_func(void *argument);
void usart2_tx_func(void *argument);
void usart2_rx_func(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of led_blink */
  led_blinkHandle = osThreadNew(led_blink_func, NULL, &led_blink_attributes);

  /* creation of usart2_tx */
  usart2_txHandle = osThreadNew(usart2_tx_func, NULL, &usart2_tx_attributes);

  /* creation of usart2_rx */
  usart2_rxHandle = osThreadNew(usart2_rx_func, NULL, &usart2_rx_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_led_blink_func */
/**
  * @brief  Function implementing the led_blink_t thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_led_blink_func */
void led_blink_func(void *argument)
{
  /* USER CODE BEGIN led_blink_func */
  /* Infinite loop */
  for(;;)
  {
	GPIOD->ODR ^= (1 << 15);
    osDelay(1000);
  }
  /* USER CODE END led_blink_func */
}

/* USER CODE BEGIN Header_usart2_tx_func */
/**
* @brief Function implementing the usart2_tx thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_usart2_tx_func */
void usart2_tx_func(void *argument)
{
  /* USER CODE BEGIN usart2_tx_func */
  /* Infinite loop */
  for(;;)
  {
	  for(uint8_t j = 0; j < sizeof(rx_buffer); j++)
	 {
	  	 /* If TXE flag is set, write data byte to DR */
	  	 while(!(USART2->SR & (1 << 6)));
	  	 USART2->DR = (rx_buffer[j] & 0xFF);
	 }
	 osDelay(10);
  }
  /* USER CODE END usart2_tx_func */
}

/* USER CODE BEGIN Header_usart2_rx_func */
/**
* @brief Function implementing the usart2_rx thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_usart2_rx_func */
void usart2_rx_func(void *argument)
{

  /* USER CODE BEGIN usart2_rx_func */
  /* Infinite loop */
  for(;;)
  {
	  for(uint8_t i= 0; i < sizeof(rx_buffer); i++)
	  {
	  	/* When a character is received, wait until RXNE flag is set, then read data */
	  	while(!(USART2->SR & (1 << 5)));
	  	rx_buffer[i] = USART2->DR; /* 0xFF & DATA_RX */
	  }

	  osDelay(10);
  }
  /* USER CODE END usart2_rx_func */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

