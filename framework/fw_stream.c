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
#define Fw_Mem_Alloc(n) (NULL)
#define Fw_Mem_Free(n)

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework stream opera block
 *******************************************************************************
 */
const struct _FwStreamOpera FifoStreamOpera = 
{
    .Init = Fw_FifoStream_Init,
    .Fini = Fw_FifoStream_Fini,
    
    .GetUseSize  = Fw_FifoStream_GetUseSize,
    .GetFreeSize = Fw_FifoStream_GetFreeSize,

    .Write = Fw_FifoStream_Write,
    .Read = Fw_FifoStream_Read,
};
     
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       init stream block
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     init finish
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Init(struct Fw_Stream *stream)
{
    //< detect stream param
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    //< init common flag
    stream->IsLock = false;
    stream->IsOverFlow = false;
    stream->IsReady = false;
    stream->IsWorking = false;
    
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
    //< detect stream param
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    //< init common flag
    stream->IsLock = false;
    stream->IsOverFlow = false;
    stream->IsReady = false;
    stream->IsWorking = false;

    //< disconnect device
    if(!IS_PTR_NULL(stream->Device.Disconnect))
    {
        stream->Device.Disconnect(stream);
    }
        
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       connent stream hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     connent success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Connent(struct Fw_Stream *stream)
{
    if(stream->IsReady == false)
    {
        if(!IS_PTR_NULL(stream->Device.Connect))
        {
            stream->Device.Connect(stream);
        }
        
        stream->IsReady = true;
    }
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       disconnent stream hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     disconnent success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Disconnent(struct Fw_Stream *stream)
{
    if(stream->IsReady == true)
    {
        if(!IS_PTR_NULL(stream->Device.Disconnect))
        {
            stream->Device.Disconnect(stream);
        }
        
        stream->IsReady = false;
    }
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get data from hardware buffer
 * @param       [in/out]  *stream         stream block
 * @param       [in/out]  *buffer         buffer
 * @param       [in/out]  size            read size
 * @return      [in/out]  FW_ERR_NONE     read success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Read(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    if(stream->IsReady == true)
    {
        stream->Opera->Read(stream, buffer, size);
    }
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       write data to hardware buffer
 * @param       [in/out]  *stream         stream block
 * @param       [in/out]  *buffer         buffer
 * @param       [in/out]  size            read size
 * @return      [in/out]  FW_ERR_NONE     write success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Stream_Write(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    if(stream->IsReady == true)
    {
        stream->Opera->Write(stream, buffer, size);
        
        if(stream->IsWorking == false)
        {
            stream->IsWorking = true;
            
            if(!IS_PTR_NULL(stream->Device.InOut))
            {
                stream->Device.InOut(stream);
            }
        }
    }
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       fifo stream init
 * @param       [in/out]  *fifoStream     stream block
 * @param       [in/out]  *buffer         buffer
 * @param       [in/out]  size            read size
 * @return      [in/out]  FW_ERR_NONE     init success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_FifoStream_Init(struct Fw_Stream *fifoStream, uint8_t *buffer, uint8_t size)
{
    struct Fw_FifoStream *stream = (struct Fw_FifoStream *)fifoStream;
    
    return Fw_Queue_Init(&stream->Buffer, buffer, size);
}

/**
 *******************************************************************************
 * @brief       deinit fifo stream 
 * @param       [in/out]  *fifoStream     stream block
 * @return      [in/out]  FW_ERR_NONE     deinit success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_FifoStream_Fini(struct Fw_Stream *fifoStream)
{
    struct Fw_FifoStream *stream = (struct Fw_FifoStream *)fifoStream;
    
    return Fw_Queue_Fini(&stream->Buffer);
}

/**
 *******************************************************************************
 * @brief       get buffer use size
 * @param       [in/out]  *fifoStream     stream block
 * @param       [in/out]  *size           get size
 * @return      [in/out]  FW_ERR_NONE     get success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_FifoStream_GetUseSize(struct Fw_Stream *fifoStream, uint8_t *size)
{
    struct Fw_FifoStream *stream = (struct Fw_FifoStream *)fifoStream;
    
    return Fw_Queue_CanRead(&stream->Buffer, size);
}

/**
 *******************************************************************************
 * @brief       get buffer free size
 * @param       [in/out]  *fifoStream     stream block
 * @param       [in/out]  *size           get size
 * @return      [in/out]  FW_ERR_NONE     get success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_FifoStream_GetFreeSize(struct Fw_Stream *fifoStream, uint8_t *size)
{
    struct Fw_FifoStream *stream = (struct Fw_FifoStream *)fifoStream;
    
    return Fw_Queue_CanWrite(&stream->Buffer, size);
}

/**
 *******************************************************************************
 * @brief       write data to hardware buffer
 * @param       [in/out]  *fifoStream     stream block
 * @param       [in/out]  *buffer         buffer
 * @param       [in/out]  size            read size
 * @return      [in/out]  FW_ERR_NONE     write success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_FifoStream_Write(struct Fw_Stream *fifoStream, uint8_t *buffer, uint8_t size)
{
    struct Fw_FifoStream *stream = (struct Fw_FifoStream *)fifoStream;

    return Fw_Queue_PutData(&stream->Buffer, buffer, size);
}

/**
 *******************************************************************************
 * @brief       read data from hardware buffer
 * @param       [in/out]  *fifoStream     stream block
 * @param       [in/out]  *buffer         buffer
 * @param       [in/out]  size            read size
 * @return      [in/out]  FW_ERR_NONE     read success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_FifoStream_Read(struct Fw_Stream *fifoStream, uint8_t *buffer, uint8_t size)
{
    struct Fw_FifoStream *stream = (struct Fw_FifoStream *)fifoStream;
    
    return Fw_Queue_PushData(&stream->Buffer, buffer, size);
}   

/** @}*/     /** framework stream component */

/**********************************END OF FILE*********************************/
