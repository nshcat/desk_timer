#pragma once

#include "stm32g0xx_hal.h"

#define OLED_CS_Pin GPIO_PIN_3
#define OLED_CS_GPIO_Port GPIOA
#define OLED_DC_Pin GPIO_PIN_4
#define OLED_DC_GPIO_Port GPIOA
#define OLED_Res_Pin GPIO_PIN_5
#define OLED_Res_GPIO_Port GPIOA

void Error_Handler(void);

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_SPI1_Init(void);
