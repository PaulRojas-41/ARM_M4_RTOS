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
const char tx_buffer[] = {"Hello USART2 in RTOS..........!\n"};
const char tx_buffer_2[] = {"Background print!\n"};

/* USER CODE END Variables */
/* Definitions for led_blink */
osThreadId_t led_blinkHandle;
const osThreadAttr_t led_blink_attributes = {
  .name = "led_blink",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow6,
};
/* Definitions for usart2_print */
osThreadId_t usart2_printHandle;
const osThreadAttr_t usart2_print_attributes = {
  .name = "usart2_print",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow7,
};
/* Definitions for usart2_print2 */
osThreadId_t usart2_print2Handle;
const osThreadAttr_t usart2_print2_attributes = {
  .name = "usart2_print2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh7,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void led_blink_func(void *argument);
void usart2_print_func(void *argument);
void usart2_print2_func(void *argument);

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

  /* creation of usart2_print */
  usart2_printHandle = osThreadNew(usart2_print_func, NULL, &usart2_print_attributes);

  /* creation of usart2_print2 */
  usart2_print2Handle = osThreadNew(usart2_print2_func, NULL, &usart2_print2_attributes);

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

/* USER CODE BEGIN Header_usart2_print_func */
/**
* @brief Function implementing the usart2_print_t thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_usart2_print_func */
void usart2_print_func(void *argument)
{
  /* USER CODE BEGIN usart2_print_func */
  /* Infinite loop */
  for(;;)
  {
	for(int i =0; i < sizeof(tx_buffer); i++)
	{
		USART2->DR = tx_buffer[i];
		while(!(USART2->SR & (1 << 6)));
	}
    osDelay(10);
  }
  /* USER CODE END usart2_print_func */
}

/* USER CODE BEGIN Header_usart2_print2_func */
/**
* @brief Function implementing the usart2_print2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_usart2_print2_func */
void usart2_print2_func(void *argument)
{
  /* USER CODE BEGIN usart2_print2_func */
  /* Infinite loop */
  for(;;)
  {
	for(int j=0; j < sizeof(tx_buffer_2); j++)
	{
		USART2->DR = tx_buffer_2[j];
		while(!(USART2->SR & (1 << 6)));
	}
    osDelay(100);
  }
  /* USER CODE END usart2_print2_func */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

