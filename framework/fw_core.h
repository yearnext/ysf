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
 * @file       fw_core.h                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      framework core head files                                       *
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
 * @defgroup framework core interface
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_CORE_H__
#define __FRAMEWORK_CORE_H__

/* Add c++ compatibility -----------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/ 
#include "fw_type.h"
#include "fw_conf.h"
    
/* Exported macro ------------------------------------------------------------*/ 
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
#if USE_FRAMEWORK_COMPONENT_LIBRARY
#ifdef USE_FRAMEWORK_BUFFER_COMPONENT
#include "fw_buffer.h"
#endif
        
#ifdef USE_FRAMEWORK_DEBUG_COMPONENT
#include "fw_debug.h"
#endif
    
#ifdef USE_FRAMEWORK_LINK_LIST_COMPONENT 
#include "fw_linklist.h"
#endif
    
#ifdef USE_FRAMEWORK_MEMORY_MANAGEMENT_COMPONENT 
#include "fw_memory.h"
#endif
    
#ifdef USE_FRAMEWORK_SIGNAL_SCAN_COMPONENT 
#include "fw_signal.h"
#endif
    
#ifdef USE_FRAMEWORK_TICK_COMPONENT 
#include "fw_tick.h"
#endif
    
#ifdef USE_FRAMEWORK_TIMER_COMPONENT  
#include "fw_timer.h"
#endif
    
#ifdef USE_FRAMEWORK_TASK_COMPONENT 
#include "fw_task.h"
#endif
    
#ifdef USE_FRAMEWORK_PT_COMPONENT 
#include "fw_pt.h"
#endif
    
#ifdef USE_FRAMEWORK_STREAM_COMPONENT 
#include "fw_stream.h"
#endif
    
#else
#warning Please Enable Framework Component Library!
#endif
    
/* Exported functions --------------------------------------------------------*/
extern void App_User_Init(void);
    
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework core interface  */

/**********************************END OF FILE*********************************/
