/**
 ******************************************************************************
  * @file       ysf_buffer.h
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-01-06
  * @brief      ysf_buffer head file
  * @par        work platform
  *                 Windows
  * @par        compiler
  *                 GCC
 ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ynf_ringbuff config file
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_BUFFER_H__
#define __YSF_BUFFER_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "../ysf/common/ysf_type.h"
#include "../ysf/compiler/ysf_compiler.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf buffer debug switch
 *******************************************************************************
 */
#define USE_YSF_BUFFER_DEBUG            (0)
#define USE_YSF_MEMORY_MANAGEMENT_DEBUG (1)

#define USE_YSF_RING_BUFFER_PTR         (0)
#define USE_YSF_MEMORY_MANAGEMENT_PTR   (0)

/* Exported types ------------------------------------------------------------*/
/**
 * @name ring buffer type
 * @{
 */
typedef ysf_u8_t ysf_buffer_size_t;
typedef ysf_u8_t ysf_buffer_point_t;

typedef struct _YSF_BUFFER_TYPE_
{
    ysf_u8_t          *buffer;
    ysf_buffer_size_t size;
}ysf_buffer_t;

#if USE_YSF_RING_BUFFER_PTR
typedef volatile struct _YSF_RING_BUFF_TYPE_
{
    ysf_buffer_t       buffer;
    ysf_u8_t           *head;
    ysf_u8_t           *tail;
    ysf_buffer_size_t  size;
}ysf_rb_t;

#else
typedef volatile struct _YSF_RING_BUFF_TYPE_
{
    ysf_buffer_t       buffer;
    ysf_buffer_point_t head;
    ysf_buffer_point_t tail;
}ysf_rb_t;
#endif

typedef ysf_rb_t ysf_queue_t;
typedef ysf_rb_t ysf_fifo_t;

/**@} */

/**
 * @name ring buffer type
 * @{
 */
#if USE_YSF_MEMORY_MANAGEMENT_PTR
YSF_PACKED_HEAD(1)
typedef struct _YSF_MEM_BLOCK_TYPE_
{
#define YSF_MEMORY_CB_NEXT_END YSF_NULL
    struct _YSF_MEM_BLOCK_TYPE_ *next;

#define IS_MEM_FREE (0)
#define IS_MEM_USE  (1)
    ysf_u8_t status;

    ysf_u8_t data[];
}ysf_mem_block_t;
YSF_PACKED_TAIL(1)

#else
YSF_PACKED_HEAD(1)
typedef struct _YSF_MEM_BLOCK_TYPE_
{
#define YSF_MEMORY_CB_NEXT_END (0)
    ysf_buffer_point_t next;

#define IS_MEM_FREE (0)
#define IS_MEM_USE  (1)
    ysf_u8_t status;

    ysf_u8_t data[];
}ysf_mem_block_t;
YSF_PACKED_TAIL(1)

#endif

typedef struct _YSF_MEM_CB_TYPE_
{
    ysf_buffer_t buffer;
    ysf_u8_t     alignment;

    enum
    {
        IS_YSF_POOL_NOT_INIT = 0,
        IS_YSF_POOL_INIT     = 1,
    }status;
}ysf_mem_cb_t;

/**@} */

typedef struct
{
    ysf_err_t (*init)(ysf_rb_t*, ysf_u8_t*, ysf_buffer_size_t);
    ysf_buffer_size_t (*len)(ysf_rb_t*);
    ysf_err_t (*write)(ysf_rb_t*, ysf_u8_t*, ysf_buffer_size_t);
    ysf_err_t (*read)(ysf_rb_t*, ysf_u8_t*, ysf_buffer_size_t);
#if USE_YSF_BUFFER_DEBUG
    void (*test)(void);
#endif
}ysf_ring_buffer_func_type_t;

typedef struct
{
    ysf_err_t (*init)(ysf_mem_cb_t*, ysf_u8_t*, ysf_buffer_size_t);
    ysf_buffer_size_t (*len)(ysf_mem_cb_t*);
    ysf_buffer_size_t (*alignment)(ysf_mem_cb_t*);
    ysf_buffer_size_t (*rate)(ysf_mem_cb_t*);
    void *(*malloc)(ysf_mem_cb_t*, ysf_buffer_size_t);
    ysf_err_t (*free)(ysf_mem_cb_t*, void*);
#if USE_YSF_MEMORY_MANAGEMENT_DEBUG
    void (*test)(void);
#endif
}ysf_memory_func_type_t;

/* Exported variables --------------------------------------------------------*/
extern const ysf_ring_buffer_func_type_t ysf_rb;
extern const ysf_memory_func_type_t      ysf_mem;

/* Exported functions --------------------------------------------------------*/
/**
 * @name ring buffer type API
 * @{
 */
extern ysf_err_t ysf_rbInit( ysf_rb_t*, ysf_u8_t*, ysf_buffer_size_t );
extern ysf_buffer_size_t ysf_rbGetLen( ysf_rb_t* );
extern ysf_err_t ysf_rbWrite( ysf_rb_t*, ysf_u8_t*, ysf_buffer_size_t );
extern ysf_err_t ysf_rbRead( ysf_rb_t*,  ysf_u8_t*, ysf_buffer_size_t );

#define ysf_queueInit(queue, buffer, size)  ysf_rbInit(queue, buffer, size)
#define ysf_queueGetLen(queue)              ysf_rbGetLen(queue)
#define ysf_queueWrite(queue, buffer, size) ysf_rbWrite(queue, buffer, size)
#define ysf_queueRead(queue, buffer, size)  ysf_rbRead(queue, buffer, size)

#define ysf_fifoInit(queue, buffer, size)   ysf_rbInit(queue, buffer, size)
#define ysf_fifoGetLen(queue)               ysf_rbGetBufferLen(queue)
#define ysf_fifoPush(queue, buffer, size)   ysf_rbWrite(queue, buffer, size)
#define ysf_fifoPushByte(queue, buffer)     ysf_rbWrite(queue, buffer, 1)
#define ysf_fifoPop(queue, buffer, size)    ysf_rbRead(queue, buffer, size)
#define ysf_fifoPopByte(queue, buffer)      ysf_rbRead(queue, buffer, 1)

#if USE_YSF_BUFFER_DEBUG
extern void ysf_rbTest( void );
#else
#define ysf_rbTest()
#endif

/**@} */

/**
 * @name memory management API
 * @{
 */
extern ysf_err_t ysf_memInit(ysf_mem_cb_t*, ysf_u8_t*, ysf_buffer_size_t);
extern ysf_buffer_size_t ysf_memGetLen(ysf_mem_cb_t*);
extern ysf_buffer_size_t ysf_memGetAlignment(ysf_mem_cb_t*);
extern ysf_buffer_size_t ysf_memUseRateCal(ysf_mem_cb_t*);
extern void* ysf_memMalloc(ysf_mem_cb_t*, ysf_buffer_size_t);
extern ysf_err_t ysf_memFree(ysf_mem_cb_t*, void*);

#if USE_YSF_MEMORY_MANAGEMENT_DEBUG
extern void ysf_memoryManagementTest( void );
#else
#define ysf_memoryManagementTest()
#endif

/**@} */
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf_buffer  */

/**********************************END OF FILE*********************************/
