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
#include "app/app_s2lp.h"

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
StatusBytes sAPP_S2LP_writeRegisters(uint8_t p_u8RegAddress, uint8_t p_u8Size, uint8_t* p_pu8DataTx) {
  Error l_error = cLIB_ERRORNO_NoErr;
  StatusBytes l_status = {0};

  g_au8BufferTx[0] = cAPP_S2LP_WRITE_HEADER;
  g_au8BufferTx[1] = p_u8RegAddress;

  for (uint8_t l_u8Index = 0; l_u8Index < p_u8Size; l_u8Index++) {
    g_au8BufferTx[l_u8Index + cAPP_S2LP_HEADER_SIZE] = p_pu8DataTx[l_u8Index];
  }

  l_error = errHAL_SPI_transmitReceive(g_au8BufferTx, g_au8BufferRx, (uint16_t)(p_u8Size + cAPP_S2LP_STATUS_SIZE));
  if (l_error == cLIB_ERRORNO_NoErr) {
    ((uint8_t*)&l_status)[1]=g_au8BufferRx[0];
    ((uint8_t*)&l_status)[0]=g_au8BufferRx[1];
  }
  else {
    //Nothing
  }

  return l_status;
}

StatusBytes sAPP_S2LP_readRegisters(uint8_t p_u8RegAddress, uint8_t p_u8Size, uint8_t* p_pu8DataRx) {
  Error l_error = cLIB_ERRORNO_NoErr;
  StatusBytes l_status = {0};

  g_au8BufferTx[0] = cAPP_S2LP_READ_HEADER;
  g_au8BufferTx[1] = p_u8RegAddress;

  l_error = errHAL_SPI_transmitReceive(g_au8BufferTx, g_au8BufferRx, (uint16_t)(p_u8Size + cAPP_S2LP_STATUS_SIZE));
  if (l_error == cLIB_ERRORNO_NoErr) {

    for (uint8_t l_u8Index = 0; l_u8Index < p_u8Size; l_u8Index++) {
      p_pu8DataRx[l_u8Index] = g_au8BufferRx[l_u8Index + cAPP_S2LP_STATUS_SIZE];
    }

    ((uint8_t*)&l_status)[1]=g_au8BufferRx[0];
    ((uint8_t*)&l_status)[0]=g_au8BufferRx[1];
  }
  else {
    //Nothing
  }

  return l_status;
}

StatusBytes sAPP_S2LP_commandStrobes(uint8_t p_u8CommandCode) {
  Error l_error = cLIB_ERRORNO_NoErr;
  StatusBytes l_status = {0};

  g_au8BufferTx[0] = cAPP_S2LP_CMD_HEADER;
  g_au8BufferTx[1] = p_u8CommandCode;

  l_error = errHAL_SPI_transmitReceive(g_au8BufferTx, g_au8BufferRx, cAPP_S2LP_HEADER_SIZE);
  if (l_error == cLIB_ERRORNO_NoErr) {
    ((uint8_t*)&l_status)[1]=g_au8BufferRx[0];
    ((uint8_t*)&l_status)[0]=g_au8BufferRx[1];
  }
  else {
    //Nothing
  }

  return l_status;
}

StatusBytes sAPP_S2LP_writeFifo(uint8_t p_u8Size, uint8_t* p_pu8FIFOBuffer) {
  Error l_error = cLIB_ERRORNO_NoErr;
  StatusBytes l_status = {0};

  g_au8BufferTx[0] = cAPP_S2LP_WRITE_HEADER;
  g_au8BufferTx[1] = cAPP_S2LP_LINEAR_FIFO_ADDRESS;

  for (uint8_t l_u8Index = 0; l_u8Index < p_u8Size; l_u8Index++) {
    g_au8BufferTx[l_u8Index + cAPP_S2LP_HEADER_SIZE] = p_pu8FIFOBuffer[l_u8Index];
  }

  l_error = errHAL_SPI_transmitReceive(g_au8BufferTx, g_au8BufferRx, (uint16_t)(p_u8Size + cAPP_S2LP_STATUS_SIZE));
  if (l_error == cLIB_ERRORNO_NoErr) {
    ((uint8_t*)&l_status)[1]=g_au8BufferRx[0];
    ((uint8_t*)&l_status)[0]=g_au8BufferRx[1];
  }
  else {
    //Nothing
  }

  return l_status;
}

StatusBytes sAPP_S2LP_readFifo(uint8_t p_u8Size, uint8_t* p_pu8FIFOBuffer) {
  Error l_error = cLIB_ERRORNO_NoErr;
  StatusBytes l_status = {0};

  g_au8BufferTx[0] = cAPP_S2LP_READ_HEADER;
  g_au8BufferTx[1] = cAPP_S2LP_LINEAR_FIFO_ADDRESS;

  l_error = errHAL_SPI_transmitReceive(g_au8BufferTx, g_au8BufferRx, (uint16_t)(p_u8Size + cAPP_S2LP_STATUS_SIZE));
  if (l_error == cLIB_ERRORNO_NoErr) {

    for (uint8_t l_u8Index = 0; l_u8Index < p_u8Size; l_u8Index++) {
      p_pu8FIFOBuffer[l_u8Index] = g_au8BufferRx[l_u8Index + cAPP_S2LP_STATUS_SIZE];
    }

    ((uint8_t*)&l_status)[1]=g_au8BufferRx[0];
    ((uint8_t*)&l_status)[0]=g_au8BufferRx[1];
  }
  else {
    //Nothing
  }

  return l_status;
}

/* Private functions ---------------------------------------------------------*/

/* ISR and Event handlers ----------------------------------------------------*/
