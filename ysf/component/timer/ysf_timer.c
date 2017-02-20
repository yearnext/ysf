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
#include "../ysf/component/timer/ysf_timer.h"
#include "../ysf/common/ysf_type.h"
#include "../ysf/component/event/ysf_event.h"
#include "../ysf/component/tick/ysf_tick.h"
#include "../ysf/component/debug/ysf_debug.h"
#include "../ysf/component/list/ysf_single_list.h"

#if USE_YSF_EVENT_TIMER_DEBUG
#include <stdlib.h>
#include <windows.h>
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ysf_timer_add(timer_cb) \
                  ysf_slist_add((void **)&head, (void **)&(timer_cb))

#define ysf_timer_del(timer_cb) \
                  ysf_slist_del((void **)&head, (void **)&(timer_cb) )

/* Private typedef -----------------------------------------------------------*/
static ysf_s_list_t *head = YSF_NULL;

const struct _YSF_TIMER_API_ ysf_timer =
{
    .init               = ysf_timer_init,
    .handler            = ysf_timer_handler,

#if USE_YSF_EVENT_TIMER
    .eTimer.arm         = ysf_event_timer_arm,
    .eTimer.disarm      = ysf_event_timer_disarm,

#if USE_YSF_EVENT_TIMER_DEBUG
    .eTimer.test        = ysf_event_timer_test,
#endif

#endif

#if USE_YSF_EVENT_CYCLE_TIMER
    .eCycleTimer.arm    = ysf_event_cycle_timer_arm,
    .eCycleTimer.disarm = ysf_event_cycle_timer_disarm,

#if USE_YSF_EVENT_CYCLE_TIMER_DEBUG
    .eCycleTimer.test   = ysf_event_timer_test,
#endif

#endif

#if USE_YSF_TRIGGER_TIMER
    .tTimer.arm         = ysf_trigger_timer_arm,
    .tTimer.disarm      = ysf_trigger_timer_disarm,

#if USE_YSF_TRIGGER_TIMER_DEBUG
    .tTimer.test        = ysf_event_timer_test,
#endif

#endif

#if USE_YSF_TRIGGER_CYCLE_TIMER
    .tCycleTimer.arm    = ysf_trigger_cycle_timer_arm,
    .tCycleTimer.disarm = ysf_trigger_cycle_timer_disarm,

#if USE_YSF_TRIGGER_CYCLE_TIMER_DEBUG
    .tCycleTimer.test   = ysf_event_timer_test,
#endif

#endif
};

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
ysf_err_t ysf_timer_init( void )
{
    head = YSF_NULL;

    return YSF_ERR_NONE;
}

#if USE_YSF_EVENT_TIMER
ysf_err_t ysf_event_timer_arm(ysf_event_timer_t *timer_cb,
                              ysf_timing_t time,
                              ysf_event_t event)
{
    ysf_assert(IS_PTR_NULL(timer_cb));
    ysf_assert(time == 0);

    timer_cb->config.time = time;
    timer_cb->param.event = event;

#if USE_YSF_VARIOUS_TIMER_TYPE
    timer_cb->cb.class    = YSF_EVENT_TIMER;
#endif

    if( ysf_timer_add(timer_cb) == YSF_TRUE )
    {
        return YSF_ERR_NONE;
    }

    return YSF_ERR_FAIL;
}

ysf_err_t ysf_event_timer_disarm(ysf_event_timer_t *timer_cb)
{
    ysf_assert(IS_PTR_NULL(timer_cb));

    timer_cb->config.time = 0;
    timer_cb->param.event = YSF_EVENT_NONE;

    if( ysf_timer_del(timer_cb) == YSF_TRUE )
    {
        return YSF_ERR_NONE;
    }

    return YSF_ERR_FAIL;
}
#endif

#if USE_YSF_EVENT_CYCLE_TIMER
ysf_err_t ysf_event_cycle_timer_arm(ysf_event_cycle_timer_t *timer_cb,
                                    ysf_timing_t time,
                                    ysf_event_t event)
{
    ysf_assert(IS_PTR_NULL(timer_cb));
    ysf_assert(time == 0);

    timer_cb->config.time    = time;
    timer_cb->config.setTime = time;
    timer_cb->param.event    = event;
    timer_cb->cb.class       = YSF_EVENT_CYCLE_TIMER;

    if( ysf_timer_add(timer_cb) == YSF_TRUE )
    {
        return YSF_ERR_NONE;
    }

    return YSF_ERR_FAIL;
}

