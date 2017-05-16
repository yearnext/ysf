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
        fw_err_t (*Simple)(void);
        fw_err_t (*CallBack)(void*);
        fw_err_t (*Event)(uint16_t);
        fw_err_t (*Message)(void*, uint16_t);
    }Handle;

    void *Param;
    uint16_t Event;

    enum
    {
        SIMPLE_TASK,
        CALL_BACK_TASK,
        EVENT_HANDLE_TASK,
        MESSAGE_HANDLE_TASK,
        
        SIMPLE_EX_TASK,
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
    fw_err_t (*Open)(void);
    fw_err_t (*Close)(void);
    
    fw_err_t (*Poll)(void);
    
    fw_err_t (*Arm)(struct TaskBlock*);
    
    struct
    {
        fw_err_t (*Simple)(struct TaskBlock*, fw_err_t (*)(void));
        fw_err_t (*CallBack)(struct TaskBlock*, fw_err_t (*)(void*), void*);
        fw_err_t (*EventHandle)(struct TaskBlock*, fw_err_t (*)(uint16_t), uint16_t);
        fw_err_t (*MessageHandle)(struct TaskBlock*, fw_err_t (*)(void*, uint16_t), void*, uint16_t);
    }Init;
    
    struct
    {
        fw_err_t (*Simple)(struct TaskBlock*, fw_err_t (*)(void));
        fw_err_t (*CallBack)(struct TaskBlock*, fw_err_t (*)(void*), void*);
        fw_err_t (*EventHandle)(struct TaskBlock*, fw_err_t (*)(uint16_t), uint16_t);
        fw_err_t (*MessageHandle)(struct TaskBlock*, fw_err_t (*)(void*, uint16_t), void*, uint16_t);
    }Add;
}TaskComponentInterface;
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework task api
 *******************************************************************************
 */
#if USE_TASK_COMPONENT
extern fw_err_t InitTaskComponent(void);
extern fw_err_t DeinitTaskComponent(void);

extern fw_err_t PollTaskComponent(void);

extern fw_err_t ArmTaskModule(struct TaskBlock*);

extern fw_err_t InitSimpleTask(struct TaskBlock*, fw_err_t (*)(void));
extern fw_err_t InitCallBackTask(struct TaskBlock*, fw_err_t (*)(void*), void*);
extern fw_err_t InitEventHandleTask(struct TaskBlock*, fw_err_t (*)(uint16_t), uint16_t);
extern fw_err_t InitMessageHandleTask(struct TaskBlock*, fw_err_t (*)(void*, uint16_t), void*, uint16_t);

extern fw_err_t AddSimpleTask(struct TaskBlock*, fw_err_t (*)(void));
extern fw_err_t AddCallBackTask(struct TaskBlock*, fw_err_t (*)(void*), void*);
extern fw_err_t AddEventHandleTask(struct TaskBlock*, fw_err_t (*)(uint16_t), uint16_t);
extern fw_err_t AddMessageHandleTask(struct TaskBlock*, fw_err_t (*)(void*, uint16_t), void*, uint16_t);

/**
 *******************************************************************************
 * @brief        define framework task interface
 *******************************************************************************
 */
#define fw_task_init                         InitTaskComponent
#define fw_task_fini                         DeinitTaskComponent
#define fw_task_poll                         PollTaskComponent
#define fw_task_arm                          ArmTaskModule
#define fw_task_simp_init                    InitSimpleTask
#define fw_task_cb_init                      InitCallBackTask
#define fw_task_evt_init                     InitEventHandleTask
#define fw_task_msg_init                     InitMessageHandleTask
#define fw_task_simp_create                  AddSimpleTask
#define fw_task_cb_create                    AddCallBackTask
#define fw_task_evt_create                   AddEventHandleTask
#define fw_task_msg_create                   AddMessageHandleTask

#else
#define fw_task_init()   
#define fw_task_fini()                         
#define fw_task_poll()                         
#define fw_task_arm(a)                         
#define fw_task_simp_init(a,b)                    
#define fw_task_cb_init(a,b,c)                     
#define fw_task_evt_init(a,b,c)                    
#define fw_task_msg_init(a,b,c,d) 
#define fw_task_simp_create(a,b)  
#define fw_task_cb_create(a,b,c)         
#define fw_task_evt_create(a,b,c)             
#define fw_task_msg_create(a,b,c,d)                    
#endif  
    
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** task component  */

/**********************************END OF FILE*********************************/
