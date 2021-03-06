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
 * @file       fw_debug.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      framework debug component head files                            *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                  						                           *
 *******************************************************************************
 */

/**
 * @defgroup framework debug component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_DEBUG_H__
#define __FRAMEWORK_DEBUG_H__

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
#ifdef USE_FRAMEWORK_DEBUG_COMPONENT
#define USE_DEBUG_COMPONENT                                                  (1)

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
#define USE_DEBUG_COMPONENT                                                 (0)
#endif

/**
 *******************************************************************************
 * @brief      define debug component filling mode
 *******************************************************************************
 */
#define USE_DEBUG_COMPONENT_FILLING_MODE                                     (1)
   
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define debug output message type
 *******************************************************************************
 */
enum _DEBUG_MESSAGE_TYPE
{
	DEBUG_OUTPUT_ERROR_MESSAGE,
	DEBUG_OUTPUT_WARNING_MESSAGE,
	DEBUG_OUTPUT_NORMAL_MESSAGE,
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      debug component init function
 *******************************************************************************
 */  
extern void Fw_Debug_InitComponent(void);

/**
 *******************************************************************************
 * @brief      debug component log message output function
 *******************************************************************************
 */ 
extern void Fw_Debug_Write(enum _DEBUG_MESSAGE_TYPE, const char*, ...); 

#if USE_DEBUG_COMPONENT
#define log(str, ...)    Fw_Debug_Write(DEBUG_OUTPUT_NORMAL_MESSAGE, str, ##__VA_ARGS__)
#define log_e(str, ...)  Fw_Debug_Write(DEBUG_OUTPUT_ERROR_MESSAGE, str, ##__VA_ARGS__)
#define log_w(str, ...)  Fw_Debug_Write(DEBUG_OUTPUT_WARNING_MESSAGE, str, ##__VA_ARGS__)
#define log_d(str, ...)  Fw_Debug_Write(DEBUG_OUTPUT_NORMAL_MESSAGE, str, ##__VA_ARGS__)
#else
#define log(str, ...)
#define log_e(str, ...)
#define log_w(str, ...)
#define log_d(str, ...)
#endif

/**
 *******************************************************************************
 * @brief      debug component put init message
 *******************************************************************************
 */ 
extern __INLINE void Fw_Debug_PutMcuInfo(void);

/**
 *******************************************************************************
 * @brief      debug component assert failed function
 *******************************************************************************
 */ 
extern __INLINE void Fw_AssertFailed(uint8_t*, uint32_t);

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */    
#if USE_DEBUG_COMPONENT
#define _FW_ASSERT(expr) _ST(if(expr) { (Fw_AssertFailed((uint8_t *)__FILE__, __LINE__)); })
#else
#define _FW_ASSERT(expr)
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework debug component */

/**********************************END OF FILE*********************************/
