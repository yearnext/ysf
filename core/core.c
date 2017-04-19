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
const CoreInterface Core = 
{
    .Version                                           = _CORE_VERSION,
    .Init                                              = InitCoreScheduling,
    .Start                                             = StartCoreScheduling,
    
    .Component.Version                                 = _FRAMEWORK_VERSION,
    
#if USE_BUFFER_COMPONENT
    .Component.RingBuffer.Init                         = InitRingBufferComponent,
    .Component.RingBuffer.GetLen                       = GetRingBufferLen,
    .Component.RingBuffer.Write                        = WriteRingBuffer,
    .Component.RingBuffer.Read                         = ReadRingBuffer,
#endif
    
#if USE_DEBUG_COMPONENT
    .Component.Debug.Init                              = InitDebugComponent,
    .Component.Debug.AssertFailed                      = AssertFailed,
#endif
    
#if USE_EVENT_COMPONENT
    .Component.Event.Init                              = InitEventComponent,
    .Component.Event.Post                              = PostEvent,
    .Component.Event.Read                              = GetEvent,
#endif

#if USE_MEMORY_COMPONENT
    .Component.Memory.Init                             = InitMemoryComponent,
    .Component.Memory.Malloc                           = MallocMemory,
    .Component.Memory.Free                             = FreeMemory,
    .Component.Memory.IsIn                             = IsInMemory,
#endif
    
#if USE_SIGNAL_COMPONENT
    .Component.Signal.Init                             = InitSignalComponent,
    .Component.Signal.Handler                          = SignalComponentPool,
    .Component.Signal.Arm                              = ArmSignalModule,
    .Component.Signal.ArmEx                            = ArmSignalExModule,
    .Component.Signal.Disarm                           = DisarmSignalModule,
#endif   

#if USE_TICK_COMPONENT
    .Component.Tick.Init                               = InitTickComponent,
    .Component.Tick.Inc                                = IncTick,
    .Component.Tick.Read                               = GetTick,
    .Component.Tick.Cal                                = CalPastTick,
#endif

#if USE_TIMER_COMPONENT
    .Component.Timer.Init                              = InitTimerComponent,
    .Component.Timer.Handler                           = TimerComponentHandle,
    .Component.Timer.Arm                               = ArmTimerModule,
    .Component.Timer.Disarm                            = DisarmTimerModule,
    .Component.Timer.GetStatus                         = GetTimerStatus,
    .Component.Timer.CallBackInit                      = InitCallBackTimer,
    .Component.Timer.EventHandleInit                   = InitEventHandleTimer,
    .Component.Timer.MessageInit                       = InitMessageHandleTimer,
    .Component.Timer.CallBackExInit                    = InitCallBackExTimer,
    .Component.Timer.EventHandleExInit                 = InitEventHandleExTimer,
    .Component.Timer.MessageHandleExInit               = InitMessageHandleExTimer,
#endif

#if USE_TASK_COMPONENT
    .Component.Task.Init                               = InitTaskComponent,
    .Component.Task.Poll                               = TaskComponentPoll,
    .Component.Task.Add                                = AddTaskToQueue,
    .Component.Task.Create.CallBack                    = CreateCallBackTask,
    .Component.Task.Create.EventHandle                 = CreateEventHandleTask,
    .Component.Task.Create.MessageHandle               = CreateMessageHandleTask,
    .Component.Task.Create.CallBackEx                  = CreateCallBackExTask,
    .Component.Task.Create.EventHandleEx               = CreateEventHandleExTask,
    .Component.Task.Create.MessageHandleEx             = CreateMessageHandleExTask,
#endif

    .Hal.Version                                       = _HAL_VERSION,
    
#if USE_MAP_GPIO_COMPONENT
    .Hal.GPIO.Enable                                   = HalEnableGPIO,
    .Hal.GPIO.Disable                                  = HalDisableGPIO,
    .Hal.GPIO.Input.Init                               = HalInitGPIO,
    .Hal.GPIO.Input.Fini                               = HalDeinitGPIO,
    .Hal.GPIO.Input.Get                                = HalGetGPIOInputStatus,
    .Hal.GPIO.Output.Init                              = HalInitGPIO,
    .Hal.GPIO.Output.Fini                              = HalDeinitGPIO,
    .Hal.GPIO.Output.Get                               = HalGetGPIOOutputStatus,
    .Hal.GPIO.Output.Set                               = HalSetGPIO,
    .Hal.GPIO.Output.Clr                               = HalClrGPIO,
    .Hal.GPIO.Output.Toggle                            = HalToggleGPIO,
    .Hal.GPIO.Multi.Init                               = HalInitGPIO,
    .Hal.GPIO.Multi.Fini                               = HalDeinitGPIO,
#endif  

#if USE_MAP_TIMER_COMPONENT
    .Hal.Timer.Enable                                  = HalEnableTimer,
    .Hal.Timer.Disable                                 = HalDisableTimer,
    .Hal.Timer.Start                                   = HalStartTimer,
    .Hal.Timer.Stop                                    = HalStopTimer,
    .Hal.Timer.Init.Base                               = HalInitTimerBaseMode,
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
void InitCoreScheduling(void)
{
    __ENTER_CRITICAL();

#if USE_DEBUG_COMPONENT
    Core.Component.Debug.Init();
#endif
#if USE_TASK_COMPONENT
    Core.Component.Task.Init();
#endif  
    
#if USE_EVENT_COMPONENT
    Core.Component.Event.Init();
#endif
    
#if USE_FRAMEWORK_MEMORY_MANAGEMENT_COMPONENT
    Core.Component.Memory.Init();
#endif
    
#if USE_TIMER_COMPONENT
    Core.Component.Timer.Init();
#endif
    
#if USE_SIGNAL_COMPONENT
    Core.Component.Signal.Init();
#endif

#if USE_TICK_COMPONENT
    Core.Component.Tick.Init();
    
#if USE_MCU_TIMER_COMPONENT
    struct HalTimerBlock TickTimer = 
    {
        .ID = MCU_TICK_TIMER,
        .Period = TICK_PERIOD,
        .Handler = Core.Component.Tick.Inc,
    };
    
    Core.Hal.Timer.Init.Base(&TickTimer);
    Core.Hal.Timer.Start(&TickTimer);
#endif
    
#endif

    __EXIT_CRITICAL();
}

/**
 *******************************************************************************
 * @brief       start core scheduling
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void StartCoreScheduling(void)
{
    while(1)
    {
#if USE_TASK_COMPONENT
        __ATOM_ACTIVE_BEGIN();
        Core.Component.Task.Poll();
        __ATOM_ACTIVE_END();
#endif
    }
}

/** @}*/     /** framework core */

/**********************************END OF FILE*********************************/
