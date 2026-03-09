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

#include <stdlib.h>

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Definitions for defaultTask */

osThreadId_t defaultTaskHandle;
osThreadId_t helloTaskHandle;
osThreadId_t ToggleBledHandle;
osThreadId_t ToggleOledHandle;

const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t HelloTask_att = {
	.name = "HelloTask",
	.stack_size = 128 * 4,
	.priority = (osPriority_t)osPriorityNormal,
};

const osThreadAttr_t Toggle_Bled_att = {
	.name = "Toggle_Bled",
	.stack_size = 128 * 4,
	.priority = (osPriority_t)osPriorityNormal,
};

const osThreadAttr_t Toggle_Oled_att = {
	.name = "Toggle_Oled",
	.stack_size = 128 * 4,
	.priority = (osPriority_t)osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void HelloTask();
void Toggle_Bled_task();
void Toggle_Oled_task();
volatile uint8_t hellotask_counter;

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
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
  helloTaskHandle   = osThreadNew(HelloTask, NULL, &HelloTask_att);
  ToggleBledHandle  = osThreadNew(Toggle_Bled_task, NULL, &Toggle_Bled_att);
  ToggleOledHandle  = osThreadNew(Toggle_Oled_task, NULL, &Toggle_Oled_att);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN HelloTask */
/**
  * @brief  Function implementing the HelloTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END HelloTask */

void HelloTask()
{
  /* USER CODE BEGIN HelloTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1000);
    hellotask_counter++;
  }
  /* USER CODE END HelloTask */
}

void Toggle_Bled_task()
{
	/* USER CODE BEGIN Toggle_Bled */
	/* Infinite loop */
	for(;;)
	{
	  osDelay(1000);
	  GPIOD->ODR ^= (1 << 15);
	}
	/* USER CODE END Toggle_Bled */
}

void Toggle_Oled_task()
{
	/* USER CODE BEGIN Toggle_Oled */
	/* Infinite loop */
	for(;;)
	{
	  osDelay(2000);
	  GPIOD->ODR ^= (1 << 13);
	}
	/* USER CODE END Toggle_Bled */
}

/* USER CODE END HelloTask */


/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

