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
 * @file       fw_timer.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-07-09                                                      *
 * @brief      timer component head files                                      *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_COMPONENT_H__
#define __TIMER_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_TASK_COMPONENT_PATH
    
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_TIMER_COMPONENT
#if USE_FRAMEWORK_TIMER_COMPONENT
#define USE_TIMER_COMPONENT                                                  (1)
#else
#define USE_TIMER_COMPONENT                                                  (0)
#endif

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
#define USE_TIMER_COMPONENT                                                  (1)
#endif

/**
 *******************************************************************************
 * @brief       timer tick config
 *******************************************************************************
 */
#define CAL_SET_TIME(time)                             ((time)/CORE_TICK_PERIOD)

/**
 *******************************************************************************
 * @brief       define timer cycle mode
 *******************************************************************************
 */
#define TIMER_CYCLE_MODE                                                    (-1)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        timer block
 *******************************************************************************
 */
struct TimerBlock
{
    struct TimerBlock *Next;

    uint32_t          SetTicks;
    uint32_t          LoadTicks;
    int16_t           Cycle;

    struct TaskBlock  Task;
};

/**
 *******************************************************************************
 * @brief      interface function defineitions 
 *******************************************************************************
 */
#if USE_TIMER_COMPONENT
typedef struct
{
    fw_err_t (*Open)(void);
    fw_err_t (*Close)(void);
    
    fw_err_t (*Poll)(void);

    fw_err_t (*Start)(struct TimerBlock*, uint32_t, int16_t);
    fw_err_t (*Stop)(struct TimerBlock*);

    fw_err_t (*Add)(struct TimerBlock*);
    fw_err_t (*Remove)(struct TimerBlock*);
    
    bool (*GetStatus)(struct TimerBlock*);
    
    struct
    {
        fw_err_t (*Simple)(struct TimerBlock*, fw_err_t (*)(void));
        fw_err_t (*CallBack)(struct TimerBlock*, fw_err_t (*)(void*), void*);
        fw_err_t (*EventHandle)(struct TimerBlock*, fw_err_t (*)(uint16_t), uint16_t);
        fw_err_t (*MessageHandle)(struct TimerBlock*, fw_err_t (*)(void*, uint16_t), void*, uint16_t);
    }Init;
}TimerComponentInterface;
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      defineitions interface function 
 *******************************************************************************
 */
#if USE_TIMER_COMPONENT
extern fw_err_t InitTimerComponent(void);
extern fw_err_t DeinitTimerComponent(void);
    
extern fw_err_t PollTimerComponent(void);

extern bool GetTimerModuleStatus(struct TimerBlock*);

extern fw_err_t StartTimerModule(struct TimerBlock*, uint32_t, int16_t);                                          
extern fw_err_t StopTimerModule(struct TimerBlock*); 

extern fw_err_t AddTimerModuleToQueue(struct TimerBlock*);
extern fw_err_t RemoveTimerModuleFromQueue(struct TimerBlock*);

extern fw_err_t InitSimpleTimerModule(struct TimerBlock*, fw_err_t (*)(void)); 
extern fw_err_t InitCallBackTimerModule(struct TimerBlock*, fw_err_t (*)(void*), void*); 
extern fw_err_t InitEventHandleTimerModule(struct TimerBlock*, fw_err_t (*)(uint16_t), uint16_t);
extern fw_err_t InitMessageHandleTimerModule(struct TimerBlock*, fw_err_t (*)(void*, uint16_t), void*, uint16_t);

/**
 *******************************************************************************
 * @brief        define framework timer interface
 *******************************************************************************
 */ 
#define fw_timer_init                        InitTimerComponent
#define fw_timer_fini                        DeinitTimerComponent
#define fw_timer_poll                        PollTimerComponent
#define fw_timer_add                         AddTimerModuleToQueue
#define fw_timer_remove                      RemoveTimerModuleFromQueue
#define fw_timer_start                       StartTimerModule
#define fw_timer_stop                        StopTimerModule
#define fw_timer_get_status                  GetTimerModuleStatus
#define fw_timer_simp_init                   InitSimpleTimerModule
#define fw_timer_cb_init                     InitCallBackTimerModule
#define fw_timer_evt_init                    InitEventHandleTimerModule
#define fw_timer_msg_init                    InitMessageHandleTimerModule

#else
#define fw_timer_init()                       
#define fw_timer_fini()                     
#define fw_timer_poll()                  
#define fw_timer_add(a)
#define fw_timer_remove(a)
#define fw_timer_start(a,b,c)              
#define fw_timer_stop(a)         
#define fw_timer_get_status(a)    
#define fw_timer_simp_init(a,b)          
#define fw_timer_cb_init(a,b,c)       
#define fw_timer_evt_init(a,b,c)             
#define fw_timer_msg_init(a,b,c,d)                

#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** timer component */

/**********************************END OF FILE*********************************/
