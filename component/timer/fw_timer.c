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
 * @file       ysf_timer.c                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2016-07-09                                                      *
 * @brief      framework timer component source files                          *
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
* @defgroup framework timer component
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
#define IS_TIMER_DISABLE(timer)  ((timer)->cycle == 0)
#define IS_TIMER_ENABLE(timer)   ((timer)->cycle != 0)

/**
 *******************************************************************************
 * @brief      timer disable function
 *******************************************************************************
 */
#define _TIMER_DISABLE(timer)    ((timer)->cycle = 0)

/* Private typedef -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      timer head node
 *******************************************************************************
 */
#if defined(USE_YSF_TIMER_API) && USE_YSF_TIMER_API
/**
 *******************************************************************************
 * @brief       ysf timer control block
 *******************************************************************************
 */
static DEFINE_SLIST_FIFO_CONTROL_BLOCK(struct ysf_timer_t, TimerControlBlock);
#endif

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if defined(USE_YSF_TIMER_API) && USE_YSF_TIMER_API
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
bool ysf_timer_isIn(struct ysf_timer_t *timer)
{
    ysf_sListFIFO_isIn(struct ysf_timer_t, TimerControlBlock, timer);
    
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
fw_err_t ysf_timer_push(struct ysf_timer_t *timer)
{
    ysf_sListFIFO_push(ysf_timer_isIn, TimerControlBlock, timer);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       push timer from queue
 * @param       [in/out]  void
 * @return      [in/out]  struct ysf_timer_t *     push timer addr in memory
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
struct ysf_timer_t *ysf_timer_pop(void)
{
    struct ysf_timer_t *timer = NULL;
    
    ysf_sListFIFO_pop(TimerControlBlock, timer);
    
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
fw_err_t ysf_timer_clear(void)
{    
    while(ysf_timer_pop() != NULL);
    
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
fw_err_t ysf_timer_init( void )
{
    ysf_timer_clear();
    
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
fw_err_t ysf_cbTimer_init(struct ysf_timer_t *timer, fw_err_t (*func)(void*), void *param)
{
    if(IS_PTR_NULL(timer) || IS_PTR_NULL(func))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    timer->task.handler.cb = func;
    timer->task.param      = param;
    timer->type            = YSF_CALL_BACK_TIMER;
    
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
struct ysf_timer_t *ysf_cbSimpTimer_init(fw_err_t (*func)(void*), void *param)
{
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
    if(IS_PTR_NULL(func))
    {
        return NULL;
    }
    
    struct ysf_timer_t *timer = (struct ysf_timer_t *)ysf_memory_malloc(sizeof(struct ysf_timer_t));
    
    if(IS_PTR_NULL(timer))
    {
        return NULL;
    }
    
    timer->task.handler.cb = func;
    timer->task.param      = param;
    timer->type            = YSF_CALL_BACK_TIMER;
    
    return timer;
#else
    return NULL;
#endif
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
fw_err_t ysf_evtTimer_init(struct ysf_timer_t *timer, fw_err_t (*func)(uint16_t), uint16_t evt)
{
    if(IS_PTR_NULL(timer) || IS_PTR_NULL(func))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    timer->task.handler.evt = func;
    timer->task.evt         = evt;
    timer->type             = YSF_EVENT_HANDLER_TIMER;
    
    return FW_ERR_NONE;
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
struct ysf_timer_t *ysf_evtSimpTimer_init(fw_err_t (*func)(uint16_t), uint16_t evt)
{
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
    struct ysf_timer_t *timer = (struct ysf_timer_t *)ysf_memory_malloc(sizeof(struct ysf_timer_t));
    
    if(IS_PTR_NULL(timer))
    {
        return NULL;
    }
    
    timer->task.handler.evt = func;
    timer->task.evt         = evt;
    timer->type             = YSF_EVENT_HANDLER_TIMER;
    
    return timer;
#else
    return NULL;
#endif
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
fw_err_t ysf_smTimer_init(struct ysf_timer_t *timer, fw_err_t (*func)(void*, uint16_t), void *param, uint16_t evt)
{
    if(IS_PTR_NULL(timer) || IS_PTR_NULL(func))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    timer->task.handler.sm = func;
    timer->task.param      = param;
    timer->task.evt        = evt;
    timer->type            = YSF_STATE_MACHINE_TIMER;
    
    return FW_ERR_NONE;
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
struct ysf_timer_t *ysf_smSimpTimer_init(fw_err_t (*func)(void*, uint16_t), void *param, uint16_t evt)
{
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
    if(IS_PTR_NULL(func))
    {
        return NULL;
    }
    
    struct ysf_timer_t *timer = (struct ysf_timer_t *)ysf_memory_malloc(sizeof(struct ysf_timer_t));
    
    if(IS_PTR_NULL(timer))
    {
        return NULL;
    }
    
    timer->task.handler.sm = func;
    timer->task.param      = param;
    timer->task.evt        = evt;
    timer->type            = YSF_STATE_MACHINE_TIMER;
    
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
fw_err_t ysf_timer_arm(struct ysf_timer_t *timer, uint32_t ticks, int16_t counts)
{
    if(IS_PTR_NULL(timer))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    timer->ticks     = ticks;
    timer->loadTicks = ticks;
    timer->cycle     = counts;
    
    ysf_timer_push(timer);
    
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
fw_err_t ysf_timer_disarm(struct ysf_timer_t *timer)
{
    if(IS_PTR_NULL(timer))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    YSF_TIMER_DISABLE(timer);
    
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
bool isTimerTrigger(struct ysf_timer_t *timer, ysf_tick_t ticks)
{    
//    if( IS_PTR_NULL(timer) )
//    {
//        return false;
//    }
    
    if( ticks >= timer->ticks )
    {
        if( timer->cycle > 0 )
        {
            timer->cycle--;
        }
        
        timer->ticks = timer->loadTicks;

        return true;
    }
    else
    {
        timer->ticks -= ticks;
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
void TimerTriggerHandler(struct ysf_timer_t *timer)
{    
    switch(timer->type)
    {
        case YSF_CALL_BACK_TIMER:
            if( timer->task.handler.cb != NULL )
            {
                ysf_cbTask_create(&timer->task, timer->task.handler.cb, timer->task.param);
            }
            break;
        case YSF_EVENT_HANDLER_TIMER:
            if( timer->task.handler.evt != NULL )
            {
                ysf_evtTask_create(&timer->task, timer->task.handler.evt, timer->task.evt);
            }
            break;
        case YSF_STATE_MACHINE_TIMER:
            if( timer->task.handler.sm != NULL )
            {
                ysf_smTask_create(&timer->task, timer->task.handler.sm, timer->task.param, timer->task.evt);
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
void ysf_timer_walk(ysf_tick_t tick)
{
    struct ysf_timer_t *now  = TimerControlBlock.head;
    struct ysf_timer_t *last = now;
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
    struct ysf_timer_t *del  = NULL;
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
            if( isTimerTrigger(now, tick) == true )
            {
                TimerTriggerHandler(now);
            }
        }

        // timer list delete
        if( IS_TIMER_DISABLE(now) )
        {   
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
            del = now;
#endif      
            if( now == TimerControlBlock.head )
            {
                TimerControlBlock.head = now->next;
                now->next              = NULL;
                now                    = TimerControlBlock.head;
            }
            else if( now == TimerControlBlock.tail )
            {
                last->next             = NULL;
                now->next              = NULL;
                TimerControlBlock.tail = last;
            }
            else
            { 
                last->next = now->next;
                now->next  = NULL;
                now        = last->next;
            }
            
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
            if( ysf_memory_is_in(del) == true )
            {
                ysf_memory_free(del);
            }
#endif
        }
        else
        {
            last = now;
            now  = now->next;
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
fw_err_t ysf_timer_handler(uint16_t event)
{
    if( TimerControlBlock.head == NULL )
    {
        return FW_ERR_NONE;
    }
    
    ysf_timer_walk(ysf_past_tick_cal());
    
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
bool ysf_timerGetStatus(struct ysf_timer_t *timer)
{
    if( ysf_timer_isIn(timer) == true && IS_TIMER_ENABLE(timer) )
    {
        return true;
    }
    
    return false;
}

#endif

/** @}*/     /** ysf timer component */
 /**********************************END OF FILE*********************************/
