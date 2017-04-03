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
#include YSF_COMPONENT_SIGNAL_PATH
#include YSF_COMPONENT_TIMER_PATH
#include YSF_COMPONENT_MEMORY_PATH
#include YSF_TYPE_PATH
#include YSF_COMPONENT_EVENT_PATH
#include YSF_COMPONENT_SINGLE_LIST_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       signal component head point
 *******************************************************************************
 */
#if defined(USE_YSF_SIGNAL_API) && USE_YSF_SIGNAL_API
/**
 *******************************************************************************
 * @brief       ysf signal control block
 *******************************************************************************
 */
static DEFINE_SLIST_FIFO_CONTROL_BLOCK(struct ysf_signal_t, tcb);

/**
 *******************************************************************************
 * @brief       signal timer
 *******************************************************************************
 */
static struct ysf_timer_t signal;
#endif
                       
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if defined(USE_YSF_SIGNAL_API) && USE_YSF_SIGNAL_API
/**
 *******************************************************************************
 * @brief       signal ex component arm
 * @param       [in/out]  *signal            signal ex component
 * @param       [in/out]  *detect            signal detect function
 * @param       [in/out]  *handler           handler detect function
 * @return      [in/out]  YSF_ERR_NONE       arm success
 * @return      [in/out]  YSF_ERR_FAIL       arm failed
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_signal_evt_arm(struct ysf_signal_t *signal, 
                             enum ysf_signal_status_t (*detect)(void), 
                             uint16_t event )
{
    if( signal == NULL )
    {
        return YSF_ERR_FAIL;
    }
    
    if( detect == NULL )
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

/**
 *******************************************************************************
 * @brief       signal component disarm
 * @param       [in/out]  *signal            signal component
 * @return      [in/out]  YSF_ERR_NONE       disarm success
 * @return      [in/out]  YSF_ERR_FAIL       disarm failed
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_signal_disarm(struct ysf_signal_t *signal)
{
    if( signal == NULL )
    {
        return YSF_ERR_FAIL;
    }

    signal->control.status  = ysf_disable;

    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal status judge
 * @param       [in/out]  *signal            signal component
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
YSF_STATIC_INLINE
void ysf_signal_judge( struct ysf_signal_t *signal )
{
    enum ysf_signal_status_t status;

    if( signal == NULL || signal->func.detect == NULL || signal->func.handler == NULL)
    {
        return;
    }
    
    status = signal->func.detect();
    
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

/**
 *******************************************************************************
 * @brief       signal list walk
 * @param       [in/out]  **node         now node
 * @param       [in/out]  **ctx          none
 * @param       [in/out]  **expand       last node
 * @return      [in/out]  false          walk is not end
 * @return      [in/out]  true           walk is end
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
static bool ysf_signal_walk( void **node, void **ctx, void **expand )
{
    struct ysf_signal_t *signal = (struct ysf_signal_t *)(*node);
    struct ysf_signal_t *last   = (struct ysf_signal_t *)(*expand); 
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
    struct ysf_signal_t *del    = (struct ysf_signal_t *)(*node); 
#endif
    
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

/**
 *******************************************************************************
 * @brief       signal handler
 * @param       [in/out]  *param         none
 * @return      [in/out]  YSF_ERR_NONE   handler end
 * @note        None
 *******************************************************************************
 */
static ysf_err_t ysf_signal_handler( void *param, void *expand )
{
    void *last = (void *)scb.head;
    
    ysf_slist_walk((void **)&scb.head, ysf_signal_walk, NULL, (void **)&last);
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       ysf signal component init
 * @param       [in/out]  void
 * @return      [in/out]  YSF_ERR_NONE       init finish
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_signal_init( void )
{        
    scb.head = NULL;
    scb.tail = NULL;
    
    ysf_timer_cb_init(&signal, ysf_signal_handler, NULL, NULL);
    ysf_timer_arm(&signal, YSF_SIGNAL_SCAN_TIME, YSF_TIMER_CYCLE_PARAM);
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       ysf signal component deinit
 * @param       [in/out]  void
 * @return      [in/out]  YSF_ERR_NONE       init finish
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_signal_deinit( void )
{    
    scb.head = NULL;
    scb.tail = NULL;
    
    if( ysf_timer_isInList(&signal) == true )
    {
        ysf_timer_disarm(&signal);
    }
    
    return YSF_ERR_NONE;
}

#endif

/** @}*/     /** ysf signal component  */

/**********************************END OF FILE*********************************/
