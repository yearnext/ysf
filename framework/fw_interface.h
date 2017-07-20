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
 * @file       fw_interface.h                                                  *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      framework interface head files                                  *
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
 * @defgroup framework interface
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_INTERFACE_H__
#define __FRAMEWORK_INTERFACE_H__

/* Add c++ compatibility -----------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/ 
#include "core_path.h"
#include _FW_PATH    
#include _FW_BUFFER_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH
#include _FW_EVENT_COMPONENT_PATH
#include _FW_LINK_LIST_COMPONENT_PATH 
#include _FW_MEMORY_COMPONENT_PATH
#include _FW_SIGNAL_COMPONENT_PATH
#include _FW_TICK_COMPONENT_PATH
#include _FW_TIMER_COMPONENT_PATH
#include _FW_TASK_COMPONENT_PATH
#include _FW_PT_COMPONENT_PATH

/* Exported macro ------------------------------------------------------------*/ 
/**
 *******************************************************************************
 * @brief        define framework compiler function
 *******************************************************************************
 */
#define fw_enter_critical()                  __ENTER_CRITICAL()
#define fw_exit_critical()                   __EXIT_CRITICAL()
    
/**
 *******************************************************************************
 * @brief        define framework core interface
 *******************************************************************************
 */
#define fw_core_init                         Framework.Init
#define fw_core_start                        Framework.Start

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        define Framework interface
 *******************************************************************************
 */
struct FrameworkInterface
{
    char *Version;
    
    void (*Init)(void);
    void (*Start)(void);
    
#if USE_BUFFER_COMPONENT
//    RingBufferComponentInterface RingBuffer;
#endif

//#if USE_MEMORY_MANAGEMENT_COMPONENT
//    MemoryManagementComponentInterface MemoryManagement;
//#endif

#if USE_DEBUG_COMPONENT
    DebugComponentInterface Debug;
#endif
    
#if USE_EVENT_COMPONENT
    EventComponentInterface Event;
#endif

//#if USE_SINGLE_LIST_COMPONENT
//    SingleListComponentInterface SingleLinkList;
//#endif

#if USE_MEMORY_COMPONENT
//    MemoryComponentInterface Memory;
#endif
    
#if USE_SIGNAL_COMPONENT
    SignalComponentInterface Signal;
#endif   

#if USE_TICK_COMPONENT
    TickComponentInterface Tick;
#endif

#if USE_TIMER_COMPONENT
//TimerComponentInterface Timer;
#endif

#if USE_TASK_COMPONENT
//    TaskComponentInterface Task;
#endif
};

/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        core interface
 *******************************************************************************
 */
extern const struct FrameworkInterface Framework;

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework interface  */

/**********************************END OF FILE*********************************/
