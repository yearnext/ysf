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
 * @file       fw_uartstream.h                                                 *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-08                                                      *
 * @brief      framework uart stream component head files                      *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_UART_STREAM_H__
#define __FRAMEWORK_UART_STREAM_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "hal_uart.h"
#include "fw_stream.h"
#include "fw_timer.h"
    
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define framework uart stream
 *******************************************************************************
 */
struct Fw_UartStream
{
    struct Fw_Stream Tx;
    struct Fw_Stream Rx;
     
    Hal_Uart_Handle Device;
    struct Fw_Timer Timer;

    enum
    {
        UART_STREAM_INIT_STATE,
        UART_STREAM_SEND_STATE,
        UART_STREAM_SLEEP_STATE,
        UART_STREAM_COMPLET_STATE,
    }State;
};
    
//struct Fw_UartStream_Config
//{
//    Fw_Stream_InitType Tx;
//    Fw_Stream_InitType Rx;
//    struct Hal_Uart_Config Device;
//};
        
/* Exported constants --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define framework stream opera
 *******************************************************************************
 */
extern const struct _FwStreamDeviceOpera UartStreamDeviceOpera;

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework uart stream apis
 *******************************************************************************
 */
extern __INLINE void Fw_UartStream_Init(struct Fw_UartStream*);
extern __INLINE void Fw_UartStream_Fini(struct Fw_UartStream*);
extern void Fw_UartStream_TxConnect(void*);
extern void Fw_UartStream_TxDisconnect(void*);
extern void Fw_UartStream_RxConnect(void*);
extern void Fw_UartStream_RxDisconnect(void*);
extern void Fw_UartStream_TxOut(void*);
extern void Fw_UartStream_RxIn(void*);
extern void Fw_UartStream_Send(void*);
extern void Fw_UartStream_Receive(void*, uint8_t);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
