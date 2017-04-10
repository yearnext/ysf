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
 * @file       ysf_buffer.c                                                    *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-06                                                      *
 * @brief      ysf_buffer source file                                          *
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
 * @defgroup ysf buffer component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_COMPONENT_BUFFER_PATH
#include YSF_TYPE_PATH
#include YSF_COMPILER_PATH
#include YSF_COMPONENT_DEBUG_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_BUFFER_API
/**
 *******************************************************************************
 * @brief       ring buffer init
 * @param       [in/out]  *rb            ring buff control block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  YSF_ERR_NONE   ring buffer init success
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_rbInit( struct ysf_rb_t *rb, uint8_t *buffer, ysf_buf_size_t size )
{
    ysf_assert(IS_PTR_NULL(rb));
    ysf_assert(IS_PTR_NULL(buffer));

    rb->buffer.buffer = buffer;
    rb->buffer.size   = size;

    rb->head          = 0;
    rb->tail          = 0;

    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get ring buffer length
 * @param       [in/out]  *rb                 ring buff control block
 * @return      [in/out]  ysf_buffer_size_t   ring buffer length
 * @note        None
 *******************************************************************************
 */
ysf_buf_size_t ysf_rbGetLen( struct ysf_rb_t *rb )
{
    ysf_assert(IS_PTR_NULL(rb));
    return rb->buffer.size;
}

/**
 *******************************************************************************
 * @brief       get ring buffer can read data size
 * @param       [in/out]  *rb                 ring buffer control block
 * @return      [in/out]  ysf_buffer_size_t   ring buffer can read data size
 * @note        None
 *******************************************************************************
 */
