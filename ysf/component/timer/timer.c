/**
******************************************************************************
* @file       timer.c
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

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      add timer node function
 *******************************************************************************
 */
#define ysf_timer_add(timer_cb) \
                  ysf_slist_add((void **)&head, (void **)(&(timer_cb)))

/* Private typedef -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      timer head node
 *******************************************************************************
 */
#if defined(USE_YSF_TIMER_API) && USE_YSF_TIMER_API
static void *head = NULL;
#endif

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if defined(USE_YSF_TIMER_API) && USE_YSF_TIMER_API
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
    YSF_ENTER_CRITICAL();
    
    ysf_slist_init((void **)&head);

    YSF_EXIT_CRITICAL();
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       call back trigger timer arm
 * @param       [in/out]  time               timer timing
 * @param       [in/out]  count              cycle counts
 * @param       [in/out]  func               call back function
 * @param       [in/out]  param              call back function param
 * @return      [in/out]  YSF_ERR_NONE       timer arm success
 * @return      [in/out]  YSF_ERR_FAIL       timer arm failed
 * @note        None
 *******************************************************************************
 */
struct ysf_timer_t *ysf_timerSimple_cb_arm(uint32_t time, 
                                           uint8_t count,
                                           ysf_err_t (*func)(void*), 
                                           void *param)
{
    YSF_ENTER_CRITICAL();
    
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
    struct ysf_timer_t *timer = (struct ysf_timer_t *)ysf_memory_malloc(sizeof(struct ysf_timer_t)/sizeof(char));
    
    if( timer == NULL )
    {
        return NULL;
    }
    
    if( func == NULL )
    {
        ysf_memory_free(timer);
        return NULL;
    }
    
    timer->control.next           = NULL;
    timer->control.status         = ysf_enable;
    
    timer->config.loadCount       = time;
    timer->config.count           = timer->config.loadCount;
    timer->config.cycle           = count;
    
    timer->trigger.callback.func  = func;
    timer->trigger.callback.param = param;
    timer->trigger.event          = YSF_EVENT_NONE;
    
    ysf_timer_add(timer);
    
    YSF_EXIT_CRITICAL();
    
    return timer;
    
#else
    YSF_EXIT_CRITICAL();
    
    return NULL;
#endif
}

/**
 *******************************************************************************
 * @brief       event trigger timer arm
 * @param       [in/out]  time               timer timing
 * @param       [in/out]  count              cycle counts
 * @param       [in/out]  event              trigger events
 * @return      [in/out]  YSF_ERR_NONE       timer arm success
 * @return      [in/out]  YSF_ERR_FAIL       timer arm failed
 * @note        None
 *******************************************************************************
 */
struct ysf_timer_t *ysf_timerSimple_evt_arm(uint32_t time, uint8_t count, uint16_t event)
{
    YSF_ENTER_CRITICAL();
    
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
    struct ysf_timer_t *timer = (struct ysf_timer_t *)ysf_memory_malloc(sizeof(struct ysf_timer_t)/sizeof(char));
    
    if( timer == NULL )
    {
        return NULL;
    }
    
    timer->control.next           = NULL;
    timer->control.status         = ysf_enable;
    
    timer->config.loadCount       = time;
    timer->config.count           = timer->config.loadCount;
    timer->config.cycle           = count;

    timer->trigger.callback.func  = NULL;
    timer->trigger.event          = event;
    
    ysf_timer_add(timer);
    
    YSF_EXIT_CRITICAL();
    
    return timer;
#else
    
    YSF_EXIT_CRITICAL();
    return NULL;
#endif
}

