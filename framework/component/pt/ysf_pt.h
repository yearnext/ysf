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
#define YSF_PT_THREAD(func_name) ysf_err_t func_name(void *event)
                              
#define ysf_pt_init(func)        static struct ysf_pt_t pt =                                                 \
                                 {                                                                           \
                                     .state = 0,                                                             \
                                     .event = YSF_PT_TIMER_EVENT,                                            \
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
    
//#define ysf_pt_delay(pt,tick) do                                                                             \
//                              {                                                                              \
//                                  #if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API                      \
//                                  ysf_timerSimple_cb_arm(tick, 0, pt.thread, (void *)&YSF_PT_TIMER_EVENT);   \
//                                  #else                                                                      \
//                                  ysf_timerEx_cb_init(&pt.timer, pt.thread, (void *)&YSF_PT_TIMER_EVENT);    \
//                                  ysf_timerEx_arm(&pt.timer, tick, 0);                                       \
//                                  #endif                                                                     \
//                                  pt.event = YSF_PT_TIMER_EVENT;                                             \
//                                  ysf_pt_entry();                                                            \
//                                  if( pt.event != (uint16_t)(*event) )                                       \
//                                  {                                                                          \
//                                      return YSF_ERR_NOT_READY;                                              \
//                                  }                                                                          \
//                                  ysf_pt_entry();                                                            \
//                              }while(0)
                              
#define ysf_pt_delay(tick)      do                                                                             \
                                {                                                                              \
                                    pt.event = YSF_PT_TIMER_EVENT;                                             \
                                    ysf_timerSimple_cb_arm(tick, 0, pt.thread, &pt.event);                     \
                                    ysf_pt_wait(pt.event != *((uint16_t *)event));                             \
                                }while(0)

#define ysf_pt_end(pt)          } return YSF_ERR_NONE
    
/* Exported types ------------------------------------------------------------*/
struct ysf_pt_t
{
    uint16_t state;
	uint16_t event;
    ysf_err_t (*thread)(void *);
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
