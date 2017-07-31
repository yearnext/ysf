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
 * @file       fw_tick.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework tick component head files
 * @par        paltform                                  
 *                 Windows
 * @par        compiler									                         
 * 				   GCC
 *******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 *******************************************************************************
 */

/**
 * @defgroup framework tick component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_TICK_H__
#define __FRAMEWORK_TICK_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @note        define tick max value
 *******************************************************************************
 */
#define FW_TICK_MAX                                               (0xFFFFFFFFUL)
    
/**
 *******************************************************************************
 * @note        define tick preiod
 *******************************************************************************
 */
#define FW_TICK_PREIOD                                                       (1)

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_TICK_COMPONENT
extern void Fw_Tick_InitComponent(void);
extern void Fw_Tick_Inc(void);
extern uint32_t Fw_Tick_GetInfo(void);
extern uint32_t Fw_Tick_CalPastTick(uint32_t, uint32_t);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework tick component */

/**********************************END OF FILE*********************************/
