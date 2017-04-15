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
 * @file       ysf_signal.c                                                    *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-15                                                      *
 * @brief      signal component source files                                   *
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
 * @defgroup ysf signal component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_SIGNAL_COMPONENT_PATH
#include _FW_TIMER_COMPONENT_PATH
#include _FW_MEMORY_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH
#include _FW_EVENT_COMPONENT_PATH
#include _FW_LINK_LIST_COMPONENT_PATH

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
static DEFINE_SLIST_FIFO_CONTROL_BLOCK(struct ysf_signal_t, scb);

/**
 *******************************************************************************
 * @brief       signal timer
 *******************************************************************************
 */
static struct ysf_timer_t signal_timer;
#endif
                       
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if defined(USE_YSF_SIGNAL_API) && USE_YSF_SIGNAL_API
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
bool ysf_signal_isIn(struct ysf_signal_t *signal)
{
    ysf_sListFIFO_isIn(struct ysf_signal_t, scb, signal);
    
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
fw_err_t ysf_signal_push(struct ysf_signal_t *signal)
{
    ysf_sListFIFO_push(ysf_signal_isIn, scb, signal);
    
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
struct ysf_signal_t *ysf_signal_pop(void)
{
    struct ysf_signal_t *signal = NULL;
    
    ysf_sListFIFO_pop(scb, signal);
    
    return signal;
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
fw_err_t ysf_signal_clear(void)
{    
    while(ysf_signal_pop() != NULL);
    
    return FW_ERR_NONE;
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
fw_err_t signalTriggerHandler(struct ysf_signal_t *signal, uint16_t evt)
{
//    if( IS_PTR_NULL(signal) )
//    {
//        return FW_ERR_FAIL;
//    }

//    switch(signal->type)
//    {
//        case YSF_EVENT_HANDLER_SIGNAL:
//            ysf_evtTask_create(&signal->task, signal->task.handler.evt, signal->task.evt);
//            break;
//        default:
//            break;
//    }
    
    ysf_evtTask_create(&signal->task, signal->task.handler.evt, evt);
    
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
fw_err_t ysf_signal_init( void )
{
    ysf_signal_clear();
    
    ysf_evtTimer_init(&signal_timer, ysf_signal_handler, FW_EVENT_NONE);
    ysf_timer_arm(&signal_timer, YSF_SIGNAL_SCAN_TIME, YSF_TIMER_CYCLE_MODE);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal ex component arm
 * @param       [in/out]  *signal            signal ex component
 * @param       [in/out]  *detect            signal detect function
 * @param       [in/out]  *handler           handler detect function
 * @return      [in/out]  FW_ERR_NONE       arm success
 * @return      [in/out]  FW_ERR_FAIL       arm failed
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_evtSignal_arm(struct ysf_signal_t *signal, 
                            enum ysf_signal_status_t (*detect)(void), 
                            fw_err_t (*handler)(uint16_t) )
{
    if( IS_PTR_NULL(signal) || IS_PTR_NULL(detect) )
    {
        return FW_ERR_FAIL;
    }

    signal->status             = SIGNAL_STATUS_RELEASE;
    signal->detect             = detect;
    signal->task.handler.evt   = handler;
    signal->type               = YSF_EVENT_HANDLER_SIGNAL;
    signal->useStatus          = true;
//    signal->next          = NULL;
    
    ysf_signal_push(signal);
    
    return FW_ERR_NONE;
}

struct ysf_signal_t *ysf_evtSimpSignal_arm(enum ysf_signal_status_t (*detect)(void), 
                                           fw_err_t (*handler)(uint16_t) )
{
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
    if( IS_PTR_NULL(detect) || IS_PTR_NULL(handler) )
    {
        return NULL;
    }
    
    struct ysf_signal_t *signal = (struct ysf_signal_t *)ysf_memory_malloc(sizeof(struct ysf_signal_t));
    
    signal->status             = SIGNAL_STATUS_RELEASE;
    signal->detect             = detect;
    signal->task.handler.evt   = handler;
    signal->type               = YSF_EVENT_HANDLER_SIGNAL;
    signal->useStatus          = true;
//    signal->next          = NULL;
    
    ysf_signal_push(signal);
    
    return signal;
#else
    return NULL;
#endif
}

/**
 *******************************************************************************
 * @brief       signal component disarm
 * @param       [in/out]  *signal            signal component
 * @return      [in/out]  FW_ERR_NONE       disarm success
 * @return      [in/out]  FW_ERR_FAIL       disarm failed
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_signal_disarm(struct ysf_signal_t *signal)
{
    signal->useStatus = false;

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       signal status judge
 * @param       [in/out]  *signal            signal component
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void ysf_signal_judge( struct ysf_signal_t *signal )
{
    enum ysf_signal_status_t status;

    if( IS_PTR_NULL(signal) || IS_PTR_NULL(signal->detect) || IS_PTR_NULL(signal->task.handler.evt) )
    {
        return;
    }
    
    status = signal->detect();
    
    switch( signal->status )
    {
        case SIGNAL_STATUS_INIT:
            if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            else
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP1:
            if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP2;
            }
            else
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP2:
            if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP3;
            }
            else
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            break;
        case SIGNAL_STATUS_PRESS_FILTER_STEP3:
            if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS_EDGE;
                signalTriggerHandler(signal, signal->status);
            }
            else
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP1:
            if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP2;
            }
            else
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP2:
            if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP3;
            }
            else
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            break;
        case SIGNAL_STATUS_RELEASE_FILTER_STEP3:
            if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE_EDGE;
                signalTriggerHandler(signal, signal->status);
            }
            else
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            break;
        case SIGNAL_STATUS_RELEASE_EDGE:
            if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE;
                signalTriggerHandler(signal, signal->status);
            }
            else
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            break;
        case SIGNAL_STATUS_RELEASE:
            if( status == SIGNAL_STATUS_RELEASE )
            {
                signal->status = SIGNAL_STATUS_RELEASE;
                signalTriggerHandler(signal, signal->status);
            }
            else
            {
                signal->status = SIGNAL_STATUS_PRESS_FILTER_STEP1;
            }
            break;
        case SIGNAL_STATUS_PRESS_EDGE:
            if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS;
                signalTriggerHandler(signal, signal->status);
            }
            else
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
            }
            break;
        case SIGNAL_STATUS_PRESS:
            if( status == SIGNAL_STATUS_PRESS )
            {
                signal->status = SIGNAL_STATUS_PRESS;
                signalTriggerHandler(signal, signal->status);
            }
            else
            {
                signal->status = SIGNAL_STATUS_RELEASE_FILTER_STEP1;
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
static bool ysf_signal_pool( void **node, void **ctx, void **expand )
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
    
    if( signal->useStatus == false )
    {
        if( (void *)last == (void *)scb.head )
        {
            *node = last->next;
            last->next = NULL;
        }
        else
        { 
            last->next = signal->next;
            signal->next = NULL;
            
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
 * @return      [in/out]  FW_ERR_NONE   handler end
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_signal_handler(uint16_t event)
{
    void *last = (void *)scb.head;
    
    ysf_slist_walk((void **)&scb.head, ysf_signal_pool, NULL, (void **)&last);
    
    return FW_ERR_NONE;
}

#endif

/** @}*/     /** ysf signal component  */

/**********************************END OF FILE*********************************/
