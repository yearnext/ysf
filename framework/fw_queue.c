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
 
/**
* @defgroup framework queue component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "fw_queue.h"
#include "fw_debug.h"
#include "fw_core.h"

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       queue write byte function
 * @param       [in/out]  *queue          queue block
 * @param       [in/out]  byteData        write data buffer
 * @return      [in/out]  fw_err_t        return init status
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void Fw_Queue_WriteByte(struct Fw_Queue *queue, uint8_t byteData)
{
    if(queue->Tail >= queue->Size)
    {
        queue->Tail = 0;
    }
    
    queue->Buffer[queue->Tail++] = byteData;
    queue->Len++;
}

/**
 *******************************************************************************
 * @brief       queue read byte function
 * @param       [in/out]  *queue          queue block
 * @param       [in/out]  *byteData       read data buffer
 * @return      [in/out]  fw_err_t        return init status
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void Fw_Queue_ReadByte(struct Fw_Queue *queue, uint8_t *byteData)
{
    if(queue->Head >= queue->Size)
    {
        queue->Head = 0;
    }
    
    *byteData = queue->Buffer[queue->Head++];
    queue->Len--;
}

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       init queue
 * @param       [in/out]  *queue          queue block
 * @param       [in/out]  *queueBuffer    queue buffer
 * @param       [in/out]  queueSize       queue size
 * @return      [in/out]  fw_err_t        return init status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Queue_Init(struct Fw_Queue *queue, uint8_t *queueBuffer, uint8_t queueSize)
{
	//< Param Check
    _FW_ASSERT(IS_PTR_NULL(queueBuffer));
    _FW_ASSERT(IS_PTR_NULL(queue));
    _FW_ASSERT(queueSize == 0);
    
	//< Queue Init
	queue->Buffer = queueBuffer;
	queue->Size   = queueSize;
	queue->Head   = 0;
	queue->Tail   = 0;
	queue->Len    = 0;

	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       deinit queue
 * @param       [in/out]  *queue          queue block
 * @return      [in/out]  fw_err_t        return deinit status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Queue_Fini(struct Fw_Queue *queue)
{
	//< Param Check
    _FW_ASSERT(IS_PTR_NULL(queue));
    
	//< Queue Init
	queue->Buffer = NULL;
	queue->Size   = 0;
	queue->Head   = 0;
	queue->Tail   = 0;
	queue->Len    = 0;

	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       queue get len
 * @param       [in/out]  *queue          queue block
 * @param       [in/out]  *len            get len *buffer
 * @return      [in/out]  fw_err_t        return get status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Queue_GetLen(struct Fw_Queue *queue, uint8_t *len)
{
	//! Param Check
    _FW_ASSERT(IS_PTR_NULL(len));
    _FW_ASSERT(IS_PTR_NULL(queue));

	//! Get Fifo Len
	*len = queue->Len;

	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       queue can read data num
 * @param       [in/out]  *queue          queue block
 * @return      [in/out]  uint8_t         can read data num
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Queue_CanRead(struct Fw_Queue *queue, uint8_t *getNum)
{
    _FW_ASSERT(IS_PTR_NULL(queue));
    _FW_ASSERT(IS_PTR_NULL(getNum));
    
    *getNum = queue->Len;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       queue can write data num
 * @param       [in/out]  *queue          queue block
 * @return      [in/out]  uint8_t         can write data num
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Queue_CanWrite(struct Fw_Queue *queue, uint8_t *getNum)
{
    _FW_ASSERT(IS_PTR_NULL(queue));
    _FW_ASSERT(IS_PTR_NULL(getNum));
    
    if(queue->Size <= queue->Len)
    {
        *getNum = 0;
    }
    
    *getNum = queue->Size - queue->Len - 1;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       put byte to queue
 * @param       [in/out]  *queue          queue block
 * @param       [in/out]  putData         put data
 * @return      [in/out]  fw_err_t        return put status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Queue_PutByte(struct Fw_Queue *queue, uint8_t putData)
{
	//! Param Check
    _FW_ASSERT(IS_PTR_NULL(queue));

    uint8_t count = 0;
    
    Fw_Queue_CanWrite(queue, &count);
    
	//! Pop Byte
	if(count > 0)
	{
		Fw_Queue_WriteByte(queue, putData);
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
fw_err_t Fw_Queue_PutData(struct Fw_Queue *queue, uint8_t *putBuffer, uint8_t putSize)
{
    _FW_ASSERT(IS_PTR_NULL(queue));
    _FW_ASSERT(IS_PTR_NULL(putBuffer));
    _FW_ASSERT(IS_PARAM_ZERO(putSize));
    
    uint8_t *writeBuffer;
    uint8_t count = 0;
    
    Fw_Queue_CanWrite(queue, &count);
	
    //! Pop Data
	if(count >= putSize)
	{
		while(putSize--)
		{
			writeBuffer = putBuffer++;
			Fw_Queue_WriteByte(queue, *writeBuffer);
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
fw_err_t Fw_Queue_PushByte(struct Fw_Queue *queue, uint8_t *pushData)
{
	//! Param Check
    _FW_ASSERT(IS_PTR_NULL(queue));
    _FW_ASSERT(IS_PTR_NULL(pushData));
    
    uint8_t count = 0;
    Fw_Queue_CanRead(queue, &count);
    
	//! Push Byte
	if(count > 0)
	{
		Fw_Queue_ReadByte(queue, pushData);
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
fw_err_t Fw_Queue_PushData(struct Fw_Queue *queue, uint8_t *PushBuffer, uint8_t pushSize)
{
	//! Param Check
    _FW_ASSERT(IS_PTR_NULL(queue));
    _FW_ASSERT(IS_PTR_NULL(PushBuffer));
    _FW_ASSERT(IS_PARAM_ZERO(pushSize));

    uint8_t *readBuffer;    
    uint8_t count = 0;
    
    Fw_Queue_CanRead(queue, &count);
    
	//! Push Data
	if(count >= pushSize)
	{
		while(pushSize--)
		{
			readBuffer = PushBuffer++;
			Fw_Queue_ReadByte(queue, readBuffer);
		}
	}
	else
	{
		return FW_ERR_FAIL;
	}

	return FW_ERR_NONE;
}

/**********************************END OF FILE*********************************/
