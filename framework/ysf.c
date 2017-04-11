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
 * @file                              ysf.c                                    *
 * @author                          yearnext                                   *
 * @version                          1.0.0                                     *
 * @date                            2017-2-18                                  *
 * @brief                         ysf source file                              *
 * @par                            work platform                               *
 *                                    Windows                                  *
 * @par                          compiler platform                             *
 *                                      GCC                                    *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                  						                           *
 *******************************************************************************
 */

/**
 * @defgroup ysf config
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf.h"
#include "ysf_path.h"
#include YSF_COMPILER_PATH

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
    .init                       = ysf_init,
    .start                      = ysf_start,
    .ver                        = YSF_VERSION,
    
#if defined(USE_YSF_TICK_API) && USE_YSF_TICK_API
    .tick.init                  = ysf_tick_init,
    .tick.inc                   = ysf_tick_inc,
    .tick.read                  = ysf_tick_get,
    .tick.cal                   = ysf_past_tick_cal,
#endif
    
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
    .memory.init                = ysf_memory_init,
    .memory.malloc              = ysf_memory_malloc,
    .memory.free                = ysf_memory_free,
    .memory.is_in               = ysf_memory_is_in,
#endif
    
#if defined(USE_YSF_EVENT_API) && USE_YSF_EVENT_API
    .event.init                 = ysf_event_init,
    .event.post                 = ysf_event_post,
    .event.read                 = ysf_event_read,
#endif
    
#if defined(USE_YSF_TIMER_API) && USE_YSF_TIMER_API
    .timer.init                 = ysf_timer_init,
    .timer.handler              = ysf_timer_handler,
    
    .timer.arm                  = ysf_timer_arm,
    .timer.disarm               = ysf_timer_disarm,
    
    .timer.getStatus            = ysf_timerGetStatus,

    .timer.cb_init              = ysf_cbTimer_init,
    .timer.evt_init             = ysf_evtTimer_init,
    .timer.sm_init              = ysf_smTimer_init,
    
    .timer.simple.cb_init       = ysf_cbSimpTimer_init,
    .timer.simple.evt_init      = ysf_evtSimpTimer_init,
    .timer.simple.sm_init       = ysf_smSimpTimer_init,
#endif

#if defined(USE_YSF_SIGNAL_API) && USE_YSF_SIGNAL_API
    .signal.init                = ysf_signal_init,
    .signal.handler             = ysf_signal_handler,

    .signal.arm                 = ysf_evtSignal_arm,
    .signal.disarm              = ysf_signal_disarm,
    
    .signal.simple.arm          = ysf_evtSimpSignal_arm,
#endif

#if defined(USE_YSF_DEBUG_API) && USE_YSF_DEBUG_API
    .debug.init                 = ysf_debug_init,
    .debug.assert_failed        = ysf_assert_failed,
#endif

#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
    .task.init                  = ysf_task_init,
    .task.poll                  = ysf_task_poll,
    
    .task.create.cb             = ysf_cbTask_create,
    .task.create.evt            = ysf_evtTask_create,
    .task.create.sm             = ysf_smTask_create,
    
    .task.create.simple.cb      = ysf_cbSimpTask_create,
    .task.create.simple.evt     = ysf_evtSimpTask_create,
    .task.create.simple.sm      = ysf_smSimpTask_create,
#endif

#if defined(USE_YSF_PT_API) && USE_YSF_PT_API
    .pt.init                    = ysf_pt_init,
    
    .pt.disarm                  = ysf_pt_disarm,
    
    .pt.arm                     = ysf_pt_arm,
    .pt.simple.arm              = ysf_pt_simp_arm,
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
    YSF_ENTER_CRITICAL();
#if defined(USE_YSF_TICK_API) && USE_YSF_TICK_API
    ysf.tick.init();
    
#if defined(USE_MSP_TIMER_API) && USE_MSP_TIMER_API
    msp.timer.init.tick(YSF_TICK_PERIOD_TIME, ysf.tick.inc);
#endif
    
#endif
    
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
    ysf.memory.init();
#endif
    
#if defined(USE_YSF_EVENT_API) && USE_YSF_EVENT_API
    ysf.event.init();
#endif
    
#if defined(USE_YSF_TIMER_API) && USE_YSF_TIMER_API
    ysf.timer.init();
#endif
    
#if defined(USE_YSF_SIGNAL_API) && USE_YSF_SIGNAL_API
    ysf.signal.init();
#endif

#if defined(USE_YSF_DEBUG_API) && USE_YSF_DEBUG_API
    ysf.debug.init();
#endif  

#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
    ysf.task.init();
#endif
    if(!IS_PTR_NULL(user_init))
    {
        user_init();
    }
    
    YSF_EXIT_CRITICAL();
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
#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
        YSF_ENTER_CRITICAL();
        ysf_task_poll();
        YSF_EXIT_CRITICAL();
#endif
    }
}

/** @}*/     /** ysf config */

/**********************************END OF FILE*********************************/
