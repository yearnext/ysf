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
    Fw_Assert(IS_PTR_NULL(rb));
    Fw_Assert(IS_PTR_NULL(rbBuffer));
    Fw_Assert(rbSize == 0);
    
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
    Fw_Assert(IS_PTR_NULL(rb));
    Fw_Assert(IS_PTR_NULL(getSize));
    
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
    Fw_Assert(IS_PTR_NULL(rb));

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
    Fw_Assert(IS_PTR_NULL(rb));
    
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
    Fw_Assert(IS_PTR_NULL(rb));
    Fw_Assert(IS_PTR_NULL(writeBuffer));
    Fw_Assert(writeSize == 0);
    
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
    Fw_Assert(IS_PTR_NULL(rb));
    Fw_Assert(IS_PTR_NULL(readBuffer));
    Fw_Assert(readSize == 0); 
    
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

#if USE_MEMORY_MANAGEMENT_COMPONENT
//fw_err_t Fw_Mem_Init(struct _Fw_MemMgmtBlock *memMgmt, void *buffer, uint32_t len)
//{
//    Fw_Assert(IS_PTR_NULL(memMgmt));
//    Fw_Assert(IS_PTR_NULL(buffer));
//    Fw_Assert(len == 0);
//    
//    //< set poll address
//    memMgmt->Poll = (struct _Fw_MemBlock *)buffer;
//    memMgmt->Size = len;
//    
//    memMgmt->Poll->Last = NULL;
//    memMgmt->Poll->Next = NULL;
//    memMgmt->Poll->Size = memMgmt->Size - sizeof(struct _Fw_MemBlock);
//    memMgmt->Poll->Status = false;
//    
//    //< init list
//    memMgmt->FreeListHead = memMgmt->Poll;
//    memMgmt->FreeListTail = NULL;
//    
//    memMgmt->UseListHead = NULL;
//    memMgmt->UseListTail = NULL;
//    
//    return FW_ERR_NONE;
//}

//#define CalNeedMemorySize(len) (len + sizeof(struct _Fw_MemBlock))
//#define CalNeedMemoryBlockSize(len) (len + sizeof(struct _Fw_MemBlock))

//void *Fw_Mem_Alloc(struct _Fw_MemMgmtBlock *memMgmt, uint32_t len)
//{
//    Fw_Assert(IS_PTR_NULL(memMgmt));
//    Fw_Assert(len == 0);
//    
//    uint32_t needSize = CalNeedMemorySize(len);
//    uint32_t needBlockSize = CalNeedMemoryBlockSize(len);
//    struct _Fw_MemBlock *ptr = memMgmt->FreeListHead;
//    uint8_t *nextBlock;
//    
//    while(1)
//    {
//        if(ptr->Size > needSize)
//        {
//            ptr->
//        }
//        else
//        {
//            
//        }
//    }
//        
//    return NULL;
//}

//void Fw_Mem_Free(struct _Fw_MemMgmtBlock *memMgmt, void *mem)
//{
//    
//}

///**
// *******************************************************************************
// * @brief       cal need memory size
// * @param       [in/out]  size                memory control block
// * @param       [in/out]  alignment           memory alignment size
// * @return      [in/out]  value               need block size
// * @note        None
// *******************************************************************************
// */
//__STATIC_INLINE
//uint32_t cal_need_memory_size(uint32_t useSize)
//{
//	uint32_t needSize = useSize + 16;
//    
//    needSize >>= HEAP_MEMORY_ALIGNMENT_POS;
//    
//    if(needSize % HEAP_MEMORY_ALIGNMENT_SIZE)
//    {
//        needSize++;
//    }

//	return needSize;
//}

///**
// *******************************************************************************
// * @brief       memory init
// * @param       [in/out]  **mem              memory control block
// * @param       [in/out]  *buffer            memory buffer address
// * @param       [in/out]  rbSize             memory buffer size
// * @return      [in/out]  FW_ERR_NONE        memory init success
// * @return      [in/out]  FW_ERR_FAIL        memory init failed
// * @note        None
// *******************************************************************************
// */
//fw_err_t InitHeapMemory(struct HeapControlBlock *mem, uint8_t *heapHeadAddr, uint32_t heapSize)
//{
//    Fw_Assert(IS_PTR_NULL(mem));
//    Fw_Assert(IS_PTR_NULL(heapHeadAddr));
//    Fw_Assert(heapSize < HEAP_MEMORY_ALIGNMENT_SIZE);
//    
//    struct HeapMemoryBlock *now, *last;
//    uint32_t blockSize = heapSize / HEAP_MEMORY_ALIGNMENT_SIZE;
//    uint32_t i;
//    
//    mem->Buffer       = heapHeadAddr;
//    mem->Size         = heapSize;

