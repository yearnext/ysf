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
#define TIME_2_TICK(time)    ((time)/CORE_TICK_PERIOD)

#define TIMER_CYCLE_MODE     (-1)

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

    enum
    {
        CALL_BACK_TIMER,
        EVENT_HANDLE_TIMER,
        MESSAGE_HANDLE_TIMER,
        
        CALL_BACK_EX_TIMER,
        EVENT_HANDLE_EX_TIMER,
        MESSAGE_HANDLE_EX_TIMER,
    }Type;
};

/**
 *******************************************************************************
 * @brief      interface function defineitions 
 *******************************************************************************
 */
#if USE_TIMER_COMPONENT
typedef struct
{
    fw_err_t (*Init)(void);
    fw_err_t (*Handler)(uint16_t);

    fw_err_t (*Arm)(struct TimerBlock*, uint32_t, int16_t);
    fw_err_t (*Disarm)(struct TimerBlock*);
    
    bool (*GetStatus)(struct TimerBlock*);
    
    fw_err_t (*CallBackInit)(struct TimerBlock*, fw_err_t (*)(void*), void*);
    fw_err_t (*EventHandleInit)(struct TimerBlock*, fw_err_t (*)(uint16_t), uint16_t);
    fw_err_t (*MessageInit)(struct TimerBlock*, fw_err_t (*)(void*, uint16_t), void*, uint16_t);

    struct TimerBlock *(*CallBackExInit)(fw_err_t (*)(void*), void*);
    struct TimerBlock *(*EventHandleExInit)(fw_err_t (*)(uint16_t), uint16_t);
    struct TimerBlock *(*MessageHandleExInit)(fw_err_t (*)(void*, uint16_t), void*, uint16_t);
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
extern fw_err_t TimerComponentInit(void);
extern fw_err_t TimerComponentHandle(uint16_t);

extern bool GetTimerStatus(struct TimerBlock*);

extern fw_err_t TimerArm(struct TimerBlock*, uint32_t, int16_t);                                          
extern fw_err_t TimerDisarm(struct TimerBlock*); 

extern fw_err_t InitCallBackTimer(struct TimerBlock*, fw_err_t (*)(void*), void*); 
extern fw_err_t InitEventHandleTimer(struct TimerBlock*, fw_err_t (*)(uint16_t), uint16_t);
extern fw_err_t InitMessageHandleTimer(struct TimerBlock*, fw_err_t (*)(void*, uint16_t), void*, uint16_t);

extern struct TimerBlock *InitCallBackExTimer(fw_err_t (*)(void*), void*);
extern struct TimerBlock *InitEventHandleExTimer(fw_err_t (*)(uint16_t), uint16_t);
extern struct TimerBlock *InitMessageHandleExTimer(fw_err_t (*)(void*, uint16_t), void*, uint16_t);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** timer component */

/**********************************END OF FILE*********************************/
