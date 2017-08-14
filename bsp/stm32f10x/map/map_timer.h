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
 * @file       map_timer.h                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-08                                                      *
 * @brief      mcu timer application component head files                      *
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
 * @defgroup map timer component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAP_TIMER_H__
#define __MAP_TIMER_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/  
#include "hal_timer.h"
    
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief      define map api
 *******************************************************************************
 */ 
extern hal_err_t Map_Timer_Open(uint8_t);
extern hal_err_t Map_Timer_Close(uint8_t);
extern hal_err_t Map_Timer_Init(uint8_t, uint8_t, void*);
extern hal_err_t Map_Timer_SetUpCallback(uint8_t, void (*)(void*), void*);
extern hal_err_t Map_Timer_Start(uint8_t);
extern hal_err_t Map_Timer_Stop(uint8_t);

/**
 *******************************************************************************
 * @brief      define hal api
 *******************************************************************************
 */ 
extern __INLINE hal_err_t Hal_Timer_Open(struct Hal_Timer_Device*);
extern __INLINE hal_err_t Hal_Timer_Close(struct Hal_Timer_Device*);
extern __INLINE hal_err_t Hal_Timer_Init(struct Hal_Timer_Device*);
extern __INLINE hal_err_t Hal_Timer_SetUpCallback(struct Hal_Timer_Device*);
extern __INLINE hal_err_t Hal_Timer_Start(struct Hal_Timer_Device*);
extern __INLINE hal_err_t Hal_Timer_Stop(struct Hal_Timer_Device*);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** map timer component */

/**********************************END OF FILE*********************************/
