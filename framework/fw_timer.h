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
#include "fw_path.h"
#include "fw_tick.h"
    
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_TIMER_COMPONENT
#define USE_TIMER_COMPONENT                                                  (1)

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
#define CAL_SET_TIME(time)                                  ((time)/TICK_PERIOD)

/**
 *******************************************************************************
 * @brief       define timer cycle mode
 *******************************************************************************
 */
#define FW_TIMER_CYCLE_MODE                                                 (-1)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        timer block
 *******************************************************************************
 */
struct Fw_Timer
{
    struct
    {
        struct Fw_Timer *Last;
        struct Fw_Timer *Next;
    }LinkList;
    
    char              *String;

    void              (*Callback)(void*);
    void              *CallbackParam;

    struct Fw_Task    *Task;
	void              *TaskParam;
    uint32_t           TaskEvent;
    
    uint32_t          InitTick;
    uint32_t          TimeOutTick;
    int16_t           Cycle;
};

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      defineitions interface function 
 *******************************************************************************
 */
#if USE_TIMER_COMPONENT           
extern fw_err_t Fw_Timer_InitComponent(void);
extern __INLINE struct Fw_Timer *Fw_Timer_Create(void);
extern fw_err_t Fw_Timer_Init(struct Fw_Timer*, char*);
extern fw_err_t Fw_Timer_Fini(struct Fw_Timer*);
extern __INLINE fw_err_t Fw_Timer_SetEvent(struct Fw_Timer*, struct Fw_Task*, uint8_t, void*);
extern __INLINE fw_err_t Fw_Timer_SetCallback(struct Fw_Timer*, void (*)(void*), void*);
extern fw_err_t Fw_Timer_Start(struct Fw_Timer*, uint32_t, int16_t);
extern fw_err_t Fw_Timer_Stop(struct Fw_Timer*);
extern fw_err_t Fw_Timer_Poll(void *);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** timer component */

/**********************************END OF FILE*********************************/
