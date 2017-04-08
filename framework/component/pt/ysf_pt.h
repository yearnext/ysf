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
    
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      protothreads config falgs
 *******************************************************************************
 */  
#ifdef USE_YSF_PROTOTHREADS_COMPONENT
#if USE_YSF_PROTOTHREADS_COMPONENT 
#define USE_YSF_PT_API           (1)
#else
#define USE_YSF_PT_API           (0)
#endif
    
/**
 *******************************************************************************
 * @brief      user config
 *******************************************************************************
 */  
#else
#define USE_YSF_PT_API           (1)
#endif

/**
 *******************************************************************************
 * @brief      protothreads handler function
 *******************************************************************************
 */ 
#define YSF_PT_THREAD(func_name)   ysf_err_t func_name(void *ptTask, uint16_t evt)
    
/**
 *******************************************************************************
 * @brief      protothreads handler function type
 *******************************************************************************
 */ 
#define YSF_PT_THREAD_NAME         ysf_err_t (*pt_thread)(void*, uint16_t)
       
/**
 *******************************************************************************
 * @brief      protothreads deinit functon
 *******************************************************************************
 */    
#define ysf_pt_deinit()          (pt->state = 0)

/**
 *******************************************************************************
 * @brief      protothreads begin functon
 *******************************************************************************
 */                              
#define ysf_pt_begin()           struct ysf_pt_t *pt = (struct ysf_pt_t*)ptTask;                             \
                                                                                                             \
                                 if(pt->useStatus == ysf_disable)                                            \
                                 {                                                                           \
                                     return YSF_ERR_NONE;                                                    \
                                 }                                                                           \
                                                                                                             \
                                 switch(pt->state)                                                           \
                                 {                                                                           \
                                    case 0:

/**
 *******************************************************************************
 * @brief      protothreads entry functon
 *******************************************************************************
 */                                    
#define ysf_pt_entry()           pt->state = (uint16_t)__LINE__; case __LINE__:
    
/**
 *******************************************************************************
 * @brief      protothreads wait functon
 *******************************************************************************
 */
#define ysf_pt_wait(state)       do                                                                          \
                                 {                                                                           \
                                     ysf_pt_entry();                                                         \
                                     if( !(state) )                                                          \
                                     {                                                                       \
                                        return YSF_ERR_NOT_READY;                                            \
                                     }                                                                       \
                                 }while(0)

/**
 *******************************************************************************
 * @brief      protothreads wait functon
 *******************************************************************************
 */                                 
#define ysf_pt_wfe(state)        do                                                                          \
                                 {                                                                           \
                                     ysf_pt_entry();                                                         \
                                     if( (state) )                                                           \
                                     {                                                                       \
                                        return YSF_ERR_NOT_READY;                                            \
                                     }                                                                       \
                                 }while(0)
                                 
/**
 *******************************************************************************
 * @brief      protothreads delay functon
 *******************************************************************************
 */
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
#define ysf_pt_delay(tick)      do                                                                           \
                                {                                                                            \
                                    struct ysf_timer_t *timer;                                               \
                                    timer = ysf_smSimpTimer_init(pt->thread, ptTask, YSF_PT_DELAY_EVENT);    \
                                    ysf_timer_arm(timer, YSF_TIME_2_TICK(tick), 1);                          \
                                    evt = YSF_EVENT_NONE;                                                    \
                                    ysf_pt_wfe(evt != YSF_PT_DELAY_EVENT);                                   \
                                }while(0)
#else
#define ysf_pt_delay(tick)      do                                                                           \
                                {                                                                            \
                                    ysf_smTimer_init(&pt->timer, pt->thread, ptTask, YSF_PT_DELAY_EVENT);    \
                                    ysf_timer_arm(&pt->timer, YSF_TIME_2_TICK(tick), 1);                     \
                                    evt = YSF_EVENT_NONE;                                                    \
                                    ysf_pt_wfe(evt != YSF_PT_DELAY_EVENT);                                   \
                                }while(0)                        
#endif

/**
 *******************************************************************************
 * @brief      protothreads exit functon
 *******************************************************************************
 */
#define ysf_pt_exit()           pt->useStatus = ysf_disable; ysf_pt_entry(); return YSF_ERR_NONE
                                 
/**
 *******************************************************************************
 * @brief      protothreads end functon
 *******************************************************************************
 */
#define ysf_pt_end()            } return YSF_ERR_NONE
    
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      protothreads type
 *******************************************************************************
 */
struct ysf_pt_t
{
    uint16_t state;
    ysf_status_t useStatus;
    ysf_err_t (*thread)(void*, uint16_t);
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
#else
    struct ysf_timer_t timer;
#endif
};

/**
 *******************************************************************************
 * @brief       ysf pt api
 *******************************************************************************
 */
#if defined(USE_YSF_PT_API) && USE_YSF_PT_API
struct YSF_PT_API
{
    ysf_err_t (*init)(struct ysf_pt_t*, YSF_PT_THREAD_NAME);
    ysf_err_t (*disarm)(struct ysf_pt_t*);

    ysf_err_t (*arm)(struct ysf_task_t*, struct ysf_pt_t*);

    struct
    {
        ysf_err_t (*arm)(struct ysf_pt_t*);
    }simple;
};
#endif

/* Exported functions --------------------------------------------------------*/
#if defined(USE_YSF_PT_API) && USE_YSF_PT_API
extern ysf_err_t ysf_pt_init(struct ysf_pt_t*, YSF_PT_THREAD_NAME);
extern ysf_err_t ysf_pt_arm(struct ysf_task_t*, struct ysf_pt_t*);
extern ysf_err_t ysf_pt_simp_arm(struct ysf_pt_t*);
extern ysf_err_t ysf_pt_disarm(struct ysf_pt_t*);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf pt component  */

/**********************************END OF FILE*********************************/
