/**
******************************************************************************
* @file       ysf_timer.c
* @author     yearnext
* @version    1.0.0
* @date       2016-7-9
* @brief      ysf timer source file
* @par        MCU paltform
*                  STM32
* @par        MCU frequency
*                  72MHz
* @par        compiler frequency
*                  Keil
******************************************************************************
* @note
* 1.XXXXX
******************************************************************************
*/

/**
* @defgroup ysf timer component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_COMPONENT_TIMER_PATH
#include YSF_COMPONENT_EVENT_PATH
#include YSF_TYPE_PATH
#include YSF_COMPONENT_TICK_PATH
#include YSF_COMPONENT_MEMORY_PATH
#include YSF_COMPONENT_SINGLE_LIST_PATH
#include YSF_COMPONENT_DEBUG_PATH

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
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
//struct ysf_timer_control_block
//{
//    struct ysf_timer_t *head;
//    struct ysf_timer_t *tail;
//} static tcb = 
//{
//    .head = NULL,
//    .tail = NULL,
//};
static DEFINE_SLIST_FIFO_CONTROL_BLOCK(struct ysf_timer_t, tcb);
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
YSF_STATIC_INLINE
bool ysf_timer_isIn(struct ysf_timer_t *timer)
{
    ysf_sListControlBlock_isIn(struct ysf_timer_t, tcb, timer);
    
    return false;
}

/**
 *******************************************************************************
 * @brief       pop timer to queue
 * @param       [in/out]  timer                will timer task
 * @return      [in/out]  YSF_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
YSF_STATIC_INLINE
ysf_err_t ysf_timer_push(struct ysf_timer_t *timer)
{
    ysf_sListControlBlock_push(ysf_timer_isIn, tcb, timer);
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       push timer from queue
 * @param       [in/out]  void
 * @return      [in/out]  struct ysf_timer_t *     push timer addr in memory
 * @note        this function is static inline type
 *******************************************************************************
 */
YSF_STATIC_INLINE
struct ysf_timer_t *ysf_timer_pop(void)
{
    struct ysf_timer_t *timer;
    
    ysf_sListControlBlock_pop(tcb, timer);
    
    return timer;
}

