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

#else
/**
 *******************************************************************************
 * @brief       not use ysf config
 *******************************************************************************
 */
#define USE_YSF_BUFFER_API              (1)
#define USE_YSF_MEMORY_MANAGEMENT_API   (1)
#endif

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define buffer type
 *******************************************************************************
 */
struct ysf_buffer_t 
{
    uint8_t  *buffer;
    uint16_t size;
};

/**
 *******************************************************************************
 * @brief       define ring buffer type
 *******************************************************************************
 */
struct ysf_rb_t
{
    struct ysf_buffer_t buffer;
    uint16_t            head;
    uint16_t            tail;
};

/**
 *******************************************************************************
 * @brief       define ring buffer api
 *******************************************************************************
 */
#if USE_YSF_BUFFER_API
struct YSF_RING_BUFFER_API
{
    ysf_err_t (*init)(struct ysf_rb_t*, uint8_t*, uint16_t);
    uint16_t (*len)(struct ysf_rb_t*);
    ysf_err_t (*write)(struct ysf_rb_t*, uint8_t*, uint16_t);
    ysf_err_t (*read)(struct ysf_rb_t*, uint8_t*, uint16_t);
};
#endif


/**
 *******************************************************************************
 * @brief       define memory block
 *******************************************************************************
 */
YSF_ALIGN_HEAD(4)
struct ysf_mem_block_t
{
	struct ysf_mem_block_t *next;
	uint16_t              size;
    bool                  status;
};
YSF_ALIGN_TAIL(4)

/**
 *******************************************************************************
 * @brief       define memory control block
 *******************************************************************************
 */
struct ysf_mem_ctrl_t
{
    union
    {
        uint8_t  *buffer;
        struct ysf_mem_block_t *head; 
    };
    
    uint32_t size;
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ring buffer function interface
 *******************************************************************************
 */
#if USE_YSF_BUFFER_API
extern ysf_err_t ysf_rbInit(struct ysf_rb_t*, uint8_t*, uint16_t);
extern uint16_t ysf_rbGetLen(struct ysf_rb_t*);
extern ysf_err_t ysf_rbWrite(struct ysf_rb_t*, uint8_t*, uint16_t);
extern ysf_err_t ysf_rbRead(struct ysf_rb_t*, uint8_t*, uint16_t);
#endif

/**
 *******************************************************************************
 * @brief       memory management function interface
 *******************************************************************************
 */
#if USE_YSF_MEMORY_MANAGEMENT_API
extern ysf_err_t ysf_mem_init(struct ysf_mem_ctrl_t*, uint8_t*, uint32_t);
extern ysf_err_t mem_deinit(struct ysf_mem_ctrl_t *);
extern void *ysf_mem_alloc(struct ysf_mem_ctrl_t *mem, uint16_t);
extern void ysf_mem_free(struct ysf_mem_ctrl_t*, void*);
extern bool ysf_mem_is_in(struct ysf_mem_ctrl_t*, void*);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf buffer component  */

/**********************************END OF FILE*********************************/
