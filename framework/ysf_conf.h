/**
 ******************************************************************************
  * @file       ysf_conf.h
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-2-18
  * @brief      ysf_conf head file
  * @par        work platform
  *                 Windows
  * @par        compiler platform
  *                 GCC
 ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_CONF_H__
#define __YSF_CONF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       EVENT PACKAGE
 *******************************************************************************
 */
#define _YSF_DEFINE_EVENT_START     enum                                       \
                                    {                                          \
                                        YSF_EVENT_NONE = 0,                    \
                                        YSF_CORE_TICK_UPDATE,                                          
                                        
#define _YSF_DEFINE_EVENT_END           YSF_EVENT_MAX,                         \
                                    };

/**
 *******************************************************************************
 * @brief       EVENT REGISTER FUNCTION
 *******************************************************************************
 */
#define RegistrarionEvent(event)    event,
                                    
/* YSF config ----------------------------------------------------------------*/
///**
// *******************************************************************************
// * @brief       YSF COMPONENT CONFIG
// * @note        1             enable
// * @note        0             disable
// *******************************************************************************
// */
//#define USE_YSF_BUFFER_COMPONENT            (1)
//#define USE_YSF_DEBUG_COMPONENT             (1)
//#define USE_YSF_EVENT_COMPONENT             (1)
//#define USE_YSF_SINGLE_LIST_COMPONENT       (1)
//#define USE_YSF_MEMORY_MANAGEMENT_COMPONENT (1)
//#define USE_YSF_SIGNAL_SCAN_COMPONENT       (1)
//#define USE_YSF_TICK_COMPONENT              (1)
//#define USE_YSF_TIMER_COMPONENT             (1)
//#define USE_YSF_HAL_COMPONENT               (1)
//                                    
///**
// *******************************************************************************
// * @brief       YSF COMPONENT CONFIG PARAM CHECK
// *******************************************************************************
// */ 
//#if !USE_YSF_BUFFER_COMPONENT
//    #if USE_YSF_EVENT_COMPONENT
//        #error "You open the event component, but you turn off buffer component configuration failed!" 
//    #elif USE_YSF_MEMORY_MANAGEMENT_COMPONENT
//        #error "You open the memory management component, but you turn off buffer component configuration failed!" 
//    #endif
//#endif       
//                                    
//#if !USE_YSF_SINGLE_LIST_COMPONENT
//    #if USE_YSF_EVENT_COMPONENT
//        #error "You open the event component, but you turn off buffer component configuration failed!" 
//    #elif USE_YSF_MEMORY_MANAGEMENT_COMPONENT
//        #error "You open the memory management component, but you turn off buffer component configuration failed!" 
//    #elif USE_YSF_SIGNAL_SCAN_COMPONENT
//        #error "You open the signal scan component, but you turn off buffer component configuration failed!" 
//    #elif USE_YSF_TIMER_COMPONENT
//        #error "You open the timer component, but you turn off buffer component configuration failed!" 
//    #endif
//#endif   
                                    
/**
 *******************************************************************************
 * @brief      EVENTS DEFINE
 *******************************************************************************
 */
_YSF_DEFINE_EVENT_START
    RegistrarionEvent(YSF_PT_TIMER_EVENT)
    RegistrarionEvent(LED1_BLINK_EVENT)
    RegistrarionEvent(LED2_BLINK_EVENT)
    RegistrarionEvent(KEY1_SCAN_EVENT)
    RegistrarionEvent(KEY2_SCAN_EVENT)
_YSF_DEFINE_EVENT_END	

/**
 *******************************************************************************
 * @brief       YSF VERSION CONFIG
 *******************************************************************************
 */
#define YSF_VERSION "YSF_DEBUG_0.0.1_201703021407"

/**
 *******************************************************************************
 * @brief       CHOOSE YOUR CHIP SERIES
 *******************************************************************************
 */
#define USE_MCU_STM32F1xx (1)
#define USE_MCU_STM8S     (2)

#define __TARGET_CHIP__   USE_MCU_STM32F1xx
        
/**
 *******************************************************************************
 * @brief      DEFINE CHIP NEED TO MACRO
 *******************************************************************************
 */
/* STM32F1xx config ----------------------------------------------------------*/
#if __TARGET_CHIP__ == USE_MCU_STM32F1xx
/**
 *******************************************************************************
 * @brief      DEFINE MCU CLOCK SPEED
 *******************************************************************************
 */
#define MCU_CLOCK_FREQ ((uint32_t)72000000) 
#define MCU_HSE_FREQ   ((uint32_t)8000000)  

/**
 *******************************************************************************
 * @brief      DEFINE MCU RAM SIZE
 *******************************************************************************
 */
#define MCU_SRAM_SIZE         64
#define MCU_SRAM_END_ADDR     ((uint32_t)((uint32_t)0x20000000 + MCU_SRAM_SIZE * 1024))

/**
 *******************************************************************************
 * @brief      DEFINE MCU CLOCK MODEL
 *******************************************************************************
 */
#define STM32F103xE
/* STM8S config --------------------------------------------------------------*/
#elif __TARGET_CHIP__ == USE_MCU_STM8S
    #define STM8S003
#else
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf config  */

/**********************************END OF FILE*********************************/
