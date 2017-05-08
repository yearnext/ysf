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
 * @file       fw_signal.c                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-15                                                      *
 * @brief      signal component source files                                   *
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
 * @defgroup signal component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_SIGNAL_COMPONENT_PATH
#include _FW_TIMER_COMPONENT_PATH
#include _FW_TASK_COMPONENT_PATH
#include _FW_LINK_LIST_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      detect signal status
 *******************************************************************************
 */
#define IS_SIGNAL_INFO_CHANGED(signal, nowInfo)    ((signal)->Info != (nowInfo))

/**
 *******************************************************************************
 * @brief      detect signal use status
 *******************************************************************************
 */
#define IS_SIGNAL_ENABLE(signal)  ((signal) != NULL && (signal)->Detect != NULL)
#define IS_SIGNAL_DISABLE(signal) ((signal) != NULL && (signal)->Detect == NULL)

#define SIGNAL_DISABLE(signal)                         ((signal)->Detect = NULL)
/**
 *******************************************************************************
 * @brief      update signal status
 *******************************************************************************
 */
#define TRANSFER_SIGNAL_STATUS(signal, status)     ((signal)->Status = (status))
#define UPDATE_SIGNAL_INFO(signal, info)           ((signal)->Info = (info))   

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/   
/**
 *******************************************************************************
 * @brief       signal component head point
 *******************************************************************************
 */
#if USE_SIGNAL_COMPONENT
/**
 *******************************************************************************
 * @brief       ysf signal control block
 *******************************************************************************
 */
static CREATE_SINGLE_LIST_FIFO_CONTROL_BLOCK(struct SignalBlock, SignalControlBlock);

/**
 *******************************************************************************
 * @brief       signal timer
 *******************************************************************************
 */
static struct TimerBlock SignalTimer;

struct
{
    struct SignalBlock *Head;
    
    uint8_t Flag;
    uint8_t Count;
}static SignalPollBlock;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_SIGNAL_COMPONENT
/**
 *******************************************************************************
 * @brief       detect the signal is in queue
 * @param       [in/out]  signal               will detect signal
 * @return      [in/out]  true                 the signal in the queue
 * @return      [in/out]  true                 the signal not in the queue
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
bool signal_is_in(struct SignalBlock *signal)
{
    IsInSingleLinkListFifo(struct SignalBlock, SignalControlBlock, signal);
    
    return false;
}

/**
 *******************************************************************************
 * @brief       pop signal to queue
 * @param       [in/out]  signal              will signal task
 * @return      [in/out]  FW_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
fw_err_t signal_push(struct SignalBlock *signal)
{
    PushSingleLinkListFifoNode(signal_is_in, SignalControlBlock, signal);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       push signal from queue
 * @param       [in/out]  void
 * @return      [in/out]  struct SignalBlock *     push timer addr in memory
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
struct SignalBlock *signal_pop(void)
{
    struct SignalBlock *signal = NULL;
    
    PopSingleLinkListFifoNode(SignalControlBlock, signal);
    
    return signal;
}

/**
 *******************************************************************************
 * @brief       signal queue clear
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
fw_err_t signal_clear(void)
{    
    while(signal_pop() != NULL);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal trigger handler
 * @param       [in/out]  *signal             signal block
 * @return      [in/out]  FW_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
fw_err_t signal_trigger_handler(struct SignalBlock *signal)
{
//    fw_assert(IS_PTR_NULL(signal));
    ArmTaskModule(&signal->Task);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal status judge
 * @param       [in/out]  *param              signal block
 * @return      [in/out]  FW_ERR_FAIL         judge failed
 * @return      [in/out]  FW_ERR_NONE         judge success
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
fw_err_t signal_judge(struct SignalBlock *signal)
{
//    fw_assert(IS_PTR_NULL(signal));
//    fw_assert(IS_PTR_NULL(signal->Detect));
    
    uint8_t nowInfo = signal->Detect();
    
    switch(signal->Status)
    {
        case SIGNAL_STATUS_INIT:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP1:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP2);
                }
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP2:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP3);
                }
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP3:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_EDGE);
                    signal_trigger_handler(signal);
                }
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP1:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP2);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP2:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP3);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP3:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_EDGE);
                    signal_trigger_handler(signal);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_RELEASE_EDGE:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE);
                    signal_trigger_handler(signal);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_RELEASE:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE);
                    signal_trigger_handler(signal);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            break;
        case SIGNAL_STATUS_PRESS_EDGE:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS);
                    signal_trigger_handler(signal);
                }
            }
            break;
        case SIGNAL_STATUS_PRESS:
            if(IS_SIGNAL_INFO_CHANGED(signal, nowInfo))
            {
                UPDATE_SIGNAL_INFO(signal, nowInfo);
                
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
                }
            }
            else
            {
                if(IS_NO_SIGNAL(nowInfo))
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
                }
                else
                {
                    TRANSFER_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS);
                    signal_trigger_handler(signal);
                }
            }
            break;
        default:
            break;
    }

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal walk
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE 
void signal_walk(void)
{
    struct SignalBlock *now = NULL;
    
    // init poll process
    if(SignalPollBlock.Flag == 0)
    {
        SignalPollBlock.Head = GetSingleLinkListHead(SignalControlBlock);
        SignalPollBlock.Flag = 1;
    }
    else
    {
        // check poll is finish
        if(IsSingleLinkListHead(SignalControlBlock, SignalPollBlock.Head))
        {
            if(!--SignalPollBlock.Count)
            {
                // exit poll
                SignalPollBlock.Flag = 0;
                SignalPollBlock.Head = NULL;
                
                return;
            }
        }
    }
    
    // get now signal module
    now = signal_pop();
    
    if(SignalPollBlock.Flag)
    {
        // check now signal is enable
        if(IS_SIGNAL_ENABLE(now))
        {
            signal_judge(now);
            signal_push(now); 
        }

        CreateEventHandleTask(NULL, PoolSignalComponent, FW_EVENT_NONE);
    }
}

/**
 *******************************************************************************
 * @brief       signal component init
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE       init finish
 * @note        None
 *******************************************************************************
 */
