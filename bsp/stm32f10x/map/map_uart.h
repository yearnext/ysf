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
#if USE_UART_COMPONENT
/**
 *******************************************************************************
 * @brief      define map api
 *******************************************************************************
 */ 
extern hal_err_t Map_Uart_Open(uint8_t);
extern hal_err_t Map_Uart_Close(uint8_t);
extern hal_err_t Map_Uart_Init(uint8_t, struct Hal_Uart_Device*);
extern hal_err_t Map_Uart_SetTxCallback(uint8_t, void (*)(void*), void*);
extern hal_err_t Map_Uart_SetRxCallback(uint8_t, void (*)(void*, uint8_t), void*);
extern hal_err_t Map_Uart_Fini(uint8_t);
extern hal_err_t Map_Uart_SendData(uint8_t, uint8_t);
extern hal_err_t Map_Uart_ReceiveData(uint8_t, uint8_t*);

/**
 *******************************************************************************
 * @brief      define hal api
 *******************************************************************************
 */ 
extern __INLINE hal_err_t Hal_Uart_Open(struct Hal_Uart_Device*);
extern __INLINE hal_err_t Hal_Uart_Close(struct Hal_Uart_Device*);
extern __INLINE hal_err_t Hal_Uart_Init(struct Hal_Uart_Device*);
extern hal_err_t Hal_Uart_SetTxCallback(struct Hal_Uart_Device*, void (*)(void*), void*);
extern hal_err_t Hal_Uart_SetRxCallback(struct Hal_Uart_Device*, void (*)(void*, uint8_t), void*);
extern __INLINE hal_err_t Hal_Uart_Fini(struct Hal_Uart_Device*);
extern hal_err_t Hal_Uart_SendData(struct Hal_Uart_Device*, uint8_t);
extern hal_err_t Hal_Uart_ReceiveData(struct Hal_Uart_Device*, uint8_t*);
extern hal_err_t Hal_Uart_TxConnect(struct Hal_Uart_Device*);
extern hal_err_t Hal_Uart_TxDisconnect(struct Hal_Uart_Device*);
extern hal_err_t Hal_Uart_RxConnect(struct Hal_Uart_Device*);
extern hal_err_t Hal_Uart_RxDisconnect(struct Hal_Uart_Device*);
extern hal_err_t Hal_Uart_GetTxCompletFlag(struct Hal_Uart_Device*, uint8_t*);
extern hal_err_t Hal_Uart_ClrTxCompletFlag(struct Hal_Uart_Device*);
extern hal_err_t Hal_Uart_GetRxCompletFlag(struct Hal_Uart_Device*, uint8_t*);
extern hal_err_t Hal_Uart_ClrRxCompletFlag(struct Hal_Uart_Device*);

/**
 *******************************************************************************
 * @brief      define test api
 *******************************************************************************
 */ 
extern void Hal_Uart_Test(void);

#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** map uart component */

/**********************************END OF FILE*********************************/
