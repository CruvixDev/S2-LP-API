/**
  ******************************************************************************
  * @file           : app_main.c
  * @brief          : main program
  * @author         : Julien Cruvieux
  * @date           : 2024/09/22
  ******************************************************************************
  */

/* General interfaces --------------------------------------------------------*/

/* Associated interfaces -----------------------------------------------------*/
#include "app/app_main.h"
#include "S2LP_General.h"

/* Used interfaces (dependencies includes) -----------------------------------*/
#include "hal/hal_clock.h"
#include "hal/hal_spi.h"
#include "hal/hal_gpio.h"
#include "hal/hal_itm.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * 
  * @return int
  */
int main(void) {
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  vHAL_Clock_init();

  /* Initialize all configured peripherals */
  vHAL_GPIO_init();
  errHAL_SPI_init();

  uint8_t l_u8DevicePN = S2LPGeneralGetDevicePN();
  vHAL_ITM_logInfo("Device Part Number: %d\n", l_u8DevicePN);

  /* Main infinite loop */
  while (true) {

  }

  return 0;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * 
  * @return None
  */
void Error_Handler(void)
{
  __disable_irq();

  while (1) {
    vHAL_GPIO_toggleRedLED();
    vHAL_Clock_delay(1000);  
  }
}

/* Private functions ---------------------------------------------------------*/
