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
 * @file       fw_stream.c                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-07-30                                                      *
 * @brief      framework stream component source files                         *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                  						                           *
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
#include "hal_device.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_STREAM_COMPONENT
/**
 *******************************************************************************
 * @brief       init stream
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
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    //< init pipe
    stream->Tx.InOut = Fw_Stream_Tx_Handle;
    stream->Tx.Stream = (void *)stream;
    Fw_Pipe_Init(&stream->Tx);
    Fw_Pipe_Connect(&stream->Tx);
    
    stream->Rx.In = NULL;
    Fw_Pipe_Init(&stream->Rx);
    Fw_Pipe_Connect(&stream->Rx);
    
    //< init hardware
    if(!IS_PTR_NULL(stream->Device))
    {
        Hal_Device_Init(stream->Device);
    }
}

/**
 *******************************************************************************
 * @brief       deinit stream
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
    Fw_Pipe_Disconnect(&stream->Tx);
    Fw_Pipe_Fini(&stream->Tx);
    
    Fw_Pipe_Disconnect(&stream->Rx);
    Fw_Pipe_Fini(&stream->Rx);
}

/**
 *******************************************************************************
 * @brief       connect pipe
 * @param       [in/out]  *pipe           pipe block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Stream_Connect(Fw_Pipe_t *pipe)
{
    Fw_Pipe_Connect(pipe);
}

/**
 *******************************************************************************
 * @brief       disconnect pipe
 * @param       [in/out]  *pipe           pipe block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Stream_Disconnect(Fw_Pipe_t *pipe)
{
    Fw_Pipe_Disconnect(pipe);
}

/**
 *******************************************************************************
 * @brief       write data to pipe cache
 * @param       [in/out]  *pipe          pipe block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  uint16_t       result num
 * @note        None
 *******************************************************************************
 */
__INLINE uint16_t Fw_Stream_Write(Fw_Pipe_t *pipe, uint8_t *buf, uint16_t size)
{
    return Fw_Pipe_Write(pipe, buf, size);
}

/**
 *******************************************************************************
 * @brief       read data from pipe cache
 * @param       [in/out]  *stream        pipe block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  uint16_t       result num
 * @note        None
 *******************************************************************************
 */
__INLINE uint16_t Fw_Stream_Read(Fw_Pipe_t *pipe, uint8_t *buf, uint16_t size)
{
    return Fw_Pipe_Read(pipe, buf, size);
}

/**
 *******************************************************************************
 * @brief       stream send option
 * @param       [in/out]  *stream        stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void Stream_Send(struct Fw_Stream *stream)
{
    void Fw_Stream_Tx_Handle(uint8_t event, void *param);
    uint8_t txData = 0;
    
    //< get tx buffer data
    if (Fw_Pipe_Read(&stream->Tx, &txData, 1) != 1)
    {
        //< unlock device
        Fw_Pipe_UnlockDevice(&stream->Tx);
        
        //< disable pipe timer
        Fw_Timer_Stop(&stream->Tx.Timer);
        
        //< post transfer complet event
        Fw_Task_PostMessage(stream->Tx.Param, FW_TRANSFER_COMPLET_EVENT, (void *)stream);
        return;
    }
    
    __ATOM_ACTIVE_BEGIN();
    
    //< start send data
    Hal_Device_Control(stream->Device, HAL_SEND_BYTE_CMD, txData);
    
    //< set tx time out
    Fw_Timer_SetEventHandle(&stream->Tx.Timer, Fw_Stream_Tx_Handle, (void *)stream, FW_TIMEOUT_EVENT);
    Fw_Timer_ForceStart(&stream->Tx.Timer, stream->Tx.TimeOutTick, 1);
    
    //< lock device
    Fw_Pipe_LockDevice(&stream->Tx);
    
    __ATOM_ACTIVE_END();
}

/**
 *******************************************************************************
 * @brief       stream tx handle
 * @param       [in/out]  event          trigger handle
 * @param       [in/out]  *param         handle param
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Stream_Tx_Handle(uint8_t event, void *param)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    struct Fw_Stream *stream = (struct Fw_Stream *)param;
    
    switch(event)
    {
        case FW_DEVICE_TX_EVENT:
        {
            Stream_Send(stream);
            break;
        }
        case FW_STREAM_TX_EVENT:
        {
            if(Fw_Pipe_GetDeviceLock(&stream->Tx) == false)
            {
                Stream_Send(stream);
            }
            break;
        }
        case FW_TIMEOUT_EVENT:
        {
            if(!IS_PTR_NULL(stream->Tx.Param))
            {
                Fw_Task_PostMessage(stream->Tx.Param, FW_TRANSFER_TX_TIMEOUT_EVENT, (void *)stream);
            }
            
            Stream_Send(stream);
            break;
        }
        default:
            break;
    }
}

/**
 *******************************************************************************
 * @brief       stream receive timeout handle
 * @param       [in/out]  *param        timeout handle
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
static void Stream_Receive_Timeout_Handle(void *param)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    struct Fw_Stream *stream = (struct Fw_Stream *)param;
    
    //< unlock device
    Fw_Pipe_UnlockDevice(&stream->Rx);
    
    //< disable pipe timer
    Fw_Timer_Stop(&stream->Rx.Timer);
    
    //< set stream rx timeout event
    Fw_Task_PostMessage(stream->Rx.Param, FW_TRANSFER_RX_TIMEOUT_EVENT, (void *)stream);
}

/**
 *******************************************************************************
 * @brief       stream receive
 * @param       [in/out]  *stream        stream block
 * @param       [in/out]  rxData         receive data
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void Stream_Receive(struct Fw_Stream *stream, uint8_t rxData)
{
    //< get tx buffer data
    if (Fw_Pipe_Write(&stream->Rx, &rxData, 1) != 1)
    {
        //< unlock device
        Fw_Pipe_UnlockDevice(&stream->Rx);
        
        //< disable pipe timer
        Fw_Timer_Stop(&stream->Rx.Timer);
        return;
    }
    
    //< set tx time out
    Fw_Timer_SetCallback(&stream->Rx.Timer, Stream_Receive_Timeout_Handle, (void *)stream);
    Fw_Timer_ForceStart(&stream->Rx.Timer, stream->Rx.TimeOutTick, 1);
    
    //< lock device
    Fw_Pipe_LockDevice(&stream->Rx);
}

/**
 *******************************************************************************
 * @brief       stream rx handle
 * @param       [in/out]  event          trigger event
 * @param       [in/out]  *param         handle param
 * @param       [in/out]  recData        receive data
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Stream_Rx_Handle(uint8_t event, void *param, uint8_t recData)
{
    _FW_ASSERT(IS_PTR_NULL(param));
    
    struct Fw_Stream *stream = (struct Fw_Stream *)param;
    
    switch(event)
    {
        case FW_DEVICE_RX_EVENT:
        {
            //< packet receive handle
            Stream_Receive(stream, recData);
            
            //< post packet resolv event
            Fw_Task_PostMessage(stream->Rx.Param, FW_TRANSFER_PARSE_EVENT, (void *)stream);
            break;
        }
        case FW_STREAM_RX_EVENT:
        {
            break;
        }
        default:
            break;
    }
}

#endif

/** @}*/     /** framework stream component */

/**********************************END OF FILE*********************************/
