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
#if USE_MEMORY_COMPONENT
    #if !defined(USE_STD_LIBRARY) || !USE_STD_LIBRARY
        #ifndef USE_COMPILER_HEAP_ADDR            
            __ALIGN_HEAD(8)
                static uint8_t McuHeap[FRAMEWORK_MEMORY_POOL_SIZE];
            __ALIGN_TAIL(8)
            
            #define _HEAP_HEAD_ADDR    (&McuHeap)
            #define _HEAP_TAIL_ADDR    (&McuHeap[FRAMEWORK_MEMORY_POOL_SIZE-1])
            #define _HEAP_SIZE         FRAMEWORK_MEMORY_POOL_SIZE
        #else
            #define _HEAP_HEAD_ADDR    __HEAP_HEAD_ADDR
            #define _HEAP_TAIL_ADDR    MCU_SRAM_END_ADDR
            #define _HEAP_SIZE         (_HEAP_TAIL_ADDR - _HEAP_HEAD_ADDR)
        #endif
    
        static struct HeapControlBlock Managemrnt;
    #endif
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_MEMORY_COMPONENT
/**
 *******************************************************************************
 * @brief       init ysf memory 
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void MemoryComponentInit(void)
{
#if !defined(USE_STD_LIBRARY) || !USE_STD_LIBRARY
    HeapComponentInit(&Managemrnt, (uint8_t *)_HEAP_HEAD_ADDR, _HEAP_SIZE);
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
void *MemoryMalloc(uint32_t size)
{
#if defined(USE_STD_LIBRARY) && USE_STD_LIBRARY
    return malloc(size);
#else 
    void *mem = NULL;
    AllocHeapMemory(&Managemrnt, size, (void **)&mem);
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
void MemoryFree(void *memory)
{
#if defined(USE_STD_LIBRARY) && USE_STD_LIBRARY
    free(memory);
#else
    FreeHeapMemory(&Managemrnt, memory);
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
bool MemoryIsIn(void *memory)
{
#if defined(USE_STD_LIBRARY) && USE_STD_LIBRARY
    return true;
#else
    return IsInHeapMemory(&Managemrnt, memory);
#endif
}

#endif

/** @}*/     /** memory component */

/**********************************END OF FILE*********************************/
