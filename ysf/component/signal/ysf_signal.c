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
#include "ysf_path.h"
#include YSF_COMPONENT_SIGNAL_DIR
#include YSF_COMPONENT_TIMER_DIR
#include YSF_COMPONENT_MEMORY_DIR
#include YSF_TYPE_DIR
#include YSF_COMPONENT_EVENT_DIR
#include YSF_COMPONENT_SINGLE_LIST_DIR

/* Private define ------------------------------------------------------------*/
#define ysf_signal_add(signal_cb) \
                       ysf_slist_add((void **)&head, (void **)&(signal_cb))

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static struct ysf_sList_t *head = NULL;
//

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_SIGNAL_API
ysf_err_t ysf_signal_init( void )
{    
//#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API    
//    ysf_timerSimple_cb_arm(YSF_SIGNAL_SCAN_TIME, YSF_TIMER_CYCLE_PARAM, ysf_signal_handler, NULL);
//#else
    static struct ysf_timer_t signal;
    ysf_timerEx_cb_init(&signal, ysf_signal_handler, NULL);
    ysf_timerEx_arm(&signal, YSF_SIGNAL_SCAN_TIME, YSF_TIMER_CYCLE_PARAM);
//#endif
    
    head = NULL;
    
    return YSF_ERR_NONE;
}

ysf_err_t ysf_signalSimple_arm( enum ysf_signal_status_t (*detect)(void), void (*handler)(enum ysf_signal_status_t) )
{
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
    struct ysf_signal_t *signal = (struct ysf_signal_t *)ysf_memory_malloc(sizeof(struct ysf_signal_t)/sizeof(char));
    
    if( signal == NULL )
    {
        return YSF_ERR_FAIL;
    }
    
    if( detect == NULL )
    {
        return YSF_ERR_FAIL;
    }
    
    if( handler == NULL )
    {
        return YSF_ERR_FAIL;
    }
    
    signal->control.next    = NULL;
    signal->control.status  = ysf_enable;
    
    signal->func.detect     = detect;
    signal->func.handler    = handler;
    
    signal->status          = SIGNAL_STATUS_RELEASE;

    ysf_signal_add(signal);
    
    return YSF_ERR_NONE;
    
#else
    return YSF_ERR_FAIL;
#endif
}

ysf_err_t ysf_signalEx_arm(struct ysf_signal_t *signal, 
                           enum ysf_signal_status_t (*detect)(void), 
                           void (*handler)(enum ysf_signal_status_t) )
{
    if( signal == NULL )
    {
        return YSF_ERR_FAIL;
    }
    
    if( detect == NULL )
    {
        return YSF_ERR_FAIL;
    }
    
    if( handler == NULL )
    {
        return YSF_ERR_FAIL;
    }
    
    signal->control.next    = NULL;
    signal->control.status  = ysf_enable;
    
    signal->func.detect     = detect;
    signal->func.handler    = handler;

    signal->status          = SIGNAL_STATUS_RELEASE;
    
    ysf_signal_add(signal);
    
    return YSF_ERR_NONE;
}

ysf_err_t ysf_signalEx_disarm(struct ysf_signal_t *signal)
{
    if( signal == NULL )
    {
        return YSF_ERR_FAIL;
    }

    signal->control.status  = ysf_disable;

    return YSF_ERR_NONE;
}

YSF_STATIC_INLINE
void ysf_signal_judge( struct ysf_signal_t *signal )
{
    enum ysf_signal_status_t status = signal->func.detect();

    if( signal == NULL )
    {
        return;
    }
    
    switch( signal->status )
    {
        case SIGNAL_STATUS_INIT:
            if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            else if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP1:
            if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP2;
            }
            else if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP2:
            if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP3;
            }
            else if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP3:
            if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS_EDGE;
                signal->func.handler(signal->status);
            }
            else if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP1:
            if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP2;
            }
            else if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP2:
            if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP3;
            }
            else if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP3:
            if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE_EDGE;
                signal->func.handler(signal->status);
            }
            else if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_RELEASE_EDGE:
            if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE;
                signal->func.handler(signal->status);
            }
            else if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_RELEASE:
            if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE;
                signal->func.handler(signal->status);
            }
            else if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_PRESS_EDGE:
            if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS;
                signal->func.handler(signal->status);
            }
            else if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        case SIGNAL_STATUS_PRESS:
            if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS;
                signal->func.handler(signal->status);
            }
            else if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            else
            {
                /** do nothing! */
            }
            break;
        default:
            break;
    }
}

YSF_STATIC_INLINE
bool ysf_signal_walk( void **node, void **ctx, void **expand )
{
    struct ysf_signal_t *signal = (struct ysf_signal_t *)(*node);
    struct ysf_signal_t *last   = (struct ysf_signal_t *)(*expand); 
    struct ysf_signal_t *del    = (struct ysf_signal_t *)(*node); 
    
    if( *node == NULL )
    {
        return true;
    }
    
    ysf_signal_judge(signal);
    
    if( signal->control.status == ysf_disable )
    {
        if( (void *)last == (void *)head )
        {
            *node = last->control.next;
            last->control.next = NULL;
        }
        else
        { 
            last->control.next = signal->control.next;
            signal->control.next = NULL;
            
            *node = *expand;
        }
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
        if( ysf_memory_is_in(del) == true )
        {
            ysf_memory_free(del);
        }
#endif
    }
    
    return false;
}

ysf_err_t ysf_signal_handler( void *param )
{
    void *last = (void *)head;
    
    ysf_slist_walk((void **)&head, ysf_signal_walk, NULL, (void **)&last);
    
    return YSF_ERR_NONE;
}

#endif

/** @}*/     /* ysf signal component  */

/**********************************END OF FILE*********************************/
