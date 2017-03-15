/**
 *******************************************************************************
 * @file       ysf_event.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework event component head files
 * @par        paltform                                  
 *                 Windows
 * @par        compiler									                         
 * 				GCC
 *******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 *******************************************************************************
 */

/**
 * @defgroup framework event component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_EVENT_H__
#define __FRAMEWORK_EVENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       API config
 *******************************************************************************
 */
#define USE_FRAMEWORK_EVENT_COMPONENT                                        (1)
     
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define event class
 * @note        event value can not be greater than FW_EVENT_MAX(127)
 *******************************************************************************
 */
enum _FRAMEWORK_EVENT
{
    /** framework event */
    FW_EVENT_NONE = 0,
    FW_TICK_EVENT,
    FW_SIGNAL_EVENT,
	FW_DELAY_EVENT,
	
    /** user define event */
    // UART_RX_END_EVENT,
    // CALL_EVENT,
    // CALL_START_EVENT,
    // TELEPHONE_CLOSE,
    
    /** framework event */
    FW_EVENT_MAX,
};

/**
 *******************************************************************************
 * @brief       define task class
 *******************************************************************************
 */
enum _FRAMEWORK_TASK
{
    /** framework task */
    FW_TICK_TASK = 0,
 	FW_SIGNAL_TASK,
     
    /** framework task */
    FW_TASK_MAX,
 };

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_EVENT_COMPONENT
extern void fw_event_init(void);
extern inline void fw_event_post(uint8_t, uint8_t);
extern inline void fw_event_poll(void);
#endif

/* Define to prevent recursive inclusion -------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework event component */

/**********************************END OF FILE*********************************/
