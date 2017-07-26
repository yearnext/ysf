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
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */

/**
 * @defgroup framework debug component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "core_path.h"
#include _FW_PATH
#include _FW_DEBUG_COMPONENT_PATH
#include _FW_MEMORY_COMPONENT_PATH
#include _FW_TASK_COMPONENT_PATH
#include _FW_TICK_COMPONENT_PATH

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       config debug buffer size
 *******************************************************************************
 */
#define FW_DEBUG_BUFFER_SIZE                                               (128)

/**
 *******************************************************************************
 * @brief      define buffer status
 *******************************************************************************
 */
#define _INIT_STATE                                                       (0x00)
#define _WAIT_WRITE_STATE                                                 (0x00)
#define _WRITING_STATE                                                    (0x02)
#define _WAIT_TRANSFER_STATE                                              (0x03)
#define _TRANSMISSION_STATE                                               (0x04)
#define _WAIT_TRANSFER_COMPLET_STATE                                      (0x05)
#define _TRANSFER_COMPLET_STATE                                           (0x06)
#define _WAIT_TIMEOUT_STATE                                               (0x07)
#define _FINI_STATE                                                       (0x08)

/**
 *******************************************************************************
 * @brief      define now debug block status
 *******************************************************************************
 */
#define _CHANNEL_IDLE_STATE                                               (0x00)
#define _CHANNEL_WAIT_STATE                                               (0x01)
#define _CHANNEL_BUSY_STATE                                               (0x02)

/**
 *******************************************************************************
 * @brief      define debug block device output type
 *******************************************************************************
 */
#define _TRANSFER_INVAILD_MODE                                            (0x00)
#define _TRANSFER_DMA_MODE                                                (0x01)
#define _TRANSFER_ISR_MODE                                                (0x02)
#define _TRANSFER_POLL_MODE                                               (0x03)

/* Private typedef -----------------------------------------------------------*/
#if USE_DEBUG_COMPONENT
/**
 *******************************************************************************
 * @brief      define buffer block
 *******************************************************************************
 */
struct _BUFFER_BLOCK
{
    struct _BUFFER_BLOCK *Next;
    
	uint32_t Tick;
	
    uint8_t *Buffer;
    uint8_t Size;
	
    uint8_t State;
};

/**
 *******************************************************************************
 * @brief      define now debug block status
 *******************************************************************************
 */
struct Fw_Debug_Block
{
	union
	{
		void *Check;
		void (*DmaSend)(uint8_t*, uint8_t);
		void (*IsrSend)(uint8_t);
        fw_err_t (*PollSend)(uint8_t);
	}Device;
	
	struct
    {
        struct _BUFFER_BLOCK *Head;
        struct _BUFFER_BLOCK *Tail;
    }LinkList;
	
 	uint8_t TransferType;
    uint8_t NowChannelState;
	uint8_t Indicator;
};

static struct Fw_Debug_Block DebugBlock;

#endif

/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 *******************************************************************************
 * @brief       debug component transfer event handle
 * @param       [in/out]  event     trigger event
 * @return      [in/out]  none
 * @note        None
 *******************************************************************************
 */
//__STATIC_INLINE
//void TransferEventHandle(uint8_t event)
//{
//    uint32_t tick = 0;
//    struct _BUFFER_BLOCK *pipeline = &DebugBlock.Pipeline[DebugBlock.Channel];
//    
//	switch(pipeline->Status)
//	{
//		case BUFFER_WAIT_TIMEOUT_STATUS:
//			//< wait time out event
//			if(event == FW_TIMEOUT_EVENT)
//			{
//				//< transfer send process
//				goto _DEBUG_SEND_PROCESS;
//			}
//			break;
//		case BUFFER_WAIT_TRANSFER_STATUS:
//            //< wait transfer event
//            if(event == FW_TRANSFER_START_EVENT)
//            {
//				//< transfer send process
//				goto _DEBUG_SEND_PROCESS;
//            }
//            break;
//		case BUFFER_TRANSFER_STATUS:
//		_DEBUG_SEND_PROCESS:
//			pipeline->Status = TransferFunction(pipeline);
//			
//            if(pipeline->Status != BUFFER_WAIT_TRANSFER_COMPLET_STATUS)
//            {
//                break;
//            }
//            
//            //< straem transfer timeout
//            if(DebugBlock.Type == DEBUG_DEVICE_OUTPUT_STREAM_TYPE)
//            {
//                StartDebugTimer(100);
//            }
//            else
//            {
//                goto _TRANSFER_END_PROCESS;
//            }
//		case BUFFER_WAIT_TRANSFER_COMPLET_STATUS:
//            //< stream transfer timeout handle
//            if(event == FW_TIMEOUT_EVENT)
//            {
//                goto _TRANSFER_END_PROCESS;
//            }
//            
//            //< wait transfer complet (stream transfer complet trigger by transfer complet event)
//            if(DebugBlock.Type == DEBUG_DEVICE_OUTPUT_STREAM_TYPE && event != FW_TRANSFER_COMPLET_EVENT)
//            {
//                break;
//            }
//            
//            StopDebugTimer();
//            
//        _TRANSFER_END_PROCESS:
//            //< load start tick value
//            tick = pipeline->Tick;
//            
//            //< init now channel
//            pipeline->Status = BUFFER_WAIT_WRITE_STATUS;

