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
 * @file       ysf_memory.c                                                    *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-20                                                      *
 * @brief      memory component source files                                   *
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

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_COMPILER_PATH
#include YSF_COMPONENT_MEMORY_PATH
#include YSF_COMPONENT_BUFFER_PATH
#include YSF_TYPE_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        define ysf memory management vailables
 *******************************************************************************
 */
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
#ifndef MCU_HEAP_HEAD_ADDR
#define YSF_HEAP_SIZE         (4096)    
YSF_ALIGN_HEAD(1)
static uint8_t MCU_HEAP[YSF_HEAP_SIZE];
YSF_ALIGN_TAIL(1)
#define MCU_HEAP_HEAD_ADDR    (&MCU_HEAP)
#define MCU_HEAP_TAIL_ADDR    (&MCU_HEAP[YSF_HEAP_SIZE-1])
#define MCU_HEAP_SIZE         YSF_HEAP_SIZE
#endif
static struct ysf_mem_cb_t memoryManagemrntCB;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
/**
 *******************************************************************************
 * @brief       init ysf memory 
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void ysf_memory_init( void )
{
    ysf_memInit(&memoryManagemrntCB, (uint8_t *)MCU_HEAP_HEAD_ADDR, MCU_HEAP_SIZE);
}

/**
 *******************************************************************************
 * @brief       allocating memory
 * @param       [in/out]  size               allocated memory size
 * @return      [in/out]  void*              return allocated memory
 * @note        None
 *******************************************************************************
 */
void *ysf_memory_malloc( ysf_mem_size_t size )
{
    return ysf_memMalloc(&memoryManagemrntCB, size);
}

/**
 *******************************************************************************
 * @brief       free memory
 * @param       [in/out]  void*              allocated memory size
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void ysf_memory_free( void *mem )
{
    ysf_memFree(&memoryManagemrntCB, mem);
}

/**
 *******************************************************************************
 * @brief       get memory len
 * @param       [in/out]  void
 * @return      [in/out]  ysf_mem_size_t    memory len
 * @note        None
 *******************************************************************************
 */
ysf_mem_size_t ysf_memory_get_len(void)
{
    return ysf_memGetLen(&memoryManagemrntCB);
}

/**
 *******************************************************************************
 * @brief       get memory alignment
 * @param       [in/out]  void
 * @return      [in/out]  ysf_mem_size_t    memory alignment size
 * @note        None
 *******************************************************************************
 */
ysf_mem_size_t ysf_memory_get_alignment(void)
{
    return ysf_memGetAlignment(&memoryManagemrntCB);
}

/**
 *******************************************************************************
 * @brief       get memory use rate
 * @param       [in/out]  void
 * @return      [in/out]  ysf_mem_size_t    use rate
 * @note        None
 *******************************************************************************
 */
ysf_mem_size_t ysf_memory_cal_use_rate(void)
{
    return ysf_memUseRateCal(&memoryManagemrntCB);
}

/**
 *******************************************************************************
 * @brief       detecting the memory is in memory pool
 * @param       [in/out]  void*             wait detect memory
 * @return      [in/out]  false             the memory not in memory pool
 * @return      [in/out]  true              the memory is in memory pool
 * @note        None
 *******************************************************************************
 */
bool ysf_memory_is_in(void *mem)
{
    return ysf_memIsIn(&memoryManagemrntCB, mem);
}

#endif

/** @}*/     /** ysf_memory component  */

/**********************************END OF FILE*********************************/
