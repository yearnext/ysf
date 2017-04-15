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
 * @file       fw_conf.h                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      framework config head files                                     *
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
 * @defgroup framework config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_CONF_H__
#define __FRAMEWORK_CONF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_conf.h"
      
/* Define and config ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define framework version
 *******************************************************************************
 */
#define _FRAMEWORK_VERSION              "FRAMEWORK_ALPHA_0.0.3_2017040132135"

/**
 *******************************************************************************
 * @brief      define framework component flags
 *******************************************************************************
 */
/* Framework buffer component config -----------------------------------------*/
/**
 *******************************************************************************
 * @brief      use core config 
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_BUFFER_COMPONENT
#if USE_FRAMEWORK_BUFFER_COMPONENT
	#define USE_FW_BUFFER_COMPONENT                                          (1)
#else
	#define USE_FW_BUFFER_COMPONENT                                          (0)
#endif

#else
/**
 *******************************************************************************
 * @brief      use user config
 *******************************************************************************
 */
	#define USE_FW_BUFFER_COMPONENT                                          (1)
#endif	

/* Framework debug component config ------------------------------------------*/
/**
 *******************************************************************************
 * @brief      use core config 
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_DEBUG_COMPONENT
#if USE_FRAMEWORK_DEBUG_COMPONENT
	#define USE_FW_DEBUG_COMPONENT                                           (1)
#else
	#define USE_FW_DEBUG_COMPONENT                                           (0)
#endif

#else
/**
 *******************************************************************************
 * @brief      use user config
 *******************************************************************************
 */
	#define USE_FW_DEBUG_COMPONENT                                           (1)
#endif

/* Framework event component config ------------------------------------------*/
/**
 *******************************************************************************
 * @brief      use core config 
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_EVENT_COMPONENT
#if USE_FRAMEWORK_EVENT_COMPONENT
	#define USE_FW_EVENT_COMPONENT                                           (1)
#else
	#define USE_FW_EVENT_COMPONENT                                           (0)
#endif

#else
/**
 *******************************************************************************
 * @brief      use user config
 *******************************************************************************
 */
	#define USE_FW_EVENT_COMPONENT                                           (1)
#endif

/* Framework link list component config --------------------------------------*/
/**
 *******************************************************************************
 * @brief      use core config 
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_LINK_LIST_COMPONENT
#if USE_FRAMEWORK_LINK_LIST_COMPONENT
	#define USE_FW_LINK_LIST_COMPONENT                                       (1)
#else
	#define USE_FW_LINK_LIST_COMPONENT                                       (0)
#endif

#else
/**
 *******************************************************************************
 * @brief      use user config
 *******************************************************************************
 */
	#define USE_FW_LINK_LISTCOMPONENT                                        (1)
#endif

/* Framework memory management component config ------------------------------*/
/**
 *******************************************************************************
 * @brief      use core config 
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_MEMORY_MANAGEMENT_COMPONENT
#if USE_FRAMEWORK_MEMORY_MANAGEMENT_COMPONENT
	#define USE_FW_MEMORY_MANAGEMENT_COMPONENT                               (1)
#else
	#define USE_FW_MEMORY_MANAGEMENT_COMPONENT                               (0)
#endif

#else
/**
 *******************************************************************************
 * @brief      use user config
 *******************************************************************************
 */
	#define USE_FW_MEMORY_MANAGEMENT_COMPONENT                               (1)
#endif

/* Framework signal scan component config -------------------------------------*/
/**
 *******************************************************************************
 * @brief      use core config 
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_SIGNAL_SCAN_COMPONENT
#if USE_FRAMEWORK_SIGNAL_SCAN_COMPONENT
	#define USE_FW_SIGNAL_SCAN_COMPONENT                                     (1)
#else
	#define USE_FW_SIGNAL_SCAN_COMPONENT                                     (0)
#endif

#else
/**
 *******************************************************************************
 * @brief      use user config
 *******************************************************************************
 */
	#define USE_FW_SIGNAL_SCAN_COMPONENT                                     (1)
#endif

/* Framework tick component config -------------------------------------------*/
/**
 *******************************************************************************
 * @brief      use core config 
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_TICK_COMPONENT
#if USE_FRAMEWORK_TICK_COMPONENT
	#define USE_FW_TICK_COMPONENT                                            (1)
#else
	#define USE_FW_TICK_COMPONENT                                            (0)
#endif

#else
/**
 *******************************************************************************
 * @brief      use user config
 *******************************************************************************
 */
	#define USE_FW_TICK_COMPONENT                                            (1)
#endif

/* Framework timer component config ------------------------------------------*/
/**
 *******************************************************************************
 * @brief      use core config 
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_TIMER_COMPONENT
#if USE_FRAMEWORK_TIMER_COMPONENT
	#define USE_FW_TIMER_COMPONENT                                           (1)
#else
	#define USE_FW_TIMER_COMPONENT                                           (0)
#endif

#else
/**
 *******************************************************************************
 * @brief      use user config
 *******************************************************************************
 */
	#define USE_FW_TIMER_COMPONENT                                           (1)
#endif

/* Framework task component config -------------------------------------------*/
/**
 *******************************************************************************
 * @brief      use core config 
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_TASK_COMPONENT
#if USE_FRAMEWORK_TASK_COMPONENT
	#define USE_FW_TASK_COMPONENT                                            (1)
#else
	#define USE_FW_TASK_COMPONENT                                            (0)
#endif

#else
/**
 *******************************************************************************
 * @brief      use user config
 *******************************************************************************
 */
	#define USE_FW_TASK_COMPONENT                                            (1)
#endif

/* Framework buffer component config -----------------------------------------*/
/**
 *******************************************************************************
 * @brief      use core config 
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_PROTOTHREADS_COMPONENT
#if USE_FRAMEWORK_PROTOTHREADS_COMPONENT
	#define USE_FW_PROTOTHREADS_COMPONENT                                    (1)
#else
	#define USE_FW_PROTOTHREADS_COMPONENT                                    (0)
#endif

#else
/**
 *******************************************************************************
 * @brief      use user config
 *******************************************************************************
 */
	#define USE_FW_PROTOTHREADS_COMPONENT                                    (1)
#endif

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define framework events type
 *******************************************************************************
 */
#define FW_EVENT_NONE                                   (_EVENT_NONE)
#define FW_EVENT_DELAY                                  (_EVENT_DELAY)

typedef _evt_t fw_evt_t;

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework config  */

/**********************************END OF FILE*********************************/
