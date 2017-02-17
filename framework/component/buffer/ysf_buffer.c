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
 * @defgroup ysf_buffer
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "..\framework\component\buffer\ysf_buffer.h"
#include "..\framework\compiler\ysf_compiler.h"
#include "..\framework\common\ysf_type.h"
#include "..\framework\component\debug\ysf_debug.h"

#if USE_YSF_BUFFER_DEBUG || USE_YSF_MEMORY_MANAGEMENT_DEBUG
#include <stdlib.h>
#include <windows.h>
#endif

/* Private define ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_RING_BUFFER_PTR
/**
 *******************************************************************************
 * @brief       ring buffer init
 * @param       [in/out]  *rb            ring buffer control block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  YSF_ERR_NONE   ring buffer init success
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_rbInit( ysf_rb_t *rb, ysf_u8_t *buffer, ysf_buffer_size_t size )
{
    ysf_assert(IS_PTR_NULL(rb));
    ysf_assert(IS_PTR_NULL(buffer));

    rb->buffer.buffer = buffer;
    rb->buffer.size   = size;

    rb->head          = buffer;
    rb->tail          = buffer;

    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get ring buffer length
 * @param       [in/out]  *rb                 ring buffer control block
 * @return      [in/out]  ysf_buffer_size_t   ring buffer length
 * @note        None
 *******************************************************************************
 */
ysf_buffer_size_t ysf_rbGetLen( ysf_rb_t *rb )
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

/**
 *******************************************************************************
 * @brief       get ring buffer can write data size
 * @param       [in/out]  *rb                 ring buffer control block
 * @return      [in/out]  ysf_buffer_size_t   ring buffer can write data size
 * @note        one byte in the ring buffer is occupied by the control system
 *******************************************************************************
 */
YSF_STATIC_INLINE
ysf_buffer_size_t ysf_rbCanWrite(ysf_rb_t *rb)
{
    ysf_assert(IS_PTR_NULL(rb));

    ysf_buffer_size_t size = 0;

    if( rb->tail >= rb->head )
    {
        size = rb->buffer.size - (ysf_buffer_size_t)(rb->tail - rb->head);

        return size;
    }
    else
    {
        size = (ysf_buffer_size_t)(rb->tail - rb->head);

        return ((size > 1) ? (size) : (0));
    }

    return 0;
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

            for (i=0; i<buffEndFree; i++ )
            {
                 buff[i] = *(rb->head);
                 rb->head++;
            }

            for( rb->head=rb->buffer.buffer; i<rbSize; i++ )
            {
                buff[i] = *(rb->head);
                rb->head++;
            }
        }
        else
        {
            for( i=0; i<rbSize; i++ )
            {
                buff[i] = *(rb->head);
                rb->head++;
            }
        }

        return YSF_ERR_NONE;
    }
#if USE_YSF_BUFFER_DEBUG
    else
    {
        ysf_log("%s Read data size is too long! \n",__FUNCTION__);
        return YSF_ERR_INVAILD_PARAM;
    }
#endif

    return YSF_ERR_FAIL;
}

