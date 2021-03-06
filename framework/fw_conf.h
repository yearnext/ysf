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
#include "app_conf.h"
//#include _HAL_PATH
//#include _HAL_TIMER_PATH     

/* Define and config ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define framework version
 *******************************************************************************
 */
#define _FRAMEWORK_VERSION                               "FRAMEWORK_ALPHA_0.0.3"

/**
 *******************************************************************************
 * @brief       core tick time(unit: ms)
 *******************************************************************************
 */
#define FW_TICK_PERIOD                                                     (1UL)
 
/**
 *******************************************************************************
 * @brief       define memory align size
 *******************************************************************************
 */ 
#define FW_MEMORY_ALIGN_SIZE                                                 (8)
    
/**
 *******************************************************************************
 * @brief       framwork component config flags
 * @note        1                       enable
 * @note        0                       disable
 *******************************************************************************
 */
#define USE_FRAMEWORK_COMPONENT                                              (1)

/**
 *******************************************************************************
 * @brief       use std library
 *******************************************************************************
 */
#define USE_STD_LIBRARY

/**
 *******************************************************************************
 * @brief      frameowrk component config <user config in>
 *******************************************************************************
 */
#if USE_FRAMEWORK_COMPONENT
#define USE_FRAMEWORK_DEBUG                                                  
#define USE_FRAMEWORK_BUFFER_COMPONENT 
#define USE_FRAMEWORK_DEBUG_COMPONENT    
#define USE_FRAMEWORK_LINK_LIST_COMPONENT           
#define USE_FRAMEWORK_MEMORY_MANAGEMENT_COMPONENT          
#define USE_FRAMEWORK_SIGNAL_SCAN_COMPONENT                               
#define USE_FRAMEWORK_TICK_COMPONENT                                      
#define USE_FRAMEWORK_TIMER_COMPONENT                                      
#define USE_FRAMEWORK_TASK_COMPONENT                                         
#define USE_FRAMEWORK_PT_COMPONENT     
#define USE_FRAMEWORK_STREAM_COMPONENT
#define USE_FRAMEWORK_PIPE_COMPONENT
#define USE_FRAMEWORK_COMMUNICATION_COMPONENT
#endif

/**
 *******************************************************************************
 * @brief      define use memory pool size
 *******************************************************************************
 */
#ifndef USE_STD_LIBRARY_IN_FRAMEWORK_COMPONENT
#define FRAMEWORK_MEMORY_POOL_SIZE                                        (4096)

#if (FRAMEWORK_MEMORY_POOL_SIZE % 8)
#error "This memory pool is not 8 byte alignment!"
#endif

#endif

/**
 *******************************************************************************
 * @brief        debug framework task queue size
 *******************************************************************************
 */
#define FW_TASK_MAX                                                          (8)

#if (FW_TASK_MAX % 8) != 0
#error Framework Task Max Num Config Error, At Line !
#endif

/**
 *******************************************************************************
 * @brief        debug framework task queue size
 *******************************************************************************
 */
#define FW_TASK_QUEUE_SIZE                                     (2*FW_TASK_MAX+1)

/**
 *******************************************************************************
 * @brief      define framework event
 *******************************************************************************
 */
enum _FRAMEWORK_EVENT
{
    FW_EVENT_NONE,
    FW_TICK_EVENT,
    FW_SIGNAL_EVENT,
    FW_DELAY_EVENT,
    FW_BEGIN_EVENT,
    FW_END_EVENT,
    FW_FLOW_EVENT,
    FW_TIMEOUT_EVENT,
    FW_INIT_EVENT,
    FW_FINI_EVENT,
    
    FW_SIGNAL_HANDLE_EVENT,
    
    FW_STREAM_TX_EVENT,
    FW_STREAM_CONNECT_TX_EVENT,
    FW_STREAM_DISCONNECT_TX_EVENT,
    FW_STREAM_TX_OVERFLOW_EVENT,
    FW_STREAM_TX_TIMEOUT_EVENT,
    FW_STREAM_TX_COMPLET_EVENT,
    
    FW_STREAM_RX_EVENT,
    FW_STREAM_CONNECT_RX_EVENT,
    FW_STREAM_DISCONNECT_RX_EVENT,
    FW_STREAM_RX_OVERFLOW_EVENT,
    FW_STREAM_RX_TIMEOUT_EVENT,
    FW_STREAM_RX_COMPLET_EVENT,
    FW_STREAM_RX_PARSE_EVENT,
    
    FW_DEVICE_TX_EVENT,
    FW_DEVICE_RX_EVENT,
};

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework config  */

/**********************************END OF FILE*********************************/