ysf_err_t ysf_event_cycle_timer_disarm(ysf_event_cycle_timer_t *timer_cb)
{
    ysf_assert(IS_PTR_NULL(timer_cb));

    timer_cb->config.time    = 0;
    timer_cb->config.setTime = 0;
    timer_cb->param.event    = YSF_EVENT_NONE;

    if( ysf_timer_del(timer_cb) == YSF_TRUE )
    {
        return YSF_ERR_NONE;
    }

    return YSF_ERR_FAIL;
}
#endif

#if USE_YSF_TRIGGER_TIMER
ysf_err_t ysf_trigger_timer_arm(ysf_trigger_timer_t *timer_cb,
                                ysf_timing_t time,
                                void (*func)(void *param),
                                void *param)
{
    ysf_assert(IS_PTR_NULL(timer_cb));
    ysf_assert(time == 0);

    timer_cb->config.time = time;
    timer_cb->param.func  = func;
    timer_cb->param.param = param;
    timer_cb->cb.class    = YSF_TRIGGER_TIMER;

    if( ysf_timer_add(timer_cb) == YSF_TRUE )
    {
        return YSF_ERR_NONE;
    }

    return YSF_ERR_FAIL;
}

ysf_err_t ysf_trigger_timer_disarm(ysf_trigger_timer_t *timer_cb)
{
    ysf_assert(IS_PTR_NULL(timer_cb));

    timer_cb->config.time = 0;
    timer_cb->param.func  = YSF_NULL;
    timer_cb->param.param = YSF_NULL;

    if( ysf_timer_del(timer_cb) == YSF_TRUE )
    {
        return YSF_ERR_NONE;
    }

    return YSF_ERR_FAIL;
}
#endif

#if USE_YSF_TRIGGER_CYCLE_TIMER
ysf_err_t ysf_trigger_cycle_timer_arm(ysf_trigger_cycle_timer_t *timer_cb,
                                      ysf_timing_t time,
                                      void (*func)(void *param),
                                      void *param)
{
    ysf_assert(IS_PTR_NULL(timer_cb));
    ysf_assert(time == 0);

    timer_cb->config.time    = time;
    timer_cb->config.setTime = time;
    timer_cb->param.func     = func;
    timer_cb->param.param    = param;
    timer_cb->cb.class       = YSF_EVENT_CYCLE_TIMER;

    if( ysf_timer_add(timer_cb) == YSF_TRUE )
    {
        return YSF_ERR_NONE;
    }

    return YSF_ERR_FAIL;
}

ysf_err_t ysf_trigger_cycle_timer_disarm(ysf_trigger_cycle_timer_t *timer_cb)
{
    ysf_assert(IS_PTR_NULL(timer_cb));

    timer_cb->config.time    = 0;
    timer_cb->config.setTime = 0;
    timer_cb->param.func     = YSF_NULL;
    timer_cb->param.param    = YSF_NULL;

    if( ysf_timer_del(timer_cb) == YSF_TRUE )
    {
        return YSF_ERR_NONE;
    }

    return YSF_ERR_FAIL;
}
#endif

#if USE_YSF_EVENT_TIMER_DEBUG
static ysf_event_timer_t testTimer[256];

void ysf_event_timer_test(void)
{
    ysf_u8_t id;
    ysf_timing_t time;

    ysf_timer.init();

    while(1)
    {
        id  = rand();
        time = rand();
        if( ysf_timer.eTimer.arm(&testTimer[id], time, YSF_EVENT_NONE) == YSF_ERR_NONE )
        {
            ysf_log("\nadd timer success! id: %4d, set time %4d \n", id, time);
        }
        else
        {
            ysf_log("\nadd timer failed! id: %4d, set time %4d \n", id, time);
        }

        id  = rand();
        if( ysf_timer.eTimer.disarm(&testTimer[id]) == YSF_ERR_NONE )
        {
            ysf_log("\ndel timer success! id: %4d \n", id);
        }
        else
        {
            ysf_log("\ndel timer failed! id: %4d \n", id);
        }

        ysf_timer_handler();
    }
}
#endif

/**
 *******************************************************************************
 * @brief       timer processing functions
 *******************************************************************************
 */
ysf_bool_t ysf_timer_status_judge( ysf_timing_t *timing, ysf_tick_t tick )
{
    ysf_assert(IS_PTR_NULL(timing));

    if( *timing > tick )
    {
        *timing -= tick;
        return YSF_FALSE;
    }
    else
    {
        *timing = 0;
        return YSF_TRUE;
    }

    return YSF_FALSE;
}

ysf_bool_t ysf_tList_eTimer_handler( void **timer_cb, void **ctx, void **expand )
{
    ysf_assert(IS_PTR_NULL(ctx));

    ysf_tick_t tick = *((ysf_tick_t *)(ctx));
    ysf_event_timer_t *timer = (ysf_event_timer_t *)(*timer_cb);

    if( timer == YSF_NULL )
    {
        return YSF_FALSE;
    }

    if( ysf_timer_status_judge(&timer->config.time, tick) == YSF_TRUE )
    {
        ysf_event_send(timer->param.event);
        ysf_event_timer_disarm(*timer_cb);
    }

    return YSF_FALSE;
}

