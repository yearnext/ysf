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
 * @file       fw_fifostream.h                                                 *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-08                                                      *
 * @brief      framework fifo stream component head files                      *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_FIFO_STREAM_H__
#define __FRAMEWORK_FIFO_STREAM_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_stream.h"
#include "fw_timer.h"
#include "hal_device.h"
    
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define framework uart stream
 *******************************************************************************
 */
typedef struct Fw_FifoStream
{
	Hal_Device_t Device;
	
    struct Fw_Stream Tx;
    struct Fw_Stream Rx;
     
    struct Fw_Timer Timer;

    enum
    {
        FIFO_STREAM_INIT_STATE,
        FIFO_STREAM_SEND_STATE,
        FIFO_STREAM_SLEEP_STATE,
        FIFO_STREAM_COMPLET_STATE,
    }State;
}Fw_FifoStream_t;
      
/* Exported constants --------------------------------------------------------*/
///**
// *******************************************************************************
// * @brief       define framework stream opera
// *******************************************************************************
// */
//extern const struct _FwStreamDeviceOpera UartStreamDeviceOpera;

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework uart stream apis
 *******************************************************************************
 */
extern __INLINE void Fw_FifoStream_Init(Fw_FifoStream_t*);
extern __INLINE void Fw_FifoStream_Fini(Fw_FifoStream_t*);
extern __INLINE void Fw_FifoStream_ConnectTx(void*);
extern __INLINE void Fw_FifoStream_DisconnectTx(void*);
extern __INLINE void Fw_FifoStream_ConnectRx(void*);
extern __INLINE void Fw_FifoStream_DisconnectRx(void*);
extern __INLINE void Fw_FifoStream_TxOut(void*);
extern __INLINE void Fw_FifoStream_RxIn(void*);
extern __INLINE void Fw_FifoStream_Send(void*);
extern __INLINE void Fw_FifoStream_Receive(void*, uint8_t);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
