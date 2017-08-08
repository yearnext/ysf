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
#include "hal_path.h"
    
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define hal uart id
 *******************************************************************************
 */ 
enum Define_Uart_ID
{
    MCU_UART_1 = 0,
    MCU_UART_2,
    MCU_UART_3,
    MCU_UART_4,
    MCU_UART_5,
};
    
/**
 *******************************************************************************
 * @brief      define hal uart config structure
 *******************************************************************************
 */ 
struct HalUartConfig
{
    uint8_t WordLen;
    uint8_t StopBits;
    uint8_t Parity;
    
    uint32_t Baud;
    
    struct HalCallback TxCallback;
    
    struct 
    {
        void (*Callback)(void*, uint16_t);
        void *Param;
    }RxCallback;
};

/**
 *******************************************************************************
 * @brief      define map deivce uart structure
 *******************************************************************************
 */ 
struct HalUartDevice
{
    uint8_t Port;
    uint8_t WordLen;
    uint8_t StopBits;
    uint8_t Parity;
    
    uint32_t Baud;
    
    struct HalCallback TxCallback;
    
    struct 
    {
        void (*Callback)(void*, uint16_t);
        void *Param;
    }RxCallback;
};

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define map api
 *******************************************************************************
 */ 
extern hal_err_t Map_Uart_Open(uint8_t);
extern hal_err_t Map_Uart_Close(uint8_t);
extern hal_err_t Map_Uart_Init(uint8_t, struct HalUartConfig*);
extern hal_err_t Map_Uart_SetTxCallback(uint8_t, void (*)(void*), void*);
extern hal_err_t Map_Uart_SetRxCallback(uint8_t, void (*)(void*, uint16_t), void*);
extern hal_err_t Map_Uart_Fini(uint8_t);
extern hal_err_t Map_Uart_SendData(uint8_t, uint16_t);
extern hal_err_t Map_Uart_ReceiveData(uint8_t, uint16_t*);

/**
 *******************************************************************************
 * @brief      define hal api
 *******************************************************************************
 */ 
extern __INLINE hal_err_t Hal_Uart_Open(struct HalUartDevice*);
extern __INLINE hal_err_t Hal_Uart_Close(struct HalUartDevice*);
extern __INLINE hal_err_t Hal_Uart_Init(struct HalUartDevice*);
extern hal_err_t Hal_Uart_SetTxCallback(struct HalUartDevice*, void (*)(void*), void*);
extern hal_err_t Hal_Uart_SetRxCallback(struct HalUartDevice*, void (*)(void*, uint16_t), void*);
extern __INLINE hal_err_t Hal_Uart_Fini(struct HalUartDevice*);
extern hal_err_t Hal_Uart_SendData(struct HalUartDevice*, uint16_t);
extern hal_err_t Hal_Uart_ReceiveData(struct HalUartDevice*, uint16_t*);
extern hal_err_t Hal_Uart_TxConnect(struct HalUartDevice*);
extern hal_err_t Hal_Uart_TxDisconnect(struct HalUartDevice*);
extern hal_err_t Hal_Uart_RxConnect(struct HalUartDevice*);
extern hal_err_t Hal_Uart_RxDisconnect(struct HalUartDevice*);
extern hal_err_t Hal_Uart_GetTxCompletFlag(struct HalUartDevice*, uint8_t*);
extern hal_err_t Hal_Uart_ClrTxCompletFlag(struct HalUartDevice*);
extern hal_err_t Hal_Uart_GetRxCompletFlag(struct HalUartDevice*, uint8_t*);
extern hal_err_t Hal_Uart_ClrRxCompletFlag(struct HalUartDevice*);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** map uart component */

/**********************************END OF FILE*********************************/
