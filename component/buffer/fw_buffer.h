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
 * @file       fw_buffer.h                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-16                                                      *
 * @brief      framework buffer head files                                     *
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
 * @defgroup framework buffer component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_BUFFER_H__
#define __FRAMEWORK_BUFFER_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_LINK_LIST_COMPONENT_PATH
    
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_BUFFER_COMPONENT
#if USE_FRAMEWORK_BUFFER_COMPONENT
    #define USE_FRAMEWORK_BUFFER_API                                         (1)
    #define USE_FRAMEWORK_MEMORY_MANAGEMENT_API                              (1)
#else
    #define USE_FRAMEWORK_BUFFER_API                                         (0)
    #define USE_FRAMEWORK_MEMORY_MANAGEMENT_API                              (0)
#endif

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
    #define USE_FRAMEWORK_BUFFER_API                                         (1)
    #define USE_FRAMEWORK_MEMORY_MANAGEMENT_API                              (1)
#endif

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define buffer type
 *******************************************************************************
 */
struct fw_buffer_t
{
    uint8_t  *buffer;
    uint16_t size;
    uint16_t head;
    uint16_t tail;
};

/**
 *******************************************************************************
 * @brief       define ring buffer api
 *******************************************************************************
 */
#if USE_FRAMEWORK_BUFFER_API
struct _RING_BUFFER_API
{
    fw_err_t (*Init)(struct fw_buffer_t*, uint8_t*, uint16_t);
    fw_err_t (*GetLen)(struct fw_buffer_t*, uint16_t*);
    fw_err_t (*Write)(struct fw_buffer_t*, uint8_t*, uint16_t);
    fw_err_t (*Read)(struct fw_buffer_t*, uint8_t*, uint16_t);
};
#endif

/**
 *******************************************************************************
 * @brief       define memory block
 *******************************************************************************
 */
__ALIGN_HEAD(8)
struct fw_memblock_t
{
	struct fw_memblock_t *next;
	uint32_t             size   : 31;
    uint32_t             status :  1;
};
__ALIGN_TAIL(8)

/**
 *******************************************************************************
 * @brief       define memory control block
 *******************************************************************************
 */
struct fw_memcontrol_t
{
    union
    {
        void                 *buffer;
        struct fw_memblock_t *head; 
    };
    
    uint16_t size;
};

/**
 *******************************************************************************
 * @brief       define memory management api
 *******************************************************************************
 */
#if USE_FRAMEWORK_MEMORY_MANAGEMENT_API
struct _MEMORY_MANAGEMENT_API
{
    fw_err_t (*Init)(struct fw_memcontrol_t*, uint8_t*, uint32_t);
    fw_err_t (*Alloc)(struct fw_memcontrol_t*, uint16_t, void*);
    fw_err_t (*Free)(struct fw_memcontrol_t*, void*);
    fw_err_t (*IsIn)(struct fw_memcontrol_t*, void*);
};
#endif


/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ring buffer function interface
 *******************************************************************************
 */
#if USE_FRAMEWORK_BUFFER_API
extern fw_err_t fw_rb_init(struct fw_buffer_t*, uint8_t*, uint16_t);
extern fw_err_t fw_rb_getlen(struct fw_buffer_t*, uint16_t*);
extern fw_err_t fw_rb_write(struct fw_buffer_t*, uint8_t*, uint16_t);
extern fw_err_t fw_rb_read(struct fw_buffer_t*, uint8_t*, uint16_t);
#endif

/**
 *******************************************************************************
 * @brief       memory management function interface
 *******************************************************************************
 */
#if USE_FRAMEWORK_MEMORY_MANAGEMENT_API
extern fw_err_t fw_mem_init(struct fw_memcontrol_t*, uint8_t*, uint32_t);
extern fw_err_t fw_mem_alloc(struct fw_memcontrol_t*, uint32_t, void*);
extern fw_err_t fw_mem_free(struct fw_memcontrol_t*, void*);
extern bool     fw_mem_isIn(struct fw_memcontrol_t*, void*);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework buffer component  */

/**********************************END OF FILE*********************************/
