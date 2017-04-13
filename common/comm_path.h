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
 * @date       2017-03-07                                                      *
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
#ifndef _COMM_TOOLS_PATH
#define _COMM_TOOLS_PATH                      "../common/comm_tools.h"	
#endif
    
#ifndef _COMM_TYPE_PATH
#define _COMM_TYPE_PATH         		      "../common/comm_type.h"
#endif

/**
 *******************************************************************************
 * @brief      compiler path
 *******************************************************************************
 */	
#ifndef _COMPILER_PATH
#define _COMPILER_PATH                        "../common/compiler/compiler.h"
#endif

#ifndef _ARMCC5_COMPILER_PATH
#define _ARMCC5_COMPILER_PATH                 "../common/compiler/armcc5/compiler_armcc5.h"
#endif

#ifndef _ARMCC6_COMPILER_PATH
#define _ARMCC6_COMPILER_PATH                 "../common/compiler/armcc6/compiler_armcc6.h"
#endif

#ifndef _ICCARM_COMPILER_PATH
#define _ICCARM_COMPILER_PATH                 "../common/compiler/iccarm/compiler_iar_arm.h"
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** common path  */

/**********************************END OF FILE*********************************/
