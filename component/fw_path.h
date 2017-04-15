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
 * @file       fw_path.h                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      framework path head files                                       *
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
 * @defgroup framework path
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_PATH_H__
#define __FRAMEWORK_PATH_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif


/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      framework common path
 *******************************************************************************
 */
#define _FW_TYPE_PATH                        "../component/fw_type.h"
#define _FW_CONF_PATH                        "../component/fw_conf.h"
    
/**
 *******************************************************************************
 * @brief      framework component path
 *******************************************************************************
 */
#define _FW_TICK_COMPONENT_PATH               "../component/tick/fw_tick.h"
#define _FW_BUFFER_COMPONENT_PATH             "../component/buffer/fw_buffer.h"
#define _FW_MEMORY_COMPONENT_PATH             "../component/memory/fw_memory.h"
#define _FW_TIMER_COMPONENT_PATH              "../component/timer/fw_timer.h"
#define _FW_EVENT_COMPONENT_PATH              "../component/event/fw_event.h"
#define _FW_SIGNAL_COMPONENT_PATH             "../component/signal/fw_signal.h"
#define _FW_DEBUG_COMPONENT_PATH              "../component/debug/fw_debug.h"
#define _FW_LINK_LIST_COMPONENT_PATH          "../component/linklist/fw_linklist.h"
#define _FW_PT_COMPONENT_PATH                 "../component/pt/fw_pt.h"
#define _FW_TASK_COMPONENT_PATH               "../component/task/fw_task.h"

/* Includes ------------------------------------------------------------------*/
#include _FW_TYPE_PATH
#include _FW_CONF_PATH

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework path  */

/**********************************END OF FILE*********************************/
