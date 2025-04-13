/**
  ******************************************************************************
  * @file           : lib_errno.h
  * @brief          : Defines all error codes for app layer
  * @author         : Julien Cruvieux
  * @date           : 2024/11/16
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIB_ERRNO_H
#define __LIB_ERRNO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef uint8_t Error;

typedef struct
{
  Error u8_errorCode;
  char* s_errorMessage;
} sError_t;


/* Exported constants --------------------------------------------------------*/
/* Global errors */
#define cLIB_ERRORNO_NoErr                (Error)0
#define cLIB_ERRORNO_Error                (Error)1

/* Functions errors */
#define cLIB_ERRORNO_FctNotImplemented    (Error)10
#define cLIB_ERRORNO_FctArgInvalid        (Error)11
#define cLIB_ERRORNO_FctArgOutOfRange     (Error)12
#define cLIB_ERRORNO_FctArgWrongNumber    (Error)13
#define cLIB_ERRORNO_FctExecutionFailed   (Error)14

/* Operations errors */
#define cLIB_ERRORNO_PointerNull          (Error)20
#define cLIB_ERRORNO_DivisionBy0          (Error)21
#define cLIB_ERRORNO_BadCheckNumber       (Error)22
#define cLIB_ERRORNO_IO                   (Error)23
#define cLIB_ERRORNO_Timeout              (Error)24
#define cLIB_ERRORNO_Exception            (Error)25
#define cLIB_ERRORNO_NoDataAvailable      (Error)26
#define cLIB_ERRORNO_NoNewData            (Error)27
#define cLIB_ERRORNO_OutOfMemory          (Error)28
#define cLIB_ERRORNO_MemoryNotAvailable   (Error)29
#define cLIB_ERRORNO_QueueIsFull          (Error)30
#define cLIB_ERRORNO_VersionNotSupported  (Error)31
#define cLIB_ERRORNO_DataOutOfRange       (Error)32
#define cLIB_ERRORNO_DataInvalid          (Error)33
#define cLIB_ERRORNO_DataInconsistent     (Error)34
#define cLIB_ERRORNO_CantInit             (Error)35

/* Communication errors */
#define cLIB_ERRORNO_TransmitFailed       (Error)40
#define cLIB_ERRORNO_ReceiveFailed        (Error)41
#define cLIB_ERRORNO_ComTimeout           (Error)42

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __LIB_ERRNO_H */
