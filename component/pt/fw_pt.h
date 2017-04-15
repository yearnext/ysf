/**
 *******************************************************************************
 *                       Copyright (C) 2017  yearnext                          *
 *                                                                             *
 *    This program is free software; you can redistribute it and/or modify     *
 *    it under the terms of the GNU General Public License as published by     *
 *    the Free Software Foundation; either version 2 of the License, or        *
 *    (at your option) any later version.                                      *
 *                                                                             *
 *    This program is distributed in the hope that it will be useful,          *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *    GNU General Public License for more details.                             *
 *                                                                             *
 *    You should have received a copy of the GNU General Public License along  *
 *    with this program; if not, write to the Free Software Foundation, Inc.,  *
 *    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.              *
 *******************************************************************************
 * @file       ysf_pt.h                                                        *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-21                                                      *
 * @brief      ysf protothreads head files                                     *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
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
#include "core_conf.h"
#include "core_path.h"
#include _COMM_TYPE_PATH
#include _FW_TIMER_COMPONENT_PATH
    
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
#define YSF_PT_THREAD(func_name)   fw_err_t func_name(void *ptTask, uint16_t evt)
    
/**
 *******************************************************************************
 * @brief      protothreads handler function type
 *******************************************************************************
 */ 
#define YSF_PT_THREAD_NAME         fw_err_t (*pt_thread)(void*, uint16_t)
       
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
                                 if(pt->useStatus == false)                                            \
                                 {                                                                           \
                                     return FW_ERR_NONE;                                                    \
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
                                    evt = FW_EVENT_NONE;                                                    \
                                    ysf_pt_wait(evt == YSF_PT_DELAY_EVENT);                                  \
                                }while(0)
#else
#define ysf_pt_delay(tick)      do                                                                           \
                                {                                                                            \
                                    ysf_smTimer_init(&pt->timer, pt->thread, ptTask, YSF_PT_DELAY_EVENT);    \
                                    ysf_timer_arm(&pt->timer, YSF_TIME_2_TICK(tick), 1);                     \
                                    evt = FW_EVENT_NONE;                                                    \
                                    ysf_pt_wait(evt == YSF_PT_DELAY_EVENT);                                  \
                                }while(0)                        
#endif

/**
 *******************************************************************************
 * @brief      protothreads exit functon
 *******************************************************************************
 */
#define ysf_pt_exit()           pt->useStatus = false; ysf_pt_entry(); return FW_ERR_NONE
                                 
/**
 *******************************************************************************
 * @brief      protothreads end functon
 *******************************************************************************
 */
#define ysf_pt_end()            } return FW_ERR_NONE
    
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      protothreads type
 *******************************************************************************
 */
struct ysf_pt_t
{
    uint16_t state;
    bool useStatus;
    fw_err_t (*thread)(void*, uint16_t);
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
    fw_err_t (*init)(struct ysf_pt_t*, YSF_PT_THREAD_NAME);
    fw_err_t (*disarm)(struct ysf_pt_t*);

    fw_err_t (*arm)(struct ysf_task_t*, struct ysf_pt_t*);

    struct
    {
        fw_err_t (*arm)(struct ysf_pt_t*);
    }simple;
};
#endif

/* Exported functions --------------------------------------------------------*/
#if defined(USE_YSF_PT_API) && USE_YSF_PT_API
extern fw_err_t ysf_pt_init(struct ysf_pt_t*, YSF_PT_THREAD_NAME);
extern fw_err_t ysf_pt_arm(struct ysf_task_t*, struct ysf_pt_t*);
extern fw_err_t ysf_pt_simp_arm(struct ysf_pt_t*);
extern fw_err_t ysf_pt_disarm(struct ysf_pt_t*);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf pt component  */

/**********************************END OF FILE*********************************/
