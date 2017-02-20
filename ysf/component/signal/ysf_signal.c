/**
  ******************************************************************************
  * @file       ysf_signal.c
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-1-15
  * @brief      ynf signal source file
  * @par        work platform
  *                 Windows
  * @par        compile platform
  * 				GCC
  ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
  ******************************************************************************
  */

/**
 * @defgroup ysf signal component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "../ysf/component/signal/ysf_signal.h"
#include "../ysf/common/ysf_type.h"
#include "../ysf/component/event/ysf_event.h"
#include "../ysf/component/list/ysf_single_list.h"
#include "../ysf/component/debug/ysf_debug.h"

/* Private define ------------------------------------------------------------*/
#define ysf_signal_add(signal_cb) \
                       ysf_slist_add((void **)&head, (void **)&(signal_cb))

#define ysf_signal_del(signal_cb) \
                       ysf_slist_del((void **)&head, (void **)&(signal_cb) )

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static ysf_s_list_t *head = YSF_NULL;

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
ysf_err_t ysf_event_signal_arm( ysf_event_signal_t *signal,
                                ysf_event_t event,
                                signal_status_t (*detect)(void) )
{
    ysf_assert(IS_PTR_NULL(signal));
    ysf_assert(IS_PTR_NULL(detect));

    signal->cb.class     = YSF_EVENT_SIGNAL;
    signal->param.detect = detect;
    signal->param.event  = event;
    signal->param.status = SIGNAL_STATUS_INIT;

    return ysf_signal_add(signal);
//
//    return YSF_ERR_NONE;
}

ysf_err_t ysf_event_signal_disarm( ysf_event_signal_t *signal )
{
    ysf_assert(IS_PTR_NULL(signal));

    signal->param.detect = YSF_NULL;
    signal->param.event  = YSF_EVENT_NONE;
    signal->param.status = SIGNAL_STATUS_INIT;

    return ysf_signal_del(signal);
//
//    return YSF_ERR_NONE;
}

ysf_err_t ysf_trigger_signal_arm( ysf_trigger_signal_t *signal,
                                  ysf_err_t (*handler)(signal_status_t),
                                  signal_status_t (*detect)(void) )
{
    ysf_assert(IS_PTR_NULL(signal));
    ysf_assert(IS_PTR_NULL(detect));

    signal->cb.class      = YSF_EVENT_SIGNAL;
    signal->param.detect  = detect;
    signal->param.handler = handler;
    signal->param.status  = SIGNAL_STATUS_INIT;

    return ysf_signal_add(signal);
//
//    return YSF_ERR_NONE;
}

ysf_err_t ysf_trigger_signal_disarm( ysf_trigger_signal_t *signal )
{
    ysf_assert(IS_PTR_NULL(signal));

    signal->param.detect  = YSF_NULL;
    signal->param.handler = YSF_NULL;
    signal->param.status  = SIGNAL_STATUS_INIT;

    return ysf_signal_del(signal);
//
//    return YSF_ERR_NONE;
}

ysf_bool_t ysf_event_signal_handler( void **signal_cb, void **ctx, void **expand )
{
    ysf_bool_t status = YSF_FALSE;



    return status;
}

ysf_bool_t ysf_trigger_signal_handler( void **signal_cb, void **ctx, void **expand )
{
    ysf_bool_t status = YSF_FALSE;

    return status;
}

ysf_bool_t ysf_signal_handler( void **signal_cb, void **ctx, void **expand )
{
    ysf_bool_t status = YSF_FALSE;

    return status;
}

/** @}*/     /* ysf signal component  */

/**********************************END OF FILE*********************************/
