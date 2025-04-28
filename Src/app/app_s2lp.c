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
#include "stm32h7xx_hal.h"
#include "hal/hal_spi.h"
#include "hal/hal_itm.h"

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
static SRadioInit g_sRadioInit = {0};
static PktBasicInit g_sBasicPacketInit = {0};
static SGpioInit g_sGPIOInit = {0};

static FlagStatus g_eEventFlag = RESET;
static S2LPIrqs g_sIrqStatus = {0};

static uint8_t g_au8BufferTx[cAPP_S2LP_HEADER_SIZE + cAPP_S2LP_FIFO_SIZE];
static uint8_t g_au8BufferRx[cAPP_S2LP_STATUS_SIZE + cAPP_S2LP_FIFO_SIZE];

/* Private function prototypes -----------------------------------------------*/
void vAPP_S2LP_onRxDataReady(void);

/* Public functions ----------------------------------------------------------*/
void vAPP_S2LP_init(void) {
  g_sRadioInit.lFrequencyBase = cAPP_S2LP_BASE_FREQUENCY_Hz;
  g_sRadioInit.xModulationSelect = cAPP_S2LP_MODULATION_SCHEME;
  g_sRadioInit.lDatarate = cAPP_S2LP_DATARATE_bps;
  g_sRadioInit.lFreqDev = cAPP_S2LP_FREQ_DEVIATION_Hz;
  g_sRadioInit.lBandwidth = cAPP_S2LP_BANDWIDTH_Hz;

  g_sBasicPacketInit.xPreambleLength = cAPP_S2LP_PREAMBLE_LENGTH;
  g_sBasicPacketInit.xSyncLength = cAPP_S2LP_SYNC_LENGTH;
  g_sBasicPacketInit.lSyncWords = cAPP_S2LP_SYNC_WORD;
  g_sBasicPacketInit.xFixVarLength = cAPP_S2LP_VARIABLE_LENGTH;
  g_sBasicPacketInit.cExtendedPktLenField = cAPP_S2LP_EXTENDED_LENGTH_FIELD;
  g_sBasicPacketInit.xCrcMode = cAPP_S2LP_CRC_MODE;
  g_sBasicPacketInit.xAddressField = cAPP_S2LP_EN_ADDRESS;
  g_sBasicPacketInit.xFec = cAPP_S2LP_EN_FEC;
  g_sBasicPacketInit.xDataWhitening = cAPP_S2LP_EN_WHITENING;

  g_sGPIOInit.xS2LPGpioPin = S2LP_GPIO_3;
  g_sGPIOInit.xS2LPGpioMode = S2LP_GPIO_MODE_DIGITAL_OUTPUT_LP;
  g_sGPIOInit.xS2LPGpioIO = S2LP_GPIO_DIG_OUT_IRQ;

  S2LPRadioInit(&g_sRadioInit);
  S2LPRadioSetMaxPALevel(S_DISABLE);
  S2LPRadioSetPALeveldBm(7, cAPP_S2LP_POWER_dBm);
  S2LPRadioSetPALevelMaxIndex(7);
  
  S2LPPktBasicInit(&g_sBasicPacketInit);

  S2LPGpioInit(&g_sGPIOInit);
  S2LPGpioIrqDeInit(NULL);
  S2LPGpioIrqConfig(TX_DATA_SENT , S_ENABLE);
  S2LPGpioIrqConfig(RX_DATA_READY, S_ENABLE);
  S2LPPktBasicSetPayloadLength(20);
  S2LPGpioIrqClearStatus();
}

void vAPP_S2LP_processEvents(void) {
  FlagStatus l_eEventFlag = RESET;

  NVIC_DisableIRQ(EXTI15_10_IRQn);
  l_eEventFlag = g_eEventFlag;
  NVIC_EnableIRQ(EXTI15_10_IRQn);

  if (l_eEventFlag == SET) {
    S2LPGpioIrqGetStatus(&g_sIrqStatus);

    if (g_sIrqStatus.IRQ_RX_DATA_READY) {
      vHAL_ITM_logInfo("RX data ready!\n");
      vAPP_S2LP_onRxDataReady();
    }

    NVIC_DisableIRQ(EXTI1_IRQn);
    g_eEventFlag = RESET;
    NVIC_EnableIRQ(EXTI1_IRQn);
  }
  else {
    //Nothing
  }
}

uint16_t S2LPSpiWriteRegisters(uint8_t RegisterAddr, uint8_t NumByteToRead, uint8_t* pBuffer) {
  Error l_error = cLIB_ERRORNO_NoErr;
  uint16_t l_status = 0;

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
  uint16_t l_status = 0;

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
  uint16_t l_status = 0;

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
  uint16_t l_status = 0;

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
  uint16_t l_status = 0;

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
void vAPP_S2LP_onRxDataReady(void) {
  //TODO
}

/* ISR and Event handlers ----------------------------------------------------*/
void EXTI15_10_IRQHandler(void) {
  if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10) != 0x00U) {
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);

    NVIC_DisableIRQ(EXTI15_10_IRQn);
    g_eEventFlag = SET;
    NVIC_EnableIRQ(EXTI15_10_IRQn);
  }
  else {
    //Nothing
  }
}
