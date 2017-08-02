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
 * @file       fw_stream.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-07-30
 * @brief      framework stream component head files
 * @par        paltform                                  
 *                 Windows
 * @par        compiler									                         
 * 				   GCC
 *******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 *******************************************************************************
 */

/**
 * @defgroup framework stream component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_STREAM_H__
#define __FRAMEWORK_STREAM_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include "fw_buffer.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
struct Fw_Stream;

/**
 *******************************************************************************
 * @brief       stream hardware opera function
 *******************************************************************************
 */
struct _FwStreamOpera
{
	fw_err_t (*Write)(Fw_Fifo_t *, uint8_t *, uint16_t);
	fw_err_t (*Read)(Fw_Fifo_t *, uint8_t *, uint16_t);
};

/**
 *******************************************************************************
 * @brief       stream hardware device function
 *******************************************************************************
 */
struct _FwStreamDevice
{
    fw_err_t (*Init)(struct Fw_Stream *);
	fw_err_t (*Fini)(struct Fw_Stream *);
};

/**
 *******************************************************************************
 * @brief       stream hardware call back function
 *******************************************************************************
 */
struct _FwStreamCallback
{
//    struct Fw_Stream *Stream;
	fw_err_t (*InOut)(struct Fw_Stream *);
	fw_err_t (*Connect)(struct Fw_Stream *);
	fw_err_t (*Disconnect)(struct Fw_Stream *);
};

/**
 *******************************************************************************
 * @brief       framework stream block
 *******************************************************************************
 */
struct Fw_Stream
{
    struct _FwStreamOpera *Opera;
    
	struct _FwStreamCallback TxCallback;
	struct _FwStreamCallback RxCallback;
    struct _FwStreamDevice   Device;
    
    Fw_Fifo_t TxFifo;
    Fw_Fifo_t RxFifo;
    
    bool IsTxReady;
    bool IsRxReady;
    
    uint8_t TxLock;
    uint8_t RxLock;
    
//    bool IsOverFlow;
};

/**
 *******************************************************************************
 * @brief       define stream init block type
 *******************************************************************************
 */
typedef struct _FwStreamCallback _StreamCallbackInitType;
typedef struct _FwStreamDevice _StreamDeviceInitType;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define stream api
 *******************************************************************************
 */
extern fw_err_t Fw_Stream_Init(struct Fw_Stream *, 
                               _StreamDeviceInitType *, 
                               _StreamCallbackInitType *, 
                               _StreamCallbackInitType *);

extern fw_err_t Fw_Stream_Enable(struct Fw_Stream *stream, 
                                 _QueueInitType *, 
                                 _QueueInitType *);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework stream component */

/**********************************END OF FILE*********************************/
