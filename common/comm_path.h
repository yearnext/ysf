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
 * @file       comm_path.h                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      common path head files                                          *
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
 * @defgroup common path
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMON_PATH_H__
#define __COMMON_PATH_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      common component path
 *******************************************************************************
 */
#define _COMM_TOOLS_PATH                      "../common/comm_tools.h"	
#define _COMM_TYPE_PATH         		      "../common/comm_type.h"

/**
 *******************************************************************************
 * @brief      compiler path
 *******************************************************************************
 */	
#define _COMPILER_PATH                        "../common/compiler/compiler.h"
#define _ARMCC5_COMPILER_PATH                 "../common/compiler/armcc5/compiler_armcc5.h"
#define _ARMCC6_COMPILER_PATH                 "../common/compiler/armcc6/compiler_armcc6.h"
#define _ICCARM_COMPILER_PATH                 "../common/compiler/iccarm/compiler_iar_arm.h"
    
/* Includes ------------------------------------------------------------------*/
#include _COMM_TOOLS_PATH
#include _COMM_TYPE_PATH
#include _COMPILER_PATH

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** common path  */

/**********************************END OF FILE*********************************/
