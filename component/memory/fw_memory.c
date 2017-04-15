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
 * @file       fw_memory.c                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-20                                                      *
 * @brief      framework memory component source files                         *
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
 * @defgroup framework memory component
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
        #ifndef USE_COMPILER_HEAP_ADDR            
            __ALIGN_HEAD(8)
                static uint8_t MCU_HEAP[FRAMEWORK_MEMORY_POOL_SIZE];
            __ALIGN_TAIL(8)
            
            #define _HEAP_HEAD_ADDR    (&MCU_HEAP)
            #define _HEAP_TAIL_ADDR    (&MCU_HEAP[YSF_HEAP_SIZE-1])
            #define _HEAP_SIZE         FRAMEWORK_MEMORY_POOL_SIZE
        #else
            #define _HEAP_HEAD_ADDR    __HEAP_HEAD_ADDR
            #define _HEAP_TAIL_ADDR    MCU_SRAM_END_ADDR
            #define _HEAP_SIZE         (_HEAP_TAIL_ADDR - _HEAP_HEAD_ADDR)
        #endif
    
        static struct fw_memcontrol_t managemrnt;
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
void fw_memory_init(void)
{
#if !defined(USE_STD_LIBRARY) || !USE_STD_LIBRARY
    fw_heap_init(&managemrnt, (uint8_t *)_HEAP_HEAD_ADDR, _HEAP_SIZE);
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
void *fw_memory_malloc(uint32_t size)
{
#if defined(USE_STD_LIBRARY) && USE_STD_LIBRARY
    return malloc(size);
#else 
    void *mem = NULL;
    fw_heap_alloc(&managemrnt, mem);
    return mem;
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
void fw_memory_free(void *memory)
{
#if defined(USE_STD_LIBRARY) && USE_STD_LIBRARY
    free(memory);
#else
    fw_heap_free(&managemrnt, memory);
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
bool fw_memory_isIn(void *memory)
{
#if defined(USE_STD_LIBRARY) && USE_STD_LIBRARY
    return true;
#else
    return fw_heap_isIn(&managemrnt, memory);
#endif
}

#endif

/** @}*/     /** framework memory component */

/**********************************END OF FILE*********************************/
