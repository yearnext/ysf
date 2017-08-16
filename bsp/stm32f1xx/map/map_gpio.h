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
 * @file       map_gpio.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-07                                                      *
 * @brief      mcu application gpio component head files                       *
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
 * @defgroup map gpio component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAP_GPIO_H__
#define __MAP_GPIO_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/  
#include "hal_gpio.h"
    
/* Exported macro ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define gpio init structure
 *******************************************************************************
 */ 
typedef struct
{
    uint8_t Port;
    uint8_t Pin;
    uint8_t Dir;
    uint8_t Mode;
}Map_GPIO_InitType;
    
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define map api
 *******************************************************************************
 */ 
extern void Map_GPIO_Open(uint8_t);
extern void Map_GPIO_Close(uint8_t);
extern void Map_GPIO_Init(uint8_t, uint8_t, uint8_t, uint8_t);
extern void Map_GPIO_Fini(uint8_t, uint8_t);
extern void Map_GPIO_Write(uint8_t, uint8_t, uint16_t, uint8_t);
extern void Map_GPIO_Read(uint8_t, uint8_t, uint8_t, uint16_t*, uint8_t);

extern void Map_GPIO_API_Register(void**);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** map gpio component */

/**********************************END OF FILE*********************************/
