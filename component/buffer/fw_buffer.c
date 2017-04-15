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
#include "core_path.h"
#include _FW_TYPE_PATH
#include _FW_BUFFER_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH

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
 * @return      [in/out]  FW_ERR_NONE   ring buffer init success
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_rbInit( struct ysf_rb_t *rb, uint8_t *buffer, uint16_t size )
{
    ysf_assert(IS_PTR_NULL(rb));
    ysf_assert(IS_PTR_NULL(buffer));

    rb->buffer.buffer = buffer;
    rb->buffer.size   = size;

    rb->head          = 0;
    rb->tail          = 0;

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get ring buffer length
 * @param       [in/out]  *rb                 ring buff control block
 * @return      [in/out]  ysf_buffer_size_t   ring buffer length
 * @note        None
 *******************************************************************************
 */
uint16_t ysf_rbGetLen( struct ysf_rb_t *rb )
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
__STATIC_INLINE 
uint16_t ysf_rbCanRead( struct ysf_rb_t *rb )
{
    ysf_assert(IS_PTR_NULL(rb));

    if( rb->tail >= rb->head )
    {
        return ((uint16_t)(rb->tail - rb->head));
    }
    else
    {
        return ((uint16_t)(rb->buffer.size - (rb->head - rb->tail)));
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
uint16_t ysf_rbCanWrite( struct ysf_rb_t *rb )
{
    ysf_assert(IS_PTR_NULL(rb));

    uint16_t size = 0;

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
 * @return      [in/out]  FW_ERR_NONE        ring buffer write success
 * @return      [in/out]  FW_ERR_FAIL        ring buffer write failed
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_rbWrite( struct ysf_rb_t *rb, uint8_t *buff, uint16_t rbSize )
{
    uint16_t free = 0;
    uint16_t i = 0;

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

        return FW_ERR_NONE;
    }
#if USE_YSF_BUFFER_DEBUG
    else
    {
        ysf_log("%s Write data size is too long! \n",__FUNCTION__);
        return FW_ERR_INVAILD_PARAM;
    }
#endif

    return FW_ERR_FAIL;
}

/**
 *******************************************************************************
 * @brief       read data from ring buffer
 * @param       [in/out]  *rb                 ring buffer control block
 * @param       [in/out]  *buff               read data buffer
 * @param       [in/out]  rbSize              read data size
 * @return      [in/out]  FW_ERR_NONE        ring buffer read success
 * @return      [in/out]  FW_ERR_FAIL        ring buffer read failed
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_rbRead( struct ysf_rb_t *rb, uint8_t *buff, uint16_t rbSize)
{
    uint16_t free = 0;
    uint16_t i = 0;

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

        return FW_ERR_NONE;
    }
#if defined(USE_YSF_BUFFER_DEBUG) && USE_YSF_BUFFER_DEBUG
    else
    {
        ysf_log("%s Read data size is too long! \n",__FUNCTION__);
        return FW_ERR_INVAILD_PARAM;
    }
#endif

    return FW_ERR_FAIL;
}
#endif

#if USE_YSF_MEMORY_MANAGEMENT_API
/**
 *******************************************************************************
 * @brief       memory init
 * @param       [in/out]  **mem               memory control block
 * @param       [in/out]  *buffer             memory buffer address
 * @param       [in/out]  rbSize              memory buffer size
 * @return      [in/out]  FW_ERR_NONE        ring buffer read success
 * @return      [in/out]  FW_ERR_FAIL        ring buffer read failed
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_mem_init(struct ysf_mem_ctrl_t *mem, uint8_t *buffer, uint16_t size)
{
	if (mem == NULL || buffer == NULL || size < sizeof(struct ysf_mem_block_t))
	{
		return FW_ERR_FAIL;
	}

    mem->buffer       = buffer;
    mem->size         = size;
    
    mem->head->next   = NULL;
	mem->head->size   = size - sizeof(struct ysf_mem_block_t);
    mem->head->status = false;
    
    return FW_ERR_NONE;
}

///**
// *******************************************************************************
// * @brief       memory deinit
// * @param       [in/out]  **mem               memory control block
// * @return      [in/out]  FW_ERR_NONE        ring buffer read success
// * @return      [in/out]  FW_ERR_FAIL        ring buffer read failed
// * @note        None
// *******************************************************************************
// */
//fw_err_t ysf_mem_deinit(struct ysf_mem_ctrl_t *mem)
//{
//    if (mem == NULL)
//	{
//		return FW_ERR_FAIL;
//	}
//    
//	mem->buffer = NULL;
//    mem->size   = 0;
//    
//    return FW_ERR_NONE;
//}

/**
 *******************************************************************************
 * @brief       cal need memory block size
 * @param       [in/out]  size                memory control block
 * @param       [in/out]  alignment           memory alignment size
 * @return      [in/out]  value               need block size
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
uint16_t ysf_mem_cal_alignment(uint16_t size, uint16_t alignment)
{
	uint16_t temp = size % alignment;
	uint16_t value = size;

	if (temp)
	{
		value += alignment - temp;
	}

	return value;
}

/**
 *******************************************************************************
 * @brief       memory alloc 
 * @param       [in/out]  *mem                memory control block
 * @param       [in/out]  size                alloc memory size
 * @return      [in/out]  void*               alloc memory address
 * @note        None
 *******************************************************************************
 */
void *ysf_mem_alloc(struct ysf_mem_ctrl_t *mem, uint16_t size)
{
    struct ysf_mem_block_t *now     = mem->head;
    struct ysf_mem_block_t *next    = mem->head;
	uint16_t freeSize = 0;
	uint16_t useSize  = ysf_mem_cal_alignment(size, 4) + sizeof(struct ysf_mem_block_t);

    if(mem == NULL || size == 0)
    {
        return NULL;
    }

    while(1)
    {
        if(now == NULL)
        {
            return NULL;
        }
        
        if(now->status == false)
        {
            if( now->size >= useSize )
            {
				freeSize     = now->size;
				now->size    = useSize;
                next         = (struct ysf_mem_block_t *)((void *)((uint8_t *)now + useSize));
				next->size   = freeSize - useSize;

                next->next   = now->next;
                now->next    = next;
                
                next->status = false;
                now->status  = true;
                
                return (void *)(now+1);
            }
        }
        
        now = now->next;
    }
    
//    return NULL;
}

/**
 *******************************************************************************
 * @brief       memory free 
 * @param       [in/out]  *mem                memory control block
 * @param       [in/out]  *buffer             need free memory address
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void ysf_mem_free(struct ysf_mem_ctrl_t *mem, void *buffer)
{
    struct ysf_mem_block_t *now       = mem->head;
    struct ysf_mem_block_t *last      = NULL;
    struct ysf_mem_block_t *data_addr = NULL;
    
    if(buffer == NULL || mem == NULL)
    {
        return;
    }
    
    while(1)
    {
        // free memory
        data_addr = now + 1;
        if( data_addr == buffer )
        {
            now->status = false;
        }

        // merge memory block
        if( now->status == false )
        {
            if( last == NULL )
            {
                last = now;
            }
            else if(now->next == NULL)
            {
                if(now->status == false)
                {
                    last->next = NULL;
                    last->size = ((uint16_t)(now - last)) * sizeof(struct ysf_mem_block_t) + now->size;
                }
                else
                {
                    last->next = now;
                    last->size = ((uint16_t)(now - last)) * sizeof(struct ysf_mem_block_t);
                }
                
//                last->status = false;
                last = NULL;
            }
        }
        else
        {
            if( last != NULL )
            {
				if (last->next != now)
				{
					last->next = now;
					last->size = ((uint16_t)(now - last)) * sizeof(struct ysf_mem_block_t);
//					last->status = false;
				}

				last = NULL;
            }
        }

        now = now->next;        
		
		if(now == NULL)
        {
            return;
        }
    }
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
bool ysf_mem_is_in(struct ysf_mem_ctrl_t *mem, void *buffer)
{
    if( buffer >= (void *)mem->buffer && buffer <= (void *)&mem->buffer[mem->size] )
    {
        return true;
    }
    
    return false;
}

#endif

/** @}*/     /** ysf buffer component */

/**********************************END OF FILE*********************************/
