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
#ifndef __FRAMEWORK_DEBUG_H__
#define __FRAMEWORK_DEBUG_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_conf.h"
#include "core_path.h"
#include _FW_TYPE_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework debug component config
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_DEBUG_COMPONENT
#if USE_FRAMEWORK_DEBUG_COMPONENT
#define USE_FRAMEWORK_DEBUG_API (1)
#else
#define USE_FRAMEWORK_DEBUG_API (0)
#endif
    
/**
 *******************************************************************************
 * @brief       user config
 *******************************************************************************
 */
#else
#define USE_FRAMEWORK_DEBUG_API (1)
#endif
 
/**
 *******************************************************************************
 * @brief       define detecting null pointer macros
 *******************************************************************************
 */    
#define IS_PTR_NULL(ptr) ((ptr) == NULL)

/**
 *******************************************************************************
 * @brief       define assert macros
 *******************************************************************************
 */ 
#define fw_assert(expr) ((expr) ? ysf_assert_failed((uint8_t *)__FILE__, __LINE__) :(void)0 )
                             
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define framework debug api
 *******************************************************************************
 */ 
#if USE_FRAMEWORK_DEBUG_API
struct FRAMEWORK_DEBUG_API
{
    fw_err_t (*init)(void);
    void (*assert_failed)(uint8_t*, uint32_t);
};
#endif
      
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define ysf debug function interface
 *******************************************************************************
 */ 
#if USE_FRAMEWORK_DEBUG_API
extern fw_err_t ysf_debug_init(void);
extern void ysf_assert_failed(uint8_t*, uint32_t);
#endif        

/**@} */

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework debug component  */

/**********************************END OF FILE*********************************/