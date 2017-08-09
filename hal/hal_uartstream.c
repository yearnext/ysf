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

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       uart stream drive function
 *******************************************************************************
 */
static void Hal_UartStream_Init(struct Fw_Stream*);
static void Hal_UartStream_Fini(struct Fw_Stream*);   
static void Hal_UartStream_TxConnect(struct Fw_Stream*);
static void Hal_UartStream_TxDisconnect(struct Fw_Stream*);
static void Hal_UartStream_RxConnect(struct Fw_Stream*);
static void Hal_UartStream_RxDisconnect(struct Fw_Stream*);
static void Hal_UartStream_TxOut(struct Fw_Stream*);
static void Hal_UartStream_RxIn(struct Fw_Stream*);
static void Hal_UartStream_Send(void*);

const struct _FwStreamDeviceOpera UartStreamDevice = 
{
    .Init          = Hal_UartStream_Init,
    .Fini          = Hal_UartStream_Fini,
    
    .Tx_Out        = Hal_UartStream_TxOut,
    .Tx_Connect    = Hal_UartStream_TxConnect,
    .Tx_Disconnect = Hal_UartStream_TxDisconnect,
    
    .Rx_In         = Hal_UartStream_RxIn,
    .Rx_Connect    = Hal_UartStream_RxConnect, 
    .Rx_Disconnect = Hal_UartStream_RxDisconnect,
};

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       init uart stream hardware
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
static void Hal_UartStream_Init(struct Fw_Stream *stream)
{
	struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;

    //< init timeout call back
	Fw_Timer_Init(&uartStream->Timer, "Stream Timeout Timer");
    Fw_Timer_SetCallback(&uartStream->Timer, Hal_UartStream_Send, (void *)uartStream);
    
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
static void Hal_UartStream_Fini(struct Fw_Stream *stream)
{
	struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;

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
static void Hal_UartStream_TxConnect(struct Fw_Stream *stream)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;
    
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
static void Hal_UartStream_TxDisconnect(struct Fw_Stream *stream)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;
    
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
static void Hal_UartStream_RxConnect(struct Fw_Stream *stream)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;
    
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
static void Hal_UartStream_RxDisconnect(struct Fw_Stream *stream)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;
    
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
static void Hal_UartStream_TxOut(struct Fw_Stream *stream)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)stream;
    
    uartStream->State = UART_STREAM_INIT_STATE;
    
    Hal_UartStream_Send((void *)stream);
}

/**
 *******************************************************************************
 * @brief       uart stream rx data
 * @param       [in/out]  *stream         uart stream block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
static void Hal_UartStream_RxIn(struct Fw_Stream *stream)
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
static void Hal_UartStream_Send(void *param)
{
    struct Fw_UartStream *uartStream = (struct Fw_UartStream *)param;
    
    switch(uartStream->State)
    {
        case UART_STREAM_INIT_STATE:
        {
        _UART_STREAM_INIT_FLOW:
            Hal_Uart_ClrTxCompletFlag(&uartStream->Device);
            Fw_Timer_Stop(&uartStream->Timer);
            uartStream->State = UART_STREAM_SEND_STATE;
//            break;
        }
        case UART_STREAM_SEND_STATE:
        {
            uint8_t sendData;
            
            if(uartStream->TxStream.Stream.Opera->Read((struct Fw_Stream *)&uartStream->TxStream, &sendData, 1) == FW_ERR_NONE)
           	{
           		Hal_Uart_SendData(&uartStream->Device, sendData);
				Fw_Timer_Start(&uartStream->Timer, CAL_SET_TIME(10), 1);
           		uartStream->State = UART_STREAM_COMPLET_STATE;
            }
            else
            {
				uartStream->State = UART_STREAM_INIT_STATE;
            }
            break;
        }
        case UART_STREAM_COMPLET_STATE:
        {
            goto _UART_STREAM_INIT_FLOW;
//            break;
        }
        default:
            break;
    }
}

/** @} */     /** hal uart stream component */

/**********************************END OF FILE*********************************/
