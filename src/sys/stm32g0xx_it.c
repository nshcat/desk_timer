/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g0xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32g0xx_it.h"

extern RTC_HandleTypeDef hrtc;
extern TIM_HandleTypeDef htim1;

void NMI_Handler(void)
{
   while (1)
  {
  }
}


void HardFault_Handler(void)
{
  while (1)
  {
  }
}


void SVC_Handler(void)
{

}


void PendSV_Handler(void)
{

}


void SysTick_Handler(void)
{
  HAL_IncTick();
}


void RTC_TAMP_IRQHandler(void)
{
  HAL_RTC_AlarmIRQHandler(&hrtc);
}


void EXTI0_1_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(JOY_RIGHT_Pin);
  HAL_GPIO_EXTI_IRQHandler(JOY_LEFT_Pin);
}


void EXTI2_3_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(JOY_DOWN_Pin);
  HAL_GPIO_EXTI_IRQHandler(JOY_UP_Pin);
}


void EXTI4_15_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(KEY_1_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_3_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_2_Pin);
  HAL_GPIO_EXTI_IRQHandler(JOY_PRESS_Pin);
}


void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim1);
}


void TIM1_CC_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim1);
}
