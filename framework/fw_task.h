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
#include "fw_path.h"
    
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_TASK_COMPONENT
#define USE_TASK_COMPONENT                                                   (1)

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
 * @brief       task handle block
 *******************************************************************************
 */
struct Fw_Task_Handle
{
    //< task handle
    union
    {
        void (*Simple)(void);
        fw_err_t (*CallBack)(void*);
        fw_err_t (*Event)(uint16_t);
        fw_err_t (*Message)(uint32_t, void*);
        fw_err_t (*PT_Thread)(void*, uint16_t);
        
        void *Check;
        void *Config;
    };
    
    //< task handle type
    enum _Fw_Task_Type
    {
        FW_SIMPLE_TYPE_TASK,
        FW_CALL_BACK_TYPE_TASK,
        FW_EVENT_HANDLE_TYPE_TASK,
        FW_MESSAGE_HANDLE_TYPE_TASK,
        FW_PT_THREAD_TYPE_TASK,
    }Type;
};

/**
 *******************************************************************************
 * @brief       framework task block
 *******************************************************************************
 */
struct Fw_Task
{
    char *Str;

    struct Fw_Task_Handle Handle;
    
    uint8_t Priority;
    
    uint8_t Status;
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework task api
 *******************************************************************************
 */
#if USE_TASK_COMPONENT
extern void Fw_Task_InitComponent(void);
extern fw_err_t Fw_Task_Init(struct Fw_Task*, char*, uint8_t, void*, enum _Fw_Task_Type);
extern void Fw_Task_PostEvent(struct Fw_Task*, uint32_t);
extern void Fw_Task_PostMessage(struct Fw_Task*, uint32_t, void*);
extern void Fw_Task_Dispatch(void);
extern void Fw_Task_Enable(struct Fw_Task*);
extern void Fw_Task_Disable(struct Fw_Task*);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework task component */

/**********************************END OF FILE*********************************/
