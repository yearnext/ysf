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
 * @file       fw_pipe.c                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-31                                                      *
 * @brief      framework pipe component source files                           *
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

/* Includes ------------------------------------------------------------------*/
#include "fw_pipe.h"
#include "fw_debug.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
#if USE_PIPE_COMPONENT
/**
 *******************************************************************************
 * @brief       pipe cache fifo type option
 *******************************************************************************
 */
static void _Fifo_Init(struct Fw_Pipe*);
static void _Fifo_Fini(struct Fw_Pipe*);
static uint16_t _Fifo_Write(struct Fw_Pipe*, uint8_t*, uint16_t);
static uint16_t _Fifo_Read(struct Fw_Pipe*, uint8_t*, uint16_t);

const struct Fw_Pipe_Pool_Interface PipeFifoInterface = 
{
    .Init = _Fifo_Init,
    .Fini = _Fifo_Fini,
    .Write = _Fifo_Write,
    .Read = _Fifo_Read,
};
#endif

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_PIPE_COMPONENT
/**
 *******************************************************************************
 * @brief       init pipe framework
 * @param       [in/out]  *pipe           pipe block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Pipe_Init(Fw_Pipe_t *pipe)
{
    //< detect stream param
    _FW_ASSERT(IS_PTR_NULL(pipe));
    
    //< init buffer
    if(!IS_PTR_NULL(pipe->Interface->Init))
    {
        pipe->Interface->Init(pipe);
    }
    
    //< init pipe timer
    Fw_Timer_Init(&pipe->Timer, "Framework Pipe Timer");
    
    //< clear pipe flags
    pipe->IsLock = false;
    pipe->IsConnect = false;
}

/**
 *******************************************************************************
 * @brief       deinit pipe framework
 * @param       [in/out]  *pipe           pipe block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Pipe_Fini(Fw_Pipe_t *pipe)
{
    _FW_ASSERT(IS_PTR_NULL(pipe));

    //< deinit stream buffer
    if(!IS_PTR_NULL(pipe->Interface->Fini))
    {
        pipe->Interface->Fini(pipe);
    }
    
    //< clear pipe falgs
    pipe->IsLock = false;
    pipe->IsConnect = false;
}

/**
 *******************************************************************************
 * @brief       lock pipe
 * @param       [in/out]  *pipe           pipe block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE void Fw_Pipe_Lock(Fw_Pipe_t *pipe)
{
    pipe->IsLock = true;
}

/**
 *******************************************************************************
 * @brief       unlock pipe
 * @param       [in/out]  *pipe           pipe block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE void Fw_Pipe_Unlock(Fw_Pipe_t *pipe)
{
    pipe->IsLock = false;
}

/**
 *******************************************************************************
 * @brief       connect pipe
 * @param       [in/out]  *pipe           pipe block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Pipe_Connect(Fw_Pipe_t *pipe)
{
    _FW_ASSERT(IS_PTR_NULL(pipe));

    //< 1. check pipe is lock 
    if(pipe->IsLock == true)
    {
        return;
    }
    
    //< 2. lock pipe
    Fw_Pipe_Lock(pipe);
    
    //< 3. connect pipe
    if(pipe->IsConnect == false)
    {
        pipe->IsConnect = true;
    }
    
   //< 4. unlock pipe
    Fw_Pipe_Unlock(pipe);
}

/**
 *******************************************************************************
 * @brief       disconnect pipe
 * @param       [in/out]  *pipe           pipe block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Pipe_Disconnect(Fw_Pipe_t *pipe)
{
    _FW_ASSERT(IS_PTR_NULL(pipe));

    //< 1. check pipe is lock 
    if(pipe->IsLock == true)
    {
        return;
    }
    
    //< 2. lock pipe
    Fw_Pipe_Lock(pipe);
    
    //< 3. disconnect pipe
    if(pipe->IsConnect == true)
    {
        pipe->IsConnect = false;
    }
    
    //< 4. unlock pipe
    Fw_Pipe_Unlock(pipe);
}

/**
 *******************************************************************************
 * @brief       lock framework pipe device active
 * @param       [in/out]  *pipe           pipe block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Pipe_LockDevice(Fw_Pipe_t *pipe)
{
    _FW_ASSERT(IS_PTR_NULL(pipe));
    
    pipe->DeviceLock = true;
}

/**
 *******************************************************************************
 * @brief       unlock framework pipe device active
 * @param       [in/out]  *pipe           pipe block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Pipe_UnlockDevice(Fw_Pipe_t *pipe)
{
    _FW_ASSERT(IS_PTR_NULL(pipe));

    pipe->DeviceLock = false;
}

/**
 *******************************************************************************
 * @brief       get framework pipe device lock status
 * @param       [in/out]  *pipe           pipe block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE bool Fw_Pipe_GetDeviceLock(Fw_Pipe_t *pipe)
{
    _FW_ASSERT(IS_PTR_NULL(pipe));

    return pipe->DeviceLock;
}

/**
 *******************************************************************************
 * @brief       set time out tick
 * @param       [in/out]  *pipe           pipe block
 * @param       [in/out]  tick            set time out tick
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Pipe_SetTimeOut(Fw_Pipe_t *pipe, uint16_t tick)
{
    _FW_ASSERT(IS_PTR_NULL(pipe));

    //< 1. check pipe is lock
    if(pipe->IsLock == true)
    {
        return;
    }
    
    //< 2. lock pipe
    Fw_Pipe_Lock(pipe);
    
    //< 3. set time out tick
    pipe->TimeOutTick = tick;
    
    //< 4. unlock pipe
    Fw_Pipe_Unlock(pipe);
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
__INLINE uint16_t Fw_Pipe_Write(Fw_Pipe_t *pipe, uint8_t *buffer, uint16_t size)
{
    _FW_ASSERT(IS_PTR_NULL(pipe));
    _FW_ASSERT(IS_PTR_NULL(pipe->Interface));
    _FW_ASSERT(IS_PTR_NULL(pipe->Pool));
    _FW_ASSERT(IS_PTR_NULL(buffer));
    _FW_ASSERT(IS_PARAM_ZERO(size));
    
    uint16_t wrSize = 0;
    
    //< 1. check pipe is lock
    if(pipe->IsLock == true)
    {
        return 0;
    }
    
    //< 2. check pipe is connect device
    if(pipe->IsConnect == false)
    {
        return 0;
    }
    
    //< 3. lock pipe
    Fw_Pipe_Lock(pipe);
    
    //< 4. read data from pipe cache
    if(!IS_PTR_NULL(pipe->Interface->Write))
    {
        wrSize = pipe->Interface->Write(pipe, buffer, size);        
    }
    
    //< 5. unlock pipe
    Fw_Pipe_Unlock(pipe);
    
    //< 6. start transfer
    if(!IS_PTR_NULL(pipe->InOut))
    {
        pipe->InOut(FW_STREAM_TX_EVENT, pipe->Stream);
    }

    return wrSize;
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
__INLINE uint16_t Fw_Pipe_Read(Fw_Pipe_t *pipe, uint8_t *buffer, uint16_t size)
{
    _FW_ASSERT(IS_PTR_NULL(pipe));
    _FW_ASSERT(IS_PTR_NULL(pipe->Interface));
    _FW_ASSERT(IS_PTR_NULL(pipe->Pool));
    _FW_ASSERT(IS_PTR_NULL(buffer));
    _FW_ASSERT(IS_PARAM_ZERO(size));
    
    uint16_t rdSize = 0;

    //< 1. check pipe is lock
    if(pipe->IsLock == true)
    {
        return 0;
    }
    
    //< 2. check pipe is connect device
    if(pipe->IsConnect == false)
    {
        return 0;
    }
    
    //< 3. lock pipe
    Fw_Pipe_Lock(pipe);
    
    //< 4. read data from pipe cache
    if(!IS_PTR_NULL(pipe->Interface->Read))
    {
        rdSize = pipe->Interface->Read(pipe, buffer, size);
    }
        
    //< 5. unlock pipe
    Fw_Pipe_Unlock(pipe);
    
    return rdSize;
}

/**
 *******************************************************************************
 * @brief       init fifo stream buffer
 * @param       [in/out]  *pipe              pipe block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
static void _Fifo_Init(struct Fw_Pipe *pipe)
{
    _FW_ASSERT(IS_PTR_NULL(pipe));

    Fw_Fifo_t *fifo = (Fw_Fifo_t *)pipe->Pool;
    
    Fw_Buffer_Init(fifo, fifo->Buffer, fifo->Size);
}

/**
 *******************************************************************************
 * @brief       deinit fifo stream buffer 
 * @param       [in/out]  *pipe              pipe block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
static void _Fifo_Fini(struct Fw_Pipe *pipe)
{
    _FW_ASSERT(IS_PTR_NULL(pipe));
    
    Fw_Buffer_Fini((struct Fw_RingBuffer *)pipe->Pool);
}

/**
 *******************************************************************************
 * @brief       write data to stream
 * @param       [in/out]  *pipe              pipe block
 * @param       [in/out]  *buff              read data buffer
 * @param       [in/out]  size               read data size
 * @return      [in/out]  readSize           read data num
 * @note        None
 *******************************************************************************
 */
static uint16_t _Fifo_Write(struct Fw_Pipe *pipe, uint8_t *buffer, uint16_t size)
{
    _FW_ASSERT(IS_PTR_NULL(pipe));
    
    return Fw_Buffer_Write((struct Fw_RingBuffer *)pipe->Pool, buffer, size);
}

/**
 *******************************************************************************
 * @brief       read data from stream
 * @param       [in/out]  *pipe              pipe block
 * @param       [in/out]  *buff              read data buffer
 * @param       [in/out]  size               read data size
 * @return      [in/out]  readSize           read data num
 * @note        None
 *******************************************************************************
 */
static uint16_t _Fifo_Read(struct Fw_Pipe *pipe, uint8_t *buffer, uint16_t size)
{
    _FW_ASSERT(IS_PTR_NULL(pipe));
    
    return Fw_Buffer_Read((struct Fw_RingBuffer *)pipe->Pool, buffer, size);
}

#endif

/** @}*/     /** framework pipe component */

/**********************************END OF FILE*********************************/
