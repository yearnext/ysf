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
 * @brief      buffer component head files                                     *
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
 * @defgroup buffer component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUFFER_COMPONENT_H__
#define __BUFFER_COMPONENT_H__

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
    #define USE_BUFFER_COMPONENT                                             (1)
    #define USE_MEMORY_MANAGEMENT_COMPONENT                                  (1)
#else
    #define USE_BUFFER_COMPONENT                                             (0)
    #define USE_MEMORY_MANAGEMENT_COMPONENT                                  (0)
#endif

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
    #define USE_BUFFER_COMPONENT                                             (1)
    #define USE_MEMORY_MANAGEMENT_COMPONENT                                  (1)
#endif

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define buffer type
 *******************************************************************************
 */
struct RingBuffer
{
    uint8_t  *Buffer;
    uint16_t Size;
    uint16_t Head;
    uint16_t Tail;
};

/**
 *******************************************************************************
 * @brief       define ring buffer interface
 *******************************************************************************
 */
#if USE_BUFFER_COMPONENT
typedef struct
{
    fw_err_t (*Init)(struct RingBuffer*, uint8_t*, uint16_t);
    fw_err_t (*GetLen)(struct RingBuffer*, uint16_t*);
    fw_err_t (*Write)(struct RingBuffer*, uint8_t*, uint16_t);
    fw_err_t (*Read)(struct RingBuffer*, uint8_t*, uint16_t);
}RingBufferComponentInterface;
#endif

/**
 *******************************************************************************
 * @brief       ring buffer function api
 *******************************************************************************
 */
#if USE_BUFFER_COMPONENT
extern fw_err_t InitRingBufferComponent(struct RingBuffer*, uint8_t*, uint16_t);
extern fw_err_t GetRingBufferLen(struct RingBuffer*, uint16_t*);
extern fw_err_t WriteRingBuffer(struct RingBuffer*, uint8_t*, uint16_t);
extern fw_err_t ReadRingBuffer(struct RingBuffer*, uint8_t*, uint16_t);
#endif

/**
 *******************************************************************************
 * @brief       define memory block
 *******************************************************************************
 */
__ALIGN_HEAD(8)
struct HeapBlock
{
	struct HeapBlock   *Next;
	uint32_t           Size   : 31;
    uint32_t           Status :  1;
};
__ALIGN_TAIL(8)

/**
 *******************************************************************************
 * @brief       define memory control block
 *******************************************************************************
 */
struct HeapControlBlock
{
    union
    {
        void             *Buffer;
        struct HeapBlock *Head; 
    };
    
    uint32_t Size;
};

/**
 *******************************************************************************
 * @brief       define memory management interface
 *******************************************************************************
 */
#if USE_MEMORY_MANAGEMENT_COMPONENT
typedef struct
{
    fw_err_t (*Init)(struct HeapControlBlock*,  uint8_t*, uint32_t);
    fw_err_t (*Alloc)(struct HeapControlBlock*, uint16_t, void**);
    fw_err_t (*Free)(struct HeapControlBlock*,  void*);
    fw_err_t (*IsIn)(struct HeapControlBlock*,  void*);
}MemoryManagementComponentInterface;
#endif

/**
 *******************************************************************************
 * @brief       memory management function api
 *******************************************************************************
 */
#if USE_MEMORY_MANAGEMENT_COMPONENT
extern fw_err_t InitHeapComponent(struct HeapControlBlock*,  uint8_t*, uint32_t);
extern fw_err_t AllocHeapMemory(struct HeapControlBlock*, uint32_t, void**);
extern fw_err_t FreeHeapMemory(struct HeapControlBlock*,  void*);
extern bool     IsInHeapMemory(struct HeapControlBlock*,  void*);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** buffer component */

/**********************************END OF FILE*********************************/
