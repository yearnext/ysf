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
 * @file       fw_queue.c                                                      *
 * @author     Mr.Sun                                                          *
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
 
/**
 * @defgroup framework queue component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_queue.h"
#include "fw_debug.h"

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework queue structure
 *******************************************************************************
 */
#if USE_FRAMEWORK_QUEUE_COMPONENT
struct fw_queue
{
	uint8_t *Buffer;
	uint8_t Size;
	uint8_t Head;
	uint8_t Tail;
	uint8_t Len;
}static Queue[FW_QUEUE_MAX];
#endif

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       Macro
 *******************************************************************************
 */
#define GetFifoCanRead(block)                       ((block).Len)

/**
 *******************************************************************************
 * @brief       Macro
 *******************************************************************************
 */
#define GetFifoCanWrite(block)                      (((block).Size <= (block).Len) ? (0) : ((block).Size - (block).Len - 1))

/**
 *******************************************************************************
 * @brief       Macro
 *******************************************************************************
 */
#define PopByteToFifo(block, byteData)              _ST( if((block).Tail >= (block).Size)              \
														 {									           \
															 (block).Tail = 0;				           \
														 } 								               \
														 	 	 	 	 	 	 	 	 	 	 	   \
														 (block).Buffer[(block).Tail++] = (byteData);  \
														 (block).Len++;                                \
													   )

/**
 *******************************************************************************
 * @brief       Macro
 *******************************************************************************
 */
#define PushByteFromFifo(block, byteData)           _ST( if((block).Head >= (block).Size)              \
													     {											   \
													     	 (block).Head = 0;                         \
														 }                                             \
														 	 	 	 	 	 	 	 	 	 	 	   \
													     (byteData) = (block).Buffer[(block).Head++];  \
													     (block).Len--;                                \
                                                       )

/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_QUEUE_COMPONENT
/**
 *******************************************************************************
 * @brief       init queue
 * @param       [in/out]  queueId         queue id
 * @param       [in/out]  *queueBuffer    queue buffer
 * @param       [in/out]  queueSize       queue size
 * @return      [in/out]  fw_err_t        return init status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Queue_Init(uint8_t queueId, uint8_t *queueBuffer, uint8_t queueSize)
{
	//! Param Check
	if(queueId >= FW_QUEUE_MAX)
	{
		return FW_ERR_FAIL;
	}

	if(IS_PTR_NULL(queueBuffer))
	{
		return FW_ERR_FAIL;
	}

	if(queueSize == 0)
	{
		return FW_ERR_FAIL;
	}

	//! Queue Init
	Queue[queueId].Buffer = queueBuffer;
	Queue[queueId].Size   = queueSize;
	Queue[queueId].Head   = 0;
	Queue[queueId].Tail   = 0;
	Queue[queueId].Len    = 0;

	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       queue get len
 * @param       [in/out]  queueId         queue id
 * @param       [in/out]  *len            get len *buffer
 * @return      [in/out]  fw_err_t        return get status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Queue_GetLen(uint8_t queueId, uint8_t *len)
{
	//! Param Check
	if(queueId >= FW_QUEUE_MAX)
	{
		return FW_ERR_FAIL;
	}

	if(IS_PTR_NULL(len))
	{
		return FW_ERR_FAIL;
	}

	//! Get Fifo Len
	*len = Queue[queueId].Len;

	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       put byte to queue
 * @param       [in/out]  queueId         queue id
 * @param       [in/out]  putData         put data
 * @return      [in/out]  fw_err_t        return put status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Queue_PutByte(uint8_t queueId, uint8_t putData)
{
	//! Param Check
	if(queueId >= FW_QUEUE_MAX)
	{
		return FW_ERR_FAIL;
	}

	//! Pop Byte
	if(GetFifoCanWrite(Queue[queueId]))
	{
		PopByteToFifo(Queue[queueId], putData);
	}
	else
	{
		return FW_ERR_FAIL;
	}

	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       put data to queue
 * @param       [in/out]  queueId         queue id
 * @param       [in/out]  putData         put data
 * @return      [in/out]  fw_err_t        return put status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Queue_PutData(uint8_t queueId, uint8_t *putBuffer, uint8_t putSize)
{
	uint8_t *writeBuffer;

	//! Param Check
	if(queueId >= FW_QUEUE_MAX)
	{
		return FW_ERR_FAIL;
	}

	if(IS_PTR_NULL(putBuffer))
	{
		return FW_ERR_FAIL;
	}

	if(putSize == 0)
	{
		return FW_ERR_FAIL;
	}

	//! Pop Data
	if(GetFifoCanWrite(Queue[queueId]) >= putSize)
	{
		while(putSize--)
		{
			writeBuffer = putBuffer++;
			PopByteToFifo(Queue[queueId], *writeBuffer);
		}
	}
	else
	{
		return FW_ERR_FAIL;
	}

	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       push byte data from queue
 * @param       [in/out]  queueId         queue id
 * @param       [in/out]  *getData        get data buffer
 * @return      [in/out]  fw_err_t        return push status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Queue_PushByte(uint8_t queueId, uint8_t *pushData)
{
	//! Param Check
	if(queueId >= FW_QUEUE_MAX)
	{
		return FW_ERR_FAIL;
	}

	if(IS_PTR_NULL(pushData))
	{
		return FW_ERR_FAIL;
	}

	//! Push Byte
	if(GetFifoCanRead(Queue[queueId]))
	{
		PushByteFromFifo(Queue[queueId], *pushData);
	}
	else
	{
		return FW_ERR_FAIL;
	}

	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       push data from queue
 * @param       [in/out]  queueId         queue id
 * @param       [in/out]  *PushBuffer     push data buffer
 * @param       [in/out]  pushSize        push data size
 * @return      [in/out]  fw_err_t        return push status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Queue_PushData(uint8_t queueId, uint8_t *PushBuffer, uint8_t pushSize)
{
	uint8_t *readBuffer;

	//! Param Check
	if(queueId >= FW_QUEUE_MAX)
	{
		return FW_ERR_FAIL;
	}

	if(IS_PTR_NULL(PushBuffer))
	{
		return FW_ERR_FAIL;
	}

	if(pushSize == 0)
	{
		return FW_ERR_FAIL;
	}

	//! Push Data
	if(GetFifoCanRead(Queue[queueId]) >= pushSize)
	{
		while(pushSize--)
		{
			readBuffer = PushBuffer++;
			PushByteFromFifo(Queue[queueId], *readBuffer);
		}
	}
	else
	{
		return FW_ERR_FAIL;
	}

	return FW_ERR_NONE;
}

#endif

/**********************************END OF FILE*********************************/
