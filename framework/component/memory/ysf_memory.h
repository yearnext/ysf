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
 * @file       ysf_memory.h                                                    *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-20                                                      *
 * @brief      ysf memory management head files                                *
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
 * @defgroup ysf_memory component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_MEMORY_H__
#define __YSF_MEMORY_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_conf.h"
#include "ysf_path.h"
#include YSF_COMPONENT_BUFFER_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        ysf config
 *******************************************************************************
 */
#ifdef USE_YSF_MEMORY_MANAGEMENT_COMPONENT
#if USE_YSF_MEMORY_MANAGEMENT_COMPONENT   
#define USE_YSF_MEMORY_API  (1)
#else
#define USE_YSF_MEMORY_API  (0)
#endif
    
/**
 *******************************************************************************
 * @brief        user config
 *******************************************************************************
 */
#else
#define USE_YSF_MEMORY_API  (1)
#endif
    
/**
 *******************************************************************************
 * @brief        config ysf memory pool size
 *******************************************************************************
 */
#define YSF_USE_MEMORY_SIZE (4096)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        ysf memory management api
 *******************************************************************************
 */
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
struct YSF_MEMORY_API
{
    void (*init)(void);
    void *(*malloc)(ysf_mem_size_t);
    void (*free)(void*);
    ysf_mem_size_t (*len)(void);
    ysf_mem_size_t (*alignment)(void);
    ysf_mem_size_t (*useRate)(void);
    bool (*isIn)(void *);
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        memory management function interface
 *******************************************************************************
 */
#if USE_YSF_MEMORY_API
extern void ysf_memory_init( void );
extern void *ysf_memory_malloc(ysf_mem_size_t);
extern void ysf_memory_free(void*);
extern ysf_mem_size_t ysf_memory_get_len(void);
extern ysf_mem_size_t ysf_memory_get_alignment(void);
extern ysf_mem_size_t ysf_memory_cal_use_rate(void);
extern bool ysf_memory_is_in(void*);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf memory component  */

/**********************************END OF FILE*********************************/
