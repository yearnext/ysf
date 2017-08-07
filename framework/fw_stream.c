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
#include <string.h>
#include "fw_stream.h"
#include "fw_debug.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       fifo stream opera function
 *******************************************************************************
 */
static fw_err_t _FifoStreamOpera_Init(struct Fw_Stream*, void*);
static fw_err_t _FifoStreamOpera_Fini(struct Fw_Stream*);
static fw_err_t _FifoStreamOpera_Write(struct Fw_Stream*, uint8_t*, uint8_t);
static fw_err_t _FifoStreamOpera_Read(struct Fw_Stream*, uint8_t*, uint8_t);

/* Private functions ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework stream opera block
 *******************************************************************************
 */
const _StreamBufferOperaInitType _StreamFifoOpera = 
{
    .Init  = _FifoStreamOpera_Init,
    .Fini  = _FifoStreamOpera_Fini,
    
    .Write = _FifoStreamOpera_Write,
    .Read  = _FifoStreamOpera_Read,
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
                        _StreamBufferOperaInitType *opera, 
                        _StreamDeviceOperaInitType *device, 
                        void *param)
{
    //< detect stream param
    _FW_ASSERT(IS_PTR_NULL(stream));
    _FW_ASSERT(IS_PTR_NULL(opera));
    _FW_ASSERT(IS_PTR_NULL(device));
    
    //< clear stream block
    memset(stream, 0, sizeof(struct Fw_Stream));

    //< set stream device opera
    memcpy(&stream->Device, device, sizeof(stream->Device));

    //< set stream buffer opera
    stream->Opera = opera;
    
    //< init stream buffer
    if(!IS_PTR_NULL(stream->Opera->Init))
    {
        stream->Opera->Init(stream, param);
    }
        
    //< init stream hardware
    if(!IS_PTR_NULL(stream->Device.Init))
    {
        stream->Device.Init(stream);
    }
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       deinit stream block
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     deinit finish
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Fini(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    //< init stream hardware
    if(!IS_PTR_NULL(stream->Device.Fini))
    {
        stream->Device.Fini(stream);
    }
    
    //< init stream buffer
    if(!IS_PTR_NULL(stream->Opera->Fini))
    {
        stream->Opera->Fini(stream);
    }
    
    memset(stream, 0, sizeof(struct Fw_Stream));
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       connect stream tx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     connect finish
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_TxConnect(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    stream->IsTxReady = true;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       disconnect stream tx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     disconnect finish
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_TxDisconnect(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    stream->IsTxReady = false;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       connect stream rx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     connect finish
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_RxConnect(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    stream->IsRxReady = true;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       disconnect stream tx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     disconnect finish
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_RxDisconnect(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    stream->IsRxReady = true;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       write data to stream
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  FW_ERR_NONE    write success
 * @return      [in/out]  FW_ERR_FAIL    write failed
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Write(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    _FW_ASSERT(IS_PTR_NULL(stream->Opera));
    _FW_ASSERT(IS_PTR_NULL(buffer));
    _FW_ASSERT(IS_PARAM_ZERO(size));
    
    if(stream->IsTxReady == true)
    {
        if(!IS_PTR_NULL(stream->Opera->Write) && !IS_PTR_NULL(stream->Device.Tx_Out))
        {
            if(stream->Opera->Write(stream, buffer, size) == FW_ERR_NONE)
            {
                stream->Device.Tx_Out(stream);
            
                return FW_ERR_NONE;
            }
        }
    }
    
    return FW_ERR_FAIL;
}

/**
 *******************************************************************************
 * @brief       read data from stream
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  FW_ERR_NONE    read success
 * @return      [in/out]  FW_ERR_FAIL    read failed
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Read(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    _FW_ASSERT(IS_PTR_NULL(stream->Opera));
    _FW_ASSERT(IS_PTR_NULL(buffer));
    _FW_ASSERT(IS_PARAM_ZERO(size));
    
    if(stream->IsRxReady == true)
    {
        if(!IS_PTR_NULL(stream->Opera->Read))
        {
            if(stream->Opera->Read(stream, buffer, size) == FW_ERR_NONE)
            {
                return FW_ERR_NONE;
            }
        }
    }
    
    return FW_ERR_FAIL;
}

/**
 *******************************************************************************
 * @brief       init fifo stream buffer
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  *buffer        buffer block
 * @return      [in/out]  FW_ERR_NONE    init success
 * @return      [in/out]  FW_ERR_FAIL    init failed
 * @note        None
 *******************************************************************************
 */
static fw_err_t _FifoStreamOpera_Init(struct Fw_Stream *stream, void *buffer)
{
    struct FwFifoStream *fifoStream = (struct FwFifoStream *)stream;
    _FifoInitType *fifo = (_FifoInitType *)buffer;
    
    _FW_ASSERT(IS_PTR_NULL(fifoStream));
    _FW_ASSERT(IS_PTR_NULL(fifo));

    return Fw_Buffer_Init((struct _Fw_RingBuffer *)&fifoStream->Fifo, fifo->Buffer, fifo->Size);
}

/**
 *******************************************************************************
 * @brief       deinit fifo stream buffer 
 * @param       [in/out]  *stream        stream block
 * @return      [in/out]  FW_ERR_NONE    deinit success
 * @return      [in/out]  FW_ERR_FAIL    deinit failed
 * @note        None
 *******************************************************************************
 */
static fw_err_t _FifoStreamOpera_Fini(struct Fw_Stream *stream)
{
    struct FwFifoStream *fifoStream = (struct FwFifoStream *)stream;

    _FW_ASSERT(IS_PTR_NULL(fifoStream));
    
    return Fw_Buffer_Fini((struct _Fw_RingBuffer *)&fifoStream->Fifo);
}

/**
 *******************************************************************************
 * @brief       write data to stream
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  FW_ERR_NONE    write success
 * @return      [in/out]  FW_ERR_FAIL    write failed
 * @note        None
 *******************************************************************************
 */
static fw_err_t _FifoStreamOpera_Write(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
    struct FwFifoStream *fifoStream = (struct FwFifoStream *)stream;

    _FW_ASSERT(IS_PTR_NULL(fifoStream));
    
    return Fw_Buffer_Write((struct _Fw_RingBuffer *)&fifoStream->Fifo, buffer, size);
}

/**
 *******************************************************************************
 * @brief       read data from stream
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  FW_ERR_NONE    read success
 * @return      [in/out]  FW_ERR_FAIL    read failed
 * @note        None
 *******************************************************************************
 */
static fw_err_t _FifoStreamOpera_Read(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
    struct FwFifoStream *fifoStream = (struct FwFifoStream *)stream;

    _FW_ASSERT(IS_PTR_NULL(fifoStream));
    
    return Fw_Buffer_Read((struct _Fw_RingBuffer *)&fifoStream->Fifo, buffer, size);
}

/** @}*/     /** framework stream component */

/**********************************END OF FILE*********************************/
