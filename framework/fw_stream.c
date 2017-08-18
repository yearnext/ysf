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
static void _FifoStreamOpera_Init(void*);
static void _FifoStreamOpera_Fini(void*);
static fw_err_t _FifoStreamOpera_Write(void*, uint8_t*, uint8_t);
static fw_err_t _FifoStreamOpera_Read(void*, uint8_t*, uint8_t);

//static void _BlockStreamOpera_Init(struct Fw_Stream*, void*);
//static void _BlockStreamOpera_Fini(struct Fw_Stream*);
//static fw_err_t _BlockStreamOpera_Write(struct Fw_Stream*, uint8_t*, uint8_t);
//static fw_err_t _BlockStreamOpera_Read(struct Fw_Stream*, uint8_t*, uint8_t);

/**
 *******************************************************************************
 * @brief       framework stream opera block
 *******************************************************************************
 */
const struct Fw_Stream_Buffer_Opera FwStreamFifoOpera = 
{
    .Init  = _FifoStreamOpera_Init,
    .Fini  = _FifoStreamOpera_Fini,
    
    .Write = _FifoStreamOpera_Write,
    .Read  = _FifoStreamOpera_Read,
};
  
//const struct Fw_Stream_Buffer_Opera FwStreamBlockOpera = 
//{
//    .Init  = _BlockStreamOpera_Init,
//    .Fini  = _BlockStreamOpera_Fini,
//    
//    .Write = _BlockStreamOpera_Write,
//    .Read  = _BlockStreamOpera_Read,
//};
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
void Fw_Stream_InitComponent(void)
{
    Fw_Task_Init(&StreamTask, 
                 "Framework Stream Task", 
                 1, 
                 (void *)Fw_StreamTask_Handle,
                 FW_MESSAGE_HANDLE_TYPE_TASK);
}

/**
 *******************************************************************************
 * @brief       post rec purse event
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE     init finish
 * @note        None
 *******************************************************************************
 */
