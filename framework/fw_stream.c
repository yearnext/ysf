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
#include "fw_task.h"
#include "fw_memory.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
///**
// *******************************************************************************
// * @brief       stream task management block
// *******************************************************************************
// */
//#if USE_STREAM_COMPONENT
//static struct Fw_Task StreamTask;
//#endif

/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       fifo stream opera function
 *******************************************************************************
 */
#if USE_STREAM_COMPONENT
//static void _FifoStreamOpera_Init(void*);
//static void _FifoStreamOpera_Fini(void*);
//static fw_err_t _FifoStreamOpera_Write(void*, uint8_t*, uint8_t);
//static fw_err_t _FifoStreamOpera_Read(void*, uint8_t*, uint8_t);

////static void _BlockStreamOpera_Init(struct Fw_Stream*, void*);
////static void _BlockStreamOpera_Fini(struct Fw_Stream*);
////static fw_err_t _BlockStreamOpera_Write(struct Fw_Stream*, uint8_t*, uint8_t);
////static fw_err_t _BlockStreamOpera_Read(struct Fw_Stream*, uint8_t*, uint8_t);

///**
// *******************************************************************************
// * @brief       framework stream opera block
// *******************************************************************************
// */
//const struct Fw_StreamBuffer_Ops Fw_FifoStream_Ops = 
//{
//    .Init  = _FifoStreamOpera_Init,
//    .Fini  = _FifoStreamOpera_Fini,
//    
//    .Write = _FifoStreamOpera_Write,
//    .Read  = _FifoStreamOpera_Read,
//};
  
//const struct Fw_Stream_Buffer_Opera FwStreamBlockOpera = 
//{
//    .Init  = _BlockStreamOpera_Init,
//    .Fini  = _BlockStreamOpera_Fini,
//    
//    .Write = _BlockStreamOpera_Write,
//    .Read  = _BlockStreamOpera_Read,
//};
#endif

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_STREAM_COMPONENT
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
__INLINE void Fw_Stream_Init(struct Fw_Stream *stream)
{
    //< detect stream param
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    //< init buffer
    if(!IS_PTR_NULL(stream->Interface->Init))
    {
        stream->Interface->Init(stream->Pool);
    }
    
    //< init hardware
    if(!IS_PTR_NULL(stream->Device))
    {
        Hal_Device_Init(stream->Device);
    }
}

/**
 *******************************************************************************
 * @brief       deinit stream block
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     deinit finish
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Stream_Fini(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));

    //< init hardware
    if(!IS_PTR_NULL(stream->Device))
    {
        Hal_Device_Fini(stream->Device);
    }
    
    //< deinit stream buffer
    if(!IS_PTR_NULL(stream->Interface->Fini))
    {
        stream->Interface->Fini(stream->Pool);
    }
}

/**
 *******************************************************************************
 * @brief       connect stream tx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     connect finish
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Stream_ConnectTx(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));

	if(stream->Tx.IsReady == false)
	{
        Hal_Device_Control(stream->Device, HAL_CONNECT_TX_CMD);
		stream->Tx.IsReady = true;
	}
}

/**
 *******************************************************************************
 * @brief       disconnect stream tx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     disconnect finish
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Stream_DisconnectTx(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));

	if(stream->Tx.IsReady == true)
	{
        Hal_Device_Control(stream->Device, HAL_DISCONNECT_TX_CMD);
		stream->Tx.IsReady = false;
	}
}

/**
 *******************************************************************************
 * @brief       connect stream tx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     connect finish
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Stream_ConnectRx(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));

	if(stream->Rx.IsReady == false)
	{
        Hal_Device_Control(stream->Device, HAL_CONNECT_RX_CMD);
		stream->Rx.IsReady = true;
	}
}

/**
 *******************************************************************************
 * @brief       disconnect stream tx hardware
 * @param       [in/out]  *stream         stream block
 * @return      [in/out]  FW_ERR_NONE     disconnect finish
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Stream_DisconnectRx(struct Fw_Stream *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));

	if(stream->Rx.IsReady == true)
	{
        Hal_Device_Control(stream->Device, HAL_DISCONNECT_RX_CMD);
		stream->Rx.IsReady = false;
	}
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
__INLINE uint16_t Fw_Stream_Write(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    _FW_ASSERT(IS_PTR_NULL(stream->Interface));
    _FW_ASSERT(IS_PTR_NULL(stream->Pool));
    _FW_ASSERT(IS_PTR_NULL(buffer));
    _FW_ASSERT(IS_PARAM_ZERO(size));
    
    if(stream->Tx.IsReady == true && !IS_PTR_NULL(stream->Interface->Write))
    {
        return stream->Interface->Write(stream->Pool, buffer, size);
    }
        
    return 0;
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
__INLINE uint16_t Fw_Stream_Read(struct Fw_Stream *stream, uint8_t *buffer, uint8_t size)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    _FW_ASSERT(IS_PTR_NULL(stream->Interface));
    _FW_ASSERT(IS_PTR_NULL(stream->Pool));
    _FW_ASSERT(IS_PTR_NULL(buffer));
    _FW_ASSERT(IS_PARAM_ZERO(size));
    
    if(stream->Rx.IsReady == true && !IS_PTR_NULL(stream->Interface->Read))
    {
        return stream->Interface->Read(stream->Pool, buffer, size);
    }
        
    return 0;
}

#endif

/** @}*/     /** framework stream component */

/**********************************END OF FILE*********************************/
