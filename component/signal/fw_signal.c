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
#include _FW_MEMORY_COMPONENT_PATH
#include _FW_EVENT_COMPONENT_PATH
#include _FW_LINK_LIST_COMPONENT_PATH
#include _FW_TASK_COMPONENT_PATH

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      detect signal status
 *******************************************************************************
 */
#define IS_SIGNAL_ENABLE(signal)             ((signal)->UseStatus == true)
#define IS_SIGNAL_DISABLE(signal)            ((signal)->UseStatus == false)
  
#define IS_SIGNAL_NEED_SCAN(signal)          ((signal)->HandleProgress == SIGNAL_STATUS_INIT)

/**
 *******************************************************************************
 * @brief      update signal status
 *******************************************************************************
 */
#define UPDATE_SIGNAL_STATUS(signal, status) ((signal)->Task.Event = (status))

/**
 *******************************************************************************
 * @brief      signal handle progress change function
 *******************************************************************************
 */
#define SIGNAL_HANDLE_INIT(signal)           ((signal)->HandleProgress = SIGNAL_STATUS_INIT)
#define SIGNAL_SCAN_PROGRESS_INIT(signal)    ((signal)->HandleProgress = SIGNAL_STATUS_DETECT)
#define SIGNAL_HANDLE_PROGRESS_INIT(signal)  ((signal)->HandleProgress = SIGNAL_STATUS_HANDLER)
    
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
    SingleLinkListFifoPush(signal_is_in, SignalControlBlock, signal);
    
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
    
    SingleLinkListFifoPop(SignalControlBlock, signal);
    
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
 * @brief       signal handler function
 * @param       [in/out]  *param              signal block
 * @param       [in/out]  event               signal event
 * @return      [in/out]  FW_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
static fw_err_t signal_handler(void *param, uint16_t event)
{
    struct SignalBlock *signal = (struct SignalBlock *)param;
    
    if( signal == NULL )
    {
        return FW_ERR_FAIL;
    }

    signal->Handler(event);
    
    SIGNAL_HANDLE_INIT(signal);
    
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
    if( signal == NULL )
    {
        return FW_ERR_FAIL;
    }
    
    SIGNAL_HANDLE_PROGRESS_INIT(signal);
    
    CreateMessageHandleTask(&signal->Task, signal_handler, (void *)signal, signal->Task.Event);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal status judge
 * @param       [in/out]  *param              signal block
 * @param       [in/out]  event               signal status event
 * @return      [in/out]  FW_ERR_FAIL         judge failed
 * @return      [in/out]  FW_ERR_NONE         judge success
 * @note        None
 *******************************************************************************
 */
static fw_err_t signal_judge(void *param, uint16_t event)
{
    struct SignalBlock *signal = (struct SignalBlock *)param;
    
    if( IS_PTR_NULL(signal) )
    {
        return FW_ERR_FAIL;
    }
    
    switch( signal->Task.Event )
    {
        case SIGNAL_STATUS_INIT:
            if( event == SIGNAL_STATUS_RELEASE )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP1:
            if( event == SIGNAL_STATUS_PRESS )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP2);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP2:
            if( event == SIGNAL_STATUS_PRESS )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP3);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP3:
            if( event == SIGNAL_STATUS_PRESS )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_EDGE);
                return signal_trigger_handler(signal);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP1:
            if( event == SIGNAL_STATUS_RELEASE )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP2);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP2:
            if( event == SIGNAL_STATUS_RELEASE )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP3);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP3:
            if( event == SIGNAL_STATUS_RELEASE )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_EDGE);
                return signal_trigger_handler(signal);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
            }
            break;
        case SIGNAL_STATUS_RELEASE_EDGE:
            if( event == SIGNAL_STATUS_RELEASE )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE);
                return signal_trigger_handler(signal);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
            }
            break;
        case SIGNAL_STATUS_RELEASE:
            if( event == SIGNAL_STATUS_RELEASE )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE);
                return signal_trigger_handler(signal);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
            }
            break;
        case SIGNAL_STATUS_PRESS_EDGE:
            if( event == SIGNAL_STATUS_PRESS )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS);
                return signal_trigger_handler(signal);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
            }
            break;
        case SIGNAL_STATUS_PRESS:
            if( event == SIGNAL_STATUS_PRESS )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS);
                return signal_trigger_handler(signal);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
            }
            break;
        default:
            break;
    }
    
    SIGNAL_HANDLE_INIT(signal);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal scan
 * @param       [in/out]  *param              signal block
 * @return      [in/out]  FW_ERR_FAIL         scan failed
 * @return      [in/out]  FW_ERR_NONE         scan success
 * @note        None
 *******************************************************************************
 */
