/**
 ******************************************************************************
  * @file       ysf.c
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-2-18
  * @brief      ysf source file
  * @par        work platform
  *                 Windows
  * @par        compiler platform
  *                 GCC
 ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf config
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf.h"

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define ysf function
 *******************************************************************************
 */
#if defined(USE_YSF_API) && USE_YSF_API
void ysf_init( ysf_err_t (*user_init)(void) );
void ysf_start(void);
#endif

/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      ysf api
 *******************************************************************************
 */
#if defined(USE_YSF_API) && USE_YSF_API
const struct YSF_API ysf = 
{
    .init                      = ysf_init,
    .start                     = ysf_start,
    .ver                       = YSF_VERSION,
    
#if defined(USE_YSF_TICK_API) && USE_YSF_TICK_API
    .tick.init                 = ysf_tick_init,
    .tick.inc                  = ysf_tick_inc,
    .tick.read                 = ysf_tick_get,
    .tick.cal                  = ysf_past_tick_cal,
#endif
    
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
    .memory.init               = ysf_memory_init,
    .memory.malloc             = ysf_memory_malloc,
    .memory.free               = ysf_memory_free,
    .memory.len                = ysf_memory_get_len,
    .memory.alignment          = ysf_memory_get_alignment,
    .memory.useRate            = ysf_memory_cal_use_rate,
    .memory.isIn               = ysf_memory_is_in,
#endif
    
#if defined(USE_YSF_EVENT_API) && USE_YSF_EVENT_API
    .event.init                = ysf_event_init,
    .event.post                = ysf_event_post,
    .event.read                = ysf_event_read,
    .event.reg                 = ysf_event_handler_register,
    .event.writeoff            = ysf_event_handler_writeoff,
    .event.handler             = ysf_event_handler,
#endif
    
#if defined(USE_YSF_TIMER_API) && USE_YSF_TIMER_API
    .timer.init                = ysf_timer_init,
    .timer.handler             = ysf_timer_handler,
    
    .timer.arm                 = ysf_timer_arm,
    .timer.disarm              = ysf_timer_disarm,
    
    .timer.getStatus           = ysf_timerGetStatus,

    .timer.ex.cb_init          = ysf_cbTimer_init,
    .timer.ex.evt_init         = ysf_evtTriggerTimer_init,
    .timer.ex.evt_dis_init     = ysf_evtDstrTimer_init,

    .timer.simple.cb_init      = ysf_cbSmpTimer_init,
    .timer.simple.evt_init     = ysf_evtTriggerSmpTimer_init,
    .timer.simple.evt_dis_init = ysf_evtDstrSmpTimer_init,
#endif

#if defined(USE_YSF_SIGNAL_API) && USE_YSF_SIGNAL_API
    .signal.init               = ysf_signal_init,
    .signal.handler            = ysf_signal_handler,

    .signal.simple.arm         = ysf_signalSimple_arm,
    .signal.simple.disarm      = ysf_signal_disarm,
    
    .signal.ex.arm             = ysf_signalEx_arm,
    .signal.ex.disarm          = ysf_signal_disarm,
#endif

#if defined(USE_YSF_DEBUG_API) && USE_YSF_DEBUG_API
    .debug.init                = ysf_debug_init,
    .debug.assert_failed       = ysf_assert_failed,
#endif

#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
    .task.init                 = ysf_task_init,
    .task.poll                 = ysf_task_poll,
    
    .task.evtCreate            = ysf_evtTask_create,
    .task.cbCreate             = ysf_cbTask_create,
#endif
};
#endif

/* Private functions ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf init
 * @param       [in/out]  *user_init     user init function
 * @return      [in/out]  void
 * @note        initialize ysf component
 *******************************************************************************
 */
void ysf_init( ysf_err_t (*user_init)(void) )
{
//    YSF_ENTER_CRITICAL();
//#if defined(USE_YSF_TICK_API) && USE_YSF_TICK_API
//    ysf.tick.init();
//    
//#if defined(USE_MSP_TIMER_API) && USE_MSP_TIMER_API
//    msp.timer.tick.init(ysf.tick.inc);
//#endif
//    
//#endif
//    
//#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
//    ysf.memory.init();
//#endif
//    
//#if defined(USE_YSF_EVENT_API) && USE_YSF_EVENT_API
//    ysf.event.init();
//#endif
//    
//#if defined(USE_YSF_TIMER_API) && USE_YSF_TIMER_API
//    ysf.timer.init();
//    ysf.event.reg(YSF_CORE_TICK_UPDATE, ysf_timer_handler);
//#endif
//    
//#if defined(USE_YSF_SIGNAL_API) && USE_YSF_SIGNAL_API
//    ysf.signal.init();
//#endif

//#if defined(USE_YSF_DEBUG_API) && USE_YSF_DEBUG_API
//    ysf.debug.init();
//#endif  

//#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
//    ysf.task.init();
//#endif
//    if(!IS_PTR_NULL(user_init))
//    {
//        user_init();
//    }
//    
//    YSF_EXIT_CRITICAL();
}

/**
 *******************************************************************************
 * @brief       ysf start
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        start ysf component
 *******************************************************************************
 */
void ysf_start(void)
{
    while(1)
    {
#if defined(USE_YSF_EVENT_API) && USE_YSF_EVENT_API
        YSF_ENTER_CRITICAL();
        ysf_event_handler();
        YSF_EXIT_CRITICAL();
#endif
    }
}

/** @}*/     /** ysf config */

/**********************************END OF FILE*********************************/
