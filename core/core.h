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
 * @file       core.h                                                          *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      core head files                                                 *
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
 * @defgroup frameowrk core
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _FRAMEWORK_CORE_H__
#define _FRAMEWORK_CORE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
    
/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_INTERFACE_PATH
#include _HAL_PATH
#include _HAL_INTERFACE_PATH

/* Exported macro ------------------------------------------------------------*/ 
/**
 *******************************************************************************
 * @brief        define core interface
 *******************************************************************************
 */
typedef struct 
{
    uint8_t *Version;
    
    void (*Init)(void);
    void (*Start)(void);
    
    FrameworkComponentInterface Component;

    FrameworkHalInterface       Hal;
}CoreInterface;
/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        core interface
 *******************************************************************************
 */
extern const CoreInterface Core;

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        core api
 *******************************************************************************
 */
void InitCoreScheduling(void);
void StartCoreScheduling(void);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework core interface */

/**********************************END OF FILE*********************************/
