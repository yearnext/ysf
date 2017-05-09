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
 * @file       core.c                                                          * 
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      framework core source files                                     *
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
 * @defgroup framework core interface
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core.h"

/* Exported constants --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        core interface config
 *******************************************************************************
 */
const struct CoreInterface Core = 
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
    
    .Signal.Arm                                        = ArmSignalModule,
    .Signal.Disarm                                     = DisarmSignalModule,
    
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
    
    .Timer.Add                                         = AddTimerModuleToQueue,
    
    .Timer.Arm                                         = ArmTimerModule,
    .Timer.Disarm                                      = DisarmTimerModule,
    
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

/**
 *******************************************************************************
 * @brief        hal interface config
 *******************************************************************************
 */
const struct HalInterface Hal = 
{
    .Version                                           = _HAL_VERSION,
    
#if USE_MAP_GPIO_COMPONENT
    .GPIO.Open                                         = MAP_GPIO_Open,
    .GPIO.Close                                        = MAP_GPIO_Close,
    .GPIO.Init                                         = MAP_GPIO_Init,
    .GPIO.Fini                                         = MAP_GPIO_Deinit,
    .GPIO.Input.Get                                    = MAP_GPIO_GetInputStatus,
    .GPIO.Output.Get                                   = MAP_GPIO_GetOutputStatus,
    .GPIO.Output.Set                                   = MAP_GPIO_Set,
    .GPIO.Output.Clr                                   = MAP_GPIO_Clr,
    .GPIO.Output.Toggle                                = MAP_GPIO_Toggle,
    .GPIO.Output.Cmd                                   = MAP_GPIO_OutputCmd,
#endif  

#if USE_MAP_TIMER_COMPONENT
    .Timer.Open                                        = MAP_Timer_Open,
    .Timer.Close                                       = MAP_Timer_Close,
    .Timer.Start                                       = MAP_Timer_Start,
    .Timer.Stop                                        = MAP_Timer_Stop,
    .Timer.Base.Init                                   = MAP_TimerBase_Init,
    .Timer.Base.Arm                                    = MAP_TimerBase_Arm,
    .Timer.Base.HandleRegister                         = MAP_TimerBaseHandle_Register,
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
    hal_timer_base_arm(MCU_TICK_TIMER, TICK_PERIOD, fw_tick_inc, NULL);
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
