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
const struct _YSF_SIGNAL_API_ ysf_signal =
{
    .init           = ysf_signal_init,
    .handler        = ysf_signal_handler,

    .eSignal.arm    = ysf_event_signal_arm,
    .eSignal.disarm = ysf_event_signal_disarm,

    .tSignal.arm    = ysf_trigger_signal_arm,
    .tSignal.disarm = ysf_trigger_signal_disarm,
};

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void ysf_signal_init( void )
{
    head = YSF_NULL;
}

ysf_err_t ysf_event_signal_arm( ysf_event_signal_t *signal,
                                ysf_singal_event_t event,
                                signal_status_t (*detect)(void) )
{
    ysf_assert(IS_PTR_NULL(signal));
    ysf_assert(IS_PTR_NULL(detect));

    ysf_u8_t i;

    signal->cb.class     = YSF_EVENT_SIGNAL;
    signal->param.detect = detect;

    for( i=0; i<USE_SINGAL_EVENT_NUM; i++ )
    {
        signal->param.event[i] = event[i];
    }

    signal->param.status = SIGNAL_STATUS_INIT;

    return ysf_signal_add(signal);
//
//    return YSF_ERR_NONE;
}

ysf_err_t ysf_event_signal_disarm( ysf_event_signal_t *signal )
{
    ysf_assert(IS_PTR_NULL(signal));
    ysf_u8_t i;

    signal->param.detect = YSF_NULL;

    for( i=0; i<USE_SINGAL_EVENT_NUM; i++ )
    {
        signal->param.event[i] = YSF_EVENT_NONE;
    }

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

void ysf_signal_judge( signal_status_t *lastStatus, signal_status_t (*detect)(void) )
{
    signal_status_t nowStatus = detect();

    switch( *lastStatus )
    {
        case SIGNAL_STATUS_INIT:
        case SIGNAL_STATUS_DETECT:
            if( nowStatus == SIGNAL_STATUS_RELEASE )
            {
                *lastStatus = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            else if( nowStatus == SIGNAL_STATUS_PRESS )
            {
                *lastStatus = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP1:
            if( nowStatus == SIGNAL_STATUS_PRESS )
            {
                *lastStatus = SIGNAL_STATUS_PRESS_FILTER_STEP2;
            }
            else if( nowStatus == SIGNAL_STATUS_RELEASE )
            {
                *lastStatus = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP2:
            if( nowStatus == SIGNAL_STATUS_PRESS )
            {
                *lastStatus = SIGNAL_STATUS_PRESS_FILTER_STEP3;
            }
            else if( nowStatus == SIGNAL_STATUS_RELEASE )
            {
                *lastStatus = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP3:
            if( nowStatus == SIGNAL_STATUS_PRESS )
            {
                *lastStatus = SIGNAL_STATUS_PRESS_EDGE;
            }
            else if( nowStatus == SIGNAL_STATUS_RELEASE )
            {
                *lastStatus = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP1:
            if( nowStatus == SIGNAL_STATUS_RELEASE )
            {
                *lastStatus = SIGNAL_STATUS_RELEASE_FILTER_STEP2;
            }
            else if( nowStatus == SIGNAL_STATUS_PRESS )
            {
                *lastStatus = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP2:
            if( nowStatus == SIGNAL_STATUS_RELEASE )
            {
                *lastStatus = SIGNAL_STATUS_RELEASE_FILTER_STEP3;
            }
            else if( nowStatus == SIGNAL_STATUS_PRESS )
            {
                *lastStatus = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP3:
            if( nowStatus == SIGNAL_STATUS_RELEASE )
            {
                *lastStatus = SIGNAL_STATUS_RELEASE_EDGE;
            }
            else if( nowStatus == SIGNAL_STATUS_PRESS )
            {
                *lastStatus = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_RELEASE_EDGE:
            if( nowStatus == SIGNAL_STATUS_RELEASE )
            {
                *lastStatus = SIGNAL_STATUS_RELEASE;
            }
            else if( nowStatus == SIGNAL_STATUS_PRESS )
            {
                *lastStatus = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_RELEASE:
            if( nowStatus == SIGNAL_STATUS_RELEASE )
            {
                *lastStatus = SIGNAL_STATUS_RELEASE;
            }
            else if( nowStatus == SIGNAL_STATUS_PRESS )
            {
                *lastStatus = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_PRESS_EDGE:
            if( nowStatus == SIGNAL_STATUS_PRESS )
            {
                *lastStatus = SIGNAL_STATUS_PRESS;
            }
            else if( nowStatus == SIGNAL_STATUS_RELEASE )
            {
                *lastStatus = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_PRESS:
            if( nowStatus == SIGNAL_STATUS_PRESS )
            {
                *lastStatus = SIGNAL_STATUS_PRESS;
            }
            else if( nowStatus == SIGNAL_STATUS_RELEASE )
            {
                *lastStatus = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
//        case SIGNAL_STATUS_LONG_PRESS:
//            break;
//        case SIGNAL_STATUS_MULTI_PRESS:
//            break;
        default:
            break;
    }
}

ysf_bool_t ysf_event_signal_handler( void **signal_cb, void **ctx, void **expand )
{
    ysf_bool_t status = YSF_FALSE;
    ysf_event_signal_t *node = (ysf_event_signal_t *)(*signal_cb);

    if( node == YSF_NULL )
    {
        return YSF_FALSE;
    }

    ysf_signal_judge( &node->param.status, node->param.detect );

    switch( node->param.status )
    {
        case SIGNAL_STATUS_RELEASE:
            ysf_event_send(node->param.event[0]);
            break;
        case SIGNAL_STATUS_PRESS_EDGE:
            ysf_event_send(node->param.event[1]);
            break;
        case SIGNAL_STATUS_PRESS:
            ysf_event_send(node->param.event[2]);
            break;
        case SIGNAL_STATUS_RELEASE_EDGE:
            ysf_event_send(node->param.event[3]);
            break;
        default:
            break;
    }

    return status;
}

ysf_bool_t ysf_trigger_signal_handler( void **signal_cb, void **ctx, void **expand )
{
    ysf_bool_t status = YSF_FALSE;

    ysf_trigger_signal_t *node = (ysf_trigger_signal_t *)(*signal_cb);

    if( node == YSF_NULL )
    {
        return YSF_FALSE;
    }

    ysf_signal_judge( &node->param.status, node->param.detect );

    node->param.handler(node->param.status);

    return status;
}

ysf_bool_t ysf_slist_signal_handler( void **signal_cb, void **ctx, void **expand )
{
    ysf_bool_t status = YSF_FALSE;
    ysf_signal_cb_t *cb = (ysf_signal_cb_t *)(*signal_cb);
    sListFunc *handler  = (sListFunc *)(expand);

    if( cb == YSF_NULL )
    {
        return YSF_FALSE;
    }

    handler[cb->class](signal_cb, YSF_NULL, YSF_NULL);

    return status;
}

void ysf_signal_handler( void )
{
    const sListFunc func[] =
    {
        ysf_event_signal_handler,
        ysf_trigger_signal_handler
    };

    ysf_slist_traversal((void **)&head, ysf_slist_signal_handler,
                        YSF_NULL, (void **)func);
}

/** @}*/     /* ysf signal component  */

/**********************************END OF FILE*********************************/
