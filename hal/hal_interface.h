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
 * @file       hal_interface.h                                                 *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-18                                                      *
 * @brief      hal interface head files                                        *
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
 * @defgroup hal interface
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_INTERFACE_H__
#define __HAL_INTERFACE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/  
#include "core_path.h"
#include _HAL_PATH
#include _HAL_GPIO_PATH   
#include _HAL_TIMER_PATH    

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        define hal interface
 *******************************************************************************
 */
typedef struct
{
    char *Version;
    
#if USE_MAP_GPIO_COMPONENT
    HalGPIOInterface GPIO;
#endif  

#if USE_MAP_TIMER_COMPONENT
    HalTimerInterface Timer;
#endif
}FrameworkHalInterface;    
    
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal interface  */

/**********************************END OF FILE*********************************/
