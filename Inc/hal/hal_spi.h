/**
  ******************************************************************************
  * @file           : hal_spi.h
  * @brief          : HAL header file for SPI peripheral
  * @author         : Julien Cruvieux
  * @date           : 2025/04/05
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_SPI_H
#define __HAL_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lib/lib_errno.h"
#include <stdint.h>

/* Private includes ----------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
Error errHAL_SPI_init(void);
Error errHAL_SPI_transmitReceive(const uint8_t* p_pu8DataTx, uint8_t* p_pu8DataRx, uint16_t p_u16Size);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __HAL_SPI_H */
