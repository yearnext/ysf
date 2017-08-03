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
#include "fw_core.h"
#include "fw_queue.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
struct Fw_Stream;

/**
 *******************************************************************************
 * @brief       stream memory opera function
 *******************************************************************************
 */
struct _FwStreamOpera
{
    fw_err_t (*Init)(struct Fw_Stream*, uint8_t*, uint8_t);
    fw_err_t (*Fini)(struct Fw_Stream*);
    
    fw_err_t (*GetUseSize)(struct Fw_Stream*, uint8_t*); 
    fw_err_t (*GetFreeSize)(struct Fw_Stream*, uint8_t*);

    fw_err_t (*Write)(struct Fw_Stream*, uint8_t*, uint8_t);
    fw_err_t (*Read)(struct Fw_Stream*, uint8_t*, uint8_t);
};

/**
 *******************************************************************************
 * @brief       stream hardware opera function
 *******************************************************************************
 */
struct _Fw_DeviceBlock
{
    void (*InOut)(struct Fw_Stream*);
    void (*Connect)(struct Fw_Stream*);
    void (*Disconnect)(struct Fw_Stream*);
};

/**
 *******************************************************************************
 * @brief       framework stream block
 *******************************************************************************
 */
struct Fw_Stream
{
    struct _FwStreamOpera *Opera;
    struct _Fw_DeviceBlock Device;
    
    bool IsReady;
    bool IsWorking;
    bool IsLock;
    bool IsOverFlow;
};

/**
 *******************************************************************************
 * @brief       define stream init block type
 *******************************************************************************
 */
struct Fw_FifoStream
{
    struct Fw_Stream Stream;
    Fw_Fifo_t Buffer;
};

/* Exported variables --------------------------------------------------------*/
extern const struct _FwStreamOpera FifoStreamOpera;

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define stream api
 *******************************************************************************
 */
extern fw_err_t Fw_Stream_Init(struct Fw_Stream*);
extern fw_err_t Fw_Stream_Fini(struct Fw_Stream*);

extern fw_err_t Fw_Stream_Connent(struct Fw_Stream*);
extern fw_err_t Fw_Stream_Disconnent(struct Fw_Stream*);

extern fw_err_t Fw_Stream_Read(struct Fw_Stream*, uint8_t*, uint8_t);
extern fw_err_t Fw_Stream_Write(struct Fw_Stream*, uint8_t*, uint8_t);

extern fw_err_t Fw_FifoStream_Init(struct Fw_Stream*, uint8_t*, uint8_t);
extern fw_err_t Fw_FifoStream_Fini(struct Fw_Stream*);
extern fw_err_t Fw_FifoStream_GetUseSize(struct Fw_Stream*, uint8_t*);
extern fw_err_t Fw_FifoStream_GetFreeSize(struct Fw_Stream*, uint8_t*);
extern fw_err_t Fw_FifoStream_Write(struct Fw_Stream*, uint8_t*, uint8_t);
extern fw_err_t Fw_FifoStream_Read(struct Fw_Stream*, uint8_t*, uint8_t);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework stream component */

/**********************************END OF FILE*********************************/
