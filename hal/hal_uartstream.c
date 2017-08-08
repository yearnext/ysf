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
 * @file       hal_uartstream.c                                                *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-08                                                      *
 * @brief      hal uart stream component source files                          *
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
* @defgroup hal uart stream component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "hal_uartstream.h"

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
static void Hal_UartStream_Init(struct Fw_Stream*);
static void Hal_UartStream_Fini(struct Fw_Stream*);   
static void Hal_UartStream_TxConnect(struct Fw_Stream*);
static void Hal_UartStream_TxDisconnect(struct Fw_Stream*);
static void Hal_UartStream_RxConnect(struct Fw_Stream*);
static void Hal_UartStream_RxDisconnect(struct Fw_Stream*);
static void Hal_UartStream_TxOut(struct Fw_Stream*);
static void Hal_UartStream_RxIn(struct Fw_Stream*);

const struct _FwStreamDeviceOpera *UartStreamDevice = 
{
    .Init = Hal_UartStream_Init,
    .Fini = Hal_UartStream_Fini,
    
    .Tx_Out = Hal_UartStream_TxOut,
    .Tx_Connect = Hal_UartStream_TxConnect,
    .Tx_Disconnect = Hal_UartStream_TxDisconnect,
    
    .Rx_In = Hal_UartStream_RxIn,
    .Rx_Connect = Hal_UartStream_RxConnect, 
    .Rx_Disconnect = Hal_UartStream_RxDisconnect,
};

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
static void Hal_UartStream_Init(struct Fw_Stream *stream)
{
	struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;

	Fw_Timer_Create(&uartStream->Timer, "Stream Timeout Timer", uartStream->TaskId, FW_TIMEOUT_EVENT, NULL);
    Hal_Uart_Open(&uartStream->Device);
	Hal_Uart_Init(&uartStream->Device);
}

static void Hal_UartStream_Fini(struct Fw_Stream *stream)
{
	struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;

	Hal_Uart_Fini(&uartStream->Device);
}

static void Hal_UartStream_TxConnect(struct Fw_Stream *stream)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;
    
    Hal_Uart_TxConnect(&uartStream->Device);
}

static void Hal_UartStream_TxDisconnect(struct Fw_Stream *stream)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;
    
    Hal_Uart_TxDisconnect(&uartStream->Device);
}

static void Hal_UartStream_RxConnect(struct Fw_Stream *stream)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;
    
    Hal_Uart_RxConnect(&uartStream->Device);
}

static void Hal_UartStream_RxDisconnect(struct Fw_Stream *stream)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;
    
    Hal_Uart_RxDisconnect(&uartStream->Device);
}

static void Hal_UartStream_TxOut(struct Fw_Stream *stream)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;	
}

static void Hal_UartStream_RxIn(struct Fw_Stream *stream)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;
}

#define UART_STREAM_SEND_INIT         (0)
#define UART_STREAM_SENDING           (1)
#define UART_STREAM_WAIT_SEND_COMPLET (2)

void Hal_UartStream_Send(struct Fw_Stream *stream)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;
    
    switch(uartStream->State)
    {
        case UART_STREAM_SEND_INIT:
        {
        _START_UART_STREAM_FLOW:
            uint8_t sendData;
            uartStream->Stream.Stream->Opera.Read(&uartStream->Stream.Stream, &sendData, 1);
			uartStream->State = UART_STREAM_SENDING;
        }
		case UART_STREAM_SENDING:
		{
			Hal_Uart_SendData(&uartStream->Device, sendData);
			uartStream->State = UART_STREAM_WAIT_SEND_COMPLET;
			//< Start timeout timer
            break;
        }
		case UART_STREAM_WAIT_SEND_COMPLET:
		{
			uint8_t flag;
			Hal_Uart_GetTxCompletFlag(&uartStream->Device, &flag);

			if(flag)
			{
				uartStream->State = UART_STREAM_SEND_INIT;
				//< stop timeout time
				goto _START_UART_STREAM_FLOW;
			}
			else
			{
				
			}
			
			break;
		}
    }
}

/** @}*/     /** hal uart stream component */

/**********************************END OF FILE*********************************/
