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
 * @file       fw_buffer.c                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-06                                                      *
 * @brief      buffer component source file                                    *
 * @par        work platform                                                   * 
 *                 Windows                                                     *
 * @par        compiler                                                        *
 * 				   GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.achieve ring buffer, queue, memory pool                  				   *
 *******************************************************************************
 */
 
/**
 * @defgroup buffer component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_buffer.h"
#include "fw_debug.h"
#include <string.h>

/* Private define ------------------------------------------------------------*/
#define HeapMemoryNodeEndAddr                                        ((void *)0)

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_BUFFER_COMPONENT
/**
 *******************************************************************************
 * @brief       ring buffer init
 * @param       [in/out]  *rb            ring buff control block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  FW_ERR_NONE   ring buffer init success
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Buffer_Init(struct Fw_RingBuffer *rb, uint8_t *rbBuffer, uint16_t rbSize)
{
    _FW_ASSERT(IS_PTR_NULL(rb));
    _FW_ASSERT(IS_PTR_NULL(rbBuffer));
    _FW_ASSERT(rbSize == 0);
    
    rb->Buffer = rbBuffer;
    rb->Size   = rbSize;
    rb->Head   = 0;
    rb->Tail   = 0;
    rb->Len    = 0;
}

/**
 *******************************************************************************
 * @brief       deinit ring buffer
 * @param       [in/out]  *rb            ring buff control block
 * @return      [in/out]  FW_ERR_NONE    deinit success
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Buffer_Fini(struct Fw_RingBuffer *rb)
{
    _FW_ASSERT(IS_PTR_NULL(rb));
    
    rb->Buffer = NULL;
    rb->Size   = 0;
    rb->Head   = 0;
    rb->Tail   = 0;
    rb->Len    = 0;
}

/**
 *******************************************************************************
 * @brief       get ring buffer length
 * @param       [in/out]  *rb                 ring buff control block
 * @param       [in/out]  *size               return data point
 * @return      [in/out]  FW_ERR_NONE   ring buffer init success
 * @note        None
 *******************************************************************************
 */
__INLINE uint16_t Fw_Buffer_GetLen(struct Fw_RingBuffer *rb)
{
    _FW_ASSERT(IS_PTR_NULL(rb));
    
    return rb->Len;
}

/**
 *******************************************************************************
 * @brief       get ring buffer can read data size
 * @param       [in/out]  *rb                 ring buffer control block
 * @return      [in/out]  uint16_t            ring buffer can read data size
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE 
uint16_t RingBufferCanRead(struct Fw_RingBuffer *rb)
{
    _FW_ASSERT(IS_PTR_NULL(rb));

    return rb->Len;
}

/**
 *******************************************************************************
 * @brief       get ring buffer can write data size
 * @param       [in/out]  *rb                 ring buffer control block
 * @return      [in/out]  uint16_t            ring buffer can write data size
 * @note        one byte in the ring buffer is occupied by the control system
 *******************************************************************************
 */
__STATIC_INLINE 
uint16_t RingBufferCanWrite(struct Fw_RingBuffer *rb)
{
    _FW_ASSERT(IS_PTR_NULL(rb));
    
    return rb->Size - rb->Len - 1;
}

/**
 *******************************************************************************
 * @brief       write data to ring buffer
 * @param       [in/out]  *rb                ring buffer control block
 * @param       [in/out]  *buff              write data buffer
 * @param       [in/out]  rbSize             write data buffer size
 * @return      [in/out]  FW_ERR_NONE        ring buffer write success
 * @return      [in/out]  FW_ERR_FAIL        ring buffer write failed
 * @note        None
 *******************************************************************************
 */
__INLINE fw_err_t Fw_Buffer_Write(struct Fw_RingBuffer *rb, uint8_t *writeBuffer, uint16_t writeSize)
{
    _FW_ASSERT(IS_PTR_NULL(rb));
    _FW_ASSERT(IS_PTR_NULL(writeBuffer));
    _FW_ASSERT(writeSize == 0);
    
    uint16_t free = 0;
    uint16_t i = 0;
    uint16_t canWriteSize = RingBufferCanWrite(rb);

    if(writeSize <= canWriteSize)
    {
        if((rb->Tail + writeSize) >= rb->Size)
        {
            free = rb->Size - rb->Tail;

            for(i=0; i<free; i++)
            {
                rb->Buffer[rb->Tail++] = writeBuffer[i];
            }

            for(rb->Tail=0; i<writeSize; i++)
            {
                rb->Buffer[rb->Tail++] = writeBuffer[i];
            }
        }
        else
        {
            for(i=0; i<writeSize; i++)
            {
                rb->Buffer[rb->Tail++] = writeBuffer[i];
            }
        }

        return FW_ERR_NONE;
    }

    return FW_ERR_OVERFLOW;
}

/**
 *******************************************************************************
 * @brief       read data from ring buffer
 * @param       [in/out]  *rb                ring buffer control block
 * @param       [in/out]  *buff              read data buffer
 * @param       [in/out]  rbSize             read data size
 * @return      [in/out]  FW_ERR_NONE        ring buffer read success
 * @return      [in/out]  FW_ERR_FAIL        ring buffer read failed
 * @note        None
 *******************************************************************************
 */