//    for(i=1, last=NULL, now=mem->Head; i<blockSize; i++)
//    {
//        now->Management.Last   = last;
//        now->Management.Next   = now + 1;
//        now->Management.Size   = 1;
//        now->Management.Status = 0;
//        
//        last = now;
//        now  = now->Management.Next;
//    }
//    
//    now->Management.Last   = last;
//    now->Management.Next   = NULL;
//    now->Management.Size   = 1;
//    now->Management.Status = 0;
//    
//    return FW_ERR_NONE;
//}

/////**
//// *******************************************************************************
//// * @brief       memory deinit
//// * @param       [in/out]  **mem              memory control block
//// * @return      [in/out]  FW_ERR_NONE        ring buffer read success
//// * @return      [in/out]  FW_ERR_FAIL        ring buffer read failed
//// * @note        None
//// *******************************************************************************
//// */
////fw_err_t ysf_mem_deinit(struct HeapControlBlock *mem)
////{
////    Fw_Assert(IS_PTR_NULL(mem));
////    
////	mem->Buffer = NULL;
////    mem->Size   = 0;
////    
////    return FW_ERR_NONE;
////}

///**
// *******************************************************************************
// * @brief       memory alloc 
// * @param       [in/out]  *mem                memory control block
// * @param       [in/out]  size                alloc memory size
// * @param       [in/out]  void*               alloc memory address
// * @return      [in/out]  FW_ERR_NONE         alloc success
// * @return      [in/out]  FW_ERR_FAIL         alloc failed
// * @note        None
// *******************************************************************************
// */
//fw_err_t AllocHeapMemory(struct HeapControlBlock *mem, uint32_t needSize, void **allocAddr)
//{
//    Fw_Assert(IS_PTR_NULL(mem));
//    Fw_Assert(needSize == 0);
//    
//    uint32_t useSize = cal_need_memory_size(needSize);
//    uint32_t count   = 0;
//    
//    struct HeapMemoryBlock *now, *begin;
//    
//    now = mem->Head;
//    
//    while(1)
//    {
//        if(now == NULL)
//        {
//            *allocAddr = NULL;
//            break;
//        }
//        else
//        {
//            if(now->Management.Status == 0)
//            {
//                if(count == 0)
//                {
//                    begin = now;
//                    count++;
//                }
//                else
//                {
//                    if(++count >= useSize)
//                    {
//                        *allocAddr = (void *)&begin->data;
//                        begin->Management.Next = begin + useSize;
//                        begin->Management.Size = useSize;
//                        begin->Management.Status = 1;
//                        
//                        return FW_ERR_NONE;
//                    }
//                }
//            }
//            else
//            {
//                count = 0;
//            }
//        }
//        
//        now = now->Management.Next;
//    }
//    
//    return FW_ERR_FAIL;
//}

///**
// *******************************************************************************
// * @brief       memory free 
// * @param       [in/out]  *mem                memory control block
// * @param       [in/out]  *buffer             need free memory address
// * @return      [in/out]  FW_ERR_NONE         free success
// * @return      [in/out]  FW_ERR_FAIL         free failed
// * @note        None
// *******************************************************************************
// */
//fw_err_t FreeHeapMemory(struct HeapControlBlock *mem, void *freeBuffer)
//{
//    Fw_Assert(IS_PTR_NULL(mem));
//    Fw_Assert(IS_PTR_NULL(freeBuffer));
//    
//    struct HeapMemoryBlock *now, *last;
//    uint32_t i;
//    
//    last = NULL;
//    now = mem->Head;
//    
//    while(1)
//    {
//        if(now == NULL)
//        {
//            break;
//        }
//        else
//        {
//            if(now->data == freeBuffer && now->Management.Status)
//            {
//                for(i=now->Management.Size; i>0; i--)
//                {
//                    now->Management.Last = last;
//                    now->Management.Next = now + 1;
//                    now->Management.Size = 1;
//                    now->Management.Status = 0;
//                    
//                    last = now;
//                    now = now->Management.Next;
//                }
//            }
//        }
//        
//        last = now;
//        now = now->Management.Next;
//    }
//    
//    return FW_ERR_FAIL;
//}

///**
// *******************************************************************************
// * @brief       detedt the address is in the memory buffer 
// * @param       [in/out]  *mem                memory control block
// * @param       [in/out]  *buffer             need free memory address
// * @return      [in/out]  true                is in
// * @return      [in/out]  false               not in
// * @note        None
// *******************************************************************************
// */
//bool IsInHeapMemory(struct HeapControlBlock *mem, void *buffer)
//{
//    Fw_Assert(IS_PTR_NULL(mem));
//    Fw_Assert(IS_PTR_NULL(buffer));
//    
//    void *end_addr = (void *)((uint8_t *)mem->Buffer + mem->Size - 1);
//    
//    if( buffer >= mem->Buffer && buffer <= end_addr)
//    {
//        return true;
//    }
//    
//    return false;
//}

#endif

/** @}*/     /** buffer component */

/**********************************END OF FILE*********************************/
