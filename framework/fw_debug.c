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
 * @file       fw_debug.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework debug component source files
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
 * @defgroup framework debug component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_debug.h"
#include "fw_tick.h"
#include "fw_timer.h"
#include "fw_stream.h"
#include "hal_uartstream.h"
#include <string.h>
#include <stdio.h>

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       config debug buffer size
 *******************************************************************************
 */
#define FW_DEBUG_BUFFER_SIZE                                                (128)

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       event handler
 * @note        user config
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_DEBUG_COMPONENT
static uint8_t TxBuffer[FW_DEBUG_BUFFER_SIZE];
static uint8_t RxBuffer[FW_DEBUG_BUFFER_SIZE];
static uint8_t BufferCache[FW_DEBUG_BUFFER_SIZE];

static struct Fw_UartStream DebugStream = 
{
    //< config hardware param
    .Device.Port = MCU_UART_1,
    .Device.Baud = 115200,
    .Device.Parity = MCU_UART_PARTY_NONE,
    .Device.StopBits = MCU_UART_STOP_BITS_1,
    .Device.WordLen = MCU_UART_WORD_LEN_8B,

    .Device.RxConfig = MCU_UART_DISABLE_RX,
    .Device.TxConfig = MCU_UART_DISABLE_TX,
    
    .Device.RxCallback.Callback = Hal_UartStream_Receive,
    .Device.RxCallback.Param    = (void *)&DebugStream,

    .Device.TxCallback.Callback = Hal_UartStream_Send,
    .Device.TxCallback.Param    = (void *)&DebugStream,
        
    //< init tx stream
    .TxStream.Stream.Tx.Param = (void*)&DebugStream,
    .TxStream.Stream.Tx.InOut = NULL,
    .TxStream.Stream.Tx.Connect = NULL,
    .TxStream.Stream.Tx.Disconnect = NULL,
	.TxStream.Stream.Rx.Param  = (void*)&DebugStream,
    .TxStream.Stream.Rx.InOut = Hal_UartStream_TxOut,
    .TxStream.Stream.Rx.Connect = Hal_UartStream_TxConnect,
    .TxStream.Stream.Rx.Disconnect = Hal_UartStream_TxDisconnect,

    //< init rx stream
	.RxStream.Stream.Tx.Param = (void*)&DebugStream,
    .RxStream.Stream.Tx.InOut = NULL,
    .RxStream.Stream.Tx.Connect = Hal_UartStream_RxConnect,
    .RxStream.Stream.Tx.Disconnect = Hal_UartStream_RxDisconnect,
	.RxStream.Stream.Rx.Param = (void*)&DebugStream,
    .RxStream.Stream.Rx.InOut = NULL,
    .RxStream.Stream.Rx.Connect = NULL,
    .RxStream.Stream.Rx.Disconnect = NULL,
};

#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#ifdef USE_FRAMEWORK_DEBUG_COMPONENT
/**
 *******************************************************************************
 * @brief       debug component init
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Debug_InitComponent(void)
{
    //< init fifo
    _FifoInitType TxFifo = {TxBuffer, FW_DEBUG_BUFFER_SIZE};
    _FifoInitType RxFifo = {RxBuffer, FW_DEBUG_BUFFER_SIZE};
    
    //< init tx stream
    Fw_Stream_Init((struct Fw_Stream *)&DebugStream.TxStream, 
                   (struct _FwStreamBufferOpera *)&StreamFifoOpera, 
                   (void *)&TxFifo);

    //< init rx stream
    Fw_Stream_Init((struct Fw_Stream *)&DebugStream.RxStream, 
                   (struct _FwStreamBufferOpera *)&StreamFifoOpera,  
                   (void *)&RxFifo);
    
    Hal_UartStream_Init(&DebugStream.Device);
                   
    Fw_Stream_TxConnect((struct Fw_Stream *)&DebugStream.TxStream);
    Fw_Stream_RxConnect((struct Fw_Stream *)&DebugStream.TxStream);
                   
    Fw_Stream_TxConnect((struct Fw_Stream *)&DebugStream.RxStream);
    Fw_Stream_RxConnect((struct Fw_Stream *)&DebugStream.RxStream);
}

/**
 *******************************************************************************
 * @brief       filling debug head info
 * @param       [in/out]  *pipeLine pipeline
 * @param       [in/out]  type      debug output info type
 * @return      [in/out]  0         filling error
 * @return      [in/out]  uint8_t   filling num
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
uint8_t Fw_Debug_FillHeadInfo(uint8_t *buffer, enum _DEBUG_MESSAGE_TYPE type)
{
    uint32_t tick = Fw_Tick_GetInfo();

	if(type == DEBUG_OUTPUT_ERROR_MESSAGE)
	{
		return (uint8_t)sprintf((char *)buffer, "[Error][Tick:%ld]", tick);
	}
	else if(type == DEBUG_OUTPUT_WARNING_MESSAGE)
	{
		return (uint8_t)sprintf((char *)buffer, "[Warning][Tick:%ld]", tick);
	}
	else
	{
		return (uint8_t)sprintf((char *)buffer, "[Tick:%ld]", tick);
	}
}

/**
 *******************************************************************************
 * @brief       write debug message
 * @param       [in/out]  *str      output string
 * @param       [in/out]  args      string param
 * @param       [in/out]  type      debug output message type
 * @return      [in/out]  0         filling error
 * @return      [in/out]  uint8_t   filling num
 * @note        None
 *******************************************************************************
 */
void Fw_Debug_Write(enum _DEBUG_MESSAGE_TYPE type, const char *str, ...)
{
	uint8_t len = 0;
    va_list args;
	
    va_start(args, str);
    len = Fw_Debug_FillHeadInfo(BufferCache, type);
    len += (uint8_t)vsprintf((char *)&BufferCache[len], str, args);
    va_end(args);
    
    Fw_Stream_Write((struct Fw_Stream *)&DebugStream.TxStream, BufferCache, len);
}

void Fw_Debug_PutMcuInfo(void)
{
    log("Framework Version: %s \r\n", _FRAMEWORK_VERSION);
}

/**
 *******************************************************************************
 * @brief       assert failed function
 * @param       [in/out]  *file    file name
 * @param       [in/out]  len      code line
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_AssertFailed(uint8_t *file, uint32_t line)
{
    log_e("Assert Failed At %s, %ld! \n", file, line);
}

#endif

/** @}*/     /** framework debug component */

/**********************************END OF FILE*********************************/
