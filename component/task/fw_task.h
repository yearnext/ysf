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
 * @file       fw_task.h                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-03-28                                                      *
 * @brief      task component head files                                       *
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
 * @defgroup task component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TASK_COMPONENT_H__
#define __TASK_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
    
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_TASK_COMPONENT
#if USE_FRAMEWORK_TASK_COMPONENT
#define USE_TASK_COMPONENT                                                   (1)
#else
#define USE_TASK_COMPONENT                                                   (0)
#endif

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
#define USE_TASK_COMPONENT                                                   (1)
#endif

/* Exported types ------------------------------------------------------------*/    
/**
 *******************************************************************************
 * @brief       task block
 *******************************************************************************
 */
struct TaskBlock
{
    struct TaskBlock *Next;
    
    union
    {
        fw_err_t (*Message)(void*, uint16_t);
        fw_err_t (*Event)(uint16_t);
        fw_err_t (*CallBack)(void*);
    }Handler;

    void *Param;
    uint16_t Event;

    enum
    {
        CALL_BACK_TASK,
        EVENT_HANDLE_TASK,
        MESSAGE_HANDLE_TASK,
        
        CALL_BACK_EX_TASK,
        EVENT_HANDLE_EX_TASK,
        MESSAGE_HANDLE_EX_TASK,
    }Type;
};

/**
 *******************************************************************************
 * @brief       framework task interface
 *******************************************************************************
 */
#if USE_TASK_COMPONENT
typedef struct
{
    fw_err_t (*Init)(void);
    fw_err_t (*Poll)(void);
    
    struct
    {
        fw_err_t (*CallBack)(struct TaskBlock*, fw_err_t (*)(void*), void*);
        fw_err_t (*EventHandle)(struct TaskBlock*, fw_err_t (*)(uint16_t), uint16_t);
        fw_err_t (*MessageHandle)(struct TaskBlock*, fw_err_t (*)(void*, uint16_t), void*, uint16_t);
        
        struct TaskBlock *(*CallBackEx)(fw_err_t (*)(void*), void*);
        struct TaskBlock *(*EventHandleEx)(fw_err_t (*)(uint16_t), uint16_t);
        struct TaskBlock *(*MessageHandleEx)(fw_err_t (*)(void*, uint16_t), void*, uint16_t);
    }Create;
}TaskComponentInterfact;
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework task api
 *******************************************************************************
 */
#if USE_TASK_COMPONENT
extern fw_err_t TaskComponentInit(void);
extern fw_err_t TaskComponentPoll(void);

extern fw_err_t CreateCallBackTask(struct TaskBlock*, fw_err_t (*)(void*), void*);
extern fw_err_t CreateEventHandleTask(struct TaskBlock*, fw_err_t (*)(uint16_t), uint16_t);
extern fw_err_t CreateMessageHandleTask(struct TaskBlock*, fw_err_t (*)(void*, uint16_t), void*, uint16_t);

extern struct TaskBlock *CreateCallBackExTask(fw_err_t (*)(void*), void*);
extern struct TaskBlock *CreateEventHandleExTask(fw_err_t (*)(uint16_t), uint16_t);
extern struct TaskBlock *CreateMessageHandleExTask(fw_err_t (*)(void*, uint16_t), void*, uint16_t);
#endif    
    
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** task component  */

/**********************************END OF FILE*********************************/
