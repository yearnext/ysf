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
 * @file       fw_stream.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-07-30
 * @brief      framework stream component source files
 * @par        paltform                                  
 *                 Windows
 * @par        compiler									                         
 * 			       GCC
 *******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 *******************************************************************************
 */

/**
 * @defgroup framework stream component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_stream.h"
#include "fw_debug.h"
#include <string.h>

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework stream opera block
 *******************************************************************************
 */
static const struct _FwStreamOpera _Fw_Stream_Opera = 
{
    .Write = Fw_Queue_PutData,
    .Read  = Fw_Queue_PushData,
};
     
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       init stream block
 * @param       [in/out]  *stream         stream block
 * @param       [in/out]  *opera          hardware call back function block
 * @param       [in/out]  *txCallback     tx call back function block
 * @param       [in/out]  *rxCallback     rx call back function block
 * @return      [in/out]  FW_ERR_NONE     init finish
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Init(struct Fw_Stream *stream, 
                        _StreamDeviceInitType *device, 
                        _StreamCallbackInitType *txCallback, 
                        _StreamCallbackInitType *rxCallback)
{
    //< detect stream param
    _FW_ASSERT(IS_PTR_NULL(stream));
    _FW_ASSERT(IS_PTR_NULL(device));
    _FW_ASSERT(IS_PTR_NULL(txCallback));
    _FW_ASSERT(IS_PTR_NULL(rxCallback));
    
    //< clear stream block
    memset(stream, 0, sizeof(struct Fw_Stream));
    
    //< init stream opera
    stream->Device.Init = device->Init;
    stream->Device.Fini = device->Fini;
    
    //< init stream opera
    stream->Opera = (struct _FwStreamOpera *)&_Fw_Stream_Opera;
    
    //< init tx call back
    stream->TxCallback.Connect = txCallback->Connect;
    stream->TxCallback.Disconnect = txCallback->Disconnect;
    stream->TxCallback.InOut = txCallback->InOut;
    
    //< init rx call back
    stream->RxCallback.Connect = rxCallback->Connect;
    stream->RxCallback.Disconnect = rxCallback->Disconnect;
    stream->RxCallback.InOut = rxCallback->InOut;

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       enable stream block
 * @param       [in/out]  *stream         stream block
 * @param       [in/out]  *txBuffer       tx buffer block
 * @param       [in/out]  *rxBuffer       rx buffer block
 * @return      [in/out]  FW_ERR_NONE     enable success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Enable(struct Fw_Stream *stream, 
                          _QueueInitType *txBuffer, 
                          _QueueInitType *rxBuffer)
{
    //< detect stream param
    _FW_ASSERT(IS_PTR_NULL(stream));
    _FW_ASSERT(IS_PTR_NULL(txBuffer));
    _FW_ASSERT(IS_PTR_NULL(txBuffer->Buffer));
    _FW_ASSERT(IS_PARAM_ZERO(txBuffer->Size));
    _FW_ASSERT(IS_PTR_NULL(rxBuffer));
    _FW_ASSERT(IS_PTR_NULL(rxBuffer->Buffer));
    _FW_ASSERT(IS_PARAM_ZERO(rxBuffer->Size));
    
    //< init fifo
    Fw_Queue_Init(&stream->TxFifo, txBuffer->Buffer, txBuffer->Size);
    Fw_Queue_Init(&stream->RxFifo, rxBuffer->Buffer, rxBuffer->Size);
    
    //< init common flag
    stream->IsRxReady = true;
    stream->IsTxReady = false;
    
    //< init stream locked count
    stream->TxLock = 0;
    stream->RxLock = 0;
    
    stream->Device.Init(stream);
    stream->RxCallback.Connect(stream);
    stream->TxCallback.Disconnect(stream);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       lock stream tx opera
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void Fw_Stream_LockTx(struct Fw_Stream *stream)
{
    if(stream->TxLock == 0)
    {
        stream->TxCallback.Disconnect(stream);
        stream->TxLock++;
    }
    else if(stream->TxLock < 200)
    {
        stream->TxLock++;
    }
    else
    {
        //< do nothing!
    }
}

/**
 *******************************************************************************
 * @brief       unlock stream tx opera
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void Fw_Stream_UnlockTx(struct Fw_Stream *stream)
{
    if(stream->TxLock > 0)
    {
        if(--stream->TxLock == 0)
        {
            stream->TxCallback.Connect(stream);
        }
    }
}

/**
 *******************************************************************************
 * @brief       lock stream rx opera
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void Fw_Stream_LockRx(struct Fw_Stream *stream)
{
    if(stream->RxLock == 0)
    {
        stream->RxCallback.Disconnect(stream);
        stream->RxLock++;
    }
    else if(stream->RxLock < 200)
    {
        stream->RxLock++;
    }
    else
    {
        //< do nothing!
    }
    
    if(stream->RxLock < 200)
    {
        stream->RxLock++;
    }
}

/**
 *******************************************************************************
 * @brief       unlock stream rx opera
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void Fw_Stream_UnlockRx(struct Fw_Stream *stream)
{
    if(stream->RxLock > 0)
    {
        if(--stream->RxLock == 0)
        {
            stream->RxCallback.Connect(stream);
        }
    }
}

/**
 *******************************************************************************
 * @brief       write data to stream
 * @param       [in/out]  *stream         stream block
 * @param       [in/out]  *txBuffer       tx buffer
 * @param       [in/out]  *txBufferSize   tx data size
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Write(struct Fw_Stream *stream, uint8_t *txBuffer, uint8_t txBufferSize)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    _FW_ASSERT(IS_PTR_NULL(txBuffer));
    _FW_ASSERT(IS_PARAM_ZERO(txBufferSize));
    
    Fw_Stream_LockTx(stream);
    
    Fw_Queue_PutData(&stream->TxFifo, txBuffer, txBufferSize);
    
    //< set tx ready flag
    if(stream->IsTxReady == false)
    {
        stream->IsTxReady = true;
        
        stream->TxCallback.InOut(stream);
    }
    
    Fw_Stream_UnlockTx(stream);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       read data from stream
 * @param       [in/out]  *stream         stream block
 * @param       [in/out]  *rxBuffer       rx buffer
 * @param       [in/out]  *rxBufferSize   rx data size
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Read(struct Fw_Stream *stream, uint8_t *rxBuffer, uint8_t rxBufferSize)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    _FW_ASSERT(IS_PTR_NULL(rxBuffer));
    _FW_ASSERT(IS_PARAM_ZERO(rxBufferSize));
    
    Fw_Stream_LockRx(stream);
    Fw_Queue_PushData(&stream->RxFifo, rxBuffer, rxBufferSize);
    Fw_Stream_UnlockRx(stream);
    
    return FW_ERR_NONE;
}

/** @}*/     /** framework stream component */

/**********************************END OF FILE*********************************/
