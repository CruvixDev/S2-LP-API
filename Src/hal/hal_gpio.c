/**
  ******************************************************************************
  * @file           : hal_gpio.c
  * @brief          : This file provides code for GPIO configuration
  * @author         : <author name>
  * @date           : <yyyy/MM/dd>
  ******************************************************************************
  */

/* General interfaces --------------------------------------------------------*/

/* Used interfaces (dependencies includes) -----------------------------------*/
#include "stm32h7xx_hal.h"

/* Associated interfaces -----------------------------------------------------*/
#include "hal/hal_gpio.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void vHAL_GPIO_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void vHAL_GPIO_toggleGreenLED(void) {
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
}

void vHAL_GPIO_toggleRedLED(void) {
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
}

/* Private functions ---------------------------------------------------------*/
