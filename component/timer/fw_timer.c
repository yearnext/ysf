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
 * @file       fw_timer.c                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2016-07-09                                                      *
 * @brief      timer component source files                                    *
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
* @defgroup timer component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_TIMER_COMPONENT_PATH
#include _FW_EVENT_COMPONENT_PATH
#include _FW_TICK_COMPONENT_PATH
#include _FW_MEMORY_COMPONENT_PATH
#include _FW_LINK_LIST_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      detect timer status
 *******************************************************************************
 */
#define IS_TIMER_DISABLE(timer)  ((timer)->Cycle == 0)
#define IS_TIMER_ENABLE(timer)   ((timer)->Cycle != 0)

/**
 *******************************************************************************
 * @brief      timer disable function
 *******************************************************************************
 */
#define TIMER_DISABLE(timer)    ((timer)->Cycle = 0)

/* Private typedef -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      timer head node
 *******************************************************************************
 */
#if USE_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief      timer control block
 *******************************************************************************
 */
static CREATE_SINGLE_LIST_FIFO_CONTROL_BLOCK(struct TimerBlock, TimerControlBlock);
#endif

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief       detect the timer is in queue
 * @param       [in/out]  timer                will detect timer
 * @return      [in/out]  true                 the timer in the queue
 * @return      [in/out]  true                 the timer not in the queue
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
bool timer_is_in(struct TimerBlock *timer)
{
    IsInSingleLinkListFifo(struct TimerBlock, TimerControlBlock, timer);
    
    return false;
}

/**
 *******************************************************************************
 * @brief       pop timer to queue
 * @param       [in/out]  timer                will timer task
 * @return      [in/out]  FW_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
fw_err_t timer_push(struct TimerBlock *timer)
{
    SingleLinkListFifoPush(timer_is_in, TimerControlBlock, timer);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       push timer from queue
 * @param       [in/out]  void
 * @return      [in/out]  struct TimerBlock *     push timer addr in memory
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
struct TimerBlock *timer_pop(void)
{
    struct TimerBlock *timer = NULL;
    
    SingleLinkListFifoPop(TimerControlBlock, timer);
    
    return timer;
}

/**
 *******************************************************************************
 * @brief       timer queue clear
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
fw_err_t timer_clear(void)
{    
    while(timer_pop() != NULL);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       ysf timer component init
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE       init finish
 * @note        None
 *******************************************************************************
 */