static fw_err_t signal_scan(void *param)
{
    struct SignalBlock *signal = (struct SignalBlock *)param;
    uint16_t event = SIGNAL_STATUS_INIT;
    
    if( signal == NULL )
    {
        return FW_ERR_FAIL;
    }
    
    if(signal->Detect() == true)
    {
        event = SIGNAL_STATUS_PRESS;
    }
    else
    {
        event = SIGNAL_STATUS_RELEASE;
    }
    
    CreateMessageHandleTask(&signal->Task, signal_judge, signal, event);
    
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
    struct SignalBlock *now  = GetSingleLinkListHead(SignalControlBlock);
    struct SignalBlock *last = now;
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    struct SignalBlock *del  = NULL;
#endif
    
    while(1)
    {
        if( IS_SIGNAL_ENABLE(now) )
        {
            if( IS_SIGNAL_NEED_SCAN(now) )
            {
                SIGNAL_SCAN_PROGRESS_INIT(now);
                CreateCallBackTask(&now->Task, signal_scan, &now);
            }
            
            last = now;
            now  = now->Next;
        }
        else
        {   
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
            del = now;
#endif      
            if( IsSingleLinkListHead(SignalControlBlock, now) )
            {
                SingleLinkListHeadWrite(SignalControlBlock, now->Next);
                
                now->Next  = NULL;
                now        = GetSingleLinkListHead(SignalControlBlock);
            }
            else if( IsSingleLinkListTail(SignalControlBlock, now) )
            {
                last->Next = NULL;
                now->Next  = NULL;
                
                SingleLinkListTailWrite(SignalControlBlock, last);
            }
            else
            { 
                last->Next = now->Next;
                now->Next  = NULL;
                now        = last->Next;
            }
            
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
            if (del->Type == EVENT_HANDLER_EX_SIGNAL)
            {
                if( MemoryIsIn(del) == true )
                {
                    MemoryFree(del);
                }
            }
#endif
        }
        
        // break
        if( now == NULL )
        {
            return;
        }
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
fw_err_t SignalComponentInit( void )
{
    signal_clear();
    
    InitEventHandleTimer(&SignalTimer, SignalComponentPool, FW_EVENT_NONE);
    TimerArm(&SignalTimer, SIGNAL_SCAN_TIME, TIMER_CYCLE_MODE);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal component arm
 * @param       [in/out]  *signal           signal block
 * @param       [in/out]  *detect           signal detect function
 * @param       [in/out]  *handler          signal handler function
 * @return      [in/out]  FW_ERR_NONE       arm success
 * @return      [in/out]  FW_ERR_FAIL       arm failed
 * @note        None
 *******************************************************************************
 */
fw_err_t EventSignalArm(struct SignalBlock *signal, 
                        bool (*detect)(void), 
                        fw_err_t (*handler)(uint16_t) )
{
    if( IS_PTR_NULL(signal) || IS_PTR_NULL(detect) )
    {
        return FW_ERR_FAIL;
    }

    SIGNAL_HANDLE_INIT(signal);
    
    signal->Detect            = detect;
    signal->Handler           = handler;
    signal->Type              = EVENT_HANDLER_SIGNAL;
    signal->UseStatus         = true;
//    signal->Next            = NULL;
    
    signal_push(signal);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal ex component arm
 * @param       [in/out]  *detect           signal detect function
 * @param       [in/out]  *handler          signal handler function
 * @return      [in/out]  NOT NULL          arm success
 * @return      [in/out]  NULL              arm failed
 * @note        None
 *******************************************************************************
 */
struct SignalBlock *EventSignalExArm(bool (*detect)(void), 
                                     fw_err_t (*handler)(uint16_t) )
{
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    if( IS_PTR_NULL(detect) || IS_PTR_NULL(handler) )
    {
        return NULL;
    }
    
    struct SignalBlock *signal = (struct SignalBlock *)MemoryMalloc(sizeof(struct SignalBlock));
    
    SIGNAL_HANDLE_INIT(signal);
    
    signal->Detect            = detect;
    signal->Handler           = handler;
    signal->Type              = EVENT_HANDLER_EX_SIGNAL;
    signal->UseStatus         = true;
//    signal->Next            = NULL;
    
    signal_push(signal);
    
    return signal;
#else
    return NULL;
#endif
}

/**
 *******************************************************************************
 * @brief       signal disarm
 * @param       [in/out]  *signal           signal block
 * @return      [in/out]  FW_ERR_NONE       disarm success
 * @note        None
 *******************************************************************************
 */
fw_err_t SignalDisarm(struct SignalBlock *signal)
{
    signal->UseStatus = false;

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
fw_err_t SignalComponentPool(uint16_t event)
{
    if( IsSingleLinkListHeadEmpty(SignalControlBlock) )
    {
        return FW_ERR_NONE;
    }
    
    signal_walk();
    
    return FW_ERR_NONE;
}

#endif

/** @}*/     /** signal component */

/**********************************END OF FILE*********************************/