void Fw_Stream_PostEvent(struct Fw_Stream *stream, uint8_t event)
{
    Fw_Task_PostMessage(&StreamTask, event, (void *)stream);
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
__INLINE void Fw_Stream_Init(struct Fw_Stream *stream)
{
    //< detect stream param
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    //< init buffer
    if(!IS_PTR_NULL(stream->Buf_Ops->Init))
    {
        stream->Buf_Ops->Init(stream->Buffer);
    }
    
    //< init tx pipe
    if(stream->Tx.IsReady)
    {
        if(!IS_PTR_NULL(stream->Tx.Connect))
        {
            stream->Tx.Connect(stream->Tx.Param);
        }
    }
    else
    {
        if(!IS_PTR_NULL(stream->Tx.Disconnect))
        {
            stream->Tx.Disconnect(stream->Tx.Param);
        }
    }
    
    //< init rx pipe
    if(stream->Tx.IsReady)
    {
        if(!IS_PTR_NULL(stream->Rx.Connect))
        {
            stream->Rx.Connect(stream->Rx.Param);
        }
    }
    else
    {
        if(!IS_PTR_NULL(stream->Rx.Disconnect))
        {
            stream->Rx.Disconnect(stream->Rx.Param);
        }
    }
}

/**
 *******************************************************************************
 * @brief       deinit stream block
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     deinit finish
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Stream_Fini(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));

    //< disconnect stream rx
	if(stream->Rx.IsReady && !IS_PTR_NULL(stream->Rx.Disconnect))
	{
        stream->Rx.Disconnect(stream->Rx.Param);
	}

    //< disconnect stream tx
	if(stream->Tx.IsReady && !IS_PTR_NULL(stream->Tx.Disconnect))
	{
		stream->Tx.Disconnect(stream->Tx.Param);
	}
	
    //< deinit stream buffer
    if(!IS_PTR_NULL(stream->Buf_Ops->Fini))
    {
        stream->Buf_Ops->Fini(stream);
    }
    
    //< clear stream param
    memset(stream, 0, sizeof(struct Fw_Stream));
}

/**
 *******************************************************************************
 * @brief       connect stream tx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     connect finish
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Stream_TxConnect(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));

	if(stream->Tx.IsReady == false)
	{
		if(!IS_PTR_NULL(stream->Tx.Connect))
		{
			stream->Tx.Connect(stream->Tx.Param);
		}

		stream->Tx.IsReady = true;
	}
}

/**
 *******************************************************************************
 * @brief       disconnect stream tx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     disconnect finish
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Stream_TxDisconnect(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
	if(stream->Tx.IsReady == true)
	{
		if(!IS_PTR_NULL(stream->Tx.Disconnect))
		{
			stream->Tx.Disconnect(stream->Tx.Param);
		}

		stream->Tx.IsReady = false;
	}
}

/**
 *******************************************************************************
 * @brief       connect stream rx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     connect finish
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Stream_RxConnect(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
	if(stream->Rx.IsReady == false)
	{
		if(!IS_PTR_NULL(stream->Rx.Connect))
		{
			stream->Rx.Connect(stream);
		}

		stream->Rx.IsReady = true;
	}
}

/**
 *******************************************************************************
 * @brief       disconnect stream tx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     disconnect finish
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Stream_RxDisconnect(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
	if(stream->Rx.IsReady == true)
	{
		if(!IS_PTR_NULL(stream->Rx.Disconnect))
		{
			stream->Rx.Disconnect(stream);
		}

		stream->Rx.IsReady = false;
	}
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
__INLINE fw_err_t Fw_Stream_Write(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    _FW_ASSERT(IS_PTR_NULL(stream->Buf_Ops));
    _FW_ASSERT(IS_PTR_NULL(buffer));
    _FW_ASSERT(IS_PARAM_ZERO(size));
    
    if(stream->Tx.IsReady == true && !IS_PTR_NULL(stream->Buf_Ops->Write))
    {
        if(stream->Buf_Ops->Write(stream->Buffer, buffer, size) == FW_ERR_NONE)
        { 
            if(!IS_PTR_NULL(stream->Rx.InOut))
            {
                stream->Rx.InOut(stream);
            }
            
            return FW_ERR_NONE;
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
__INLINE fw_err_t Fw_Stream_Read(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    _FW_ASSERT(IS_PTR_NULL(stream->Buf_Ops));
    _FW_ASSERT(IS_PTR_NULL(buffer));
    _FW_ASSERT(IS_PARAM_ZERO(size));
    
    if(stream->Rx.IsReady == true && !IS_PTR_NULL(stream->Buf_Ops->Read))
    {
        return stream->Buf_Ops->Read(stream->Buffer, buffer, size);
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
static void _FifoStreamOpera_Init(void *fifo)
{
    _FW_ASSERT(IS_PTR_NULL(fifo));

    struct Fw_RingBuffer *rb = (struct Fw_RingBuffer *)fifo;
        
    Fw_Buffer_Init(rb, rb->Buffer, rb->Size);
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
static void _FifoStreamOpera_Fini(void *fifo)
{
    Fw_Buffer_Fini((struct Fw_RingBuffer *)fifo);
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
static fw_err_t _FifoStreamOpera_Write(void *fifo, uint8_t *buffer, uint8_t size)
{
    return Fw_Buffer_Write((struct Fw_RingBuffer *)fifo, buffer, size);
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
static fw_err_t _FifoStreamOpera_Read(void *fifo, uint8_t *buffer, uint8_t size)
{
    return Fw_Buffer_Read((struct Fw_RingBuffer *)fifo, buffer, size);
}
//
///**
// *******************************************************************************
// * @brief       block stream opera init
// * @param       [in/out]  *stream        stream block
// * @param       [in/out]  *buffer        buffer
// * @return      [in/out]  FW_ERR_NONE    init success
// * @return      [in/out]  FW_ERR_FAIL    init failed
// * @note        None
// *******************************************************************************
// */
//static void _BlockStreamOpera_Init(void *block, void *buffer)
//{
//    struct Fw_BlockStream *blockStream = (struct Fw_BlockStream *)stream;
//    
//	blockStream->LinkList.Head = NULL;
//	blockStream->LinkList.Tail = NULL;
//}
//
///**
// *******************************************************************************
// * @brief       block stream opera deinit
// * @param       [in/out]  *stream        stream block
// * @return      [in/out]  FW_ERR_NONE    deinit success
// * @return      [in/out]  FW_ERR_FAIL    deinit failed
// * @note        None
// *******************************************************************************
// */
//static void _BlockStreamOpera_Fini(struct Fw_Stream *stream)
//{
//    struct Fw_BlockStream *blockStream = (struct Fw_BlockStream *)stream;
//    
//	blockStream->LinkList.Head = NULL;
//	blockStream->LinkList.Tail = NULL;
//}
//
///**
// *******************************************************************************
// * @brief       create queue and write data
// * @param       [in/out]  *stream        stream block
// * @param       [in/out]  *buffer        buffer
// * @param       [in/out]  size           buffer size
// * @return      [in/out]  FW_ERR_NONE    opera success
// * @return      [in/out]  FW_ERR_FAIL    opera failed
// * @note        None
// *******************************************************************************
// */
//__STATIC_INLINE
//fw_err_t _BlockStream_CreateBufferAndWrite(struct Fw_BlockStream *stream, uint8_t *buffer, uint8_t size)
//{
//	struct Fw_BlockStreamBuffer *queue = (struct Fw_BlockStreamBuffer *)Fw_Mem_Alloc(sizeof(struct Fw_BlockStreamBuffer));
//
//	_FW_ASSERT(IS_PTR_NULL(queue));
//
//	uint8_t *memBuffer = (uint8_t *)Fw_Mem_Alloc(BLOCK_STREAM_BUFFER_SIZE);
//
//	if(IS_PTR_NULL(memBuffer))
//	{
//		Fw_Mem_Free(queue);
//		return FW_ERR_FAIL;
//	}
//
//	Fw_sLinkList_Init((struct Fw_sLinkList *)&queue->LinkList);
//	Fw_sLinkList_Push((struct Fw_sLinkList_Block *)&stream->LinkList,
//					  (struct Fw_sLinkList *)&queue->LinkList);
//
//	Fw_Queue_Init(&queue->Queue, memBuffer, BLOCK_STREAM_BUFFER_SIZE);
//	Fw_Queue_Write(&queue->Queue, buffer, size);
//		
//	return FW_ERR_NONE;
//}
//
///**
// *******************************************************************************
// * @brief       write data to stream
// * @param       [in/out]  *stream        stream block
// * @param       [in/out]  *buffer        buffer
// * @param       [in/out]  size           buffer size
// * @return      [in/out]  FW_ERR_NONE    opera success
// * @return      [in/out]  FW_ERR_FAIL    opera failed
// * @note        None
// *******************************************************************************
// */
//static fw_err_t _BlockStreamOpera_Write(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
//{
//	struct Fw_BlockStream *blockStream = (struct Fw_BlockStream *)stream;
//
//	_FW_ASSERT(IS_PTR_NULL(blockStream));
//	_FW_ASSERT(size > BLOCK_STREAM_BUFFER_SIZE);
//
//	if(Fw_sLinkList_IsEmpty((struct Fw_sLinkList_Block *)&blockStream->LinkList) == true)
//	{
//		_BlockStream_CreateBufferAndWrite(blockStream, buffer, size);
//	}
//	else
//	{
//		uint8_t canWrite = 0;
//		Fw_Queue_GetFreeSize(&blockStream->LinkList.Tail->Queue, &canWrite);
//
//		if(canWrite >= size)
//		{
//			Fw_Queue_Write(&blockStream->LinkList.Tail->Queue, buffer, size);
//		}
//		else
//		{
//			Fw_Queue_Write(&blockStream->LinkList.Tail->Queue, buffer, canWrite);
//			return _BlockStream_CreateBufferAndWrite(blockStream, &buffer[canWrite], size-canWrite);
//		}
//	}
//
//    return FW_ERR_NONE;
//}
//
///**
// *******************************************************************************
// * @brief       remove buffer and read data
// * @param       [in/out]  *stream        stream block
// * @param       [in/out]  *buffer        buffer
// * @param       [in/out]  size           buffer size
// * @return      [in/out]  FW_ERR_NONE    opera success
// * @return      [in/out]  FW_ERR_FAIL    opera failed
// * @note        None
// *******************************************************************************
// */
//__STATIC_INLINE
//fw_err_t _BlockStream_RemoveBufferAndRead(struct Fw_BlockStream *stream, uint8_t *buffer, uint8_t size)
//{
//	struct Fw_sLinkList *node = NULL;
//	Fw_sLinkList_Pop((struct Fw_sLinkList_Block *)&stream->LinkList, 
//                     (struct Fw_sLinkList **)&node);
//	Fw_Mem_Free(node);
//	Fw_Queue_Read(&stream->LinkList.Head->Queue, buffer, size);
//
//	return FW_ERR_NONE;
//}
//
///**
// *******************************************************************************
// * @brief       read data from stream
// * @param       [in/out]  *stream        stream block
// * @param       [in/out]  *buffer        buffer
// * @param       [in/out]  size           buffer size
// * @return      [in/out]  FW_ERR_NONE    opera success
// * @return      [in/out]  FW_ERR_FAIL    opera failed
// * @note        None
// *******************************************************************************
// */
//static fw_err_t _BlockStreamOpera_Read(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
//{
//	struct Fw_BlockStream *blockStream = (struct Fw_BlockStream *)stream;
//	uint8_t canRead = 0;
//	
//	_FW_ASSERT(IS_PTR_NULL(blockStream));
//	
//	Fw_Queue_GetUseSize(&blockStream->LinkList.Head->Queue, &canRead);
//
//	if(canRead >= size)
//	{
//		Fw_Queue_Read(&blockStream->LinkList.Head->Queue, buffer, size);
//	}
//	else
//	{
//		Fw_Queue_Read(&blockStream->LinkList.Head->Queue, buffer, canRead);
//		_BlockStream_RemoveBufferAndRead(blockStream, &buffer[canRead], size - canRead);
//	}
//	
//    return FW_ERR_NONE;
//}
#endif

/** @}*/     /** framework stream component */

/**********************************END OF FILE*********************************/
