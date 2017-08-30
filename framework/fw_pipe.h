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
 * @file       fw_pipe.h                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-31                                                      *
 * @brief      framework pipe component head files                             *
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
 * @defgroup framework pipe component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_PIPE_H__
#define __FRAMEWORK_PIPE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_path.h"
#include "fw_buffer.h"
#include "fw_timer.h"
#include "fw_task.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_PIPE_COMPONENT
#define USE_PIPE_COMPONENT                                                   (1)

/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
#define USE_PIPE_COMPONENT                                                   (1)
#endif

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define pipe pool interface
 *******************************************************************************
 */
struct Fw_Pipe;
struct Fw_Pipe_Pool_Interface
{
    void (*Init)(struct Fw_Pipe*);
    void (*Fini)(struct Fw_Pipe*);
    uint16_t (*Write)(struct Fw_Pipe*, uint8_t*, uint16_t);
    uint16_t (*Read)(struct Fw_Pipe*, uint8_t*, uint16_t);
};

/**
 *******************************************************************************
 * @brief       define framework pipe type
 *******************************************************************************
 */
typedef struct Fw_Pipe
{
    //< pipe cache memory pool
    void *Pool;
    struct Fw_Pipe_Pool_Interface *Interface;
    
    //< pipe task call back
    struct Fw_Task *Param;
    
    //< pipe in out handle
    union
    {
        void (*Out)(uint8_t, void*);
        void (*In)(uint8_t, void*, uint8_t);
        void (*InOut)(uint8_t, void*);
    };
        
    void *Stream;
    
    //< pipe status
	bool IsConnect;
    bool IsLock;
    
    //< pipe timer
    uint16_t TimeOutTick;
    struct Fw_Timer Timer;

    bool DeviceLock;
}Fw_Pipe_t;

/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       pipe cache fifo type option
 *******************************************************************************
 */
#if USE_PIPE_COMPONENT
extern const struct Fw_Pipe_Pool_Interface PipeFifoInterface;
#endif

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define framework stream api
 *******************************************************************************
 */
#if USE_PIPE_COMPONENT
extern __INLINE void Fw_Pipe_Init(Fw_Pipe_t*);
extern __INLINE void Fw_Pipe_Fini(Fw_Pipe_t*);
extern __INLINE void Fw_Pipe_Connect(Fw_Pipe_t*);
extern __INLINE void Fw_Pipe_Disconnect(Fw_Pipe_t*);
extern __INLINE void Fw_Pipe_LockDevice(Fw_Pipe_t*);
extern __INLINE void Fw_Pipe_UnlockDevice(Fw_Pipe_t*);
extern __INLINE bool Fw_Pipe_GetDeviceLock(Fw_Pipe_t*);
extern __INLINE void Fw_Pipe_SetTimeOut(Fw_Pipe_t*, uint16_t);
extern __INLINE uint16_t Fw_Pipe_Write(Fw_Pipe_t*, uint8_t*, uint16_t);
extern __INLINE uint16_t Fw_Pipe_Read(Fw_Pipe_t*, uint8_t*, uint16_t);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework pipe component */

/**********************************END OF FILE*********************************/