fw_err_t TimerComponentInit( void )
{
    timer_clear();
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       call back trigger timer init
 * @param       [in/out]  *timer             timer block
 * @param       [in/out]  func               call back function
 * @param       [in/out]  param              call back function param
 * @return      [in/out]  FW_ERR_NONE       init success
 * @return      [in/out]  FW_ERR_FAIL       init failed
 * @note        None
 *******************************************************************************
 */
fw_err_t InitCallBackTimer(struct TimerBlock *timer, fw_err_t (*func)(void*), void *param)
{
    if(IS_PTR_NULL(timer) || IS_PTR_NULL(func))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    timer->Task.Handler.CallBack = func;
    timer->Task.Param            = param;
    timer->Type                  = CALL_BACK_TIMER;
    
    return FW_ERR_NONE;
}


/**
 *******************************************************************************
 * @brief       event distribute timer init
 * @param       [in/out]  *timer             timer block
 * @param       [in/out]  event              distribute event
 * @return      [in/out]  FW_ERR_NONE       init success
 * @return      [in/out]  FW_ERR_FAIL       init failed
 * @note        None
 *******************************************************************************
 */
fw_err_t InitEventHandleTimer(struct TimerBlock *timer, fw_err_t (*func)(uint16_t), uint16_t evt)
{
    if(IS_PTR_NULL(timer) || IS_PTR_NULL(func))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    timer->Task.Handler.Event = func;
    timer->Task.Event         = evt;
    timer->Type               = EVENT_HANDLE_TIMER;
    
    return FW_ERR_NONE;
}


/**
 *******************************************************************************
 * @brief       event trigger timer init
 * @param       [in/out]  *timer             timer block
 * @param       [in/out]  func               event handler function
 * @param       [in/out]  param              event function param
 * @param       [in/out]  event              trigger event
 * @return      [in/out]  FW_ERR_NONE       init success
 * @return      [in/out]  FW_ERR_FAIL       init failed
 * @note        None
 *******************************************************************************
 */
fw_err_t InitMessageHandleTimer(struct TimerBlock *timer, fw_err_t (*func)(void*, uint16_t), void *param, uint16_t evt)
{
    if(IS_PTR_NULL(timer) || IS_PTR_NULL(func))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    timer->Task.Handler.Message = func;
    timer->Task.Param           = param;
    timer->Task.Event           = evt;
    timer->Type                 = MESSAGE_HANDLE_TIMER;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       call back trigger timer init
 * @param       [in/out]  func               call back function
 * @param       [in/out]  param              call back function param
 * @return      [in/out]  FW_ERR_NONE       init success
 * @return      [in/out]  FW_ERR_FAIL       init failed
 * @note        None
 *******************************************************************************
 */
struct TimerBlock *InitCallBackExTimer(fw_err_t (*func)(void*), void *param)
{
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    if(IS_PTR_NULL(func))
    {
        return NULL;
    }
    
    struct TimerBlock *timer = (struct TimerBlock *)MemoryMalloc(sizeof(struct TimerBlock));
    
    if(IS_PTR_NULL(timer))
    {
        return NULL;
    }
    
    timer->Task.Handler.CallBack = func;
    timer->Task.Param            = param;
    timer->Type                  = CALL_BACK_EX_TIMER;
    
    return timer;
#else
    return NULL;
#endif
}

/**
 *******************************************************************************
 * @brief       event distribute timer init
 * @param       [in/out]  event              distribute event
 * @return      [in/out]  FW_ERR_NONE       init success
 * @return      [in/out]  FW_ERR_FAIL       init failed
 * @note        None
 *******************************************************************************
 */
struct TimerBlock *InitEventHandleExTimer(fw_err_t (*func)(uint16_t), uint16_t evt)
{
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    struct TimerBlock *timer = (struct TimerBlock *)MemoryMalloc(sizeof(struct TimerBlock));
    
    if(IS_PTR_NULL(timer))
    {
        return NULL;
    }
    
    timer->Task.Handler.Event = func;
    timer->Task.Event         = evt;
    timer->Type               = EVENT_HANDLE_EX_TIMER;
    
    return timer;
#else
    return NULL;
#endif
}

/**
 *******************************************************************************
 * @brief       event trigger timer init
 * @param       [in/out]  func               event handler function
 * @param       [in/out]  param              event function param
 * @param       [in/out]  event              trigger event
 * @return      [in/out]  FW_ERR_NONE       init success
 * @return      [in/out]  FW_ERR_FAIL       init failed
 * @note        None
 *******************************************************************************
 */
struct TimerBlock *InitMessageHandleExTimer(fw_err_t (*func)(void*, uint16_t), void *param, uint16_t evt)
{
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    if(IS_PTR_NULL(func))
    {
        return NULL;
    }
    
    struct TimerBlock *timer = (struct TimerBlock *)MemoryMalloc(sizeof(struct TimerBlock));
    
    if(IS_PTR_NULL(timer))
    {
        return NULL;
    }
    
    timer->Task.Handler.Message = func;
    timer->Task.Param           = param;
    timer->Task.Event           = evt;
    timer->Type                 = MESSAGE_HANDLE_EX_TIMER;
    
    return timer;
#else
    return NULL;
#endif
}

/**
 *******************************************************************************
 * @brief       timer arm
 * @param       [in/out]  *timer             timer block
 * @param       [in/out]  ticks              timer timing
 * @param       [in/out]  counts             cycle counts
 * @return      [in/out]  FW_ERR_NONE       timer arm success
 * @return      [in/out]  FW_ERR_FAIL       timer arm failed
 * @note        None
 *******************************************************************************
 */
fw_err_t TimerArm(struct TimerBlock *timer, uint32_t ticks, int16_t cycles)
{
    if(IS_PTR_NULL(timer))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    timer->SetTicks  = ticks;
    timer->LoadTicks = ticks;
    timer->Cycle     = cycles;
    
    timer_push(timer);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer disarm
 * @param       [in/out]  *timer             timer block
 * @return      [in/out]  FW_ERR_NONE       timer disarm success
 * @return      [in/out]  FW_ERR_FAIL       timer disarm failed
 * @note        None
 *******************************************************************************
 */
fw_err_t TimerDisarm(struct TimerBlock *timer)
{
    if(IS_PTR_NULL(timer))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    TIMER_DISABLE(timer);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       determines whether the timer is triggered
 * @param       [in/out]  *timer     timer block
 * @param       [in/out]  ticks      elapsed time
 * @return      [in/out]  false      timer is not triggered
 * @return      [in/out]  true       timer is triggered
 * @note        this is a static inline type function
 *******************************************************************************
 */
__STATIC_INLINE
bool is_timer_trigger(struct TimerBlock *timer, uint32_t ticks)
{    
//    if( IS_PTR_NULL(timer) )
//    {
//        return false;
//    }
    
    if( ticks >= timer->SetTicks )
    {
        if( timer->Cycle > 0 )
        {
            timer->Cycle--;
        }
        
        timer->SetTicks = timer->LoadTicks;

        return true;
    }
    else
    {
        timer->SetTicks -= ticks;
        return false;
    }
    
//     return false;
}

/**
 *******************************************************************************
 * @brief       timer trigger handler
 * @param       [in/out]  *timer     timer block
 * @return      [in/out]  false      timer handler failed
 * @return      [in/out]  true       timer handler success
 * @note        this is a static inline type function
 *******************************************************************************
 */
__STATIC_INLINE
void timer_trigger_handler(struct TimerBlock *timer)
{    
    switch(timer->Type)
    {
        case CALL_BACK_TIMER:
        case CALL_BACK_EX_TIMER:
            if( timer->Task.Handler.CallBack != NULL )
            {
                CreateCallBackTask(&timer->Task, timer->Task.Handler.CallBack, timer->Task.Param);
            }
            break;
        case EVENT_HANDLE_TIMER:
        case EVENT_HANDLE_EX_TIMER:
            if( timer->Task.Handler.Event != NULL )
            {
                CreateEventHandleTask(&timer->Task, timer->Task.Handler.Event, timer->Task.Event);
            }
            break;
        case MESSAGE_HANDLE_TIMER:
        case MESSAGE_HANDLE_EX_TIMER:
            if( timer->Task.Handler.Message != NULL )
            {
                CreateMessageHandleTask(&timer->Task, timer->Task.Handler.Message, timer->Task.Param, timer->Task.Event);
            }
            break;
//        default:
//            break;
    }
}

/**
 *******************************************************************************
 * @brief       timer walk
 * @param       [in/out]  **node         now timer node
 * @param       [in/out]  **ctx          elapsed time
 * @param       [in/out]  **expand       last timer node
 * @return      [in/out]  false          timer walk is not end
 * @return      [in/out]  true           timer walk is end
 * @note        this is a static type function
 *******************************************************************************
 */
__STATIC_INLINE
void timer_walk(uint32_t tick)
{
    struct TimerBlock *now  = GetSingleLinkListHead(TimerControlBlock);
    struct TimerBlock *last = now;
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    struct TimerBlock *del  = NULL;
#endif
    
    while(1)
    {
        // break
        if( now == NULL )
        {
            return;
        }
        
        // timer handler
        if( IS_TIMER_ENABLE(now) )
        {
            if( is_timer_trigger(now, tick) == true )
            {
                timer_trigger_handler(now);
            }
        }

        // timer list delete
        if( IS_TIMER_DISABLE(now) )
        {   
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
            del = now;
#endif      
            if( IsSingleLinkListHead(TimerControlBlock, now) )
            {
                SingleLinkListHeadWrite(TimerControlBlock, now->Next);
                
                now->Next  = NULL;
                now        = GetSingleLinkListHead(TimerControlBlock);
            }
            else if( IsSingleLinkListTail(TimerControlBlock, now) )
            {
                last->Next = NULL;
                now->Next  = NULL;
                
                SingleLinkListTailWrite(TimerControlBlock, last);
            }
            else
            { 
                last->Next = now->Next;
                now->Next  = NULL;
                now        = last->Next;
            }
            
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
            if (del->Type == CALL_BACK_EX_TIMER 
                || del->Type == EVENT_HANDLE_EX_TIMER  
                || del->Type == MESSAGE_HANDLE_EX_TIMER)
            {
                if( MemoryIsIn(del) == true )
                {
                    MemoryFree(del);
                }
            }
#endif
        }
        else
        {
            last = now;
            now  = now->Next;
        }
    }
}

/**
 *******************************************************************************
 * @brief       timer handler
 * @param       [in/out]  event           trigger event
 * @return      [in/out]  FW_ERR_NONE    not happen error
 * @note        timer processing function without errors
 *******************************************************************************
 */
fw_err_t TimerComponentHandle(uint16_t event)
{
    if( IsSingleLinkListHeadEmpty(TimerControlBlock) )
    {
        return FW_ERR_NONE;
    }
    
    timer_walk(CalPastTick());
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get timer status
 * @param       [in/out]  timer           timer block
 * @return      [in/out]  false           timer is disable
 * @return      [in/out]  true            timer is enable
 * @note        timer processing function without errors
 *******************************************************************************
 */
bool GetTimerStatus(struct TimerBlock *timer)
{
    if( timer_is_in(timer) == true && IS_TIMER_ENABLE(timer) )
    {
        return true;
    }
    
    return false;
}

#endif

/** @}*/     /** ysf timer component */
 /**********************************END OF FILE*********************************/
