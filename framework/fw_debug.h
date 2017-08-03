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
#include "fw_stream.h"
#include <stdarg.h>

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define debug component filling mode
 *******************************************************************************
 */
#define USE_DEBUG_COMPONENT_FILLING_MODE                                     (1)
   
/**
 *******************************************************************************
 * @brief      define hardware interface
 *******************************************************************************
 */
#define DebugTxConnectHandle                     (NULL)
#define DebugTxDisconnectHandle                  (NULL)
#define DebugTxOutputHandle                      (NULL)

#define DebugRxConnectHandle                     (NULL)
#define DebugRxDisconnectHandle                  (NULL)
#define DebugRxIntputHandle                      (NULL)
      
#define DebugDeviceFiniHandle                    (NULL)
#define DebugDeviceInitHandle                    (NULL)
     
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

struct Fw_DebugBlock
{
    struct Fw_FifoStream Tx;
    struct Fw_FifoStream Rx;
};

/* Exported variables --------------------------------------------------------*/
extern struct Fw_DebugBlock DebugBlock;

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

#define log(str, ...)    Fw_Debug_Write(DEBUG_OUTPUT_NORMAL_MESSAGE, str, ##__VA_ARGS__)
#define log_e(str, ...)  Fw_Debug_Write(DEBUG_OUTPUT_ERROR_MESSAGE, str, ##__VA_ARGS__)
#define log_w(str, ...)  Fw_Debug_Write(DEBUG_OUTPUT_WARNING_MESSAGE, str, ##__VA_ARGS__)
#define log_d(str, ...)  Fw_Debug_Write(DEBUG_OUTPUT_NORMAL_MESSAGE, str, ##__VA_ARGS__)

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

/** @}*/     /** framework debug component */

/**********************************END OF FILE*********************************/
