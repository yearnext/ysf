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
    CALL_START_EVENT,
    UART_RX_END_EVENT,
    
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
    
    /** user define event */
    USER_CALL_TASK,
    USER_UART_RX_TASK,
    USER_KEY_TASK,
    
    /** framework task */
    FW_TASK_MAX,
 };

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_EVENT_COMPONENT
extern void InitEventComponent(void);
extern fw_err_t RegisterEvent(uint8_t, void (*)(uint8_t));
extern inline void PostEvent(uint8_t, uint8_t);
extern inline void PollEvent(void);
#endif

/* Define to prevent recursive inclusion -------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework event component */

/**********************************END OF FILE*********************************/