__INLINE fw_err_t Fw_Buffer_Read(struct Fw_RingBuffer *rb, uint8_t *readBuffer, uint16_t readSize)
{
    _FW_ASSERT(IS_PTR_NULL(rb));
    _FW_ASSERT(IS_PTR_NULL(readBuffer));
    _FW_ASSERT(readSize == 0); 
    
    uint16_t free = 0;
    uint16_t i = 0;
    uint16_t canReadSize = RingBufferCanRead(rb);
    
    if (readSize <= canReadSize)
    {
        if ((rb->Head + readSize) >= rb->Size)
        {
            free = rb->Size - rb->Head;

            for (i=0; i<free; i++)
            {
                 readBuffer[i] = rb->Buffer[rb->Head++];
            }

            for (rb->Head=0; i<readSize; i++)
            {
                readBuffer[i] = rb->Buffer[rb->Head++];
            }
        }
        else
        {
            for (i=0; i<readSize; i++)
            {
                readBuffer[i] = rb->Buffer[rb->Head++];
            }
        }

        return FW_ERR_NONE;
    }

    return FW_ERR_FAIL;
}

/**
 *******************************************************************************
 * @brief       init queue
 * @param       [in/out]  *queue             queue block
 * @param       [in/out]  *buffer            buffer
 * @param       [in/out]  len                buffer size
 * @return      [in/out]  FW_ERR_NONE        init success
 * @return      [in/out]  FW_ERR_FAIL        init failed
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Queue_Init(struct Fw_Queue *queue, uint8_t *buffer, uint16_t len)
{
    _FW_ASSERT(IS_PTR_NULL(queue));
    _FW_ASSERT(IS_PTR_NULL(buffer));
    _FW_ASSERT(len == 0); 
    
    queue->Buffer = buffer;
	queue->Len    = len;
	queue->Head   = 0;
    queue->Tail   = 0;
}

/**
 *******************************************************************************
 * @brief       deinit queue
 * @param       [in/out]  *queue             queue block
 * @return      [in/out]  FW_ERR_NONE        deinit success
 * @return      [in/out]  FW_ERR_FAIL        deinit failed
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Queue_Fini(struct Fw_Queue *queue)
{
    _FW_ASSERT(IS_PTR_NULL(queue));

    queue->Buffer = NULL;
	queue->Len    = 0;
	queue->Head   = 0;
    queue->Tail   = 0;
}

/**
 *******************************************************************************
 * @brief       write data to data queue
 * @param       [in/out]  *queue             queue block
 * @param       [in/out]  *buffer            buffer
 * @param       [in/out]  len                buffer size
 * @return      [in/out]  FW_ERR_NONE        write success
 * @return      [in/out]  FW_ERR_FAIL        write failed
 * @note        None
 *******************************************************************************
 */
__INLINE fw_err_t Fw_Queue_Write(struct Fw_Queue *queue, uint8_t *buffer, uint16_t size)
{
    _FW_ASSERT(IS_PTR_NULL(queue));
    _FW_ASSERT(IS_PTR_NULL(buffer));
    _FW_ASSERT(size == 0); 

	uint16_t freeSize = queue->Len - queue->Tail;
	uint8_t *queueBuffer = &queue->Buffer[queue->Tail];
	
	if(size > freeSize)
	{
		return FW_ERR_OVERFLOW;
	}
	
	memcpy(queueBuffer, buffer, size);

	queue->Tail += freeSize;

	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       read data from data queue
 * @param       [in/out]  *queue             queue block
 * @param       [in/out]  *buffer            buffer
 * @param       [in/out]  len                buffer size
 * @return      [in/out]  FW_ERR_NONE        read success
 * @return      [in/out]  FW_ERR_FAIL        read failed
 * @note        None
 *******************************************************************************
 */
__INLINE fw_err_t Fw_Queue_Read(struct Fw_Queue *queue, uint8_t *buffer, uint16_t size)
{
    _FW_ASSERT(IS_PTR_NULL(queue));
    _FW_ASSERT(IS_PTR_NULL(buffer));
    _FW_ASSERT(size == 0); 

	uint16_t useSize = queue->Tail - queue->Head;
	uint8_t *queueBuffer = &queue->Buffer[queue->Head];
	
	if(size > useSize)
	{
		return FW_ERR_FAIL;
	}
	
	memcpy(buffer, queueBuffer, size);

	queue->Head += useSize;

	return FW_ERR_NONE;
}

__INLINE uint16_t Fw_Queue_GetFreeSize(struct Fw_Queue *queue)
{
    _FW_ASSERT(IS_PTR_NULL(queue));

	return queue->Len - queue->Tail;
}

__INLINE uint16_t Fw_Queue_GetUseSize(struct Fw_Queue *queue)
{
    _FW_ASSERT(IS_PTR_NULL(queue));

	return queue->Tail - queue->Head;
}

#endif

/** @}*/     /** framework buffer component */

/**********************************END OF FILE*********************************/
