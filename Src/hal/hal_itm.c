/**
  ******************************************************************************
  * @file           : hal_itm.c
  * @brief          : Redirects printf function from stdio.h to ITM
  * @author         : Julien Cruvieux
  * @date           : 2025/01/03
  ******************************************************************************
  */

/* General interfaces --------------------------------------------------------*/

/* Used interfaces (dependencies includes) -----------------------------------*/
#include "stm32h7xx_hal.h"
#include <stdarg.h>
#include <stdio.h>

/* Associated interfaces -----------------------------------------------------*/
#include "hal/hal_itm.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

void vHAL_ITM_logInfo(const char* format, ...) {
  va_list args;
  va_start(args, format);
  printf("#GRN#[INFO] ");
  vprintf(format, args);
  printf("\n");
  va_end(args);
}

void vHAL_ITM_logWarning(const char* format, ...) {
  va_list args;
  va_start(args, format);
  printf("#ORG#[WARNING] ");
  vprintf(format, args);
  printf("\n");
  va_end(args);
}

void vHAL_ITM_logError(const char* format, ...) {
  va_list args;
  va_start(args, format);
  printf("#RED#[ERROR] ");
  vprintf(format, args);
  printf("\n");
  va_end(args);
}

int _write(int file, char *ptr, int len) {
  file = file; //Avoid warning on not used parameter

  for (int i = 0; i < len; i++) {
    ITM_SendChar((*ptr++));
  }

  return len;
}

/* Private functions ---------------------------------------------------------*/

/* ISR and Event handlers ----------------------------------------------------*/
