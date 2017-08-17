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
#include "fw_uartstream.h"
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
static uint8_t BufferCache[FW_DEBUG_BUFFER_SIZE];
static bool StreamInitFlag = false;

static struct Fw_UartStream DebugStream;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_DEBUG_COMPONENT
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
    struct Fw_UartStream_Config config;
    
    static uint8_t TxBuffer[FW_DEBUG_BUFFER_SIZE];
    static uint8_t RxBuffer[FW_DEBUG_BUFFER_SIZE];
    
    Fw_Fifo_t TxFifo = {TxBuffer, FW_DEBUG_BUFFER_SIZE};
    Fw_Fifo_t RxFifo = {RxBuffer, FW_DEBUG_BUFFER_SIZE};
    
    //< uart stream hardware param init
    config.Device.Port = MCU_UART_1;
    config.Device.Group = 0;
    config.Device.Baud = 115200;
    config.Device.WordLen = MCU_UART_WORD_LEN_8B;
    config.Device.Priority = MCU_UART_PARTY_NONE;
    config.Device.StopBits = MCU_UART_STOP_BITS_1;
    config.Device.TxConfig = MCU_UART_ENABLE_TX_ISR;
    config.Device.RxConfig = MCU_UART_ENABLE_RX_ISR;
    config.Device.Parity = 1;

    //< uart stream hardware call back config
    config.Device.RxCallback.Callback = Fw_UartStream_Receive;
    config.Device.RxCallback.Param = (void *)&DebugStream;
        
    config.Device.TxCallback.Callback = Fw_UartStream_Send;
    config.Device.TxCallback.Param = (void *)&DebugStream;
    
    //< uart stream tx pipe config
    config.Tx.Buffer = (void *)&TxFifo;
    config.Tx.Buf_Ops = (struct Fw_Stream_Buffer_Opera *)&FwStreamFifoOpera;
    config.Tx.Callback = NULL;
        
    config.Tx.Rx.Connect = Fw_UartStream_TxConnect;
    config.Tx.Rx.Disconnect = Fw_UartStream_TxDisconnect;
    config.Tx.Rx.InOut = Fw_UartStream_TxOut;
    config.Tx.Rx.IsReady = true;
    config.Tx.Rx.Param = (void *)&DebugStream;
        
    config.Tx.Tx.Connect = NULL;
    config.Tx.Tx.Disconnect = NULL;
    config.Tx.Tx.InOut = NULL;
    config.Tx.Tx.IsReady = true;
    config.Tx.Tx.Param = (void *)&DebugStream;
        
    //< uart stream tx pipe config
    config.Rx.Buffer = (void *)&RxFifo;
    config.Rx.Buf_Ops = (struct Fw_Stream_Buffer_Opera *)&FwStreamFifoOpera;
    config.Rx.Callback = NULL;
        
    config.Rx.Rx.Connect = NULL;
    config.Rx.Rx.Disconnect = NULL;
    config.Rx.Rx.InOut = NULL;
    config.Rx.Rx.IsReady = true;
    config.Rx.Rx.Param = (void *)&DebugStream;
        
    config.Rx.Tx.Connect = Fw_UartStream_RxConnect;
    config.Rx.Tx.Disconnect = Fw_UartStream_RxDisconnect;
    config.Rx.Tx.InOut = Fw_UartStream_RxIn;
    config.Rx.Tx.IsReady = true;
    config.Rx.Tx.Param = (void *)&DebugStream;

    Fw_UartStream_Init(&DebugStream, (void *)&config);

    StreamInitFlag = true;
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
	
    if(StreamInitFlag == false)
    {
        return;
    }
    
    va_start(args, str);
    len = Fw_Debug_FillHeadInfo(BufferCache, type);
    len += (uint8_t)vsprintf((char *)&BufferCache[len], str, args);
    va_end(args);
    
    Fw_Stream_Write(&DebugStream.Tx, BufferCache, len);
}

/**
 *******************************************************************************
 * @brief       debug put mcu info
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Debug_PutMcuInfo(void)
{
    log("Framework Version: %s_%s_%s \r\n", _FRAMEWORK_VERSION, __DATE__, __TIME__);
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
__INLINE void Fw_AssertFailed(uint8_t *file, uint32_t line)
{
    log_e("Assert Failed At %s, %ld! \n", file, line);
}

#endif

/** @}*/     /** framework debug component */

/**********************************END OF FILE*********************************/
