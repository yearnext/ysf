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

#if USE_TIMER_DEBUG
#include <stdlib.h>
#include <windows.h>
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
static void *head = YSF_NULL;

const ysf_timer_func_t ysf_timer =
{
    .init             = ysf_timer_init,
    .general.e.arm    = ysf_event_timer_arm,
    .general.e.disarm = ysf_event_timer_disarm,
#if USE_EVENT_TIMER_DEBUG
    .general.e.test   = ysf_event_timer_test,
#endif
};

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
ysf_err_t ysf_timer_init( void )
{
    head = YSF_NULL;

    return YSF_ERR_NONE;
}

ysf_err_t ysf_event_timer_arm(ysf_event_timer_t *timer_cb,
                              ysf_timing_t time,
                              ysf_event_t event)
{
    ysf_assert(IS_PTR_NULL(timer_cb));
    ysf_assert(time == 0);

    timer_cb->config.time = time;
    timer_cb->param.event = event;

    if( ysf_sList.traversal((void **)&head, ysf_sList.add, (void **)&timer_cb, YSF_NULL ) == YSF_TRUE )
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

    if( ysf_sList.traversal((void **)&head, ysf_sList.del, (void **)&timer_cb, YSF_NULL ) == YSF_TRUE )
    {
        return YSF_ERR_NONE;
    }

    return YSF_ERR_FAIL;
}

#if USE_EVENT_TIMER_DEBUG
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
        if( ysf_timer.general.e.arm(&testTimer[id], time, YSF_EVENT_NONE) == YSF_ERR_NONE )
        {
            ysf_log("\nadd timer success! id: %4d, set time %4d \n\n", id, time);
        }
        else
        {
            ysf_log("\nadd timer failed! id: %4d, set time %4d \n\n", id, time);
        }

        id  = rand();
        if( ysf_timer.general.e.disarm(&testTimer[id]) == YSF_ERR_NONE )
        {
            ysf_log("\ndel timer success! id: %4d \n", id);
        }
        else
        {
            ysf_log("\ndel timer failed! id: %4d \n\n", id);
        }

        Sleep(3000);
    }
}
#endif

/** @}*/     /* ysf timer component */
 /**********************************END OF FILE*********************************/
