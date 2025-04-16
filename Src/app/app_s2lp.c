/**
  ******************************************************************************
  * @file           : app_s2lp.c
  * @brief          : Source file for S2LP application layer
  * @author         : Julien Cruvieux
  * @date           : 2025/04/13
  ******************************************************************************
  */

/* General interfaces --------------------------------------------------------*/
#include "lib/lib_errno.h"

/* Used interfaces (dependencies includes) -----------------------------------*/
#include "hal/hal_spi.h"

/* Associated interfaces -----------------------------------------------------*/
#include "S2LP_CORE_SPI.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define cAPP_S2LP_WRITE_HEADER        (uint8_t)0x00
#define cAPP_S2LP_READ_HEADER         (uint8_t)0x01
#define cAPP_S2LP_CMD_HEADER          (uint8_t)0x80
#define cAPP_S2LP_LINEAR_FIFO_ADDRESS (uint8_t)0xFF

#define cAPP_S2LP_FIFO_SIZE   (uint8_t)128
#define cAPP_S2LP_HEADER_SIZE (uint8_t)2
#define cAPP_S2LP_STATUS_SIZE (uint8_t)2

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint8_t g_au8BufferTx[cAPP_S2LP_HEADER_SIZE + cAPP_S2LP_FIFO_SIZE];
static uint8_t g_au8BufferRx[cAPP_S2LP_STATUS_SIZE + cAPP_S2LP_FIFO_SIZE];

/* Private function prototypes -----------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
uint16_t S2LPSpiWriteRegisters(uint8_t RegisterAddr, uint8_t NumByteToRead, uint8_t* pBuffer) {
  Error l_error = cLIB_ERRORNO_NoErr;
  uint16_t l_status = {0};

  g_au8BufferTx[0] = cAPP_S2LP_WRITE_HEADER;
  g_au8BufferTx[1] = RegisterAddr;

  for (uint8_t l_u8Index = 0; l_u8Index < NumByteToRead; l_u8Index++) {
    g_au8BufferTx[l_u8Index + cAPP_S2LP_HEADER_SIZE] = pBuffer[l_u8Index];
  }

  l_error = errHAL_SPI_transmitReceive(g_au8BufferTx, g_au8BufferRx, (uint16_t)(NumByteToRead + cAPP_S2LP_STATUS_SIZE));
  if (l_error == cLIB_ERRORNO_NoErr) {
    ((uint8_t*)&l_status)[1] = g_au8BufferRx[0];
    ((uint8_t*)&l_status)[0] = g_au8BufferRx[1];
  }
  else {
    //Nothing
  }

  return l_status;
}

uint16_t S2LPSpiReadRegisters(uint8_t RegisterAddr, uint8_t NumByteToRead, uint8_t* pBuffer) {
  Error l_error = cLIB_ERRORNO_NoErr;
  uint16_t l_status = {0};

  g_au8BufferTx[0] = cAPP_S2LP_READ_HEADER;
  g_au8BufferTx[1] = RegisterAddr;

  l_error = errHAL_SPI_transmitReceive(g_au8BufferTx, g_au8BufferRx, (uint16_t)(NumByteToRead + cAPP_S2LP_STATUS_SIZE));
  if (l_error == cLIB_ERRORNO_NoErr) {

    for (uint8_t l_u8Index = 0; l_u8Index < NumByteToRead; l_u8Index++) {
      pBuffer[l_u8Index] = g_au8BufferRx[l_u8Index + cAPP_S2LP_STATUS_SIZE];
    }

    ((uint8_t*)&l_status)[1] = g_au8BufferRx[0];
    ((uint8_t*)&l_status)[0] = g_au8BufferRx[1];
  }
  else {
    //Nothing
  }

  return l_status;
}

uint16_t S2LPSpiCommandStrobes(uint8_t command) {
  Error l_error = cLIB_ERRORNO_NoErr;
  uint16_t l_status = {0};

  g_au8BufferTx[0] = cAPP_S2LP_CMD_HEADER;
  g_au8BufferTx[1] = command;

  l_error = errHAL_SPI_transmitReceive(g_au8BufferTx, g_au8BufferRx, cAPP_S2LP_HEADER_SIZE);
  if (l_error == cLIB_ERRORNO_NoErr) {
    ((uint8_t*)&l_status)[1] = g_au8BufferRx[0];
    ((uint8_t*)&l_status)[0] = g_au8BufferRx[1];
  }
  else {
    //Nothing
  }

  return l_status;
}

uint16_t S2LPSpiWriteFifo(uint8_t n_bytes, uint8_t* buffer) {
  Error l_error = cLIB_ERRORNO_NoErr;
  uint16_t l_status = {0};

  g_au8BufferTx[0] = cAPP_S2LP_WRITE_HEADER;
  g_au8BufferTx[1] = cAPP_S2LP_LINEAR_FIFO_ADDRESS;

  for (uint8_t l_u8Index = 0; l_u8Index < n_bytes; l_u8Index++) {
    g_au8BufferTx[l_u8Index + cAPP_S2LP_HEADER_SIZE] = buffer[l_u8Index];
  }

  l_error = errHAL_SPI_transmitReceive(g_au8BufferTx, g_au8BufferRx, (uint16_t)(n_bytes + cAPP_S2LP_STATUS_SIZE));
  if (l_error == cLIB_ERRORNO_NoErr) {
    ((uint8_t*)&l_status)[1] = g_au8BufferRx[0];
    ((uint8_t*)&l_status)[0] = g_au8BufferRx[1];
  }
  else {
    //Nothing
  }

  return l_status;
}

uint16_t S2LPSpiReadFifo(uint8_t n_bytes, uint8_t* buffer) {
  Error l_error = cLIB_ERRORNO_NoErr;
  uint16_t l_status = {0};

  g_au8BufferTx[0] = cAPP_S2LP_READ_HEADER;
  g_au8BufferTx[1] = cAPP_S2LP_LINEAR_FIFO_ADDRESS;

  l_error = errHAL_SPI_transmitReceive(g_au8BufferTx, g_au8BufferRx, (uint16_t)(n_bytes + cAPP_S2LP_STATUS_SIZE));
  if (l_error == cLIB_ERRORNO_NoErr) {

    for (uint8_t l_u8Index = 0; l_u8Index < n_bytes; l_u8Index++) {
      buffer[l_u8Index] = g_au8BufferRx[l_u8Index + cAPP_S2LP_STATUS_SIZE];
    }

    ((uint8_t*)&l_status)[1] = g_au8BufferRx[0];
    ((uint8_t*)&l_status)[0] = g_au8BufferRx[1];
  }
  else {
    //Nothing
  }

  return l_status;
}

/* Private functions ---------------------------------------------------------*/

/* ISR and Event handlers ----------------------------------------------------*/
