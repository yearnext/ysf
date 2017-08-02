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
 * @file       fw_queue.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-06-13                                                      *
 * @brief      framework queue component                                       *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_QUEUE_H__
#define __FRAMEWORK_QUEUE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework queue structure
 *******************************************************************************
 */
struct Fw_Queue
{
	uint8_t *Buffer;
	uint8_t Size;
	uint8_t Head;
	uint8_t Tail;
	uint8_t Len;
};

typedef struct Fw_Queue Fw_Fifo_t;

typedef struct
{
    uint8_t *Buffer;
    uint8_t Size;
}_QueueInitType;

/* Exported variables --------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       Queue Interface
 *******************************************************************************
 */
extern fw_err_t Fw_Queue_Init(struct Fw_Queue*, uint8_t*, uint8_t);
extern fw_err_t Fw_Queue_GetLen(struct Fw_Queue*, uint8_t*);

extern fw_err_t Fw_Queue_CanRead(struct Fw_Queue*, uint8_t*);
extern fw_err_t Fw_Queue_CanWrite(struct Fw_Queue*, uint8_t*);

extern fw_err_t Fw_Queue_PutByte(struct Fw_Queue*, uint8_t);
extern fw_err_t Fw_Queue_PutData(struct Fw_Queue*, uint8_t*, uint8_t);

extern fw_err_t Fw_Queue_PushByte(struct Fw_Queue*, uint8_t*);
extern fw_err_t Fw_Queue_PushData(struct Fw_Queue*, uint8_t*, uint8_t);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
