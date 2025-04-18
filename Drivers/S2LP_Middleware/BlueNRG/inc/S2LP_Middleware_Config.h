/**
 * @file    S2LP_Middleware_Config.h
 * @author  AMS VMA RF application team
 * @version V2.0.0
 * @date    June, 2021
 * @brief   This file contains S2LP Middleware configuration and useful defines.
 * @details
 *
 * This file is used to include all or a part of the SDK Eval
 * libraries into the application program which will be used.
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * THIS SOURCE CODE IS PROTECTED BY A LICENSE.
 * FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
 * IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
 *
 * <h2><center>&copy; COPYRIGHT 2021 STMicroelectronics</center></h2>
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __S2LP_MIDLLEWARE_H
#define __S2LP_MIDLLEWARE_H

/* Includes ------------------------------------------------------------------*/

/* User defined custom platform */
/*************************** USER CUSTOM PALTFORM ****************************/
#ifdef USER_EVAL_PLATFORM
/* Adding the symbol USER_EVAL_PLATFORM an user platform can be supported
 * at compile time, by following these steps:
 *
 * 1) Create a file  "USER_Platform_Configuration.h" with specific user
 *    platform configuration.
 *
 * 2) Place the "USER_Platform_Configuration.h" on the
 *    \Drivers\S2LP_Middleware\BlueNRG\inc folder.
 */
  #include "USER_Platform_Configuration.h"
#else
  #ifdef IDB00xV2
  #include "S2LP_IDB00xV2_AUTO.h"
  #endif

  #ifdef FKI001V1
  #include "S2LP_FKI001V1.h"
  #endif

  #ifdef MON_REF_DES
  #include "S2LP_MON_REF_DES.h"
  #endif
#endif

/* Includes for Core Module*/
#include "S2LP_CORE_SPI.h"
#include "S2LP_CORE_GPIO.h"

/*Includes for Aux Module*/
#include "S2LP_AUX_EEPROM.h"
#include "S2LP_AUX_UTILS.h"
#include "S2LP_AUX_FEM.h"
#include "S2LP_AUX_TCXO.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup SDK_EVAL_BlueNRG1
 * @{
 */

/** @addtogroup SDK_EVAL_Config         SDK EVAL Config
 * @brief SDK EVAL configuration.
 * @details See the file <i>@ref SDK_EVAL_Config.h</i> for more details.
 * @{
 */

/** @addtogroup SDK_EVAL_Config_Exported_Types          SDK EVAL Config Exported Types
 * @{
 */

/**
 * @}
 */

/** @defgroup SDK_EVAL_Config_Exported_Constants        SDK EVAL Config Exported Constants
 * @{
 */

/**
 * @}
 */

/** @defgroup SDK_EVAL_Config_Exported_Macros           SDK EVAL Config Exported Macros
 * @{
 */

void SdkEvalIdentification(void);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*__S2LP_MIDLLEWARE_H */
/******************* (C) COPYRIGHT 2015 STMicroelectronics *****END OF FILE****/
