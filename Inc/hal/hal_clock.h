/**
  ******************************************************************************
  * @file           : hal_clock.h
  * @brief          : Header file for STM32 clock configuration and 
  * initialisation
  * @author         : Julien Cruvieux
  * @date           : 2025/04/05
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _HAL_CLOCK_
#define _HAL_CLOCK_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Public includes -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void vHAL_Clock_init(void);
void vHAL_Clock_delay(uint32_t pu32Delay);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* _HAL_CLOCK_ */
