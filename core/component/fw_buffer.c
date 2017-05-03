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
fw_err_t InitRingBufferComponent(struct RingBuffer *rb, uint8_t *rbBuffer, uint16_t rbSize )
{
    fw_assert(IS_PTR_NULL(rb));
    fw_assert(IS_PTR_NULL(rbBuffer));
    fw_assert(rbSize == 0);
    
    rb->Buffer = rbBuffer;
    rb->Size   = rbSize;
    rb->Head   = 0;
    rb->Tail   = 0;

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
fw_err_t GetRingBufferLen(struct RingBuffer *rb, uint16_t *getSize)
{
    fw_assert(IS_PTR_NULL(rb));
    fw_assert(IS_PTR_NULL(getSize));
    
    *getSize =  rb->Size;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get ring buffer can read data size
 * @param       [in/out]  *rb                 ring buffer control block
 * @return      [in/out]  ysf_buffer_size_t   ring buffer can read data size
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE 
uint16_t rb_can_read(struct RingBuffer *rb )
{
    fw_assert(IS_PTR_NULL(rb));

    if( rb->Tail >= rb->Head )
    {
        return ((uint16_t)(rb->Tail - rb->Head));
    }
    else
    {
        return ((uint16_t)(rb->Size - (rb->Head - rb->Tail)));
    }

//    return 0;
}

/**
 *******************************************************************************
 * @brief       get ring buffer can write data size
 * @param       [in/out]  *rb                 ring buffer control block
 * @return      [in/out]  ysf_buffer_size_t   ring buffer can write data size
 * @note        one byte in the ring buffer is occupied by the control system
 *******************************************************************************
 */
__STATIC_INLINE 
uint16_t rb_can_write(struct RingBuffer *rb)
{
    fw_assert(IS_PTR_NULL(rb));

    uint16_t size = 0;

    if( rb->Tail >= rb->Head )
    {
        size = rb->Size - (rb->Tail - rb->Head);

        return size;
    }
    else
    {
        size = rb->Head - rb->Tail;

        return ((size > 1) ? (size) : (0));
    }

//    return 0;
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
fw_err_t WriteRingBuffer(struct RingBuffer *rb, uint8_t *writeBuffer, uint16_t writeSize)
{
    fw_assert(IS_PTR_NULL(rb));
    fw_assert(IS_PTR_NULL(writeBuffer));
    fw_assert(writeSize == 0);
    
    uint16_t free = 0;
    uint16_t i = 0;


    if( writeSize <= rb_can_write(rb) )
    {
        if( (rb->Tail + writeSize) >= rb->Size )
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
fw_err_t ReadRingBuffer( struct RingBuffer *rb, uint8_t *readBuffer, uint16_t readSize)
{
    fw_assert(IS_PTR_NULL(rb));
    fw_assert(IS_PTR_NULL(readBuffer));
    fw_assert(readSize == 0); 
    
    uint16_t free = 0;
    uint16_t i = 0;

    if (readSize <= rb_can_read(rb))
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

#if USE_MEMORY_MANAGEMENT_COMPONENT
/**
 *******************************************************************************
 * @brief       memory init
 * @param       [in/out]  **mem              memory control block
 * @param       [in/out]  *buffer            memory buffer address
 * @param       [in/out]  rbSize             memory buffer size
 * @return      [in/out]  FW_ERR_NONE        memory init success
 * @return      [in/out]  FW_ERR_FAIL        memory init failed
 * @note        None
 *******************************************************************************
 */
fw_err_t InitHeapMemory(struct HeapControlBlock *mem, uint8_t *heapHeadAddr, uint32_t heapSize)
{
    fw_assert(IS_PTR_NULL(mem));
    fw_assert(IS_PTR_NULL(heapHeadAddr));
    fw_assert(heapSize < sizeof(struct HeapBlock));
    
    mem->Buffer       = heapHeadAddr;
    mem->Size         = heapSize;
    
    mem->Head->Last   = NULL;
    mem->Head->Next   = NULL;
    mem->Head->Status = 0;
    mem->Head->Size   = mem->Size - sizeof(struct HeapBlock);

    return FW_ERR_NONE;
}

///**
// *******************************************************************************
// * @brief       memory deinit
// * @param       [in/out]  **mem              memory control block
// * @return      [in/out]  FW_ERR_NONE        ring buffer read success
// * @return      [in/out]  FW_ERR_FAIL        ring buffer read failed
// * @note        None
// *******************************************************************************
// */
//fw_err_t ysf_mem_deinit(struct HeapControlBlock *mem)
//{
//    fw_assert(IS_PTR_NULL(mem));
//    
//	mem->Buffer = NULL;
//    mem->Size   = 0;
//    
//    return FW_ERR_NONE;
//}

/**
 *******************************************************************************
 * @brief       cal need memory size
 * @param       [in/out]  size                memory control block
 * @param       [in/out]  alignment           memory alignment size
 * @return      [in/out]  value               need block size
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
uint32_t cal_need_memory_size(uint32_t useSize)
{
	uint32_t needSize = useSize + HEAP_MEMORY_ALIGNMENT_SIZE;
    
    if( needSize % HEAP_MEMORY_ALIGNMENT_SIZE )
    {
        needSize >>= HEAP_MEMORY_ALIGNMENT_POS;
        
        needSize++;
        
        needSize <<= HEAP_MEMORY_ALIGNMENT_POS;
    }

	return needSize;
}

/**
 *******************************************************************************
 * @brief       memory alloc 
 * @param       [in/out]  *mem                memory control block
 * @param       [in/out]  size                alloc memory size
 * @param       [in/out]  void*               alloc memory address
 * @return      [in/out]  FW_ERR_NONE         alloc success
 * @return      [in/out]  FW_ERR_FAIL         alloc failed
 * @note        None
 *******************************************************************************
 */
fw_err_t AllocHeapMemory(struct HeapControlBlock *mem, uint32_t needSize, void **allocAddr)
{
    fw_assert(IS_PTR_NULL(mem));
    fw_assert(needSize == 0);
    
    uint32_t useSize = cal_need_memory_size(needSize);
    struct HeapBlock *now = mem->Head;
    struct HeapBlock *next;
    
    while (1)
    {
        if (!now->Status && now->Size >= useSize)
        {
            next = (struct HeapBlock *)( (uint8_t *)now + useSize - HEAP_MEMORY_ALIGNMENT_SIZE );
            
            next->Next = now->Next;
            now->Next = next;
            
            
            
            now->Status = 1;
            
            *allocAddr = (void *)(now+1);
            
            return FW_ERR_NONE;
        }
        
        if ( (now = now->Next) == NULL )
        {
            break;
        }
    }
    
    return FW_ERR_FAIL;
}

/**
 *******************************************************************************
 * @brief       memory free 
 * @param       [in/out]  *mem                memory control block
 * @param       [in/out]  *buffer             need free memory address
 * @return      [in/out]  FW_ERR_NONE         free success
 * @return      [in/out]  FW_ERR_FAIL         free failed
 * @note        None
 *******************************************************************************
 */
fw_err_t FreeHeapMemory(struct HeapControlBlock *mem, void *freeBuffer)
{
    fw_assert(IS_PTR_NULL(mem));
    fw_assert(IS_PTR_NULL(freeBuffer));
    
    return FW_ERR_FAIL;
}

/**
 *******************************************************************************
 * @brief       detedt the address is in the memory buffer 
 * @param       [in/out]  *mem                memory control block
 * @param       [in/out]  *buffer             need free memory address
 * @return      [in/out]  true                is in
 * @return      [in/out]  false               not in
 * @note        None
 *******************************************************************************
 */
bool IsInHeapMemory(struct HeapControlBlock *mem, void *buffer)
{
    fw_assert(IS_PTR_NULL(mem));
    fw_assert(IS_PTR_NULL(buffer));
    
    void *end_addr = (void *)((uint8_t *)mem->Buffer + mem->Size - 1);
    
    if( buffer >= mem->Buffer && buffer <= end_addr)
    {
        return true;
    }
    
    return false;
}

#endif

/** @}*/     /** buffer component */

/**********************************END OF FILE*********************************/
