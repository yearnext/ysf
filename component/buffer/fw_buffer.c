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
 * @brief      framework buffer component source file                          *
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
 * @defgroup framework buffer component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_BUFFER_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_BUFFER_API
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
fw_err_t fw_rb_init(struct fw_buffer_t *rb, uint8_t *buffer, uint16_t size )
{
    fw_assert(IS_PTR_NULL(rb));
    fw_assert(IS_PTR_NULL(buffer));

    rb->buffer = buffer;
    rb->size   = size;
    rb->head   = 0;
    rb->tail   = 0;

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
fw_err_t fw_rb_getlen(struct fw_buffer_t *rb, uint16_t *size)
{
    fw_assert(IS_PTR_NULL(rb));
    
    *size =  rb->size;
    
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
uint16_t _rb_can_read(struct fw_buffer_t *rb )
{
    fw_assert(IS_PTR_NULL(rb));

    if( rb->tail >= rb->head )
    {
        return ((uint16_t)(rb->tail - rb->head));
    }
    else
    {
        return ((uint16_t)(rb->size - (rb->head - rb->tail)));
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
uint16_t _rb_can_write(struct fw_buffer_t *rb)
{
    fw_assert(IS_PTR_NULL(rb));

    uint16_t size = 0;

    if( rb->tail >= rb->head )
    {
        size = rb->size - (rb->tail - rb->head);

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
 * @param       [in/out]  *rb                ring buffer control block
 * @param       [in/out]  *buff              write data buffer
 * @param       [in/out]  rbSize             write data buffer size
 * @return      [in/out]  FW_ERR_NONE        ring buffer write success
 * @return      [in/out]  FW_ERR_FAIL        ring buffer write failed
 * @note        None
 *******************************************************************************
 */
fw_err_t fw_rb_write(struct fw_buffer_t *rb, uint8_t *buffer, uint16_t rbSize)
{
    uint16_t free = 0;
    uint16_t i = 0;

    fw_assert(IS_PTR_NULL(rb));
    fw_assert(IS_PTR_NULL(buffer));
    fw_assert(rbSize == 0);

    if( rbSize <= _rb_can_write(rb) )
    {
        if( (rb->tail + rbSize) >= rb->size )
        {
            free = rb->size - rb->tail;

            for(i=0; i<free; i++)
            {
                rb->buffer[rb->tail++] = buffer[i];
            }

            for(rb->tail=0; i<rbSize; i++)
            {
                rb->buffer[rb->tail++] = buffer[i];
            }
        }
        else
        {
            for(i=0; i<rbSize; i++)
            {
                rb->buffer[rb->tail++] = buffer[i];
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
fw_err_t fw_rb_read( struct fw_buffer_t *rb, uint8_t *buffer, uint16_t rbSize)
{
    uint16_t free = 0;
    uint16_t i = 0;

    fw_assert(IS_PTR_NULL(rb));
    fw_assert(IS_PTR_NULL(buffer));
    fw_assert(rbSize == 0);

    if (rbSize <= _rb_can_read(rb))
    {
        if ((rb->head + rbSize) >= rb->size)
        {
            free = rb->size - rb->head;

            for (i=0; i<free; i++)
            {
                 buffer[i] = rb->buffer[rb->head++];
            }

            for (rb->head=0; i<rbSize; i++)
            {
                buffer[i] = rb->buffer[rb->head++];
            }
        }
        else
        {
            for (i=0; i<rbSize; i++)
            {
                buffer[i] = rb->buffer[rb->head++];
            }
        }

        return FW_ERR_NONE;
    }

    return FW_ERR_FAIL;
}
#endif

#if USE_FRAMEWORK_MEMORY_MANAGEMENT_API
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
fw_err_t fw_mem_init(struct fw_memcontrol_t *mem, uint8_t *buffer, uint32_t size)
{
	if (mem == NULL || buffer == NULL || size > INT32_MAX ||size < sizeof(struct fw_memblock_t))
	{
		return FW_ERR_FAIL;
	}

    mem->buffer       = buffer;
    mem->size         = size;
    
    mem->head->next   = NULL;
	mem->head->size   = size - sizeof(struct fw_memblock_t);
    mem->head->status = 0;
    
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
//fw_err_t ysf_mem_deinit(struct fw_memcontrol_t *mem)
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
uint32_t _mem_cal_block_size(uint32_t size, uint32_t alignment)
{
	uint32_t temp = size % alignment;
	uint32_t value = size;

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
 * @param       [in/out]  void*               alloc memory address
 * @return      [in/out]  FW_ERR_NONE         alloc success
 * @return      [in/out]  FW_ERR_FAIL         alloc failed
 * @note        None
 *******************************************************************************
 */
fw_err_t fw_mem_alloc(struct fw_memcontrol_t *mem, uint32_t size, void *ret_addr)
{
    struct fw_memblock_t *now     = mem->head;
    struct fw_memblock_t *next    = mem->head;
	uint32_t freeSize             = 0;
	uint32_t useSize              = _mem_cal_block_size(size, 4) + sizeof(struct fw_memblock_t);

    if(mem == NULL || size == 0)
    {
        ret_addr = NULL;
        return FW_ERR_FAIL;
    }

    ret_addr = NULL;
    
    while(1)
    {
        if(now == NULL)
        {
            return FW_ERR_FAIL;
        }
        
        if(now->status == 0)
        {
            if( now->size >= useSize )
            {
				freeSize     = now->size;
				now->size    = useSize;
                next         = (struct fw_memblock_t *)((void *)((uint8_t *)now + useSize));
				next->size   = freeSize - useSize;

                next->next   = now->next;
                now->next    = next;
                
                next->status = false;
                now->status  = true;
                
                ret_addr = (void *)(now + 1);
                
                return FW_ERR_NONE;
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
 * @return      [in/out]  FW_ERR_NONE         free success
 * @return      [in/out]  FW_ERR_FAIL         free failed
 * @note        None
 *******************************************************************************
 */
fw_err_t fw_mem_free(struct fw_memcontrol_t *mem, void *buffer)
{
    struct fw_memblock_t *now       = mem->head;
    struct fw_memblock_t *last      = NULL;
    struct fw_memblock_t *data_addr = NULL;
    bool                 status     = false;
    
    if(buffer == NULL || mem == NULL)
    {
        return FW_ERR_FAIL;
    }
    
    while(1)
    {
        // free memory
        data_addr = now + 1;
        if( data_addr == buffer )
        {
            status      = true;
            now->status = 0;
        }

        // merge memory block
        if( now->status == 0 )
        {
            if( last == NULL )
            {
                last = now;
            }
            else if(now->next == NULL)
            {
                if(now->status == 0)
                {
                    last->next = NULL;
                    last->size = ((uint32_t)(now - last)) * sizeof(struct fw_memblock_t) + now->size;
                }
                else
                {
                    last->next = now;
                    last->size = ((uint32_t)(now - last)) * sizeof(struct fw_memblock_t);
                }
                
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
					last->size = ((uint16_t)(now - last)) * sizeof(struct fw_memblock_t);
				}

				last = NULL;
            }
        }

        now = now->next;        
		
		if(now == NULL)
        {
            break;
        }
    }
    
    if( status == true )
    {
        return FW_ERR_NONE;
    }
    
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
bool fw_mem_isIn(struct fw_memcontrol_t *mem, void *buffer)
{
    if(mem == NULL || buffer == NULL)
    {
        return false;
    }
    
    void *end_addr = (void *)((uint8_t *)mem->buffer + mem->size - 1);
    
    if( buffer >= mem->buffer && buffer <= end_addr)
    {
        return true;
    }
    
    return false;
}

#endif

/** @}*/     /** framework buffer component */

/**********************************END OF FILE*********************************/