#else
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
ysf_err_t ysf_rbInit( ysf_rb_t *cb, ysf_u8_t *buffer, ysf_buffer_size_t size )
{
    ysf_assert(IS_PTR_NULL(cb));
    ysf_assert(IS_PTR_NULL(buffer));

    cb->buffer.buffer = buffer;
    cb->buffer.size   = size;

    cb->head          = 0;
    cb->tail          = 0;

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
ysf_buffer_size_t ysf_rbGetLen( ysf_rb_t *rb )
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
YSF_STATIC_INLINE ysf_buffer_size_t ysf_rbCanRead(ysf_rb_t *rb)
{
    ysf_assert(IS_PTR_NULL(rb));

    if( rb->tail >= rb->head )
    {
        return ((ysf_buffer_size_t)(rb->tail - rb->head));
    }
    else
    {
        return ((ysf_buffer_size_t)(rb->buffer.size - (rb->head - rb->tail)));
    }

    return 0;
}

/**
 *******************************************************************************
 * @brief       get ring buffer can write data size
 * @param       [in/out]  *rb                 ring buffer control block
 * @return      [in/out]  ysf_buffer_size_t   ring buffer can write data size
 * @note        one byte in the ring buffer is occupied by the control system
 *******************************************************************************
 */
YSF_STATIC_INLINE ysf_buffer_size_t ysf_rbCanWrite(ysf_rb_t *rb)
{
    ysf_assert(IS_PTR_NULL(rb));

    ysf_buffer_size_t size = 0;

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

    return 0;
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
ysf_err_t ysf_rbWrite(ysf_rb_t *rb, ysf_u8_t *buff, ysf_buffer_size_t rbSize)
{
    ysf_buffer_size_t free = 0;
    ysf_buffer_size_t i = 0;

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
ysf_err_t ysf_rbRead(ysf_rb_t *rb, ysf_u8_t *buff, ysf_buffer_size_t rbSize)
{
    ysf_buffer_size_t free = 0;
    ysf_buffer_size_t i = 0;

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
#if USE_YSF_BUFFER_DEBUG
    else
    {
        ysf_log("%s Read data size is too long! \n",__FUNCTION__);
        return YSF_ERR_INVAILD_PARAM;
    }
#endif

    return YSF_ERR_FAIL;
}
#endif

#if USE_YSF_BUFFER_DEBUG
static ysf_u8_t buffer[YSF_UINT8_MAX];
static ysf_rb_t rb;

static ysf_u8_t write[YSF_UINT8_MAX];
static ysf_u8_t read[YSF_UINT8_MAX];

/**
 *******************************************************************************
 * @brief       ring buffer component test function
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
static void ysf_rbWriteTest( void )
{
    ysf_u8_t writeSize, i;

    writeSize = rand();

    ysf_log("\n%s want to write %d data! \n", __YSF_FUNCNAME__, writeSize);

    for( i=0; i<writeSize; i++ )
    {
        write[i] = (ysf_u8_t)rand();
    }

    if( ysf_rbWrite(&rb, write, writeSize) == YSF_ERR_NONE )
    {
        for( i=0; i<writeSize; i++ )
        {
            ysf_log("%4d", write[i]);
        }

        ysf_log("\n");
    }

    ysf_log("buffer have %d use data! \n", ysf_rbCanRead(&rb));
    ysf_log("buffer have %d free data! \n\n", ysf_rbCanWrite(&rb));
}

/**
 *******************************************************************************
 * @brief       ring buffer component test function
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
static void ysf_rbReadTest( void )
{
    ysf_u8_t readSize, i;

    readSize = rand();

    ysf_log("\n%s want to read %d data! \n", __YSF_FUNCNAME__, readSize);

    if( ysf_rbRead(&rb, read, readSize) == YSF_ERR_NONE )
    {
        for( i=0; i<readSize; i++ )
        {
            ysf_log("%4d", read[i]);
        }

        ysf_log("\n");
    }

    ysf_log("buffer have %d use data! \n", ysf_rbCanRead(&rb));
    ysf_log("buffer have %d free data! \n\n", ysf_rbCanWrite(&rb));
}

/**
 *******************************************************************************
 * @brief       ring buffer component test function
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void ysf_rbTest( void )
{
    ysf_rbInit(&rb, buffer, sizeof(buffer));

    while(1)
    {
        ysf_rbWriteTest();
        ysf_rbReadTest();

        Sleep(5000);
    }
}
#endif

#if USE_YSF_MEMORY_MANAGEMENT_PTR
/**
 *******************************************************************************
 * @brief       memory block init
 * @param       [in/out]  *mem                memory block
 * @return      [in/out]  YSF_ERR_NONE        memory block init finish
 * @note        None
 *******************************************************************************
 */
YSF_STATIC_INLINE
ysf_err_t ysf_memBlockInit( ysf_mem_cb_t *mem )
{
    ysf_assert(IS_PTR_NULL(mem));
    ysf_assert(mem->status == IS_YSF_POOL_NOT_INIT);

    ysf_mem_block_t *memCB = YSF_NULL;
    ysf_buffer_size_t nowNode = 0, nextNode = 0;

    while(1)
    {
        memCB = (ysf_mem_block_t *)&mem->buffer.buffer[nowNode];
        nextNode = nowNode + mem->alignment;

        memCB->status = IS_MEM_FREE;

        if( nextNode > mem->buffer.size )
        {
            memCB->next = YSF_MEMORY_CB_NEXT_END;

            break;
        }

        memCB->next = (ysf_mem_block_t *)&mem->buffer.buffer[nextNode];

        nowNode     = nextNode;
    }

    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       calculation memory alignment size
 * @param       [in/out]  memCBSize           memory control block size
 * @return      [in/out]  ysf_buffer_size_t   calculation results
 * @note        wait test
 *******************************************************************************
 */
YSF_STATIC_INLINE
ysf_buffer_size_t ysf_memAlignmentCal( ysf_buffer_size_t memSize )
{
    ysf_buffer_size_t size = 0;
    ysf_buffer_size_t temp = memSize >> 3;

    ((memSize%8) == 0) ? (0) : (temp++);

    size = temp << 1;
    size = temp << 3;

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
ysf_buffer_size_t ysf_memNeedBlockCal( ysf_mem_cb_t *mem, ysf_buffer_size_t size )
{
    ysf_buffer_size_t needSize = size / mem->alignment;

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
ysf_buffer_size_t ysf_memUseBlockCal(ysf_mem_cb_t *mem, ysf_mem_block_t *block)
{
    ysf_assert(IS_PTR_NULL(mem));
    ysf_assert(IS_PTR_NULL(block));

    ysf_buffer_size_t size = 0;

    if( block->next != YSF_MEMORY_CB_NEXT_END )
    {
        size = (ysf_buffer_size_t)((ysf_u8_t *)block->next - (ysf_u8_t *)block);
    }
    else
    {
        size = (ysf_buffer_size_t)((ysf_u8_t *)&mem->buffer.buffer[mem->buffer.size] - (ysf_u8_t *)block);
    }

    return (size / mem->alignment);
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
ysf_err_t ysf_memInit(ysf_mem_cb_t *mem, ysf_u8_t *buffer, ysf_buffer_size_t size)
{
    ysf_buffer_size_t alignment = ysf_memAlignmentCal(sizeof(ysf_mem_block_t)/sizeof(char));

    ysf_assert(IS_PTR_NULL(mem));
    ysf_assert(IS_PTR_NULL(buffer));
    ysf_assert(size == 0);
    ysf_assert((size % alignment) != 0);

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
ysf_buffer_size_t ysf_memGetLen(ysf_mem_cb_t *mem)
{
    ysf_assert(IS_PTR_NULL(mem));

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
ysf_buffer_size_t ysf_memGetAlignment(ysf_mem_cb_t *mem)
{
    ysf_assert(IS_PTR_NULL(mem));

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
ysf_buffer_size_t ysf_memUseRateCal(ysf_mem_cb_t *mem)
{
    ysf_assert(IS_PTR_NULL(mem));

    ysf_mem_block_t *node    = (ysf_mem_block_t *)&mem->buffer.buffer;
    ysf_buffer_size_t use = 0;

    while(1)
    {
        if(node->status == IS_MEM_USE)
        {
            use = ysf_memUseBlockCal(mem, node);
            use = use >> 3;
        }

        if( node->next == YSF_MEMORY_CB_NEXT_END )
        {
            break;
        }

        node = node->next;
    }

    return (use / mem->buffer.size);
}

/**
 *******************************************************************************
 * @brief       memory malloc
 * @param       [in/out]  *mem           memory block
 * @param       [in/out]  size           malloc size
 * @return      [in/out]  YSF_NULL       malloc failed
 * @return      [in/out]  addr           malloc success
 * @note        None
 *******************************************************************************
 */
void *ysf_memMalloc( ysf_mem_cb_t *mem, ysf_buffer_size_t size )
{
    ysf_assert(IS_PTR_NULL(mem));
    ysf_assert(mem->status == IS_YSF_POOL_NOT_INIT);

    ysf_mem_block_t *nowNode  = (ysf_mem_block_t *)&mem->buffer.buffer;
    ysf_mem_block_t *nextNode;

    const ysf_buffer_size_t needBlock = ysf_memNeedBlockCal(mem, sizeof(ysf_mem_block_t)+size);
    ysf_buffer_size_t getSize  = 0;

    while(1)
    {
        if( nowNode->status == IS_MEM_FREE )
        {
            if( ++getSize >= needBlock )
            {
                nextNode        = nowNode->next;
                nowNode         = nowNode - getSize * mem->alignment;
                nowNode->next   = nextNode;
                nowNode->status = IS_MEM_USE;

                return ((void *)nowNode->data);
            }
        }
        else
        {
            getSize = 0;
        }

        if( nowNode->next == YSF_MEMORY_CB_NEXT_END )
        {
            break;
        }

        nowNode = nowNode->next;
    }

    return YSF_NULL;
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
ysf_err_t ysf_memFree(ysf_mem_cb_t *mem, void *useMem)
{
    ysf_assert(IS_PTR_NULL(mem));
    ysf_assert(IS_PTR_NULL(useMem));
    ysf_assert(mem->status == IS_YSF_POOL_NOT_INIT);

    ysf_mem_block_t *node  = (ysf_mem_block_t *)&mem->buffer.buffer;
    ysf_buffer_size_t next;
    ysf_buffer_size_t block;

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

        node = node->next;
    }

    block = ysf_memUseBlockCal(mem, node);
    next  = (ysf_buffer_size_t)((ysf_u8_t *)node - (ysf_u8_t *)&mem->buffer.buffer);
    next  = next + mem->alignment;

    for( ; block>0; block-- )
    {
        node->status = IS_MEM_FREE;
        node->next   = (ysf_mem_block_t *)&mem->buffer.buffer[next];

        node = node->next;
        next += mem->alignment;
    }

    return YSF_ERR_NONE;
}

#else
/**
 *******************************************************************************
 * @brief       memory block init
 * @param       [in/out]  *mem                memory block
 * @return      [in/out]  YSF_ERR_NONE        memory block init finish
 * @note        None
 *******************************************************************************
 */
YSF_STATIC_INLINE
ysf_err_t ysf_memBlockInit( ysf_mem_cb_t *mem )
{
    ysf_assert(IS_PTR_NULL(mem));
    ysf_assert(mem->status == IS_YSF_POOL_NOT_INIT);

    ysf_mem_block_t *memCB = YSF_NULL;
    ysf_buffer_size_t nowNode = 0, nextNode = 0;

    while(1)
    {
        memCB = (ysf_mem_block_t *)&mem->buffer.buffer[nowNode];
        nextNode = nowNode + mem->alignment;

        memCB->status = IS_MEM_FREE;

        if( nextNode > mem->buffer.size )
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
ysf_buffer_size_t ysf_memAlignmentCal( ysf_buffer_size_t memSize )
{
    ysf_buffer_size_t size = 0;
    ysf_buffer_size_t temp = memSize >> 3;

    ((memSize%8) == 0) ? (0) : (temp++);

    size = temp << 1;
    size = temp << 3;
    
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
ysf_buffer_size_t ysf_memNeedBlockCal( ysf_mem_cb_t *mem, ysf_buffer_size_t size )
{
    ysf_buffer_size_t needSize = size / mem->alignment;

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
ysf_buffer_size_t ysf_memUseBlockCal(ysf_mem_cb_t *mem, ysf_mem_block_t *block)
{
    ysf_assert(IS_PTR_NULL(mem));
    ysf_assert(IS_PTR_NULL(block));

    ysf_buffer_size_t size = 0;

    if( block->next != YSF_MEMORY_CB_NEXT_END )
    {
        size = (ysf_buffer_size_t)((ysf_u8_t *)&mem->buffer.buffer[block->next] - (ysf_u8_t *)block);
    }
    else
    {
        size = (ysf_buffer_size_t)((ysf_u8_t *)&mem->buffer.buffer[mem->buffer.size] - (ysf_u8_t *)block);
    }

    return (size / mem->alignment);
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
ysf_err_t ysf_memInit(ysf_mem_cb_t *mem, ysf_u8_t *buffer, ysf_buffer_size_t size)
{
    ysf_buffer_size_t alignment = ysf_memAlignmentCal(sizeof(ysf_mem_block_t)/sizeof(char));

    ysf_assert(IS_PTR_NULL(mem));
    ysf_assert(IS_PTR_NULL(buffer));
    ysf_assert(size == 0);
    ysf_assert((size % alignment) != 0);

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
ysf_buffer_size_t ysf_memGetLen(ysf_mem_cb_t *mem)
{
    ysf_assert(IS_PTR_NULL(mem));

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
ysf_buffer_size_t ysf_memGetAlignment(ysf_mem_cb_t *mem)
{
    ysf_assert(IS_PTR_NULL(mem));

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
ysf_buffer_size_t ysf_memUseRateCal(ysf_mem_cb_t *mem)
{
    ysf_assert(IS_PTR_NULL(mem));

    ysf_mem_block_t *node    = (ysf_mem_block_t *)&mem->buffer.buffer;
    ysf_buffer_size_t use = 0;

    while(1)
    {
        if(node->status == IS_MEM_USE)
        {
            use = ysf_memUseBlockCal(mem, node);
            use = use >> 3;
        }

        if( node->next == YSF_MEMORY_CB_NEXT_END )
        {
            break;
        }

        node = (ysf_mem_block_t *)&mem->buffer.buffer[node->next];
    }

    return (use / mem->buffer.size);
}

/**
 *******************************************************************************
 * @brief       memory malloc
 * @param       [in/out]  *mem           memory block
 * @param       [in/out]  size           malloc size
 * @return      [in/out]  YSF_NULL       malloc failed
 * @return      [in/out]  addr           malloc success
 * @note        None
 *******************************************************************************
 */
void *ysf_memMalloc( ysf_mem_cb_t *mem, ysf_buffer_size_t size )
{
    ysf_assert(IS_PTR_NULL(mem));
    ysf_assert(mem->status == IS_YSF_POOL_NOT_INIT);

    ysf_mem_block_t *nowNode  = (ysf_mem_block_t *)&mem->buffer.buffer;

    const ysf_buffer_size_t needSize = ysf_memNeedBlockCal(mem, sizeof(ysf_mem_block_t)+size);

    ysf_buffer_size_t nextNode;
    ysf_buffer_size_t getSize  = 0;

    while(1)
    {
        if( nowNode->status == IS_MEM_FREE )
        {
            if( ++getSize >= needSize )
            {
                nextNode = nowNode->next;
                nowNode  = nowNode - getSize * mem->alignment;
                nowNode->next = nextNode;
                nowNode->status = IS_MEM_USE;

                return ((void *)nowNode->data);
            }
        }
        else
        {
            getSize = 0;
        }

        if( nowNode->next == YSF_MEMORY_CB_NEXT_END )
        {
            break;
        }

        nowNode = (ysf_mem_block_t *)&mem->buffer.buffer[nowNode->next];
    }

    return YSF_NULL;
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
ysf_err_t ysf_memFree(ysf_mem_cb_t *mem, void *useMem)
{
    ysf_assert(IS_PTR_NULL(mem));
    ysf_assert(IS_PTR_NULL(useMem));
    ysf_assert(mem->status == IS_YSF_POOL_NOT_INIT);

    ysf_mem_block_t *node  = (ysf_mem_block_t *)&mem->buffer.buffer;
    ysf_buffer_size_t next;
    ysf_buffer_size_t block;

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

        node = (ysf_mem_block_t *)&mem->buffer.buffer[node->next];
    }

    block = ysf_memUseBlockCal(mem, node);
    next  = (ysf_buffer_size_t)((ysf_u8_t *)node - (ysf_u8_t *)&mem->buffer.buffer);
    next  = next + mem->alignment;

    for( ; block>0; block-- )
    {
        node->status = IS_MEM_FREE;
        node->next   = next;

        node = (ysf_mem_block_t *)&mem->buffer.buffer[node->next];
        next += mem->alignment;
    }

    return YSF_ERR_NONE;
}

#endif

#if USE_YSF_MEMORY_MANAGEMENT_DEBUG
static ysf_u8_t pool[YSF_UINT8_MAX];
static ysf_mem_cb_t memCB;
static ysf_u8_t *memory[2] = {YSF_NULL, YSF_NULL};
static ysf_u8_t size;

/**
 *******************************************************************************
 * @brief       ring buffer component test function
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void ysf_memoryManagementTest( void )
{
    ysf_memInit(&memCB, pool, YSF_UINT8_MAX);

    while(1)
    {
        size = rand();
        memory[0] = (ysf_u8_t *)ysf_memMalloc(&memCB, size);
        if( memory[0] == YSF_NULL )
        {
            ysf_log("\nmalloc %d size memory failed! \n\n", size);
        }
        else
        {
            ysf_log("\nmalloc %d size memory success, memory addr is %p! \n\n", size, memory[0]);
        }


        if( ysf_memFree(&memCB, memory[1]) == YSF_ERR_NONE )
        {
            ysf_log("free memory success, memory addr is %p! \n\n", memory[1]);
        }
        else
        {
            ysf_log("free memory failed, memory addr is %p! \n\n", memory[1]);
        }
        memory[1] = YSF_NULL;

        size = rand();
        memory[1] = (ysf_u8_t *)ysf_memMalloc(&memCB, size);
        if( memory[1] == YSF_NULL )
        {
            ysf_log("\nmalloc %d size memory failed! \n\n", size);
        }
        else
        {
            ysf_log("\nmalloc %d size memory success, memory addr is %p! \n\n", size, memory[1]);
        }

        if( ysf_memFree(&memCB, memory[0]) == YSF_ERR_NONE )
        {
            ysf_log("free memory success, memory addr is %p! \n\n", memory[0]);
        }
        else
        {
            ysf_log("free memory failed, memory addr is %p! \n\n", memory[0]);
        }
        memory[0] = YSF_NULL;

        Sleep(5000);
    }
}

#endif

/** @}*/     /* ysf_buffer  */

/**********************************END OF FILE*********************************/
