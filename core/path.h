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
 * @file       path.h                                                          *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-03-07                                                      *
 * @brief       path head files                                                *
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
 * @defgroup path
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
 * @brief      common component path
 *******************************************************************************
 */
#define _COMMTOOLS_PATH                       "../common/tools.h"	
#define _TYPE_PATH         		              "../common/type.h"

/**
 *******************************************************************************
 * @brief      compiler path
 *******************************************************************************
 */	
#define _COMPILER_PATH                        "../common/compiler/compiler.h"
#define _ARMCC5_COMPILER_PATH                 "../common/compiler/armcc5/compiler_armcc5.h"
#define _ARMCC6_COMPILER_PATH                 "../common/compiler/armcc6/compiler_armcc6.h"
#define _ICCARM_COMPILER_PATH                 "../common/compiler/iccarm/compiler_iar_arm.h"

/**
 *******************************************************************************
 * @brief      hal path
 *******************************************************************************
 */	
#define _HAL_DIR_PATH                         "../hal/path.h"
#define _HAL_PATH                             "../hal/hal.h"

/**
 *******************************************************************************
 * @brief      framework component path
 *******************************************************************************
 */
#define _FW_TICK_COMPONENT_PATH               "../framework/component/tick/ysf_tick.h"
#define _FW_BUFFER_COMPONENT_PATH             "../framework/component/buffer/ysf_buffer.h"
#define _FW_MEMORY_COMPONENT_PATH             "../framework/component/memory/FW_memory.h"
#define _FW_TIMER_COMPONENT_PATH              "../framework/component/timer/ysf_timer.h"
#define _FW_EVENT_COMPONENT_PATH              "../framework/component/event/ysf_event.h"
#define _FW_SIGNAL_COMPONENT_PATH             "../framework/component/signal/ysf_signal.h"
#define _FW_DEBUG_COMPONENT_PATH              "../framework/component/debug/ysf_debug.h"
#define _FW_LIST_COMPONENT_PATH               "../framework/component/list/ysf_list.h"
#define _FW_PT_COMPONENT_PATH                 "../framework/component/pt/ysf_pt.h"
#define _FW_TASK_COMPONENT_PATH               "../framework/component/task/ysf_task.h"

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** path  */

/**********************************END OF FILE*********************************/
