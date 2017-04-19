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
#include _FW_DEBUG_COMPONENT_PATH

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
#define UPDATE_SIGNAL_STATUS(signal, status) ((signal)->SignalStatus = (status))
    
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
#if !defined(USE_MEMORY_COMPONENT) && !USE_MEMORY_COMPONENT
    CreateEventHandleTask(&signal->Task, signal->Handler, signal->SignalStatus);
#else
    CreateEventHandleExTask(signal->Handler, signal->SignalStatus);
#endif    
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
__STATIC_INLINE
fw_err_t signal_judge(struct SignalBlock *signal)
{
//    fw_assert(IS_PTR_NULL(signal));
    
    bool nowStatus = signal->Detect();
    
    switch( signal->SignalStatus )
    {
        case SIGNAL_STATUS_INIT:
            if( nowStatus == false )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP1:
            if( nowStatus == true )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP2);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP2:
            if( nowStatus == true )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP3);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP1);
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP3:
            if( nowStatus == true )
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
            if( nowStatus == false )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP2);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP2:
            if( nowStatus == false )
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_RELEASE_FILTER_STEP3);
            }
            else
            {
                UPDATE_SIGNAL_STATUS(signal, SIGNAL_STATUS_PRESS_FILTER_STEP1);
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP3:
            if( nowStatus == false )
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
            if( nowStatus == false )
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
            if( nowStatus == false )
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
            if( nowStatus == true )
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
            if( nowStatus == true )
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
            signal_judge(now);
            
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
                UpdateSingleLinkListHead(SignalControlBlock, now->Next);
                
                now->Next  = NULL;
                now        = GetSingleLinkListHead(SignalControlBlock);
            }
            else if( IsSingleLinkListTail(SignalControlBlock, now) )
            {
                last->Next = NULL;
                now->Next  = NULL;
                
                UpdateSingleLinkListTail(SignalControlBlock, last);
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
                if( IsInMemory(del) == true )
                {
                    FreeMemory(del);
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
fw_err_t InitSignalComponent( void )
{
    signal_clear();
    
    InitEventHandleTimer(&SignalTimer, SignalComponentPool, FW_EVENT_NONE);
    ArmTimerModule(&SignalTimer, SIGNAL_SCAN_TIME, TIMER_CYCLE_MODE);
    
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
fw_err_t ArmSignalModule(struct SignalBlock *signal, 
                         bool (*detect)(void), 
                         fw_err_t (*handler)(uint16_t) )
{
    fw_assert(IS_PTR_NULL(signal));
    fw_assert(IS_PTR_NULL(detect));
    fw_assert(IS_PTR_NULL(handler));
    
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
struct SignalBlock *ArmSignalExModule(bool (*detect)(void), 
                                      fw_err_t (*handler)(uint16_t) )
{
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    fw_assert(IS_PTR_NULL(detect));
    fw_assert(IS_PTR_NULL(handler));
    
    struct SignalBlock *signal = (struct SignalBlock *)MallocMemory(sizeof(struct SignalBlock));
    
    fw_assert(IS_PTR_NULL(signal));

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
fw_err_t DisarmSignalModule(struct SignalBlock *signal)
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

/**
 *******************************************************************************
 * @brief       add signal to signal queue
 * @param       [in/out]  *signal              signal block
 * @return      [in/out]  FW_ERR_NONE          add success
 * @return      [in/out]  FW_ERR_FAIL          add failed
 * @note        None
 *******************************************************************************
 */
fw_err_t AddSignalToQueue(struct SignalBlock *signal)
{
    fw_assert(IS_PTR_NULL(signal));
    
    PushSingleLinkListFifoNode(signal_is_in, SignalControlBlock, signal);
    
    return FW_ERR_NONE;
}

#endif

/** @}*/     /** signal component */

/**********************************END OF FILE*********************************/
