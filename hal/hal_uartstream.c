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
 * @file       hal_uartstream.c                                                *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-08                                                      *
 * @brief      hal uart stream component source files                          *
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
* @defgroup hal uart stream component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "hal_uartstream.h"
#include "fw_debug.h"

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
void _Tx_Init(struct Fw_UartStream *uartStream)
{
    Hal_Uart_ClrTxCompletFlag(&uartStream->Device);
    Fw_Timer_Stop(&uartStream->Timer); 
    uartStream->State = UART_STREAM_SEND_STATE;
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
void Hal_UartStream_Init(void *param)
{
	struct Fw_UartStream *uartStream = (struct Fw_UartStream *)param;

    //< init timeout call back
	Fw_Timer_Init(&uartStream->Timer, "Stream Timeout Timer");
    Fw_Timer_SetCallback(&uartStream->Timer, Hal_UartStream_TxInit, (void *)uartStream);
    
    //< init hardware
    Hal_Uart_Open(&uartStream->Device);
	Hal_Uart_Init(&uartStream->Device);
}

/**
 *******************************************************************************
 * @brief       deinit uart stream hardware
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Hal_UartStream_Fini(void *param)
{
	struct Fw_UartStream *uartStream = (struct Fw_UartStream *)param;

	Hal_Uart_Fini(&uartStream->Device);
}

/**
 *******************************************************************************
 * @brief       enable uart stream tx function
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Hal_UartStream_TxConnect(void *param)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)param;
    
    Hal_Uart_TxConnect(&uartStream->Device);
}

/**
 *******************************************************************************
 * @brief       disable uart stream tx function
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Hal_UartStream_TxDisconnect(void *param)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)param;
    
    Hal_Uart_TxDisconnect(&uartStream->Device);
}

/**
 *******************************************************************************
 * @brief       enable uart stream rx function
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Hal_UartStream_RxConnect(void *param)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)param;
    
    Hal_Uart_RxConnect(&uartStream->Device);
}

/**
 *******************************************************************************
 * @brief       disable uart stream rx function
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Hal_UartStream_RxDisconnect(void *param)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)param;
    
    Hal_Uart_RxDisconnect(&uartStream->Device);
}

/**
 *******************************************************************************
 * @brief       uart stream out data
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Hal_UartStream_TxOut(void *param)
{
    Hal_UartStream_Send(param);
}

/**
 *******************************************************************************
 * @brief       uart stream rx data
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Hal_UartStream_RxIn(void *param)
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
void Hal_UartStream_Send(void *param)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)param;
    struct Fw_FifoStream *txStream = &uartStream->TxStream;
    struct _FwStreamBufferOpera *opera = txStream->Stream.Opera;
    
    if(txStream->Stream.IsRxReady == false)
    {
        return;
    }
    
    switch(uartStream->State)
    {
        case UART_STREAM_INIT_STATE:
        {
        _UART_STREAM_INIT_FLOW:
            _Tx_Init(uartStream);
//            break;
        }
        case UART_STREAM_SEND_STATE:
        {
            uint8_t sendData;
 
            if(opera->Read((struct Fw_Stream *)&txStream, &sendData, 1) == FW_ERR_NONE)
           	{
           		Hal_Uart_SendData(&uartStream->Device, sendData);
				Fw_Timer_Start(&uartStream->Timer, CAL_SET_TIME(10), 1);
           		uartStream->State = UART_STREAM_COMPLET_STATE;
            }
            else
            {
                struct HalCallback *Tx = &uartStream->Device.TxCallback;
                
                if(!IS_PTR_NULL(Tx->Callback))
                {
                    Tx->Callback(Tx->Param);
                }
                
				uartStream->State = UART_STREAM_INIT_STATE;
            }
            break;
        }
        case UART_STREAM_COMPLET_STATE:
        {
            uint8_t flag = 0;
            Hal_Uart_GetTxCompletFlag(&uartStream->Device, &flag);
            
            if(flag)
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
void Hal_UartStream_Receive(void *param, uint8_t recData)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)param;
    struct Fw_FifoStream *rxStream = &uartStream->RxStream;
    struct _FwStreamBufferOpera *opera = rxStream->Stream.Opera;
    
    if(rxStream->Stream.IsTxReady == true)
    {
        if (opera->Write((struct Fw_Stream *)&rxStream, &recData, 1) == FW_ERR_NONE)
        {
            Fw_Stream_PostRxEvent((struct Fw_Stream *)param);
        }
    }
}

/** @} */     /** hal uart stream component */

/**********************************END OF FILE*********************************/
