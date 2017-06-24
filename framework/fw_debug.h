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
    
/* Framework debug -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      debug config
 *******************************************************************************
 */    
#if USE_GLOBAL_DEBUG
#include <stdio.h>

#define log(a, ...)     printf(a, ##__VA_ARGS__)
#else
#define log(a, ...)
#endif
                             
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework debug */

/**********************************END OF FILE*********************************/
