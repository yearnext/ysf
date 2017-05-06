/**
 *******************************************************************************
 * @file       fw_timer.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2016-07-09
 * @brief      framework timer component head files
 * @par        paltform
 *                  Windows
 * @par        compiler
 *                  GCC
 *******************************************************************************
 * @note
 * 1.XXXXX
 *******************************************************************************
 */

/**
 * @defgroup framework timer component
 * @{
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_TIMER_H__
#define __FRAMEWORK_TIMER_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"
#include "fw_tick.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       timer compoent config flag
 *******************************************************************************
 */
#define USE_FRAMEWORK_TIMER_COMPONENT                                        (1)

/**
 *******************************************************************************
 * @brief       cal timer set time
 *******************************************************************************
 */
#define FW_TIME_SET(time)                                ((time)/FW_TICK_PREIOD)

/**
 *******************************************************************************
 * @brief       use timer num config
 *******************************************************************************
 */
#define USE_FRAMEWORK_TIMER_NUM                                              (3)

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_TIMER_COMPONENT
extern void     fw_timer_init(void);
extern fw_err_t fw_timer_arm(uint8_t, uint16_t);
extern void     fw_timer_handler(uint8_t);
#endif

/* Define to prevent recursive inclusion -------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /* end include define */

/** @}*/    /** framework event component */

/**********************************END OF FILE*********************************/
