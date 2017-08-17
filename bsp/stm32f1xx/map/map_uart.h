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
 * @file       map_uart.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-08                                                      *
 * @brief      mcu uart application component head files                       *
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
 * @defgroup map uart component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAP_UART_H__
#define __MAP_UART_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/  
#include "hal_uart.h"
    
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define map api
 *******************************************************************************
 */ 
extern void Map_Uart_Open(uint8_t);
extern void Map_Uart_Close(uint8_t);
extern void Map_Uart_Init(uint8_t, void*);
extern void Map_Uart_Fini(uint8_t);
extern void Map_Uart_SetTxCallback(uint8_t, void (*)(void*), void*);
extern void Map_Uart_SetRxCallback(uint8_t, void (*)(void*, uint8_t), void*);
extern void Map_Uart_SendData(uint8_t, uint8_t);
extern uint8_t Map_Uart_ReceiveData(uint8_t);
extern void Map_Uart_TxConnect(uint8_t);
extern void Map_Uart_TxDisconnect(uint8_t);
extern void Map_Uart_RxConnect(uint8_t);
extern void Map_Uart_RxDisconnect(uint8_t);
extern bool Map_Uart_IsTxComplet(uint8_t);
extern bool Map_Uart_IsRxComplet(uint8_t);

extern void Map_Uart_API_Register(void**);

/**
 *******************************************************************************
 * @brief      define test api
 *******************************************************************************
 */ 
extern void Hal_Uart_Test(void);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** map uart component */

/**********************************END OF FILE*********************************/
