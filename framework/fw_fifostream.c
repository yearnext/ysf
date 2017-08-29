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
 * @brief       init fifo stream hardware
 * @param       [in/out]  *stream         fifo stream block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_FifoStream_Init(Fw_FifoStream_t *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
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
void Fw_FifoStream_ConnectTx(Fw_FifoStream_t *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));

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
void Fw_FifoStream_DisconnectTx(Fw_FifoStream_t *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
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
void Fw_FifoStream_ConnectRx(Fw_FifoStream_t *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));

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
void Fw_FifoStream_DisconnectRx(Fw_FifoStream_t *stream)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    Hal_Device_Control(&stream->Device, HAL_DISCONNECT_RX_CMD);
}

__INLINE
void Fw_FifoStream_SetTimeOutTick(Fw_FifoStream_t *stream, uint32_t tick)
{
    _FW_ASSERT(IS_PTR_NULL(stream));
    
    stream->TimeOutTick = tick;
}

/** @} */     /** hal fifo stream component */

/**********************************END OF FILE*********************************/
