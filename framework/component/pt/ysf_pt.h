/**
 ******************************************************************************
 * @file       ysf_pt.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017Äê2ÔÂ21ÈÕ
 * @brief      ysf pt head file
 * @par        work paltform		                             
 *                 Windows
 * @par        compiler paltform									                         
 * 				   GCC
 ******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf pt component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_PT_H__
#define __YSF_PT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_conf.h"
#include "ysf_path.h"
#include YSF_TYPE_PATH
#include YSF_COMPONENT_TIMER_PATH
#include YSF_COMPONENT_MEMORY_PATH
#include YSF_COMPONENT_EVENT_PATH
    
/* Exported macro ------------------------------------------------------------*/
#define YSF_PT_THREAD(func_name) ysf_err_t func_name(uint16_t evt)
                              
#define ysf_pt_init(func)        static struct ysf_pt_t pt =                                                 \
                                 {                                                                           \
                                     .state  = 0,                                                            \
                                     .thread = func,                                                         \
                                 }                                                                           
                              
#define ysf_pt_begin()           switch(pt.state){case 0:
    
#define ysf_pt_entry()           pt.state = (uint16_t)__LINE__; case __LINE__:
    
#define ysf_pt_wait(state)       do                                                                          \
                                 {                                                                           \
                                     ysf_pt_entry();                                                         \
                                     if( !(state) )                                                          \
                                     {                                                                       \
                                        return YSF_ERR_NOT_READY;                                            \
                                     }                                                                       \
                                 }while(0)
                              
#define ysf_pt_wfe(state)        do                                                                          \
                                 {                                                                           \
                                     ysf_pt_entry();                                                         \
                                     if( (state) )                                                           \
                                     {                                                                       \
                                        return YSF_ERR_NOT_READY;                                            \
                                     }                                                                       \
                                 }while(0)
                                 
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
#define ysf_pt_delay(tick)      do                                                                           \
                                {                                                                            \
                                    struct ysf_timer_t *timer;                                               \
                                    timer = ysf_evtSimpTimer_init(pt.thread, YSF_PT_DELAY_EVENT);            \
                                    ysf_timer_arm(timer, YSF_TIME_2_TICK(tick), 1);                          \
                                    ysf_pt_wfe(evt != YSF_PT_DELAY_EVENT);                                   \
                                }while(0)
#else
#define ysf_pt_delay(tick)      do                                                                           \
                                {                                                                            \
                                    ysf_evtTimer_init(&pt.timer, pt.thread, YSF_PT_DELAY_EVENT);             \
                                    ysf_timerEx_arm(&pt.timer, YSF_TIME_2_TICK(tick), 1);                    \
                                    ysf_pt_wfe(evt != YSF_PT_DELAY_EVENT);                                   \
                                }while(0)                        
#endif

#define ysf_pt_end(pt)          } return YSF_ERR_NONE
    
/* Exported types ------------------------------------------------------------*/
struct ysf_pt_t
{
    uint16_t state;
    ysf_err_t (*thread)(uint16_t);
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
#else
    struct ysf_timer_t timer;
#endif
};

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf pt component  */

/**********************************END OF FILE*********************************/
