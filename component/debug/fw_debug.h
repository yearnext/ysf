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
 * @brief      framework debug component header files                          *
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
 * @defgroup framework debug component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_DEBUG_COMPONENT_H__
#define __FRAMEWORK_DEBUG_COMPONENT_H__

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
#if USE_FRAMEWORK_DEBUG_COMPONENT
#define USE_FRAMEWORK_DEBUG_API                                              (1)
#else
#define USE_FRAMEWORK_DEBUG_API                                              (0)
#endif
    
/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
#define USE_FRAMEWORK_DEBUG_API                                              (1)
#endif
 
/**
 *******************************************************************************
 * @brief       define assert macros
 *******************************************************************************
 */ 
#if defined(USE_FRAMEWORK_DEBUG) && USE_FRAMEWORK_DEBUG
#define fw_assert(expr) ((expr) ? fw_assert_failed((uint8_t *)__FILE__, __LINE__) :(void)0 )
#else
#define fw_assert(expr)
#endif 

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define framework debug api
 *******************************************************************************
 */ 
#if USE_FRAMEWORK_DEBUG_API
struct _DEBUG_API
{
    fw_err_t (*Init)(void);
    void (*AssertFailed)(uint8_t*, uint32_t);
};
#endif
      
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define framework debug function interface
 *******************************************************************************
 */ 
#if USE_FRAMEWORK_DEBUG_API
extern fw_err_t fw_debug_init(void);
extern void fw_assert_failed(uint8_t*, uint32_t);
#endif        

/**@} */

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework debug component  */

/**********************************END OF FILE*********************************/
