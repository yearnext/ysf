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
 * @file       fw_stream.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-07-30
 * @brief      framework stream component source files
 * @par        paltform                                  
 *                 Windows
 * @par        compiler									                         
 * 			       GCC
 *******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 *******************************************************************************
 */

/**
 * @defgroup framework stream component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "fw_stream.h"
#include "fw_debug.h"
#include "fw_task.h"
#include "fw_memory.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       stream task management block
 *******************************************************************************
 */
#if USE_STREAM_COMPONENT
static struct Fw_Task StreamTask;
#endif

/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       fifo stream opera function
 *******************************************************************************
 */
#if USE_STREAM_COMPONENT
static fw_err_t _FifoStreamOpera_Init(struct Fw_Stream*, void*);
static fw_err_t _FifoStreamOpera_Fini(struct Fw_Stream*);
static fw_err_t _FifoStreamOpera_Write(struct Fw_Stream*, uint8_t*, uint8_t);
static fw_err_t _FifoStreamOpera_Read(struct Fw_Stream*, uint8_t*, uint8_t);

static fw_err_t _BlockStreamOpera_Init(struct Fw_Stream*, void*);
static fw_err_t _BlockStreamOpera_Fini(struct Fw_Stream*);
static fw_err_t _BlockStreamOpera_Write(struct Fw_Stream*, uint8_t*, uint8_t);
static fw_err_t _BlockStreamOpera_Read(struct Fw_Stream*, uint8_t*, uint8_t);

/**
 *******************************************************************************
 * @brief       framework stream opera block
 *******************************************************************************
 */
const _StreamBufferOperaInitType StreamFifoOpera = 
{
    .Init  = _FifoStreamOpera_Init,
    .Fini  = _FifoStreamOpera_Fini,
    
    .Write = _FifoStreamOpera_Write,
    .Read  = _FifoStreamOpera_Read,
};
  
const _StreamBufferOperaInitType StreamBlockOpera = 
{
    .Init  = _BlockStreamOpera_Init,
    .Fini  = _BlockStreamOpera_Fini,
    
    .Write = _BlockStreamOpera_Write,
    .Read  = _BlockStreamOpera_Read,
};
#endif

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_STREAM_COMPONENT
/**
 *******************************************************************************
 * @brief       stream task handle
 * @param       [in/out]  event           trigger event
 * @param       [in/out]  *param          param
 * @return      [in/out]  FW_ERR_NONE     init finish
 * @note        None
 *******************************************************************************
 */