fw_err_t InitSignalComponent(void)
{
    signal_clear();
    
    SignalPollBlock.Head  = NULL;
    SignalPollBlock.Count = 0;
    SignalPollBlock.Flag  = 0;
    
    InitEventHandleTimerModule(&SignalTimer, PoolSignalComponent, FW_EVENT_DELAY);
    ArmTimerModule(&SignalTimer, SIGNAL_SCAN_TIME, TIMER_CYCLE_MODE);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal component deinit
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE       deinit finish
 * @note        None
 *******************************************************************************
 */
fw_err_t DeinitSignalComponent(void)
{
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal component init
 * @param       [in/out]  *signal           signal block
 * @param       [in/out]  *detect           signal detect function
 * @param       [in/out]  *handler          signal handler function
 * @return      [in/out]  FW_ERR_NONE       arm success
 * @return      [in/out]  FW_ERR_FAIL       arm failed
 * @note        None
 *******************************************************************************
 */
fw_err_t ArmSignalModule(struct SignalBlock *signal, uint8_t (*detect)(void), fw_err_t (*handler)(uint16_t))
{
    fw_assert(IS_PTR_NULL(signal));
    fw_assert(IS_PTR_NULL(detect));
    fw_assert(IS_PTR_NULL(handler));
    
    signal->Detect = detect;
    InitEventHandleTask(&signal->Task, handler, FW_EVENT_NONE);

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal disarm
 * @param       [in/out]  *signal           signal block
 * @return      [in/out]  FW_ERR_NONE       disarm success
 * @note        None
 *******************************************************************************
 */
fw_err_t DisarmSignalModule(struct SignalBlock *signal)
{
    fw_assert(IS_PTR_NULL(signal));
    
    SIGNAL_DISABLE(signal);

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal component pool
 * @param       [in/out]  event                event
 * @return      [in/out]  FW_ERR_NONE          pool not error
 * @note        None
 *******************************************************************************
 */
fw_err_t PoolSignalComponent(uint16_t event)
{
    if( IsSingleLinkListHeadEmpty(SignalControlBlock) )
    {
        return FW_ERR_NONE;
    }
    
    if(event == FW_EVENT_DELAY)
    {
        SignalPollBlock.Count++;
    }
    
    if(SignalPollBlock.Count)
    {
        signal_walk();
    }
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get signal info
 * @param       [in/out]  *signal           signal block
 * @return      [in/out]  FW_ERR_NONE       get success
 * @note        None
 *******************************************************************************
 */
inline uint8_t GetSignalModuleInfo(struct SignalBlock *signal)
{
    uint8_t info;
    
    if(IS_PTR_NULL(signal))
    {
        return 0;
    }
        
    info = signal->Info;

    return info;
}

#endif

/** @}*/     /** signal component */

/**********************************END OF FILE*********************************/
