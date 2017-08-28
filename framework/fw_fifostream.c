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
 * @file       fw_fifostream.c                                                 *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-08                                                      *
 * @brief      framework fifo stream component source files                    *
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
 * @defgroup framework fifo stream component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_fifostream.h"
#include "fw_debug.h"
#include "hal_device.h"

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       init fifo stream tx param
 * @param       [in/out]  *param          fifo stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void _Init_Tx(Fw_FifoStream_t *stream)
{
    //< clear tx isr flag
    Hal_Device_Control(&stream->Device, HAL_CLR_TX_FLAG_CMD);
    
    //< stop time out timer
    Fw_Timer_Stop(&stream->Timer);
    
    //< reset uart stream send state mechine
    stream->State = FIFO_STREAM_SEND_STATE;
}

/**
 *******************************************************************************
 * @brief       init fifo stream tx param
 * @param       [in/out]  *param          fifo stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
static void Fw_FifoStream_InitTx(void *param)
{
    Fw_FifoStream_t *uartStream = (Fw_FifoStream_t *)param;

    _Init_Tx(uartStream);
}

/**
 *******************************************************************************
 * @brief       init fifo stream hardware
 * @param       [in/out]  *stream         fifo stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_FifoStream_Init(Fw_FifoStream_t *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    //< init stream
    Fw_Stream_Init(&stream->Tx);
    Fw_Stream_Init(&stream->Rx);
    
    //< init timeout call back
	Fw_Timer_Init(&stream->Timer, "Stream Timeout Timer");
    Fw_Timer_SetCallback(&stream->Timer, Fw_FifoStream_InitTx, (void *)stream);
    
    //< init hardware
    Hal_Device_Init(&stream->Device);
}

/**
 *******************************************************************************
 * @brief       deinit fifo stream hardware
 * @param       [in/out]  *stream         fifo stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE 
void Fw_FifoStream_Fini(Fw_FifoStream_t *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    //< deinit stream hardware
    Hal_Device_Fini(&stream->Device);
        
    //< deinit stream 
    Fw_Stream_Fini(&stream->Tx);
    Fw_Stream_Fini(&stream->Rx);
    
    //< deinit module timer
    Fw_Timer_Fini(&stream->Timer);
}

/**
 *******************************************************************************
 * @brief       enable fifo stream tx function
 * @param       [in/out]  *stream         fifo stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void Fw_FifoStream_ConnectTx(void *param)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    Fw_FifoStream_t *stream = (Fw_FifoStream_t *)param;
    
    Hal_Device_Control(&stream->Device, HAL_CONNECT_TX_CMD);
}

/**
 *******************************************************************************
 * @brief       disable fifo stream tx function
 * @param       [in/out]  *stream         fifo stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void Fw_FifoStream_DisconnectTx(void *param)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    Fw_FifoStream_t *stream = (Fw_FifoStream_t *)param;
    
    Hal_Device_Control(&stream->Device, HAL_DISCONNECT_TX_CMD);
}

/**
 *******************************************************************************
 * @brief       enable fifo stream rx function
 * @param       [in/out]  *stream         fifo stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void Fw_FifoStream_ConnectRx(void *param)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    Fw_FifoStream_t *stream = (Fw_FifoStream_t *)param;
    
    Hal_Device_Control(&stream->Device, HAL_CONNECT_RX_CMD);
}

/**
 *******************************************************************************
 * @brief       disable fifo stream rx function
 * @param       [in/out]  *stream         fifo stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void Fw_FifoStream_DisconnectRx(void *param)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    Fw_FifoStream_t *stream = (Fw_FifoStream_t *)param;
    
    Hal_Device_Control(&stream->Device, HAL_DISCONNECT_RX_CMD);
}

/**
 *******************************************************************************
 * @brief       fifo stream out data
 * @param       [in/out]  *stream         fifo stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void Fw_FifoStream_TxOut(void *param)
{
    Fw_FifoStream_Send(param);
}

/**
 *******************************************************************************
 * @brief       fifo stream rx data
 * @param       [in/out]  *stream         fifo stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void Fw_FifoStream_RxIn(void *param)
{
//    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;
}

/**
 *******************************************************************************
 * @brief       fifo stream send data
 * @param       [in/out]  *stream         fifo stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void Fw_FifoStream_Send(void *param)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    Fw_FifoStream_t *stream = (Fw_FifoStream_t *)param;

    if(stream->Tx.Tx.IsReady == false)
    {
        return;
    }
    
    switch(stream->State)
    {
        case FIFO_STREAM_INIT_STATE:
        {
        _FIFO_STREAM_INIT_FLOW:
            _Init_Tx(stream);
//            break;
        }
        case FIFO_STREAM_SEND_STATE:
        {
            uint8_t sendData;
 
            if(Fw_Stream_Read(&stream->Tx, &sendData, 1) == FW_ERR_NONE)
           	{
           		Hal_Device_Control(&stream->Device, HAL_SEND_BYTE_CMD, &sendData);
                
                //< start time out timer
				Fw_Timer_Start(&stream->Timer, CAL_SET_TIME(10), 1);
           		stream->State = FIFO_STREAM_COMPLET_STATE;
            }
            else
            {
                if(!IS_PTR_NULL(stream->Tx.Callback))
                {
                    Fw_Stream_PostEvent((struct Fw_Stream *)stream, FW_STREAM_TX_EVENT);
                }
                
				stream->State = FIFO_STREAM_INIT_STATE;
            }
            break;
        }
        case FIFO_STREAM_COMPLET_STATE:
        {
            bool status = false;
            
            Hal_Device_Control(&stream->Device, HAL_GET_TX_FLAG_CMD, &status);
            
            if (status == true)
            {
                goto _FIFO_STREAM_INIT_FLOW;
            }
//            break;
        }
        default:
            break;
    }
}

/**
 *******************************************************************************
 * @brief       uart stream receive data
 * @param       [in/out]  *stream         uart stream block
 * @param       [in/out]  recData         receive data
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Fw_UartStream_Receive(void *param, uint8_t recData)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    Fw_FifoStream_t *stream = (Fw_FifoStream_t *)param;

    if(stream->Rx.Rx.IsReady == false)
    {
        return;
    }
    
    Fw_Stream_Write(&stream->Rx, &recData, 1);
    
    if(!IS_PTR_NULL(stream->Rx.Callback))
    {
        Fw_Stream_PostEvent((struct Fw_Stream *)stream, FW_STREAM_RX_EVENT);
    }
}

/** @} */     /** hal fifo stream component */

/**********************************END OF FILE*********************************/
