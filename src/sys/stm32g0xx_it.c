#include "stm32g0xx_it.h"
#include "stm32g0xx_hal.h"

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

/******************************************************************************/
/* STM32G0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g0xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
