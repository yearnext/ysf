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
#include "core_path.h"
#include _FW_PATH
#include _FW_BUFFER_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH

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
fw_err_t Fw_Buffer_Init(struct _Fw_RingBuffer *rb, uint8_t *rbBuffer, uint16_t rbSize)
{
    _FW_ASSERT(IS_PTR_NULL(rb));
    _FW_ASSERT(IS_PTR_NULL(rbBuffer));
    _FW_ASSERT(rbSize == 0);
    
    rb->Buffer = rbBuffer;
    rb->Size   = rbSize;
    rb->Head   = 0;
    rb->Tail   = 0;
    rb->Len    = 0;
    
    return FW_ERR_NONE;
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
fw_err_t Fw_Buffer_GetLen(struct _Fw_RingBuffer *rb, uint16_t *getSize)
{
    _FW_ASSERT(IS_PTR_NULL(rb));
    _FW_ASSERT(IS_PTR_NULL(getSize));
    
    *getSize =  rb->Len;
    
    return FW_ERR_NONE;
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
uint16_t RingBufferCanRead(struct _Fw_RingBuffer *rb)
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
uint16_t RingBufferCanWrite(struct _Fw_RingBuffer *rb)
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
fw_err_t Fw_Buffer_Write(struct _Fw_RingBuffer *rb, uint8_t *writeBuffer, uint16_t writeSize)
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

    return FW_ERR_FAIL;
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
fw_err_t Fw_Buffer_Read(struct _Fw_RingBuffer *rb, uint8_t *readBuffer, uint16_t readSize)
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
#endif

/** @}*/     /** framework buffer component */

/**********************************END OF FILE*********************************/
