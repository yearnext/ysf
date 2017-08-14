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
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_GPIO_COMPONENT
/**
 *******************************************************************************
 * @brief      define map api
 *******************************************************************************
 */ 
extern hal_err_t Map_GPIO_Open(uint8_t);
extern hal_err_t Map_GPIO_Close(uint8_t);
extern hal_err_t Map_GPIO_Init(uint8_t, uint8_t, uint8_t, uint8_t);
extern hal_err_t Map_GPIO_Fini(uint8_t, uint8_t);
extern hal_err_t Map_GPIO_Set(uint8_t, uint8_t);
extern hal_err_t Map_GPIO_Clear(uint8_t, uint8_t);
extern hal_err_t Map_GPIO_GetIntputStatus(uint8_t, uint8_t, uint16_t*);
extern hal_err_t Map_GPIO_GetOutputStatus(uint8_t, uint8_t, uint16_t*);
extern hal_err_t Map_GPIO_Toggle(uint8_t, uint8_t);
extern hal_err_t Map_GPIO_Write(uint8_t, uint8_t, uint16_t, uint8_t);
extern hal_err_t Map_GPIO_Read(uint8_t, uint8_t, uint16_t*, uint8_t);
extern hal_err_t Map_GPIO_Control(struct Hal_GPIO_Device*, uint8_t, void*);

/**
 *******************************************************************************
 * @brief      define hal api
 *******************************************************************************
 */ 
extern __INLINE hal_err_t Hal_GPIO_Open(struct Hal_GPIO_Device*);
extern __INLINE hal_err_t Hal_GPIO_Close(struct Hal_GPIO_Device*);
extern __INLINE hal_err_t Hal_GPIO_Init(struct Hal_GPIO_Device*);
extern __INLINE hal_err_t Hal_GPIO_Fini(struct Hal_GPIO_Device*);
extern __INLINE hal_err_t Hal_GPIO_Set(struct Hal_GPIO_Device*);
extern __INLINE hal_err_t Hal_GPIO_Clear(struct Hal_GPIO_Device*);
extern __INLINE hal_err_t Hal_GPIO_GetIntputStatus(struct Hal_GPIO_Device*, uint16_t*);
extern __INLINE hal_err_t Hal_GPIO_GetOutputStatus(struct Hal_GPIO_Device*, uint16_t*);
extern __INLINE hal_err_t Hal_GPIO_Toggle(struct Hal_GPIO_Device*);
extern __INLINE hal_err_t Hal_GPIO_Write(struct Hal_GPIO_Device*, struct Hal_GPIO_Param*);
extern __INLINE hal_err_t Hal_GPIO_Read(struct Hal_GPIO_Device*, struct Hal_GPIO_Param*);
extern __INLINE hal_err_t Hal_GPIO_Control(struct Hal_GPIO_Device*, uint8_t, void*);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** map gpio component */

/**********************************END OF FILE*********************************/
