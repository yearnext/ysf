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
#include "fw_event.h"
#include "fw_timer.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

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
#endif

/* Exported variables --------------------------------------------------------*/
#ifdef USE_FRAMEWORK_DEBUG_COMPONENT
struct Fw_Stream DebugStream;
#endif

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
    struct _FwStreamCallback TxCallback;
	struct _FwStreamCallback RxCallback;
    struct _FwStreamDevice   Device;
    _QueueInitType TxFifo;
    _QueueInitType RxFifo;
    
	memset(&DebugStream, 0, sizeof(DebugStream));

    TxCallback.Connect    = DebugTxConnectHandle;
    TxCallback.Disconnect = DebugTxDisconnectHandle;
    TxCallback.InOut      = DebugTxOutputHandle;

    RxCallback.Connect    = DebugRxConnectHandle;
    RxCallback.Disconnect = DebugRxDisconnectHandle;
    RxCallback.InOut      = DebugRxIntputHandle;

    Device.Fini = DebugDeviceFiniHandle;
    Device.Init = DebugDeviceInitHandle;
    
    TxFifo.Buffer = TxBuffer;
    TxFifo.Size   = FW_DEBUG_BUFFER_SIZE;
    RxFifo.Buffer = RxBuffer;
    RxFifo.Size   = FW_DEBUG_BUFFER_SIZE;
        
    Fw_Stream_Init(&DebugStream, &Device, &TxCallback, &RxCallback);
    Fw_Stream_Enable(&DebugStream, &TxFifo, &RxFifo);
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
    
    DebugStream.Opera->Write(&DebugStream.TxFifo, BufferCache, len);
    
    if(DebugStream.IsTxReady == false)
    {
        DebugStream.IsTxReady = true;
        
        DebugStream.TxCallback.InOut(&DebugStream);
    }
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
