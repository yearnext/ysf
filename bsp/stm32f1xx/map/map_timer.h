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
///**
// *******************************************************************************
// * @brief      define set timer time mode param structure
// *******************************************************************************
// */ 
//struct Hal_Timer_Config
//{
//    uint8_t Port;
//    uint8_t Priority;
//    uint8_t Mode;
//	uint16_t Period;
//	uint16_t Prescaler;
//
//	struct Hal_Callback Callback;
//};

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define map api
 *******************************************************************************
 */ 
extern void Map_Timer_Open(uint8_t);
extern void Map_Timer_Close(uint8_t);
extern void Map_Timer_Init(uint8_t, void*);
extern void Map_Timer_Fini(uint8_t);
extern void Map_Timer_SetUpCallback(uint8_t, void (*)(void*), void*);
extern void Map_Timer_Start(uint8_t);
extern void Map_Timer_Stop(uint8_t);

extern void Map_Timer_API_Register(void**);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** map timer component */

/**********************************END OF FILE*********************************/
