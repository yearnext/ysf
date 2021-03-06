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
 * @file       map_spi.h                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-08                                                      *
 * @brief      mcu spi application component head files                        *
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
 * @defgroup map spi component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAP_SPI_H__
#define __MAP_SPI_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/  
#include "hal_spi.h"
    
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define map spi api
 *******************************************************************************
 */ 
extern const struct Map_SPI_Opera map_spi_api;

/* Exported functions --------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** map spi component */

/**********************************END OF FILE*********************************/
