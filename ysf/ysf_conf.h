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

/* Exported macro ------------------------------------------------------------*/  
#define USE_YSF_API (1)   
#define YSF_VERSION "YSF_DEBUG_0.0.1_201703021407"

/* Includes ------------------------------------------------------------------*/    
#include "ysf_event_conf.h"
#include "ysf_path.h"
#include YSF_TYPE_DIR    
  
#if USE_YSF_API
#include YSF_COMPONENT_TICK_DIR
#include YSF_COMPONENT_MEMORY_DIR
#include YSF_COMPONENT_EVENT_DIR
#include YSF_COMPONENT_TIMER_DIR
#include YSF_COMPONENT_SIGNAL_DIR
#include YSF_COMPONENT_DEBUG_DIR
#include YSF_HAL_DIR
#endif

/* Exported types ------------------------------------------------------------*/
#if USE_YSF_API    
struct YSF_API
{
    void (*init)(ysf_err_t (*user_init)(void));
    void (*start)(void);
    char *ver;
    
#if USE_YSF_TICK_API
    struct YSF_TICK_API tick;
#endif
        
#if USE_YSF_MEMORY_API
    struct YSF_MEMORY_API memory;
#endif
    
#if USE_YSF_EVENT_API
    struct YSF_EVENT_API event;
#endif
    
#if USE_YSF_TIMER_API
    struct YSF_TIMER_API timer;
#endif

#if USE_YSF_SIGNAL_API
    struct YSF_SIGNAL_API signal;
#endif

#if USE_YSF_DEBUG_API
    struct YSF_DEBUG_API debug;
#endif
};
#endif    

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf config  */

/**********************************END OF FILE*********************************/
