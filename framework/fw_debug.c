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
 * @file       fw_debug.c                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      framework debug component source files                          *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                  						                           *
 *******************************************************************************
 */
 
/**
 * @defgroup framework debug component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "fw_debug.h"
#include "fw_tick.h"
#include "fw_timer.h"
#include "fw_stream.h"
#include "fw_pipe.h"
#include "hal_device.h"
#include "hal_uart.h"

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       config debug buffer size
 *******************************************************************************
 */
#define FW_DEBUG_BUFFER_SIZE                                               (128)

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if USE_DEBUG_COMPONENT
/**
 *******************************************************************************
 * @brief       buffer cache
 *******************************************************************************
 */
static uint8_t BufferCache[FW_DEBUG_BUFFER_SIZE];

/**
 *******************************************************************************
 * @brief       debug component init flag
 *******************************************************************************
 */
static bool FwDebugInitFlag = false;

/**
 *******************************************************************************
 * @brief       define stream buffer
 *******************************************************************************
 */
static uint8_t TxBuffer[FW_DEBUG_BUFFER_SIZE];
static uint8_t RxBuffer[FW_DEBUG_BUFFER_SIZE];

/**
 *******************************************************************************
 * @brief       define stream fifo management block
 *******************************************************************************
 */
static Fw_Fifo_t TxFifo = {.Buffer = TxBuffer, .Size = FW_DEBUG_BUFFER_SIZE};
static Fw_Fifo_t RxFifo = {.Buffer = RxBuffer, .Size = FW_DEBUG_BUFFER_SIZE};

/**
 *******************************************************************************
 * @brief       define stream debug hardware block
 *******************************************************************************
 */
extern struct Fw_Stream DebugStream;
static Hal_Device_Uart DebugHardware = 
{
    //< uart stream hardware param init
    .Config.Port = MCU_UART_1,
    .Config.Group = 0,
    .Config.Baud = 115200,
    .Config.WordLen = MCU_UART_WORD_LEN_8B,
    .Config.Priority = MCU_UART_PARTY_NONE,
    .Config.StopBits = MCU_UART_STOP_BITS_1,
    .Config.TxConfig = MCU_UART_ENABLE_TX_ISR,
    .Config.RxConfig = MCU_UART_ENABLE_RX_ISR,
    .Config.Parity = 1,
    
    //< uart stream hardware call back config
    .RxCallback.Rx    = Fw_Stream_Rx_Handle,
    .RxCallback.Param = (void *)&DebugStream,
        
    .TxCallback.Tx    = Fw_Stream_Tx_Handle,
    .TxCallback.Param = (void *)&DebugStream,
};

/**
 *******************************************************************************
 * @brief       define common device operate block
 *******************************************************************************
 */
static Hal_Device_t DebugDevice = 
{
    .Device = (void *)&DebugHardware,
    .Interface = (struct Hal_Interface *)&Hal_Uart_Interface,
};

/**
 *******************************************************************************
 * @brief       define debug stream block
 *******************************************************************************
 */
static struct Fw_Stream DebugStream = 
{
    .Device = (void *)&DebugDevice,
        
    .Tx.Pool = (void *)&TxFifo,
    .Tx.Interface = (struct Fw_Pipe_Pool_Interface *)&PipeFifoInterface,
    .Tx.Task = NULL,
    .Tx.TimeOutTick = CAL_SET_TIME(10),
    .Tx.Callback = Fw_Stream_Tx_Handle,
    .Tx.Param = (void *)&DebugStream,
    
    .Rx.Pool = (void *)&RxFifo,
    .Rx.Interface = (struct Fw_Pipe_Pool_Interface *)&PipeFifoInterface,
    .Rx.TimeOutTick = CAL_SET_TIME(10),
}; 
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
    Fw_Stream_Init(&DebugStream);
    
    FwDebugInitFlag = true;
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
		return (uint8_t)sprintf((char *)buffer, "[Error][Tick:%ld]", (long)tick);
	}
	else if(type == DEBUG_OUTPUT_WARNING_MESSAGE)
	{
		return (uint8_t)sprintf((char *)buffer, "[Warning][Tick:%ld]", (long)tick);
	}
	else
	{
		return (uint8_t)sprintf((char *)buffer, "[Tick:%ld]", (long)tick);
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
	
    if(FwDebugInitFlag == false)
    {
        return;
    }
    
    va_start(args, str);
    len = Fw_Debug_FillHeadInfo(BufferCache, type);
    len += (uint8_t)vsprintf((char *)&BufferCache[len], str, args);
    va_end(args);
    
    Fw_Stream_Write(&DebugStream, BufferCache, len);
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
