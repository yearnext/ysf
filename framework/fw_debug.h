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
 * @file       debug.h                                                         *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      debug component header files                                    *
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
 * @defgroup debug component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_COMPONENT_H__
#define __DEBUG_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH

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
#define USE_DEBUG_COMPONENT                                                  (1)
#endif
 
/**
 *******************************************************************************
 * @brief       define assert macros
 *******************************************************************************
 */ 
#ifndef USE_FRAMEWORK_DEBUG
#define Fw_Assert(expr)
#else
#define Fw_Assert(expr)
#endif 

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define debug interface
 *******************************************************************************
 */ 
#if USE_DEBUG_COMPONENT
typedef struct
{
    fw_err_t (*Init)(void);
    void (*AssertFailed)(uint8_t*, uint32_t);
}DebugComponentInterface;
#endif
      
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define debug function api
 *******************************************************************************
 */ 
#if USE_DEBUG_COMPONENT
extern fw_err_t InitDebugComponent(void);
extern void     AssertFailed(uint8_t*, uint32_t);

/**
 *******************************************************************************
 * @brief        define framework debug interface
 *******************************************************************************
 */
#define fw_debug_init                        InitDebugComponent
#define fw_debug_assert                      AssertFailed
#else
#define fw_debug_init()                        
#define fw_debug_assert(a,b)                      
#endif        

/**@} */

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** debug component */

/**********************************END OF FILE*********************************/