/**
 *******************************************************************************
 * @brief       call back trigger timer init
 * @param       [in/out]  *timer             timer block
 * @param       [in/out]  func               call back function
 * @param       [in/out]  param              call back function param
 * @return      [in/out]  YSF_ERR_NONE       init success
 * @return      [in/out]  YSF_ERR_FAIL       init failed
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_timerEx_cb_init(struct ysf_timer_t *timer, 
                              ysf_err_t (*func)(void*), 
                              void *param)
{
    YSF_ENTER_CRITICAL();
    
    if( timer == NULL )
    {
        return YSF_ERR_FAIL;
    }
    
    if( func == NULL )
    {
        return YSF_ERR_FAIL;
    }
    
    timer->trigger.callback.func  = func;
    timer->trigger.callback.param = param;
    timer->trigger.event          = YSF_EVENT_NONE;
    
    YSF_EXIT_CRITICAL();
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       event trigger timer init
 * @param       [in/out]  *timer             timer block
 * @param       [in/out]  event              trigger events
 * @return      [in/out]  YSF_ERR_NONE       init success
 * @return      [in/out]  YSF_ERR_FAIL       init failed
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_timerEx_evt_init(struct ysf_timer_t *timer, uint16_t event)
{
    YSF_ENTER_CRITICAL();
    
    if( timer == NULL )
    {
        return YSF_ERR_FAIL;
    }
    
    timer->trigger.callback.func = NULL;
    timer->trigger.event         = event;
    
    YSF_EXIT_CRITICAL();
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer arm
 * @param       [in/out]  *timer             timer block
 * @param       [in/out]  time               timer timing
 * @param       [in/out]  count              cycle counts
 * @return      [in/out]  YSF_ERR_NONE       timer arm success
 * @return      [in/out]  YSF_ERR_FAIL       timer arm failed
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_timerEx_arm(struct ysf_timer_t *timer, 
                          uint32_t time, 
                          uint8_t count)
{
    YSF_ENTER_CRITICAL();
    
    if( timer == NULL )
    {
        return YSF_ERR_FAIL;
    }
    
    timer->config.loadCount = time;
    timer->config.count     = timer->config.loadCount;
    timer->config.cycle     = count;
    
    timer->control.status   = ysf_enable;
    
    ysf_timer_add(timer);
    
    YSF_EXIT_CRITICAL();
    
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
ysf_err_t ysf_timer_disarm( struct ysf_timer_t *timer )
{
    YSF_ENTER_CRITICAL();
    
    if( timer == NULL )
    {
        return YSF_ERR_FAIL;
    }
    
    timer->control.status = ysf_disable;
        
    YSF_EXIT_CRITICAL();
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       determines whether the timer is triggered
 * @param       [in/out]  sys            elapsed time
 * @param       [in/out]  *timer         timer block
 * @return      [in/out]  false      timer is not triggered
 * @return      [in/out]  true       timer is triggered
 * @note        this is a static inline type function
 *******************************************************************************
 */
YSF_STATIC_INLINE
bool isTimerTrigger(ysf_tick_t sys, struct ysf_timer_t *timer)
{    
    if( timer == NULL )
    {
        return false;
    }
    
    if( timer->control.status == ysf_disable )
    {
        return false;
    }
    
    if( sys >= timer->config.count )
    {
        if( timer->config.cycle > 0 )
        {
            timer->config.cycle--;
            if( timer->config.cycle == 0 )
            {
                timer->control.status = ysf_disable;
            }
        }
        
        timer->config.count = timer->config.loadCount;

        return true;
    }
    else
    {
        timer->config.count -= sys;
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
    if( timer == NULL )
    {
        return false;
    }    
    
    if( timer->trigger.event == YSF_EVENT_NONE )
    {
//        perform this function will directly lead to the cortex m3 kernel abort          
//        timer->trigger.callback.func(timer->trigger.callback.param);
        
        if( timer->trigger.callback.param != NULL )
        {
            timer->trigger.callback.func(timer->trigger.callback.param);
        }
        else
        {
            timer->trigger.callback.func(NULL);
        }
    }
    else
    {
        ysf_event_post(timer->trigger.event);
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
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
    void *del = *node;
#endif
    ysf_tick_t tick = (ysf_tick_t)(*(ctx));
    
    if( *node == NULL )
    {
        return true;
    }
    
    if( isTimerTrigger(tick, timer) == true )
    {
        timerTriggerHandler(timer);
    }
    
    if( timer->control.status == ysf_disable )
    {
        if( (void *)last == (void *)head )
        {
            *node = last->control.next;
            last->control.next = NULL;
        }
        else
        { 
            last->control.next = timer->control.next;
            timer->control.next = NULL;
            
            *node = *expand;
        }
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
        if( ysf_memory_is_in(del) == true )
        {
            ysf_memory_free(del);
        }
#endif
    }
    
    *expand = *node;
    
    return false;
}

/**
 *******************************************************************************
 * @brief       timer handler
 * @return      [in/out]  YSF_ERR_NONE    not happen error
 * @note        timer processing function without errors
 *******************************************************************************
 */
ysf_err_t ysf_timer_handler( uint16_t event )
{
    ysf_tick_t tick = ysf_past_tick_cal();
    void *expand = (void *)head;
    
    ysf_slist_walk((void **)&head, ysf_timer_walk, (void **)&tick, (void **)&expand);
    
    return YSF_ERR_NONE;
}

#endif

/** @}*/     /** ysf timer component */
 /**********************************END OF FILE*********************************/
