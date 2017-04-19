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
 * @file       fw_pt.h                                                         *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-21                                                      *
 * @brief      protothreads component head files                               *
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
#ifndef __PT_COMPONENT_H__
#define __PT_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_TIMER_COMPONENT_PATH
#include _FW_MEMORY_COMPONENT_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_PT_COMPONENT
#if USE_FRAMEWORK_PT_COMPONENT 
#define USE_PT_COMPONENT                                                     (1)
#else
#define USE_PT_COMPONENT                                                     (0)
#endif
/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
#define USE_PT_COMPONENT                                                     (1)
#endif

/**
 *******************************************************************************
 * @brief      protothreads handler function
 *******************************************************************************
 */ 
#define _PT_THREAD(func_name)     fw_err_t func_name(void *ptTask, uint16_t evt)
    
/**
 *******************************************************************************
 * @brief      protothreads handler function type
 *******************************************************************************
 */ 
#define _PT_THREAD_NAME          fw_err_t (*pt_thread)(void*, uint16_t)
       
/**
 *******************************************************************************
 * @brief      protothreads deinit functon
 *******************************************************************************
 */    
#define _pt_deinit()            (pt->State = 0)

/**
 *******************************************************************************
 * @brief      protothreads begin functon
 *******************************************************************************
 */                              
#define _pt_begin()              struct ProtoThreads *pt = (struct ProtoThreads*)ptTask;                     \
                                                                                                             \
                                 if(pt->UseStatus == false)                                                  \
                                 {                                                                           \
                                     return FW_ERR_NONE;                                                     \
                                 }                                                                           \
                                                                                                             \
                                 switch(pt->State)                                                           \
                                 {                                                                           \
                                    case 0:

/**
 *******************************************************************************
 * @brief      protothreads entry functon
 *******************************************************************************
 */                                    
#define _pt_entry()              pt->State = (uint16_t)__LINE__; case __LINE__:
    
/**
 *******************************************************************************
 * @brief      protothreads wait functon
 *******************************************************************************
 */
#define _pt_wait(state)          do                                                                          \
                                 {                                                                           \
                                     _pt_entry();                                                            \
                                     if( !(state) )                                                          \
                                     {                                                                       \
                                        return FW_ERR_NOT_READY;                                             \
                                     }                                                                       \
                                 }while(0)

/**
 *******************************************************************************
 * @brief      protothreads wait functon
 *******************************************************************************
 */                                 
#define _pt_wfe(state)           do                                                                          \
                                 {                                                                           \
                                     _pt_entry();                                                            \
                                     if( (state) )                                                           \
                                     {                                                                       \
                                        return FW_ERR_NOT_READY;                                             \
                                     }                                                                       \
                                 }while(0)
                                 
/**
 *******************************************************************************
 * @brief      protothreads delay functon
 *******************************************************************************
 */
#if defined(USE_TIMER_COMPONENT) && USE_TIMER_COMPONENT
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
#define _pt_delay(tick)         do                                                                           \
                                {                                                                            \
                                    struct TimerBlock *timer;                                                \
                                    timer = InitMessageHandleExTimer(pt->Thread, ptTask, FW_EVENT_DELAY);    \
                                    ArmTimerModule(timer, TIME_2_TICK(tick), 1);                             \
                                    evt = FW_EVENT_NONE;                                                     \
                                    _pt_wait(evt == FW_EVENT_DELAY);                                         \
                                }while(0)
#else
#define _pt_delay(tick)         do                                                                           \
                                {                                                                            \
                                    InitMessageHandleTimer(&pt->Timer, pt->Thread, ptTask, FW_EVENT_DELAY);  \
                                    ArmTimerModule(&pt->timer, TIME_2_TICK(tick), 1);                        \
                                    evt = FW_EVENT_NONE;                                                     \
                                    _pt_wait(evt == FW_EVENT_DELAY);                                         \
                                }while(0)                        
#endif
#else
 #define _pt_delay(tick)                            
#endif
                                
/**
 *******************************************************************************
 * @brief      protothreads exit functon
 *******************************************************************************
 */
#define _pt_exit()              pt->UseStatus = false; _pt_entry(); return FW_ERR_NONE
                                 
/**
 *******************************************************************************
 * @brief      protothreads end functon
 *******************************************************************************
 */
#define _pt_end()               } return FW_ERR_NONE
    
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      protothreads type
 *******************************************************************************
 */
struct ProtoThreads
{
    fw_err_t (*Thread)(void*, uint16_t);
    
#if !defined(USE_MEMORY_COMPONENT) && !USE_MEMORY_COMPONENT
    struct TimerBlock Timer;
#endif
    
    uint16_t State;
    bool     UseStatus;
};

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define pt api
 *******************************************************************************
 */
#if defined(USE_PT_COMPONENT) && USE_PT_COMPONENT
extern fw_err_t _pt_init(struct ProtoThreads*, _PT_THREAD_NAME);
extern fw_err_t _pt_arm(struct TaskBlock*, struct ProtoThreads*);
extern fw_err_t _pt_ex_arm(struct ProtoThreads*);
extern fw_err_t _pt_disarm(struct ProtoThreads*);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** pt component */

/**********************************END OF FILE*********************************/
