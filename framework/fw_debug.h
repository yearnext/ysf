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
 * @file       fw_debug.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework debug head files
 * @par        paltform
 *                 Windows
 * @par        compiler
 *                 GCC
 *******************************************************************************
 * @note
 * 1.XXXXX
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
#include "fw_core.h"
#include <stdarg.h>

/* Exported macro ------------------------------------------------------------*/
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

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      debug component init function
 *******************************************************************************
 */  
extern void InitDebugComponent(void);

/**
 *******************************************************************************
 * @brief      login debug compoent device call back
 * @note       please login deivce function to debug component
 *******************************************************************************
 */  
extern fw_err_t LoginDebugSendByteCallBack(fw_err_t (*)(uint8_t));
extern fw_err_t LoginDebugISRSendByteCallBack(void (*sendByte)(uint8_t));
extern fw_err_t LoginDebugSendDataCallBack(void (*)(uint8_t*, uint8_t));

/**
 *******************************************************************************
 * @brief      debug component device isr handle call back function
 * @note       please add this function in device isr handle or main loop
 *******************************************************************************
 */ 
extern void DebugComponentISRCallBack(void);

/**
 *******************************************************************************
 * @brief      debug component log message output function
 *******************************************************************************
 */ 
#if USE_DEBUG_COMPONENT_FILLING_MODE
extern void WriteDebugMessage(enum _DEBUG_MESSAGE_TYPE, const char*, ...); 

#define log(str, ...)    WriteDebugMessage(DEBUG_OUTPUT_NORMAL_MESSAGE, str, ##__VA_ARGS__)
#define log_e(str, ...)  WriteDebugMessage(DEBUG_OUTPUT_ERROR_MESSAGE, str, ##__VA_ARGS__)
#define log_w(str, ...)  WriteDebugMessage(DEBUG_OUTPUT_WARNING_MESSAGE, str, ##__VA_ARGS__)
#define log_d(str, ...)  WriteDebugMessage(DEBUG_OUTPUT_NORMAL_MESSAGE, str, ##__VA_ARGS__)
#else 
extern void log(const char *str, ...);
extern void log_e(const char *str, ...);
extern void log_w(const char *str, ...);
extern void log_d(const char *str, ...);
#endif

/**
 *******************************************************************************
 * @brief      debug component assert failed function
 *******************************************************************************
 */ 
extern void Fw_AssertFailed(uint8_t*, uint32_t);

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */                                           
#define _FW_ASSERT(expr) _ST(if(expr) { (Fw_AssertFailed((uint8_t *)__FILE__, __LINE__)); })

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework debug */

/**********************************END OF FILE*********************************/
