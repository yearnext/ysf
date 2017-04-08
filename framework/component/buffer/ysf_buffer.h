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
 * @file       ysf_buffer.h                                                    *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-16                                                      *
 * @brief      ysf_buffer head files                                           *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */
 
/**
 * @defgroup ysf buffer component
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
#include "ysf_conf.h"
#include "ysf_path.h"
#include YSF_TYPE_PATH
#include YSF_COMPILER_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       use ysf config
 *******************************************************************************
 */
#ifdef USE_YSF_BUFFER_COMPONENT
#if USE_YSF_BUFFER_COMPONENT
#define USE_YSF_BUFFER_API              (1)
#define USE_YSF_MEMORY_MANAGEMENT_API   (1)  
#else
#define USE_YSF_BUFFER_API              (0)
#define USE_YSF_MEMORY_MANAGEMENT_API   (0)  
#endif

/**
 *******************************************************************************
 * @brief       not use ysf config
 *******************************************************************************
 */
#else
#define USE_YSF_BUFFER_API              (1)
#define USE_YSF_MEMORY_MANAGEMENT_API   (1)  
#endif
/**
 *******************************************************************************
 * @brief       buffer debug switch
 *******************************************************************************
 */
#define USE_YSF_BUFFER_DEBUG            (0)
#define USE_YSF_MEMORY_MANAGEMENT_DEBUG (0)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define buffer size type
 *******************************************************************************
 */
typedef uint16_t ysf_buf_size_t;

/**
 *******************************************************************************
 * @brief       define buffer indicator type
 *******************************************************************************
 */
typedef uint16_t ysf_buf_ptr_t;

/**
 *******************************************************************************
 * @brief       define buffer type
 *******************************************************************************
 */
struct ysf_buffer_t 
{
    uint8_t    *buffer;
    ysf_buf_size_t size;
};

/**
 *******************************************************************************
 * @brief       define ring buffer type
 *******************************************************************************
 */
struct ysf_rb_t
{
    struct ysf_buffer_t buffer;
    ysf_buf_ptr_t       head;
    ysf_buf_ptr_t       tail;
};

/**
 *******************************************************************************
 * @brief       define queue type
 *******************************************************************************
 */
typedef struct ysf_rb_t ysf_queue_t;

/**
 *******************************************************************************
 * @brief       define fifo type
 *******************************************************************************
 */
typedef struct ysf_rb_t ysf_fifo_t;

/**
 *******************************************************************************
 * @brief       define ring buffer api
 *******************************************************************************
 */
#if USE_YSF_BUFFER_API
struct YSF_RING_BUFFER_API
{
    ysf_err_t (*init)(struct ysf_rb_t*, uint8_t*, ysf_buf_size_t);
    ysf_buf_size_t (*len)(struct ysf_rb_t*);
    ysf_err_t (*write)(struct ysf_rb_t*, uint8_t*, ysf_buf_size_t);
    ysf_err_t (*read)(struct ysf_rb_t*, uint8_t*, ysf_buf_size_t);
};
#endif

/**
 *******************************************************************************
 * @brief       define memory pool size type
 *******************************************************************************
 */
typedef uint32_t ysf_mem_size_t;

/**
 *******************************************************************************
 * @brief       define memory block type
 *******************************************************************************
 */
//YSF_ALIGN_HEAD(1)
struct ysf_mem_block_t 
{
#define YSF_MEMORY_CB_NEXT_END (0)
    ysf_mem_size_t next;

#define IS_MEM_FREE (0)
#define IS_MEM_USE  (1)
    uint8_t status;

    uint8_t data[];
};
//YSF_ALIGN_TAIL(1)

/**
 *******************************************************************************
 * @brief       define memory management block type
 *******************************************************************************
 */
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

/**
 *******************************************************************************
 * @brief       define memory management api
 *******************************************************************************
 */
#if USE_YSF_MEMORY_MANAGEMENT_API
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
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ring buffer function interface
 *******************************************************************************
 */
#if USE_YSF_BUFFER_API
extern ysf_err_t ysf_rbInit(struct ysf_rb_t*, uint8_t*, ysf_buf_size_t);
extern ysf_buf_size_t ysf_rbGetLen(struct ysf_rb_t*);
extern ysf_err_t ysf_rbWrite(struct ysf_rb_t*, uint8_t*, ysf_buf_size_t);
extern ysf_err_t ysf_rbRead(struct ysf_rb_t*, uint8_t*, ysf_buf_size_t);
#endif

/**
 *******************************************************************************
 * @brief       memory management function interface
 *******************************************************************************
 */
#if USE_YSF_MEMORY_MANAGEMENT_API
extern ysf_err_t ysf_memInit(struct ysf_mem_cb_t*, uint8_t*, ysf_mem_size_t);
extern ysf_mem_size_t ysf_memGetLen(struct ysf_mem_cb_t*);
extern ysf_mem_size_t ysf_memGetAlignment(struct ysf_mem_cb_t*);
extern ysf_mem_size_t ysf_memUseRateCal(struct ysf_mem_cb_t*);
extern void *ysf_memMalloc(struct ysf_mem_cb_t*, ysf_mem_size_t);
extern ysf_err_t ysf_memFree(struct ysf_mem_cb_t*, void*);
extern bool ysf_memIsIn(struct ysf_mem_cb_t*, void*);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf buffer component  */

/**********************************END OF FILE*********************************/