static fw_err_t Fw_StreamTask_Handle(uint32_t event, void *param)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    struct Fw_Stream *stream = (struct Fw_Stream *)param;
    
    if(!IS_PTR_NULL(stream->Callback))
    {
        stream->Callback(event, param);
    }
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       init stream component
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE     init finish
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_InitComponent(void)
{
    Fw_Task_Init(&StreamTask, 
                 "Framework Stream Task", 
                 1, 
                 (void *)Fw_StreamTask_Handle,
                 FW_MESSAGE_HANDLE_TYPE_TASK);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       post rec purse event
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE     init finish
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_PostRxEvent(struct Fw_Stream *stream)
{
    Fw_Task_PostMessage(&StreamTask, FW_STREAM_RX_EVENT, (void *)stream);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       init stream block
 * @param       [in/out]  *stream         stream block
 * @param       [in/out]  *opera          hardware call back function block
 * @param       [in/out]  *txCallback     tx call back function block
 * @param       [in/out]  *rxCallback     rx call back function block
 * @return      [in/out]  FW_ERR_NONE     init finish
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Init(struct Fw_Stream *stream, 
                        _StreamBufferOperaInitType *opera, 
                        void *param)
{
    //< detect stream param
    _FW_ASSERT(IS_PTR_NULL(stream));
    _FW_ASSERT(IS_PTR_NULL(opera));
    
    //< init stream block
    stream->IsRxReady = false;
	stream->IsTxReady = false;

    //< set stream buffer opera
    stream->Opera = opera;
    
    //< init memory
    if(!IS_PTR_NULL(stream->Opera->Init))
    {
        stream->Opera->Init(stream, param);
    }
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       deinit stream block
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     deinit finish
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Fini(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));

	if(stream->IsRxReady)
	{
		stream->Rx.Disconnect(stream->Rx.Param);
	}

	if(stream->IsTxReady)
	{
		stream->Tx.Disconnect(stream->Tx.Param);
	}
	
    //< init stream buffer
    if(!IS_PTR_NULL(stream->Opera->Fini))
    {
        stream->Opera->Fini(stream);
    }
    
    memset(stream, 0, sizeof(struct Fw_Stream));
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       connect stream tx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     connect finish
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_TxConnect(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));

	if(stream->IsTxReady == false)
	{
		if(!IS_PTR_NULL(stream->Tx.Connect))
		{
			stream->Tx.Connect(stream);
		}

		stream->IsTxReady = true;
	}
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       disconnect stream tx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     disconnect finish
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_TxDisconnect(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
	if(stream->IsTxReady == true)
	{
		if(!IS_PTR_NULL(stream->Tx.Disconnect))
		{
			stream->Tx.Disconnect(stream);
		}

		stream->IsTxReady = false;
	}

    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       connect stream rx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     connect finish
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_RxConnect(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
	if(stream->IsRxReady == false)
	{
		if(!IS_PTR_NULL(stream->Rx.Connect))
		{
			stream->Rx.Connect(stream);
		}

		stream->IsRxReady = true;
	}
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       disconnect stream tx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     disconnect finish
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_RxDisconnect(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
	if(stream->IsRxReady == true)
	{
		if(!IS_PTR_NULL(stream->Rx.Disconnect))
		{
			stream->Rx.Disconnect(stream);
		}

		stream->IsRxReady = false;
	}
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       write data to stream
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  FW_ERR_NONE    write success
 * @return      [in/out]  FW_ERR_FAIL    write failed
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Write(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    _FW_ASSERT(IS_PTR_NULL(stream->Opera));
    _FW_ASSERT(IS_PTR_NULL(buffer));
    _FW_ASSERT(IS_PARAM_ZERO(size));
    
    if(stream->IsTxReady == true)
    {
        if(!IS_PTR_NULL(stream->Opera->Write) && !IS_PTR_NULL(stream->Tx.InOut))
        {
            if(stream->Opera->Write(stream, buffer, size) == FW_ERR_NONE)
            {
                stream->Tx.InOut(stream);
            
                return FW_ERR_NONE;
            }
        }
    }
    
    return FW_ERR_FAIL;
}

/**
 *******************************************************************************
 * @brief       read data from stream
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  FW_ERR_NONE    read success
 * @return      [in/out]  FW_ERR_FAIL    read failed
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Read(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    _FW_ASSERT(IS_PTR_NULL(stream->Opera));
    _FW_ASSERT(IS_PTR_NULL(buffer));
    _FW_ASSERT(IS_PARAM_ZERO(size));
    
    if(stream->IsRxReady == true)
    {
        if(!IS_PTR_NULL(stream->Opera->Read))
        {
            return stream->Opera->Read(stream, buffer, size);
        }
    }
    
    return FW_ERR_FAIL;
}

/**
 *******************************************************************************
 * @brief       init fifo stream buffer
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  *buffer        buffer block
 * @return      [in/out]  FW_ERR_NONE    init success
 * @return      [in/out]  FW_ERR_FAIL    init failed
 * @note        None
 *******************************************************************************
 */
static fw_err_t _FifoStreamOpera_Init(struct Fw_Stream *stream, void *buffer)
{
    struct Fw_FifoStream *fifoStream = (struct Fw_FifoStream *)stream;
    _FifoInitType *fifo = (_FifoInitType *)buffer;
    
    _FW_ASSERT(IS_PTR_NULL(fifoStream));
    _FW_ASSERT(IS_PTR_NULL(fifo));

    return Fw_Buffer_Init((struct Fw_RingBuffer *)&fifoStream->Fifo, fifo->Buffer, fifo->Size);
}

/**
 *******************************************************************************
 * @brief       deinit fifo stream buffer 
 * @param       [in/out]  *stream        stream block
 * @return      [in/out]  FW_ERR_NONE    deinit success
 * @return      [in/out]  FW_ERR_FAIL    deinit failed
 * @note        None
 *******************************************************************************
 */
static fw_err_t _FifoStreamOpera_Fini(struct Fw_Stream *stream)
{
    struct Fw_FifoStream *fifoStream = (struct Fw_FifoStream *)stream;

    _FW_ASSERT(IS_PTR_NULL(fifoStream));
    
    return Fw_Buffer_Fini((struct Fw_RingBuffer *)&fifoStream->Fifo);
}

/**
 *******************************************************************************
 * @brief       write data to stream
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  FW_ERR_NONE    write success
 * @return      [in/out]  FW_ERR_FAIL    write failed
 * @note        None
 *******************************************************************************
 */
static fw_err_t _FifoStreamOpera_Write(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
    struct Fw_FifoStream *fifoStream = (struct Fw_FifoStream *)stream;

    _FW_ASSERT(IS_PTR_NULL(fifoStream));
    
    return Fw_Buffer_Write((struct Fw_RingBuffer *)&fifoStream->Fifo, buffer, size);
}

/**
 *******************************************************************************
 * @brief       read data from stream
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  FW_ERR_NONE    read success
 * @return      [in/out]  FW_ERR_FAIL    read failed
 * @note        None
 *******************************************************************************
 */
static fw_err_t _FifoStreamOpera_Read(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
    struct Fw_FifoStream *fifoStream = (struct Fw_FifoStream *)stream;

    _FW_ASSERT(IS_PTR_NULL(fifoStream));
    
    return Fw_Buffer_Read((struct Fw_RingBuffer *)&fifoStream->Fifo, buffer, size);
}

/**
 *******************************************************************************
 * @brief       block stream opera init
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  *buffer        buffer
 * @return      [in/out]  FW_ERR_NONE    init success
 * @return      [in/out]  FW_ERR_FAIL    init failed
 * @note        None
 *******************************************************************************
 */
static fw_err_t _BlockStreamOpera_Init(struct Fw_Stream *stream, void *buffer)
{
    struct Fw_BlockStream *blockStream = (struct Fw_BlockStream *)stream;
    
	blockStream->LinkList.Head = NULL;
	blockStream->LinkList.Tail = NULL;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       block stream opera deinit
 * @param       [in/out]  *stream        stream block
 * @return      [in/out]  FW_ERR_NONE    deinit success
 * @return      [in/out]  FW_ERR_FAIL    deinit failed
 * @note        None
 *******************************************************************************
 */
static fw_err_t _BlockStreamOpera_Fini(struct Fw_Stream *stream)
{
    struct Fw_BlockStream *blockStream = (struct Fw_BlockStream *)stream;
    
	blockStream->LinkList.Head = NULL;
	blockStream->LinkList.Tail = NULL;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       create queue and write data
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  FW_ERR_NONE    opera success
 * @return      [in/out]  FW_ERR_FAIL    opera failed
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
fw_err_t _BlockStream_CreateBufferAndWrite(struct Fw_BlockStream *stream, uint8_t *buffer, uint8_t size)
{
	struct Fw_BlockStreamBuffer *queue = (struct Fw_BlockStreamBuffer *)Fw_Mem_Alloc(sizeof(struct Fw_BlockStreamBuffer));

	_FW_ASSERT(IS_PTR_NULL(queue));

	uint8_t *memBuffer = (uint8_t *)Fw_Mem_Alloc(BLOCK_STREAM_BUFFER_SIZE);

	if(IS_PTR_NULL(memBuffer))
	{
		Fw_Mem_Free(queue);
		return FW_ERR_FAIL;
	}

	Fw_sLinkList_Init((struct Fw_sLinkList *)&queue->LinkList);
	Fw_sLinkList_Push((struct Fw_sLinkList_Block *)&stream->LinkList,
					  (struct Fw_sLinkList *)&queue->LinkList);

	Fw_Queue_Init(&queue->Queue, memBuffer, BLOCK_STREAM_BUFFER_SIZE);
	Fw_Queue_Write(&queue->Queue, buffer, size);
		
	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       write data to stream
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  FW_ERR_NONE    opera success
 * @return      [in/out]  FW_ERR_FAIL    opera failed
 * @note        None
 *******************************************************************************
 */
static fw_err_t _BlockStreamOpera_Write(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
	struct Fw_BlockStream *blockStream = (struct Fw_BlockStream *)stream;

	_FW_ASSERT(IS_PTR_NULL(blockStream));
	_FW_ASSERT(size > BLOCK_STREAM_BUFFER_SIZE);

	if(Fw_sLinkList_IsEmpty((struct Fw_sLinkList_Block *)&blockStream->LinkList) == true)
	{
		_BlockStream_CreateBufferAndWrite(blockStream, buffer, size);
	}
	else
	{
		uint8_t canWrite = 0;
		Fw_Queue_GetFreeSize(&blockStream->LinkList.Tail->Queue, &canWrite);

		if(canWrite >= size)
		{
			Fw_Queue_Write(&blockStream->LinkList.Tail->Queue, buffer, size);
		}
		else
		{
			Fw_Queue_Write(&blockStream->LinkList.Tail->Queue, buffer, canWrite);
			return _BlockStream_CreateBufferAndWrite(blockStream, &buffer[canWrite], size-canWrite);
		}
	}

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       remove buffer and read data
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  FW_ERR_NONE    opera success
 * @return      [in/out]  FW_ERR_FAIL    opera failed
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
fw_err_t _BlockStream_RemoveBufferAndRead(struct Fw_BlockStream *stream, uint8_t *buffer, uint8_t size)
{
	struct Fw_sLinkList *node = NULL;
	Fw_sLinkList_Pop((struct Fw_sLinkList_Block *)&stream->LinkList, 
                     (struct Fw_sLinkList **)&node);
	Fw_Mem_Free(node);
	Fw_Queue_Read(&stream->LinkList.Head->Queue, buffer, size);

	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       read data from stream
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  FW_ERR_NONE    opera success
 * @return      [in/out]  FW_ERR_FAIL    opera failed
 * @note        None
 *******************************************************************************
 */
static fw_err_t _BlockStreamOpera_Read(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
	struct Fw_BlockStream *blockStream = (struct Fw_BlockStream *)stream;
	uint8_t canRead = 0;
	
	_FW_ASSERT(IS_PTR_NULL(blockStream));
	
	Fw_Queue_GetUseSize(&blockStream->LinkList.Head->Queue, &canRead);

	if(canRead >= size)
	{
		Fw_Queue_Read(&blockStream->LinkList.Head->Queue, buffer, size);
	}
	else
	{
		Fw_Queue_Read(&blockStream->LinkList.Head->Queue, buffer, canRead);
		_BlockStream_RemoveBufferAndRead(blockStream, &buffer[canRead], size - canRead);
	}
	
    return FW_ERR_NONE;
}
#endif

/** @}*/     /** framework stream component */

/**********************************END OF FILE*********************************/