//            //< switch channel
//            if (++DebugBlock.Channel >= FW_DEBUG_PIPELINE_NUM)
//            {
//                DebugBlock.Channel = 0;
//            }
//            
//            pipeline = &DebugBlock.Pipeline[DebugBlock.Channel];
//		case BUFFER_TRANSFER_COMPLET_STATUS:
//            if(pipeline->Status == BUFFER_WAIT_TRANSFER_STATUS)
//            {
//                tick = CalPastTick(tick, pipeline->Tick);
//                
//                if(tick == 0)
//                {
//                    pipeline->Status = BUFFER_TRANSFER_STATUS;
//                    event = FW_EVENT_NONE;
//                    
//                    goto _DEBUG_SEND_PROCESS;
//                }
//                else
//                {
//                    pipeline->Status = BUFFER_WAIT_TIMEOUT_STATUS;
//                    
//                    //< start timeout timer
//                    StartDebugTimer(tick);
//                }
//            }
//            else
//            {
//                pipeline->Status         = BUFFER_WAIT_WRITE_STATUS;
//                DebugBlock.ChannelStatus = DEBUG_BLOCK_CHANNEL_IDLE_STATUS;
//            }
//			break;
//		default:
//			break;
//	}
//}

/* Exported functions --------------------------------------------------------*/
#if USE_DEBUG_COMPONENT
/**
 *******************************************************************************
 * @brief       framework debug component initialization
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE    without exception
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Debug_Init(void)
{
    memset(&DebugBlock, 0, sizeof(DebugBlock));
    return FW_ERR_NONE;
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
uint8_t Fw_Debug_FillHead(struct _BUFFER_BLOCK *pipeLine, uint8_t type)
{
	if (IS_PTR_NULL(pipeLine))
	{
		return 0;
	}

	pipeLine->Tick = Fw_GetTick();

	if(type == DEBUG_OUTPUT_ERROR_MESSAGE)
	{
		return (uint8_t)sprintf((char *)&pipeLine->Buffer, "[Error][Tick:%ld]", pipeLine->Tick);
	}
	else if(type == DEBUG_OUTPUT_WARNING_MESSAGE)
	{
		return (uint8_t)sprintf((char *)&pipeLine->Buffer, "[Warning][Tick:%ld]", pipeLine->Tick);
	}
	else
	{
		return (uint8_t)sprintf((char *)&pipeLine->Buffer, "[Tick:%ld]", pipeLine->Tick);
	}
	
}

void WriteDebugMessage(uint8_t type, const char *str, ...)
{
	struct _BUFFER_BLOCK *buffer = (struct _BUFFER_BLOCK *)Fw_Mem_Alloc(sizeof(struct _BUFFER_BLOCK));
	uint8_t bufferLen = 0;
	va_list args;
	
	if (IS_PTR_NULL(buffer) || IS_PTR_NULL(str))
	{
		return;
	}
   
    //< clear buffer param
    memset(buffer, 0, sizeof(struct _BUFFER_BLOCK));
    
    
	switch(buffer->State)
	{
		//< filling debug info
		case _INIT_STATE:
//			va_start(args, cmd);
			bufferLen  = Fw_Debug_FillHead(buffer, type);
			bufferLen += vsprintf((char *)&buffer->Buffer[bufferLen], str, args);
			va_end(args);
			
			buffer->Size  = bufferLen;
			buffer->State = _WAIT_TRANSFER_STATE;
		//< start transfer	
		case _WAIT_TRANSFER_STATE:
			if(DebugBlock.NowChannelState == _CHANNEL_IDLE_STATE)
			{
                DebugBlock.NowChannelState = _CHANNEL_BUSY_STATE;
                
				Fw_Task_PostEvent(FW_DEBUG_TASK, FW_TRANSFER_START_EVENT);
			}
			break;	
		default:
			break;
	}
}

#endif

/** @}*/     /** framework debug component */

/**********************************END OF FILE*********************************/
