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
 * @file       fw_interface.c                                                  * 
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      framework interface source files                                *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                  						                           *
 *******************************************************************************
 */

/**
 * @defgroup framework interface
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_interface.h"

/* Private functions ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        core api
 *******************************************************************************
 */
void InitFrameworkCore(void);
void StartFrameworkCore(void);

/* Exported constants --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        core interface config
 *******************************************************************************
 */
const struct FrameworkInterface Framework = 
{
    .Version                                           = _CORE_VERSION,
    .Init                                              = InitFrameworkCore,
    .Start                                             = StartFrameworkCore,

#if USE_BUFFER_COMPONENT
    .RingBuffer.Init                                   = InitRingBufferComponent,
    .RingBuffer.GetLen                                 = GetRingBufferLen,
    .RingBuffer.Write                                  = WriteRingBuffer,
    .RingBuffer.Read                                   = ReadRingBuffer,
#endif
    
#if USE_DEBUG_COMPONENT
    .Debug.Init                                        = InitDebugComponent,
    .Debug.AssertFailed                                = AssertFailed,
#endif
    
#if USE_EVENT_COMPONENT
    .Event.Init                                        = InitEventComponent,
    .Event.Post                                        = PostEvent,
    .Event.Read                                        = GetEvent,
#endif

#if USE_MEMORY_COMPONENT
    .Memory.Init                                       = InitMemoryComponent,
    .Memory.Malloc                                     = MallocMemory,
    .Memory.Free                                       = FreeMemory,
    .Memory.IsIn                                       = IsInMemory,
#endif
    
#if USE_SIGNAL_COMPONENT
    .Signal.Open                                       = InitSignalComponent,
    .Signal.Close                                      = DeinitSignalComponent,
    
    .Signal.Poll                                       = PoolSignalComponent,
    
    .Signal.Add                                        = AddSignalModuleToQueue,
    .Signal.Remove                                     = RemoveSignalModuleFromQueue,
    
    .Signal.Start                                      = StartSignalModule,
    .Signal.Stop                                       = StopSignalModule,
    
    .Signal.GetInfo                                    = GetSignalModuleInfo,
#endif   

#if USE_TICK_COMPONENT
    .Tick.Init                                         = InitTickComponent,
    .Tick.Inc                                          = IncTick,
    .Tick.Read                                         = GetTick,
    .Tick.Cal                                          = CalPastTick,
#endif

#if USE_TIMER_COMPONENT
    .Timer.Open                                        = InitTimerComponent,
    .Timer.Close                                       = DeinitTimerComponent,
    
    .Timer.Poll                                        = PollTimerComponent,
    
    .Timer.Start                                       = StartTimerModule,
    .Timer.Stop                                        = StopTimerModule,
    
    .Timer.Add                                         = AddTimerModuleToQueue,
    .Timer.Remove                                      = RemoveTimerModuleFromQueue,
    
    .Timer.GetStatus                                   = GetTimerModuleStatus,
    
    .Timer.Init.Simple                                 = InitSimpleTimerModule,
    .Timer.Init.CallBack                               = InitCallBackTimerModule,
    .Timer.Init.EventHandle                            = InitEventHandleTimerModule,
    .Timer.Init.MessageHandle                          = InitMessageHandleTimerModule,
#endif

#if USE_TASK_COMPONENT
    .Task.Open                                         = InitTaskComponent,
    .Task.Close                                        = DeinitTaskComponent,
    .Task.Poll                                         = PollTaskComponent,
    .Task.Arm                                          = ArmTaskModule,
    
    .Task.Init.Simple                                  = InitSimpleTask,
    .Task.Init.CallBack                                = InitCallBackTask,
    .Task.Init.EventHandle                             = InitEventHandleTask,
    .Task.Init.MessageHandle                           = InitMessageHandleTask,
    
    .Task.Create.Simple                                = CreateSimpleTask,
    .Task.Create.CallBack                              = CreateCallBackTask,
    .Task.Create.EventHandle                           = CreateEventHandleTask,
    .Task.Create.MessageHandle                         = CreateMessageHandleTask,
#endif
};

/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       core scheduling init
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void InitFrameworkCore(void)
{
    __ATOM_ACTIVE_BEGIN();

#if USE_DEBUG_COMPONENT
    fw_debug_init();
#endif
#if USE_TASK_COMPONENT
    fw_task_init();
#endif  
    
#if USE_EVENT_COMPONENT
   fw_event_init();
#endif
    
#if USE_FRAMEWORK_MEMORY_MANAGEMENT_COMPONENT
    fw_memory_init();
#endif
    
#if USE_TIMER_COMPONENT
    fw_timer_init();
#endif
    
#if USE_SIGNAL_COMPONENT
    InitSignalComponent();
#endif
    
#if USE_TICK_COMPONENT
    fw_tick_init();
    
#if USE_MCU_TIMER_COMPONENT
//    hal_timer_base_arm(MCU_TICK_TIMER, TICK_PERIOD, fw_tick_inc, NULL);
#endif
    
#endif

    __ATOM_ACTIVE_END();
}

/**
 *******************************************************************************
 * @brief       start core scheduling
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void StartFrameworkCore(void)
{
    while(1)
    {
#if USE_TASK_COMPONENT
        fw_task_poll();
#endif
    }
}

/** @}*/     /** framework core */

/**********************************END OF FILE*********************************/