YSF_STATIC_INLINE 
ysf_buf_size_t ysf_rbCanRead( struct ysf_rb_t *rb )
{
    ysf_assert(IS_PTR_NULL(rb));

    if( rb->tail >= rb->head )
    {
        return ((ysf_buf_size_t)(rb->tail - rb->head));
    }
    else
    {
        return ((ysf_buf_size_t)(rb->buffer.size - (rb->head - rb->tail)));
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
YSF_STATIC_INLINE 
ysf_buf_size_t ysf_rbCanWrite( struct ysf_rb_t *rb )
{
    ysf_assert(IS_PTR_NULL(rb));

    ysf_buf_size_t size = 0;

    if( rb->tail >= rb->head )
    {
        size = rb->buffer.size - (rb->tail - rb->head);

        return size;
    }
    else
    {
        size = rb->head - rb->tail;

        return ((size > 1) ? (size) : (0));
    }

//    return 0;
}

/**
 *******************************************************************************
 * @brief       write data to ring buffer
 * @param       [in/out]  *rb                 ring buffer control block
 * @param       [in/out]  *buff               write data buffer
 * @param       [in/out]  rbSize              write data buffer size
 * @return      [in/out]  YSF_ERR_NONE        ring buffer write success
 * @return      [in/out]  YSF_ERR_FAIL        ring buffer write failed
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_rbWrite( struct ysf_rb_t *rb, uint8_t *buff, ysf_buf_size_t rbSize )
{
    ysf_buf_size_t free = 0;
    ysf_buf_size_t i = 0;

    ysf_assert(IS_PTR_NULL(rb));
    ysf_assert(IS_PTR_NULL(buff));
    ysf_assert(rbSize == 0);

    if( rbSize <= ysf_rbCanWrite(rb) )
    {
        if( (rb->tail + rbSize) >= rb->buffer.size )
        {
            free = rb->buffer.size - rb->tail;

            for(i=0; i<free; i++)
            {
                rb->buffer.buffer[rb->tail++] = buff[i];
            }

            for(rb->tail=0; i<rbSize; i++)
            {
                rb->buffer.buffer[rb->tail++] = buff[i];
            }
        }
        else
        {
            for(i=0; i<rbSize; i++)
            {
                rb->buffer.buffer[rb->tail++] = buff[i];
            }
        }

        return YSF_ERR_NONE;
    }
#if USE_YSF_BUFFER_DEBUG
    else
    {
        ysf_log("%s Write data size is too long! \n",__FUNCTION__);
        return YSF_ERR_INVAILD_PARAM;
    }
#endif

    return YSF_ERR_FAIL;
}

/**
 *******************************************************************************
 * @brief       read data from ring buffer
 * @param       [in/out]  *rb                 ring buffer control block
 * @param       [in/out]  *buff               read data buffer
 * @param       [in/out]  rbSize              read data size
 * @return      [in/out]  YSF_ERR_NONE        ring buffer read success
 * @return      [in/out]  YSF_ERR_FAIL        ring buffer read failed
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_rbRead( struct ysf_rb_t *rb, uint8_t *buff, ysf_buf_size_t rbSize)
{
    ysf_buf_size_t free = 0;
    ysf_buf_size_t i = 0;

    ysf_assert(IS_PTR_NULL(rb));
    ysf_assert(IS_PTR_NULL(buff));
    ysf_assert(rbSize == 0);

    if (rbSize <= ysf_rbCanRead(rb))
    {
        if ((rb->head + rbSize) >= rb->buffer.size)
        {
            free = rb->buffer.size - rb->head;

            for (i=0; i<free; i++)
            {
                 buff[i] = rb->buffer.buffer[rb->head++];
            }

            for (rb->head=0; i<rbSize; i++)
            {
                buff[i] = rb->buffer.buffer[rb->head++];
            }
        }
        else
        {
            for (i=0; i<rbSize; i++)
            {
                buff[i] = rb->buffer.buffer[rb->head++];
            }
        }

        return YSF_ERR_NONE;
    }
#if defined(USE_YSF_BUFFER_DEBUG) && USE_YSF_BUFFER_DEBUG
    else
    {
        ysf_log("%s Read data size is too long! \n",__FUNCTION__);
        return YSF_ERR_INVAILD_PARAM;
    }
#endif

    return YSF_ERR_FAIL;
}
#endif

#if USE_YSF_MEMORY_MANAGEMENT_API
/**
 *******************************************************************************
 * @brief       memory block init
 * @param       [in/out]  *mem                memory block
 * @return      [in/out]  YSF_ERR_NONE        memory block init finish
 * @note        None
 *******************************************************************************
 */
YSF_STATIC_INLINE
ysf_err_t ysf_memBlockInit( struct ysf_mem_cb_t *mem )
{
    ysf_assert(IS_PTR_NULL(mem));
    ysf_assert(mem->status == IS_YSF_POOL_NOT_INIT);

    struct ysf_mem_block_t *memCB = NULL;
    ysf_mem_size_t nowNode = 0, nextNode = 0;

    while(1)
    {
        memCB = (struct ysf_mem_block_t *)((void *)&mem->buffer.buffer[nowNode]);
        nextNode = nowNode + mem->alignment;

        memCB->status = IS_MEM_FREE;

        if( nextNode >= mem->buffer.size )
        {
            memCB->next = YSF_MEMORY_CB_NEXT_END;

            break;
        }

        memCB->next = nextNode;

        nowNode = nextNode;
    }

    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       calculation memory alignment size
 * @param       [in/out]  memCBSize           memory control block size
 * @return      [in/out]  ysf_buffer_size_t   calculation results
 * @note        None
 *******************************************************************************
 */
YSF_STATIC_INLINE
ysf_mem_size_t ysf_memAlignmentCal( ysf_mem_size_t memSize )
{
    ysf_mem_size_t size = 0;
    ysf_mem_size_t temp = memSize / 8;

    ((memSize%8) == 0) ? (0) : (temp++);

    size = temp  * 2;
    size = size  * 8;
    
    return size;
}

/**
 *******************************************************************************
 * @brief       malloc need block size calculate
 * @param       [in/out]  *mem                memory block
 * @param       [in/out]  size                need malloc memory size
 * @return      [in/out]  ysf_buffer_size_t   the calculate results
 * @note        None
 *******************************************************************************
 */
YSF_STATIC_INLINE
ysf_mem_size_t ysf_memNeedBlockCal( struct ysf_mem_cb_t *mem, ysf_mem_size_t size )
{
    ysf_mem_size_t needSize = size / mem->alignment;

    return ((size % mem->alignment) == 0) ? (needSize) : (++needSize);
}

/**
 *******************************************************************************
 * @brief       free use block size calculate
 * @param       [in/out]  *mem                memory block
 * @param       [in/out]  *block              use memory block
 * @return      [in/out]  ysf_buffer_size_t   the calculate results
 * @note        None
 *******************************************************************************
 */
YSF_STATIC_INLINE
ysf_mem_size_t ysf_memUseBlockCal(struct ysf_mem_cb_t *mem, struct ysf_mem_block_t *block)
{
    ysf_assert(IS_PTR_NULL(mem));
    ysf_assert(IS_PTR_NULL(block));

    ysf_mem_size_t size = 0;

    if( block->next != YSF_MEMORY_CB_NEXT_END )
    {
        size = (ysf_mem_size_t)((ysf_addr_t)&mem->buffer.buffer[block->next] - (ysf_addr_t)block);
    }
    else
    {
        size = (ysf_mem_size_t)((ysf_addr_t)&mem->buffer.buffer[mem->buffer.size] - (ysf_addr_t)block);
    }

    return (size / mem->alignment);
}

/**
 *******************************************************************************
 * @brief       detection this memory is init
 * @param       [in/out]  *mem           memory management block
 * @return      [in/out]  false          this memory is not initialized
 * @return      [in/out]  true           this memory is initialized
 * @note        None
 *******************************************************************************
 */
YSF_STATIC_INLINE
bool ysf_memIsInit(struct ysf_mem_cb_t *mem)
{
    if( mem == NULL )
    {
        return false;
    }
    
    if( mem->status == IS_YSF_POOL_INIT )
    {
        return true;
    }
    else
    {
        return true;
    }
    
//    return false;
}

/**
 *******************************************************************************
 * @brief       memory init function
 * @param       [in/out]  *mem           memory block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  YSF_ERR_NONE   init success
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_memInit(struct ysf_mem_cb_t *mem, uint8_t *buffer, ysf_mem_size_t size)
{
    ysf_mem_size_t alignment = ysf_memAlignmentCal(sizeof(struct ysf_mem_block_t)/sizeof(char));

    ysf_assert(IS_PTR_NULL(mem));
    ysf_assert(IS_PTR_NULL(buffer));
    ysf_assert(size == 0);
//    ysf_assert((size % alignment) != 0);

    mem->buffer.buffer = buffer;
    mem->buffer.size   = size;
    mem->status        = IS_YSF_POOL_INIT;
    mem->alignment     = alignment;

    ysf_memBlockInit(mem);

    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get memory length
 * @param       [in/out]  *mem                memory block
 * @return      [in/out]  ysf_buffer_size_t   memory length
 * @note        None
 *******************************************************************************
 */
ysf_mem_size_t ysf_memGetLen(struct ysf_mem_cb_t *mem)
{
    if( ysf_memIsInit(mem) == false )
    {
        return 0;
    }
    
    return mem->buffer.size;
}

/**
 *******************************************************************************
 * @brief       get memory alignment
 * @param       [in/out]  *mem                memory block
 * @return      [in/out]  ysf_buffer_size_t   memory alignment
 * @note        None
 *******************************************************************************
 */
ysf_mem_size_t ysf_memGetAlignment(struct ysf_mem_cb_t *mem)
{
    if( ysf_memIsInit(mem) == false )
    {
        return 0;
    }
    
    return mem->alignment;
}

/**
 *******************************************************************************
 * @brief       calculate use memory rate
 * @param       [in/out]  *mem                memory block
 * @return      [in/out]  ysf_buffer_size_t   use memory rate
 * @note        None
 *******************************************************************************
 */
ysf_mem_size_t ysf_memUseRateCal(struct ysf_mem_cb_t *mem)
{
    struct ysf_mem_block_t *node = (struct ysf_mem_block_t *)((void *)&mem->buffer.buffer);
    ysf_mem_size_t use = 0;
    
    if( ysf_memIsInit(mem) == false )
    {
        return 0;
    }
    
    while(1)
    {
        if(node->status == IS_MEM_USE)
        {
            use = ysf_memUseBlockCal(mem, node);
            use = use * 8;
        }

        if( node->next == YSF_MEMORY_CB_NEXT_END )
        {
            break;
        }

        node = (struct ysf_mem_block_t *)((void *)&mem->buffer.buffer[node->next]);
    }

    return (use / mem->buffer.size);
}

/**
 *******************************************************************************
 * @brief       memory malloc
 * @param       [in/out]  *mem           memory block
 * @param       [in/out]  size           malloc size
 * @return      [in/out]  NULL       malloc failed
 * @return      [in/out]  addr           malloc success
 * @note        None
 *******************************************************************************
 */
void *ysf_memMalloc( struct ysf_mem_cb_t *mem, ysf_mem_size_t size )
{
    ysf_assert(IS_PTR_NULL(mem));
    ysf_assert(mem->status == IS_YSF_POOL_NOT_INIT);

    struct ysf_mem_block_t *nowNode  = (struct ysf_mem_block_t *)((void *)mem->buffer.buffer);
    struct ysf_mem_block_t *startNode = NULL;

    const ysf_mem_size_t needSize = ysf_memNeedBlockCal(mem, ((sizeof(struct ysf_mem_block_t)/sizeof(char))+size));
    ysf_mem_size_t getSize  = 0;

    if( ysf_memIsInit(mem) == false )
    {
        return NULL;
    }
    
    while(1)
    {
        if( nowNode->status == IS_MEM_FREE )
        {
            (startNode == NULL) ? (startNode = nowNode) : (0);

            if( ++getSize >= needSize )
            {
                startNode->next   = nowNode->next;
                startNode->status = IS_MEM_USE;

                return ((void *)startNode->data);
            }
        }
        else
        {
            getSize   = 0;
            startNode = NULL;
        }

        if( nowNode->next == YSF_MEMORY_CB_NEXT_END )
        {
            break;
        }

        nowNode = (struct ysf_mem_block_t *)((void *)&mem->buffer.buffer[nowNode->next]);
    }

    return NULL;
}

/**
 *******************************************************************************
 * @brief       memory free
 * @param       [in/out]  *mem           memory block
 * @param       [in/out]  size           use memory addr
 * @return      [in/out]  YSF_ERR_FAIL   free failed
 * @return      [in/out]  YSF_ERR_NONE   free success
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_memFree(struct ysf_mem_cb_t *mem, void *useMem)
{
    ysf_assert(IS_PTR_NULL(mem));
    ysf_assert(mem->status == IS_YSF_POOL_NOT_INIT);

    struct ysf_mem_block_t *node  = (struct ysf_mem_block_t *)((void *)mem->buffer.buffer);
    ysf_mem_size_t next;
    ysf_mem_size_t block;

    if( ysf_memIsInit(mem) == false )
    {
        return YSF_ERR_FAIL;
    }
    
    if(useMem == NULL)
    {
        return YSF_ERR_FAIL;
    }

    while(1)
    {
        if( node->data == useMem )
        {
            if( node->status == IS_MEM_FREE )
            {
                return YSF_ERR_FAIL;
            }

            break;
        }

        if( node->next == YSF_MEMORY_CB_NEXT_END )
        {
            return YSF_ERR_FAIL;
        }

        node = (struct ysf_mem_block_t *)((void *)&mem->buffer.buffer[node->next]);
    }

    block = ysf_memUseBlockCal(mem, node);
    next  = (ysf_mem_size_t)((ysf_addr_t)node - (ysf_addr_t)mem->buffer.buffer);
    next  = next + mem->alignment;

    for( ; block>0; block-- )
    {
        node->status = IS_MEM_FREE;
        node->next   = next;

        node = (struct ysf_mem_block_t *)((void *)&mem->buffer.buffer[node->next]);
        next += mem->alignment;
    }

    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       detection whether memory areas
 * @param       [in/out]  *mem           memory management block
 * @param       [in/out]  *useMem        need to test addresses
 * @return      [in/out]  false          the address not in this memory areas
 * @return      [in/out]  true           the address is in this memory areas
 * @note        None 
 *******************************************************************************
 */
bool ysf_memIsIn(struct ysf_mem_cb_t *mem, void *useMem)
{    
    if( useMem == NULL )
    {
        return false;
    }
    
    if( mem == NULL )
    {
        return false;
    }
    
    if( (useMem >= (void *)&mem->buffer.buffer[0]) && (useMem < (void *)&mem->buffer.buffer[mem->buffer.size]) )
    {
        return true;
    }
    else
    {
        return false;
    }
    
//    return false;
}
#endif

/** @}*/     /** ysf buffer component */

/**********************************END OF FILE*********************************/