ysf_bool_t ysf_tList_eCycleTimer_handler( void **timer_cb, void **ctx, void **expand )
{
    ysf_assert(IS_PTR_NULL(ctx));

    ysf_tick_t tick = *((ysf_tick_t *)(ctx));
    ysf_event_cycle_timer_t *timer = (ysf_event_cycle_timer_t *)(*timer_cb);

    if( timer == YSF_NULL )
    {
        return YSF_FALSE;
    }

    if( ysf_timer_status_judge(&timer->config.time, tick) == YSF_TRUE )
    {
        ysf_event_send(timer->param.event);
        timer->config.time = timer->config.setTime;
    }

    return YSF_FALSE;
}

ysf_bool_t ysf_tList_tTimer_handler( void **timer_cb, void **ctx, void **expand )
{
    ysf_assert(IS_PTR_NULL(ctx));

    ysf_tick_t tick = *((ysf_tick_t *)(ctx));
    ysf_trigger_timer_t *timer = (ysf_trigger_timer_t *)(*timer_cb);

    if( timer == YSF_NULL )
    {
        return YSF_FALSE;
    }

    if( ysf_timer_status_judge(&timer->config.time, tick) == YSF_TRUE )
    {
        if( timer->param.func != YSF_NULL )
        {
            timer->param.func(timer->param.param);
        }

        ysf_event_timer_disarm(*timer_cb);
    }

    return YSF_FALSE;
}

ysf_bool_t ysf_tList_tCycleTimer_handler( void **timer_cb, void **ctx, void **expand )
{
    ysf_assert(IS_PTR_NULL(ctx));

    ysf_tick_t tick = *((ysf_tick_t *)(ctx));
    ysf_trigger_cycle_timer_t *timer = (ysf_trigger_cycle_timer_t *)(*timer_cb);

    if( timer == YSF_NULL )
    {
        return YSF_FALSE;
    }

    if( ysf_timer_status_judge(&timer->config.time, tick) == YSF_TRUE )
    {
        if( timer->param.func != YSF_NULL )
        {
            timer->param.func(timer->param.param);
        }

        timer->config.time = timer->config.setTime;
    }

    return YSF_FALSE;
}

ysf_bool_t ysf_tList_timer_handler( void **timer_cb, void **ctx, void **expand )
{
    ysf_assert(IS_PTR_NULL(ctx));
    ysf_assert(IS_PTR_NULL(expand));

    ysf_timer_cb_t *timer = (ysf_timer_cb_t *)(*timer_cb);
    sListFunc *handler = (sListFunc *)(expand);

    if( timer == YSF_NULL )
    {
        return YSF_FALSE;
    }

    handler[timer->class](timer_cb, ctx, YSF_NULL);

    return YSF_FALSE;
}

#if USE_YSF_VARIOUS_TIMER_TYPE
ysf_err_t ysf_timer_handler( void )
{
    ysf_tick_t tick = ysf_past_tick_cal();

    const sListFunc timer_handler[] =
    {
        ysf_tList_eTimer_handler,
        ysf_tList_eCycleTimer_handler,
        ysf_tList_tTimer_handler,
        ysf_tList_tCycleTimer_handler,
    };

    ysf_slist_traversal((void **)&head, ysf_tList_timer_handler,
                        (void **)&tick, (void **)timer_handler);

    return YSF_ERR_NONE;
}

#else
ysf_err_t ysf_timer_handler( void )
{
    ysf_tick_t tick = ysf_past_tick_cal();

    ysf_slist_traversal((void **)&head, ysf_tList_eTimer_handler,
                        (void **)&tick, YSF_NULL);

    return YSF_ERR_NONE;
}

//ysf_err_t ysf_timer_handler( void )
//{
//    ysf_tick_t tick = ysf_past_tick_cal();
//
//    ysf_event_timer_t *timer_cb = (ysf_event_timer_t *)head;
//
//    while(1)
//    {
//        if(timer_cb != YSF_NULL)
//        {
//            if( ysf_timer_status_judge(&timer_cb->config.time, tick) == YSF_TRUE )
//            {
//                ysf_event_send(timer_cb->param.event);
//                ysf_event_timer_disarm(timer_cb);
//            }
//
//            timer_cb = (ysf_event_timer_t *)timer_cb->cb.next;
//        }
//        else
//        {
//            break;
//        }
//    }
//
//    return YSF_ERR_NONE;
//}
#endif

/** @}*/     /* ysf timer component */
 /**********************************END OF FILE*********************************/
