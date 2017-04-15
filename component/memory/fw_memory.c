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
#include "core_path.h"
#include _FW_PATH
#include _FW_MEMORY_COMPONENT_PATH
#include _FW_BUFFER_COMPONENT_PATH

#if defined(USE_STD_LIBRARY) && USE_STD_LIBRARY
#include <stdlib.h>
#endif

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        define ysf memory management vailables
 *******************************************************************************
 */
#if !defined(USE_STD_LIBRARY) || !USE_STD_LIBRARY
    #if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
        #ifndef MCU_HEAP_HEAD_ADDR
            #define YSF_HEAP_SIZE         (4096)    
            
            __ALIGN_HEAD(8)
                static uint8_t MCU_HEAP[YSF_HEAP_SIZE];
            __ALIGN_TAIL(8)
            
            #define MCU_HEAP_HEAD_ADDR    (&MCU_HEAP)
            #define MCU_HEAP_TAIL_ADDR    (&MCU_HEAP[YSF_HEAP_SIZE-1])
            #define MCU_HEAP_SIZE         YSF_HEAP_SIZE
        #endif
    
        static struct ysf_mem_ctrl_t managemrnt;
    #endif
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
#if !defined(USE_STD_LIBRARY) || !USE_STD_LIBRARY
    ysf_mem_init(&managemrnt, (uint8_t *)MCU_HEAP_HEAD_ADDR, MCU_HEAP_SIZE);
#endif
}

/**
 *******************************************************************************
 * @brief       allocating memory
 * @param       [in/out]  size               allocated memory size
 * @return      [in/out]  void*              return allocated memory
 * @note        None
 *******************************************************************************
 */
void *ysf_memory_malloc( uint16_t size )
{
#if defined(USE_STD_LIBRARY) && USE_STD_LIBRARY
    return malloc(size);
#else 
    return ysf_mem_alloc(&managemrnt, size);
#endif
}

/**
 *******************************************************************************
 * @brief       free memory
 * @param       [in/out]  void*              allocated memory size
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void ysf_memory_free( void *memory )
{
#if defined(USE_STD_LIBRARY) && USE_STD_LIBRARY
    free(memory);
#else
    ysf_mem_free(&managemrnt, memory);
#endif
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
bool ysf_memory_is_in(void *memory)
{
#if defined(USE_STD_LIBRARY) && USE_STD_LIBRARY
    return true;
#else
    return ysf_mem_is_in(&managemrnt, memory);
#endif
}

#endif

/** @}*/     /** ysf_memory component  */

/**********************************END OF FILE*********************************/
