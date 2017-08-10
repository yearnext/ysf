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
 * @file       hal_uartstream.h                                                *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-08                                                      *
 * @brief      hal uart stream component head files                            *
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
#ifndef __HAL_UART_STREAM_H__
#define __HAL_UART_STREAM_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "map_uart.h"
#include "fw_stream.h"
#include "fw_timer.h"
    
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define uart stream
 *******************************************************************************
 */
struct Fw_UartStream
{
    struct Fw_FifoStream TxStream;
    struct Fw_FifoStream RxStream;
    
    struct HalUartDevice Device;
    struct Fw_Timer Timer;

    enum
    {
        UART_STREAM_INIT_STATE,
        UART_STREAM_SEND_STATE,
        UART_STREAM_SLEEP_STATE,
        UART_STREAM_COMPLET_STATE,
    }State;
};
    
/* Exported constants --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define stream opera
 *******************************************************************************
 */
extern const struct _FwStreamDeviceOpera UartStreamDeviceOpera;

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       hal uart stream apis
 *******************************************************************************
 */
extern void Hal_UartStream_Send(void*);
extern void Hal_UartStream_Receive(void*, uint8_t);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
