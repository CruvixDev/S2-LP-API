/**
  ******************************************************************************
  * @file           : hal_itm.h
  * @brief          : Redirects printf function from stdio.h to ITM
  * @author         : Julien Cruvieux
  * @date           : 2025/01/03
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _HAL_ITM_H_
#define _HAL_ITM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void vHAL_ITM_logInfo(const char* format, ...);
void vHAL_ITM_logWarning(const char* format, ...);
void vHAL_ITM_logError(const char* format, ...);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* _HAL_ITM_H_ */
