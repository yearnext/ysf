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
#include "fw_path.h"
#include "fw_timer.h"
#include "fw_task.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_PT_COMPONENT
#define USE_PT_COMPONENT                                                     (1)

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

typedef fw_err_t (*pt_thread)(void*, uint16_t);

/**
 *******************************************************************************
 * @brief      protothreads begin functon
 *******************************************************************************
 */                              
#define _pt_begin()              struct Fw_ProtoThread *pt = (struct Fw_ProtoThread *)ptTask; \
                                                                                              \
                                 if(pt->UseStatus == false)                                   \
                                 {                                                            \
                                     return FW_ERR_NONE;                                      \
                                 }                                                            \
                                                                                              \
                                 if(evt == FW_FINI_EVENT)                                     \
                                 {                                                            \
                                     pt->State = 0;                                           \
                                                                                              \
                                     return FW_ERR_NONE;                                      \
                                 }                                                            \
                                                                                              \
                                 switch(pt->State)                                            \
                                 {                                                            \
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
#define _pt_wait(state) _ST(_pt_entry(); if(!(state)) {return FW_ERR_NOT_READY;})

/**
 *******************************************************************************
 * @brief      protothreads wait functon
 *******************************************************************************
 */                                 
#define _pt_wfe(state) _ST(_pt_entry(); if(state) {return FW_ERR_NOT_READY;})
                               
/**
 *******************************************************************************
 * @brief      protothreads delay functon
 *******************************************************************************
 */
#define _pt_delay(tick)         do                                                      \
                                {                                                       \
                                    Fw_Timer_Start(&pt->Timer, CAL_SET_TIME(tick), 1);  \
                                    evt = FW_EVENT_NONE;                                \
                                    _pt_wait(evt == FW_DELAY_EVENT);                    \
                                }while(0)                        
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
struct Fw_ProtoThread
{
    fw_err_t (*Thread)(void*, uint16_t);
    
    char      *Str;
    
    struct Fw_Timer Timer;
    struct Fw_Task  Task;
    
    uint16_t        State;
    
    bool            UseStatus;
};

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        define framework protothreads api
 *******************************************************************************
 */
extern fw_err_t Fw_PT_Init(struct Fw_ProtoThread* /*pt*/, char* /*str*/, 
                           pt_thread /*ptThread*/, uint8_t /*priority*/);
extern fw_err_t Fw_PT_Fini(struct Fw_ProtoThread* /*pt*/);
extern fw_err_t Fw_PT_Open(struct Fw_ProtoThread* /*pt*/);
extern fw_err_t Fw_PT_Close(struct Fw_ProtoThread* /*pt*/);

/**
 *******************************************************************************
 * @brief        define framework protothreads interface
 *******************************************************************************
 */
#define Fw_PT_Begin()                                                _pt_begin()
#define Fw_PT_Entry()                                                _pt_entry()
#define Fw_PT_Wait(n)                                                _pt_wait(n)
#define Fw_PT_WFE(n)                                                  _pt_wfe(n)
#define Fw_PT_Delay(n)                                              _pt_delay(n)
#define Fw_PT_Exit()                                                  _pt_exit()
#define Fw_PT_End()                                                    _pt_end()

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework pt component */

/**********************************END OF FILE*********************************/
