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
 * @file       fw_uartstream.c                                                 *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-08                                                      *
 * @brief      framework uart stream component source files                    *
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
 * @defgroup framework uart stream component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_uartstream.h"
#include "fw_debug.h"
#include "hal_uart.h"

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       init uart stream tx param
 * @param       [in/out]  *param          uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void _Tx_Init(struct Fw_UartStream *stream)
{
    //< clear tx isr flag
    Hal_Uart_IsTxComplet(&stream->Device);
    
    //< stop time out timer
    Fw_Timer_Stop(&stream->Timer);
    
    //< reset uart stream send state mechine
    stream->State = UART_STREAM_SEND_STATE;
}

/**
 *******************************************************************************
 * @brief       init uart stream tx param
 * @param       [in/out]  *param          uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Hal_UartStream_TxInit(void *param)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)param;

    _Tx_Init(uartStream);
}

/**
 *******************************************************************************
 * @brief       init uart stream hardware
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_UartStream_Init(struct Fw_UartStream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    //< init stream
    Fw_Stream_Init(&stream->Tx);
    Fw_Stream_Init(&stream->Rx);
    
    //< init timeout call back
	Fw_Timer_Init(&stream->Timer, "Stream Timeout Timer");
    Fw_Timer_SetCallback(&stream->Timer, Hal_UartStream_TxInit, (void *)stream);
    
    //< init hardware
	Hal_Uart_Init(&stream->Device, (void *)&stream->Device);
}

/**
 *******************************************************************************
 * @brief       deinit uart stream hardware
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_UartStream_Fini(struct Fw_UartStream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    //< deinit stream hardware
	Hal_Uart_Fini(&stream->Device);
    
    //< deinit stream 
    Fw_Stream_Fini(&stream->Tx);
    Fw_Stream_Fini(&stream->Rx);
    
    //< deinit module timer
    Fw_Timer_Fini(&stream->Timer);
}

/**
 *******************************************************************************
 * @brief       enable uart stream tx function
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Fw_UartStream_TxConnect(void *param)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    struct Fw_UartStream *stream = (struct Fw_UartStream *)param;
    
    Hal_Uart_TxConnect(&stream->Device);
}

/**
 *******************************************************************************
 * @brief       disable uart stream tx function
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Fw_UartStream_TxDisconnect(void *param)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    struct Fw_UartStream *stream = (struct Fw_UartStream *)param;
    
    Hal_Uart_TxDisconnect(&stream->Device);
}

/**
 *******************************************************************************
 * @brief       enable uart stream rx function
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Fw_UartStream_RxConnect(void *param)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    struct Fw_UartStream *stream = (struct Fw_UartStream *)param;
    
    Hal_Uart_RxConnect(&stream->Device);
}

/**
 *******************************************************************************
 * @brief       disable uart stream rx function
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Fw_UartStream_RxDisconnect(void *param)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    struct Fw_UartStream *stream = (struct Fw_UartStream *)param;
    
    Hal_Uart_RxDisconnect(&stream->Device);
}

/**
 *******************************************************************************
 * @brief       uart stream out data
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Fw_UartStream_TxOut(void *param)
{
    Fw_UartStream_Send(param);
}

/**
 *******************************************************************************
 * @brief       uart stream rx data
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Fw_UartStream_RxIn(void *param)
{
//    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;
}

/**
 *******************************************************************************
 * @brief       uart stream send data
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Fw_UartStream_Send(void *param)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    struct Fw_UartStream *stream = (struct Fw_UartStream *)param;

    if(stream->Tx.Tx.IsReady == false)
    {
        return;
    }
    
    switch(stream->State)
    {
        case UART_STREAM_INIT_STATE:
        {
        _UART_STREAM_INIT_FLOW:
            _Tx_Init(stream);
//            break;
        }
        case UART_STREAM_SEND_STATE:
        {
            uint8_t sendData;
 
            if(Fw_Stream_Read(&stream->Tx, &sendData, 1) == FW_ERR_NONE)
           	{
           		Hal_Uart_Send(&stream->Device, sendData);
                
                //< start time out timer
				Fw_Timer_Start(&stream->Timer, CAL_SET_TIME(10), 1);
           		stream->State = UART_STREAM_COMPLET_STATE;
            }
            else
            {
                if(!IS_PTR_NULL(stream->Tx.Callback))
                {
                    Fw_Stream_PostEvent((struct Fw_Stream *)stream, FW_STREAM_TX_EVENT);
                }
                
				stream->State = UART_STREAM_INIT_STATE;
            }
            break;
        }
        case UART_STREAM_COMPLET_STATE:
        {
            if (Hal_Uart_IsTxComplet(&stream->Device) == true)
            {
                goto _UART_STREAM_INIT_FLOW;
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
    
    struct Fw_UartStream *stream = (struct Fw_UartStream *)param;

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

/** @} */     /** framework uart stream component */

/**********************************END OF FILE*********************************/