/**
 *******************************************************************************
 * @brief       timer queue clear
 * @param       [in/out]  void
 * @return      [in/out]  YSF_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
YSF_STATIC_INLINE
ysf_err_t ysf_timer_clear(void)
{    
    while(ysf_timer_pop() != NULL);
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       ysf timer component init
 * @param       [in/out]  void
 * @return      [in/out]  YSF_ERR_NONE       init finish
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_timer_init( void )
{
    ysf_timer_clear();
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       call back trigger timer init
 * @param       [in/out]  *timer             timer block
 * @param       [in/out]  func               call back function
 * @param       [in/out]  param              call back function param
 * @param       [in/out]  expand             call back function expand param
 * @return      [in/out]  YSF_ERR_NONE       init success
 * @return      [in/out]  YSF_ERR_FAIL       init failed
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_timer_config(struct ysf_timer_t *timer, ysf_err_t (*func)(void*), void *param, uint16_t event)
{
    if(IS_PTR_NULL(timer) || IS_PTR_NULL(func))
    {
        return YSF_ERR_INVAILD_PTR;
    }
    
    timer->handler.cb.func  = func;
    timer->handler.cb.param = param;
    timer->event            = event;
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer arm
 * @param       [in/out]  *timer             timer block
 * @param       [in/out]  ticks              timer timing
 * @param       [in/out]  counts             cycle counts
 * @return      [in/out]  YSF_ERR_NONE       timer arm success
 * @return      [in/out]  YSF_ERR_FAIL       timer arm failed
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_timer_arm(struct ysf_timer_t *timer, uint32_t ticks, uint16_t counts)
{
    if(IS_PTR_NULL(timer))
    {
        return YSF_ERR_INVAILD_PTR;
    }
    
    timer->ticks     = ticks;
    timer->loadTicks = ticks;
    timer->cycle     = counts;
    
//    timer->next     = NULL;
    timer->status   = ysf_enable;
    
    ysf_timer_push(timer);
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer disarm
 * @param       [in/out]  *timer             timer block
 * @return      [in/out]  YSF_ERR_NONE       timer disarm success
 * @return      [in/out]  YSF_ERR_FAIL       timer disarm failed
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_timer_disarm(struct ysf_timer_t *timer)
{
    if(IS_PTR_NULL(timer))
    {
        return YSF_ERR_INVAILD_PTR;
    }
    
    timer->status = ysf_disable;
    
    return YSF_ERR_NONE;
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
YSF_STATIC_INLINE
bool isTimerTrigger(struct ysf_timer_t *timer, ysf_tick_t ticks)
{    
    if( timer == NULL )
    {
        return false;
    }
    
    if( timer->status == ysf_disable )
    {
        return false;
    }
    
    if( ticks >= timer->ticks )
    {
        if( timer->cycle > 0 )
        {
            timer->cycle--;
            if( timer->cycle == 0 )
            {
                timer->status = ysf_disable;
            }
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
YSF_STATIC_INLINE
bool timerTriggerHandler(struct ysf_timer_t *timer)
{    
//    if( timer == NULL )
//    {
//        return false;
//    }    

    switch(timer->type)
    {
        case YSF_EVENT_DISTRIBUTE_TIMER:
            if( timer->event != YSF_EVENT_NONE )
            {
                ysf_event_post(timer->event);
            }
            break;
        case YSF_EVENT_TRIGGER_TIMER:
            if(timer->handler.evt.func != NULL && timer->handler.evt.param != NULL)
            {
                ysf_evtTask_create(&timer->handler, timer->handler.evt.func, timer->handler.evt.param, timer->handler.evt.event);
            }
            break;
        case YSF_CALL_BACK_TIMER:
            if(timer->handler.cb.func != NULL)
            {
                ysf_cbTask_create(&timer->handler, timer->handler.cb.func, timer->handler.cb.param);
            }
            break;
        default:
            return false;
            break;
    }
    
    return true;
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
static bool ysf_timer_walk(void **node, void **ctx, void **expand)
{
    struct ysf_timer_t *timer = (struct ysf_timer_t *)(*node);
    struct ysf_timer_t *last  = (struct ysf_timer_t *)(*expand);
    ysf_tick_t tick = (ysf_tick_t)(*(ctx));
    
    if( *node == NULL )
    {
        return true;
    }
    
    if( isTimerTrigger(timer, tick) == true )
    {
        timerTriggerHandler(timer);
    }
    
    if( timer->status == ysf_disable )
    {
        if( (void *)last == (void *)tcb.head )
        {
            *node = last->next;
            last->next = NULL;
        }
        else
        { 
            last->next = timer->next;
            timer->next = NULL;
            
            *node = *expand;
        }
        
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
        if( ysf_memory_is_in(timer) == true )
        {
            ysf_memory_free(timer);
        }
#endif
    }
    
    *expand = *node;
    
    return false;
}

/**
 *******************************************************************************
 * @brief       timer handler
 * @param       [in/out]  event           trigger event
 * @return      [in/out]  YSF_ERR_NONE    not happen error
 * @note        timer processing function without errors
 *******************************************************************************
 */
ysf_err_t ysf_timer_handler( uint16_t event )
{
    if( tcb.head == NULL )
    {
        return YSF_ERR_NONE;
    }
    
    ysf_tick_t tick = ysf_past_tick_cal();
    void *expand = (void *)tcb.head;
    
    ysf_slist_walk((void **)&tcb.head, ysf_timer_walk, (void **)&tick, (void **)&expand);
    
    return YSF_ERR_NONE;
}

#endif

/** @}*/     /** ysf timer component */
 /**********************************END OF FILE*********************************/
