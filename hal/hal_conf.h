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
 * @file       hal_conf.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-18                                                      *
 * @brief      hal conf head files                                             *
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
 * @defgroup hal config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_CONF_H__
#define __HAL_CONF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/    
#include "core_conf.h"
    
/* Exported types ------------------------------------------------------------*/   
/**
 *******************************************************************************
 * @brief       define hal version
 *******************************************************************************
 */
#define _HAL_VERSION                              "HAL_ALPHA_0.0.1_201704132135"
 
/**
 *******************************************************************************
 * @brief        debug configuration
 *******************************************************************************
 */
#if USE_HAL_DEBUG
    #include _FW_PATH
    #include _FW_DEBUG_COMPONENT_PATH
    
    #define hal_assert(expr)                                      _Assert(expr)
#else
    #define hal_assert(expr)
#endif
    
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal config */

/**********************************END OF FILE*********************************/
