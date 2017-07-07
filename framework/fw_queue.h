/**
 *******************************************************************************
 * @file       fw_queue.h                                                      *
 * @author     Mr.Sun                                                          *
 * @version    1.0.0                                                           *
 * @date       2017-06-13                                                      *
 * @brief      framework queue component                                        *
 * @par        work platform                                                   *
 *                 IAR                                                         *
 * @par        compiler                                                        *
 *                 STM8L052                                                    *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_QUEUE_H__
#define __FRAMEWORK_QUEUE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       Queue Interface
 *******************************************************************************
 */
extern fw_err_t Fw_Queue_Init(uint8_t, uint8_t*, uint8_t);
extern fw_err_t Fw_Queue_GetLen(uint8_t, uint8_t*);
extern fw_err_t Fw_Queue_PutByte(uint8_t, uint8_t);
extern fw_err_t Fw_Queue_PutData(uint8_t, uint8_t*, uint8_t);
extern fw_err_t Fw_Queue_PushByte(uint8_t, uint8_t*);
extern fw_err_t Fw_Queue_PushData(uint8_t, uint8_t*, uint8_t);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
