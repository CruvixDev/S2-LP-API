/**
  ******************************************************************************
  * @file           : app_s2lp.h
  * @brief          : Header file for S2LP application layer
  * @author         : Julien Cruvieux
  * @date           : 2025/04/13
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _APP_S2LP_H
#define _APP_S2LP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "S2LP_Config.h"
#include "S2LP_CORE_SPI.h"

/* Private includes ----------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define cAPP_S2LP_WRITE_HEADER        (uint8_t)0x00
#define cAPP_S2LP_READ_HEADER         (uint8_t)0x01
#define cAPP_S2LP_CMD_HEADER          (uint8_t)0x80
#define cAPP_S2LP_LINEAR_FIFO_ADDRESS (uint8_t)0xFF

#define cAPP_S2LP_FIFO_SIZE   (uint8_t)128
#define cAPP_S2LP_HEADER_SIZE (uint8_t)2
#define cAPP_S2LP_STATUS_SIZE (uint8_t)2

/* Exported types ------------------------------------------------------------*/
typedef S2LPStatus StatusBytes;

/* Exported macro ------------------------------------------------------------*/
#define S2LPSpiWriteRegisters(cRegAddress, cNbBytes, pcBuffer) sAPP_S2LP_writeRegisters(cRegAddress, cNbBytes, pcBuffer)
#define S2LPSpiReadRegisters(cRegAddress, cNbBytes, pcBuffer)  sAPP_S2LP_readRegisters(cRegAddress, cNbBytes, pcBuffer)
#define S2LPSpiCommandStrobes(cCommandCode)                    sAPP_S2LP_commandStrobes(cCommandCode)
#define S2LPSpiWriteFifo(cNbBytes, pcBuffer)                   sAPP_S2LP_writeFifo(cNbBytes, pcBuffer)
#define S2LPSpiReadFifo(cNbBytes, pcBuffer)                    sAPP_S2LP_readFifo(cNbBytes, pcBuffer)

/* Exported functions prototypes ---------------------------------------------*/
StatusBytes sAPP_S2LP_writeRegisters(uint8_t p_u8RegAddress, uint8_t p_u8Size, uint8_t* p_pu8DataTx);
StatusBytes sAPP_S2LP_readRegisters(uint8_t p_u8RegAddress, uint8_t p_u8Size, uint8_t* p_pu8DataRx);
StatusBytes sAPP_S2LP_commandStrobes(uint8_t p_u8CommandCode);
StatusBytes sAPP_S2LP_writeFifo(uint8_t p_u8Size, uint8_t* p_pu8FIFOBuffer);
StatusBytes sAPP_S2LP_readFifo(uint8_t p_u8Size, uint8_t* p_pu8FIFOBuffer);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* _APP_S2LP_H */
