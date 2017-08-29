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
#include "fw_path.h"
#include "fw_linklist.h"
    
/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_BUFFER_COMPONENT
    #define USE_BUFFER_COMPONENT                                             (1)

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
    #define USE_BUFFER_COMPONENT                                             (1)
#endif

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define framework buffer type
 *******************************************************************************
 */
struct Fw_RingBuffer
{
    uint8_t  *Buffer;
    uint16_t Head;
    uint16_t Tail;
    uint16_t Size;
    uint16_t Len;
};

typedef struct Fw_RingBuffer Fw_Fifo_t;

/**
 *******************************************************************************
 * @brief       define queue init type
 *******************************************************************************
 */
typedef struct
{
    uint8_t  *Buffer;
    uint16_t Size;
}Fw_Fifo_InitType;


/**
 *******************************************************************************
 * @brief       define framework queue type
 *******************************************************************************
 */
struct Fw_Queue
{
    uint8_t  *Buffer;
    uint16_t Tail;
	uint16_t Head;
    uint16_t Len;
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ring buffer function api
 *******************************************************************************
 */
extern __INLINE void Fw_Buffer_Init(struct Fw_RingBuffer*, uint8_t*, uint16_t);
extern __INLINE void Fw_Buffer_Fini(struct Fw_RingBuffer*);
extern __INLINE uint16_t Fw_Buffer_GetLen(struct Fw_RingBuffer*);
extern __INLINE uint16_t Fw_Buffer_Write(struct Fw_RingBuffer*, uint8_t*, uint16_t);
extern __INLINE uint16_t Fw_Buffer_Read(struct Fw_RingBuffer*, uint8_t*, uint16_t);

/**
 *******************************************************************************
 * @brief       queue function api
 *******************************************************************************
 */
extern __INLINE void Fw_Queue_Init(struct Fw_Queue*, uint8_t*, uint16_t);
extern __INLINE void Fw_Queue_Fini(struct Fw_Queue*);
extern __INLINE uint16_t Fw_Queue_Write(struct Fw_Queue*, uint8_t*, uint16_t);
extern __INLINE uint16_t Fw_Queue_Read(struct Fw_Queue*, uint8_t*, uint16_t);
extern __INLINE uint16_t Fw_Queue_GetFreeSize(struct Fw_Queue*);
extern __INLINE uint16_t Fw_Queue_GetUseSize(struct Fw_Queue*);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** buffer component */

/**********************************END OF FILE*********************************/
