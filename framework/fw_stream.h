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
#include "fw_path.h"
#include "fw_buffer.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
struct Fw_Stream;

/**
 *******************************************************************************
 * @brief       stream hardware opera function
 *******************************************************************************
 */
struct _FwStreamBufferOpera
{
    fw_err_t (*Init)(struct Fw_Stream*, void *);
    fw_err_t (*Fini)(struct Fw_Stream*);
    
    fw_err_t (*Write)(struct Fw_Stream*, uint8_t*, uint8_t);
    fw_err_t (*Read)(struct Fw_Stream*, uint8_t*, uint8_t);
    
//    uint32_t (*GetFreeSize)(struct Fw_Stream*);
//    uint32_t (*GetUseSize)(struct Fw_Stream*);
};

/**
 *******************************************************************************
 * @brief       stream hardware device function
 *******************************************************************************
 */
struct _FwStreamDeviceOpera
{
    void (*Init)(struct Fw_Stream*);
    void (*Fini)(struct Fw_Stream*);
    
    void (*Tx_Out)(struct Fw_Stream*);
    void (*Tx_Connect)(struct Fw_Stream*);
    void (*Tx_Disconnect)(struct Fw_Stream*);
    
    void (*Rx_In)(struct Fw_Stream*);
    void (*Rx_Connect)(struct Fw_Stream*);
    void (*Rx_Disconnect)(struct Fw_Stream*);
};

/**
 *******************************************************************************
 * @brief       stream hardware call back function
 *******************************************************************************
 */
struct Fw_Stream
{
    struct _FwStreamBufferOpera *Opera;
    struct _FwStreamDeviceOpera Device;

    bool IsTxReady;
    bool IsRxReady;
};

/**
 *******************************************************************************
 * @brief       define framework fifo stream
 *******************************************************************************
 */
struct FwFifoStream
{
    struct Fw_Stream stream;
    
    Fw_Fifo_t Fifo;
};

/**
 *******************************************************************************
 * @brief       define stream init block type
 *******************************************************************************
 */
typedef struct _FwStreamBufferOpera _StreamBufferOperaInitType;
typedef struct _FwStreamDeviceOpera _StreamDeviceOperaInitType;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define framework stream api
 *******************************************************************************
 */
extern fw_err_t Fw_Stream_Init(struct Fw_Stream *stream, 
                               _StreamBufferOperaInitType*, 
                               _StreamDeviceOperaInitType*,
                               void*);

extern fw_err_t Fw_Stream_Fini(struct Fw_Stream*);

extern fw_err_t Fw_Stream_TxConnect(struct Fw_Stream*);
extern fw_err_t Fw_Stream_TxDisconnect(struct Fw_Stream*);
extern fw_err_t Fw_Stream_RxConnect(struct Fw_Stream*);
extern fw_err_t Fw_Stream_RxDisconnect(struct Fw_Stream*);

extern fw_err_t Fw_Stream_Write(struct Fw_Stream*, uint8_t*, uint8_t);
extern fw_err_t Fw_Stream_Read(struct Fw_Stream*, uint8_t*, uint8_t);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework stream component */

/**********************************END OF FILE*********************************/
