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
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_STREAM_COMPONENT
#define USE_STREAM_COMPONENT                                                 (1)

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
#define USE_STREAM_COMPONENT                                                 (1)
#endif
   
/**
 *******************************************************************************
 * @brief       define stream block size
 *******************************************************************************
 */
#define BLOCK_STREAM_BUFFER_SIZE                                           (128)

/* Exported types ------------------------------------------------------------*/
struct Fw_Stream;

/**
 *******************************************************************************
 * @brief       stream buffer opera function
 *******************************************************************************
 */
struct Fw_Stream_Buffer_Opera
{
    void (*Init)(void*);
    void (*Fini)(void*);

    fw_err_t (*Write)(void*, uint8_t*, uint8_t);
    fw_err_t (*Read)(void*, uint8_t*, uint8_t);
};

///**
// *******************************************************************************
// * @brief       stream hardware opera function
// *******************************************************************************
// */
//struct Fw_Stream_Device_Opera
//{
////    void (*Init)(struct Fw_Stream*, void*);
////    void (*Fini)(struct Fw_Stream*);
//    void (*Callback)(uint8_t, void*); 
//};

/**
 *******************************************************************************
 * @brief       define stream comm pipe
 *******************************************************************************
 */
struct Fw_Stream_Pipe
{
    //< pipe function param
	void *Param;
	
	void (*InOut)(void*);
    void (*Connect)(void*);
    void (*Disconnect)(void*);

    //< pipe ready flag
	bool IsReady;
};

/**
 *******************************************************************************
 * @brief       stream hardware call back function
 *******************************************************************************
 */
struct Fw_Stream
{
    void *Buffer;
    struct Fw_Stream_Buffer_Opera *Buf_Ops;
    void (*Callback)(uint8_t, void*);

	struct Fw_Stream_Pipe Tx;
	struct Fw_Stream_Pipe Rx;
};

//typedef struct 
//{
//    void *Buffer;
//    struct Fw_Stream_Buffer_Opera *Buf_Ops;
//    void (*Callback)(uint8_t, void*);
//
//    struct Fw_Stream_Pipe Tx;
//    struct Fw_Stream_Pipe Rx;
//}Fw_Stream_InitType;

//
///**
// *******************************************************************************
// * @brief       define framework fifo stream
// *******************************************************************************
// */
//struct Fw_FifoStream
//{
//    struct Fw_Stream Stream;
//    
//    Fw_Fifo_t Fifo;
//};
//
///**
// *******************************************************************************
// * @brief       define framework fifo stream
// *******************************************************************************
// */
//struct Fw_BlockStreamBuffer
//{
//	struct
//	{
//		struct Fw_BlockStreamBuffer *Next;
//	}LinkList;
//
//	struct Fw_Queue Queue;
//};
//
//struct Fw_BlockStream
//{
//    struct Fw_Stream Stream;
//    
//    struct
//    {
//        struct Fw_BlockStreamBuffer *Head;
//        struct Fw_BlockStreamBuffer *Tail;
//    }LinkList;
//};

/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define stream opera
 *******************************************************************************
 */
#if USE_STREAM_COMPONENT
extern const struct Fw_Stream_Buffer_Opera FwStreamFifoOpera;
//extern const struct Fw_Stream_Buffer_Opera FwStreamBlockOpera;
#endif

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define framework stream api
 *******************************************************************************
 */
#if USE_STREAM_COMPONENT
extern void Fw_Stream_InitComponent(void);
extern void Fw_Stream_PostEvent(struct Fw_Stream*, uint8_t);

extern __INLINE void Fw_Stream_Init(struct Fw_Stream*);
extern __INLINE void Fw_Stream_Fini(struct Fw_Stream*);
extern __INLINE void Fw_Stream_TxConnect(struct Fw_Stream*);
extern __INLINE void Fw_Stream_TxDisconnect(struct Fw_Stream*);
extern __INLINE void Fw_Stream_RxConnect(struct Fw_Stream*);
extern __INLINE void Fw_Stream_RxDisconnect(struct Fw_Stream*);
extern __INLINE fw_err_t Fw_Stream_Write(struct Fw_Stream*, uint8_t*, uint8_t);
extern __INLINE fw_err_t Fw_Stream_Read(struct Fw_Stream*, uint8_t*, uint8_t);

#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework stream component */

/**********************************END OF FILE*********************************/
