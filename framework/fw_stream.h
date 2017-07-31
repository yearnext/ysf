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
 * @file       fw_stream.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-07-30
 * @brief      framework stream component head files
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
 * @defgroup framework stream component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_STREAM_H__
#define __FRAMEWORK_STREAM_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
struct Fw_Stream_Opera
{
	void (*Init)(void);
	void (*Fini)(void);

	void (*Write)(uint8_t *, uint8_t);
	void (*Read)(uint8_t *, uint8_t);

	uint8_t (*GetTxLen)(void);
	uint8_t (*GetRxLen)(void);

	void (*GetTxBuffer)(uint8_t *, uint8_t);
	void (*GetRxBuffer)(uint8_t *, uint8_t);
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework stream component */

/**********************************END OF FILE*********************************/

