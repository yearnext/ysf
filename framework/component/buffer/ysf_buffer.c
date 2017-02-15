/**
 ******************************************************************************
  * @file       ysf_buffer.c
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-01-06
  * @brief      ysf_buffer source file
  * @par        work platform
  *                 Windows
  * @par        compiler
  * 				GCC
 ******************************************************************************
  * @note
  * 1. achieve ring buffer, queue, memory pool
 ******************************************************************************
 */

/**
 * @defgroup ysf_ringbuff閰嶇疆
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_buffer.h"
#include "ysf_type.h"
#include "ysf_debug.h"

/* Private define ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_RING_BUFFER_PTR
ysf_err_t ysf_rbInit( ysf_rb_t *rb,
                      ysf_u8_t *buffer,
                      ysf_buffer_size_t size )
{
    ysf_assert(IS_PTR_NULL(rb));
    ysf_assert(IS_PTR_NULL(buffer));

    rb->buffer.buffer = buffer;
    rb->buffer.size   = size;

    rb->head          = buffer;
    rb->tail          = buffer;

    return YSF_ERR_NONE;
}

ysf_buffer_size_t ysf_rbCanRead(ysf_rb_t *rb)
{
    ysf_assert(IS_PTR_NULL(rb));

    if( rb->tail >= rb->head )
    {
        return (ysf_buffer_size_t)(rb->tail - rb->head);
    }
    else
    {
        return (rb->buffer.size - (ysf_buffer_size_t)(rb->head - rb->tail));
    }

    return 0;
}

ysf_buffer_size_t ysf_rbCanWrite(ysf_rb_t *rb)
{
    ysf_assert(IS_PTR_NULL(rb));

    if( rb->tail >= rb->head )
    {
        if( (rb->tail - rb->head) < rb->buffer.size )
        {
            return (rb->buffer.size - (ysf_buffer_size_t)(rb->tail - rb->head));
        }
    }
    else
    {
        if( (rb->head - rb->tail) > 1 )
        {
            return (ysf_buffer_size_t)(rb->head - rb->tail);
        }
    }

    return 0;
}

ysf_err_t ysf_rbWrite(ysf_rb_t *rb, ysf_u8_t *buff, ysf_buffer_size_t rbSize)
{
    ysf_u8_t *buffEndAddr = &rb->buffer.buffer[rb->buffer.size];
    ysf_buffer_size_t buffEndFree = 0;
    ysf_buffer_size_t i = 0;

    ysf_assert(IS_PTR_NULL(rb));
    ysf_assert(IS_PTR_NULL(buff));
    ysf_assert(rbSize == 0);

    if( rbSize <= ysf_rbCanWrite(rb) )
    {
        if( (rb->tail + rbSize) >= buffEndAddr )
        {
            buffEndFree = buffEndAddr - rb->tail;

            for(i=0; i<buffEndFree; i++)
            {
                *(rb->tail) = buff[i];
                rb->tail++;
            }

            for(rb->tail = rb->buffer.buffer; i<rbSize; i++)
            {
                *(rb->tail) = buff[i];
                rb->tail++;
            }
        }
        else
        {
            for(i=0; i<rbSize; i++)
            {
                *(rb->tail) = buff[i];
                rb->tail++;
            }
        }

        return YSF_ERR_NONE;
    }
#if USE_YSF_BUFFER_DEBUG
    else
    {
        ysf_LOG("%s Write data size is too long! \n",__FUNCTION__);
        return YSF_ERR_INVAILD_PARAM;
    }
#endif

    return YSF_ERR_FAIL;
}

ysf_err_t ysf_rbRead(ysf_rb_t *rb, ysf_u8_t *buff, ysf_buffer_size_t rbSize)
{
    ysf_u8_t *buffEndAddr = &rb->buffer.buffer[rb->buffer.size];
    ysf_buffer_size_t buffEndFree = 0;
    ysf_buffer_size_t i = 0;

    ysf_assert(IS_PTR_NULL(rb));
    ysf_assert(IS_PTR_NULL(buff));
    ysf_assert(rbSize == 0);

    if (rbSize <= ysf_rbCanRead(rb))
    {
        if ((rb->head + rbSize) >= buffEndAddr)
        {
            buffEndFree = buffEndAddr - rb->head;

            for (i = 0; i < buffEndFree; i++, rb->head++)
            {
                 buff[i] = *(rb->head);
            }

            for (rb->head = rb->buffer.buffer; i < rbSize; i++, rb->head++)
            {
                buff[i] = *(rb->head);
            }
        }
        else
        {
            for (i = 0; i < rbSize; i++, rb->head++)
            {
                buff[i] = *(rb->head);
            }
        }

        return YSF_ERR_NONE;
    }
#if USE_YSF_BUFFER_DEBUG
    else
    {
        ysf_LOG("%s Read data size is too long! \n",__FUNCTION__);
        return YSF_ERR_INVAILD_PARAM;
    }
#endif

    return YSF_ERR_FAIL;
}

#else
ysf_err_t ysf_rbInit( ysf_rb_t *cb,
                                ysf_u8_t *buffer,
                                ysf_buffer_size_t size )
{
    ysf_assert(IS_PTR_NULL(cb));
    ysf_assert(IS_PTR_NULL(buffer));

    cb->buffer.buffer = buffer;
    cb->buffer.size   = size;

    cb->head          = 0;
    cb->tail          = 0;

    return YSF_ERR_NONE;
}


ysf_buffer_size_t ysf_rbCanRead(ysf_rb_t *rb)
{
    ysf_assert(IS_PTR_NULL(rb));

    if( rb->tail >= rb->head )
    {
        return (rb->tail - rb->head);
    }
    else
    {
        return (rb->buffer.size - (rb->head - rb->tail));
    }

    return 0;
}

ysf_buffer_size_t ysf_rbCanWrite(ysf_rb_t *rb)
{
    ysf_buffer_size_t size = 0;

    ysf_assert(IS_PTR_NULL(rb));

    if( rb->tail >= rb->head )
    {
        size = rb->buffer.size - (rb->tail - rb->head);

        return size;
    }
    else
    {
        size = rb->head - rb->tail;

        if( size > 1 )
        {
            return size;
        }
    }

    return 0;
}

ysf_err_t ysf_rbWrite(ysf_rb_t *rb, ysf_u8_t *buff, ysf_buffer_size_t rbSize)
{
    ysf_u8_t *buffEndAddr = &rb->buffer.buffer[rb->buffer.size];
    ysf_buffer_size_t buffEndFree = 0;
    ysf_buffer_size_t i = 0;

    ysf_assert(IS_PTR_NULL(rb));
    ysf_assert(IS_PTR_NULL(buff));
    ysf_assert(rbSize == 0);

    if( rbSize <= ysf_rbCanWrite(rb) )
    {
        if( (rb->tail + rbSize) >= buffEndAddr )
        {
            buffEndFree = buffEndAddr - rb->tail;

            for(i=0; i<buffEndFree; i++)
            {
                *(rb->tail) = buff[i];
                rb->tail++;
            }

            for(rb->tail = rb->buffer.buffer; i<rbSize; i++)
            {
                *(rb->tail) = buff[i];
                rb->tail++;
            }
        }
        else
        {
            for(i=0; i<rbSize; i++)
            {
                *(rb->tail) = buff[i];
                rb->tail++;
            }
        }

        return YSF_ERR_NONE;
    }
#if USE_YSF_BUFFER_DEBUG
    else
    {
        ysf_LOG("%s Write data size is too long! \n",__FUNCTION__);
        return YSF_ERR_INVAILD_PARAM;
    }
#endif

    return YSF_ERR_FAIL;
}

ysf_err_t ysf_rbRead(ysf_rb_t *rb, ysf_u8_t *buff, ysf_buffer_size_t rbSize)
{
    ysf_u8_t *buffEndAddr = &rb->buffer.buffer[rb->buffer.size];
    ysf_buffer_size_t buffEndFree = 0;
    ysf_buffer_size_t i = 0;

    ysf_assert(IS_PTR_NULL(rb));
    ysf_assert(IS_PTR_NULL(buff));
    ysf_assert(rbSize == 0);

    if (rbSize <= ysf_rbCanRead(rb))
    {
        if ((rb->head + rbSize) >= buffEndAddr)
        {
            buffEndFree = buffEndAddr - rb->head;

            for (i = 0; i < buffEndFree; i++, rb->head++)
            {
                 buff[i] = *(rb->head);
            }

            for (rb->head = rb->buffer.buffer; i < rbSize; i++, rb->head++)
            {
                buff[i] = *(rb->head);
            }
        }
        else
        {
            for (i = 0; i < rbSize; i++, rb->head++)
            {
                buff[i] = *(rb->head);
            }
        }

        return YSF_ERR_NONE;
    }
#if USE_YSF_BUFFER_DEBUG
    else
    {
        ysf_LOG("%s Read data size is too long! \n",__FUNCTION__);
        return YSF_ERR_INVAILD_PARAM;
    }
#endif

    return YSF_ERR_FAIL;
}

#endif

/** @}*/     /* ysf_ringbuff 閰嶇疆  */

/**********************************END OF FILE*********************************/
