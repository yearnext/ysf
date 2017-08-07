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
 * @brief       define buffer type
 *******************************************************************************
 */
struct _Fw_RingBuffer
{
    uint8_t  *Buffer;
    uint16_t Head;
    uint16_t Tail;
    uint16_t Size;
    uint16_t Len;
};

typedef struct _Fw_RingBuffer Fw_Fifo_t;

/**
 *******************************************************************************
 * @brief       define queue init type
 *******************************************************************************
 */
typedef struct _QueueInitType
{
    uint8_t  *Buffer;
    uint16_t Size;
}_QueueInitType, _FifoInitType;

/**
 *******************************************************************************
 * @brief       ring buffer function api
 *******************************************************************************
 */
extern fw_err_t Fw_Buffer_Init(struct _Fw_RingBuffer*, uint8_t*, uint16_t);
extern fw_err_t Fw_Buffer_Fini(struct _Fw_RingBuffer*);
extern fw_err_t Fw_Buffer_GetLen(struct _Fw_RingBuffer*, uint16_t*);
extern fw_err_t Fw_Buffer_Write(struct _Fw_RingBuffer*, uint8_t*, uint16_t);
extern fw_err_t Fw_Buffer_Read(struct _Fw_RingBuffer*, uint8_t*, uint16_t);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** buffer component */

/**********************************END OF FILE*********************************/
