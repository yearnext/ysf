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
#include "ysf_path.h"
#include YSF_TYPE_DIR
#include YSF_COMPILER_DIR

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf buffer debug switch
 *******************************************************************************
 */
#define USE_YSF_BUFFER_DEBUG            (0)
#define USE_YSF_MEMORY_MANAGEMENT_DEBUG (0)
    
/* Exported types ------------------------------------------------------------*/
/**
 * @name ring buffer type
 * @{
 */
typedef uint16_t ysf_buf_size_t;
typedef uint16_t ysf_buf_ptr_t;

struct ysf_buffer_t 
{
    uint8_t    *buffer;
    ysf_buf_size_t size;
};

struct ysf_rb_t
{
    struct ysf_buffer_t buffer;
    ysf_buf_ptr_t       head;
    ysf_buf_ptr_t       tail;
};

typedef struct ysf_rb_t ysf_queue_t;
typedef struct ysf_rb_t ysf_fifo_t;

struct YSF_RING_BUFFER_API
{
    ysf_err_t (*init)(struct ysf_rb_t*, uint8_t*, ysf_buf_size_t);
    ysf_buf_size_t (*len)(struct ysf_rb_t*);
    ysf_err_t (*write)(struct ysf_rb_t*, uint8_t*, ysf_buf_size_t);
    ysf_err_t (*read)(struct ysf_rb_t*, uint8_t*, ysf_buf_size_t);
};

/**@} */

/**
 * @name memory management
 * @{
 */
typedef uint16_t ysf_mem_size_t;

YSF_ALIGN_HEAD(1)
struct ysf_mem_block_t 
{
#define YSF_MEMORY_CB_NEXT_END (0)
    ysf_mem_size_t next;

#define IS_MEM_FREE (0)
#define IS_MEM_USE  (1)
    uint8_t status;

    uint8_t data[];
};
YSF_ALIGN_TAIL(1)

struct ysf_mem_cb_t
{
    struct
    {
        uint8_t    *buffer;
        ysf_mem_size_t size;
    }buffer;

    ysf_mem_size_t alignment;
    
    enum
    {
        IS_YSF_POOL_NOT_INIT = 0,
        IS_YSF_POOL_INIT     = 1,
    }status;
};

/**@} */

struct YSF_MEM_API
{
    ysf_err_t (*init)(struct ysf_mem_cb_t*, uint8_t*, ysf_mem_size_t);
    ysf_mem_size_t (*len)(struct ysf_mem_cb_t*);
    ysf_mem_size_t (*alignment)(struct ysf_mem_cb_t*);
    ysf_mem_size_t (*rate)(struct ysf_mem_cb_t*);
    void *(*malloc)(struct ysf_mem_cb_t*, ysf_mem_size_t);
    ysf_err_t (*free)(struct ysf_mem_cb_t*, void*);
    bool (*isIn)(struct ysf_mem_cb_t*, void*);
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 * @name ring buffer type API
 * @{
 */
extern ysf_err_t ysf_rbInit(struct ysf_rb_t*, uint8_t*, ysf_buf_size_t);
extern ysf_buf_size_t ysf_rbGetLen(struct ysf_rb_t*);
extern ysf_err_t ysf_rbWrite(struct ysf_rb_t*, uint8_t*, ysf_buf_size_t);
extern ysf_err_t ysf_rbRead(struct ysf_rb_t*, uint8_t*, ysf_buf_size_t);

/**@} */

/**
 * @name memory management API
 * @{
 */
extern ysf_err_t ysf_memInit(struct ysf_mem_cb_t*, uint8_t*, uint16_t);
extern ysf_mem_size_t ysf_memGetLen(struct ysf_mem_cb_t*);
extern ysf_mem_size_t ysf_memGetAlignment(struct ysf_mem_cb_t*);
extern ysf_mem_size_t ysf_memUseRateCal(struct ysf_mem_cb_t*);
extern void *ysf_memMalloc(struct ysf_mem_cb_t*, ysf_mem_size_t);
extern ysf_err_t ysf_memFree(struct ysf_mem_cb_t*, void*);
extern bool ysf_memIsIn(struct ysf_mem_cb_t*, void*);

/**@} */
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf_buffer  */

/**********************************END OF FILE*********************************/
