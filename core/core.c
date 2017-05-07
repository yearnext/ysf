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
    .Signal.GetInfo                                    = GetSignalInfo,
    .Signal.Arm                                        = ArmSignalModule,
    .Signal.Disarm                                     = DisarmSignalModule,
    .Signal.Create.Simple                              = InitSimpleSignalModule,
    .Signal.Create.Complex                             = InitComplexSignalModule,
    .Signal.Create.SimpleEx                            = InitSimpleExSignalModule,
    .Signal.Create.ComplexEx                           = InitComplexExSignalModule,
#endif   

#if USE_TICK_COMPONENT
    .Tick.Init                                         = InitTickComponent,
    .Tick.Inc                                          = IncTick,
    .Tick.Read                                         = GetTick,
    .Tick.Cal                                          = CalPastTick,
#endif

#if USE_TIMER_COMPONENT
    .Timer.Init                                        = InitTimerComponent,
    .Timer.Handler                                     = TimerComponentHandle,
    .Timer.Arm                                         = ArmTimerModule,
    .Timer.Disarm                                      = DisarmTimerModule,
    .Timer.GetStatus                                   = GetTimerStatus,
    .Timer.Create.CallBack                             = InitCallBackTimer,
    .Timer.Create.EventHandle                          = InitEventHandleTimer,
    .Timer.Create.Message                              = InitMessageHandleTimer,
    .Timer.Create.CallBackEx                           = InitCallBackExTimer,
    .Timer.Create.EventHandleEx                        = InitEventHandleExTimer,
    .Timer.Create.MessageHandleEx                      = InitMessageHandleExTimer,
#endif

#if USE_TASK_COMPONENT
    .Task.Init                                         = InitTaskComponent,
    .Task.Poll                                         = TaskComponentPoll,
    .Task.Add                                          = AddTaskToQueue,
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
    
#if USE_MSP_GPIO_COMPONENT
    .GPIO.Open                                         = MSP_GPIO_Open,
    .GPIO.Close                                        = MSP_GPIO_Close,
    .GPIO.Init                                         = MSP_GPIO_Init,
    .GPIO.Fini                                         = MSP_GPIO_Deinit,
    .GPIO.Input.Get                                    = MSP_GPIO_GetInputStatus,
    .GPIO.Output.Get                                   = MSP_GPIO_GetOutputStatus,
    .GPIO.Output.Set                                   = MSP_GPIO_Set,
    .GPIO.Output.Clr                                   = MSP_GPIO_Clr,
    .GPIO.Output.Toggle                                = MSP_GPIO_Toggle,
    .GPIO.Output.Cmd                                   = MSP_GPIO_OutputCmd,
#endif  

#if USE_MSP_TIMER_COMPONENT
    .Timer.Open                                        = MSP_Timer_Open,
    .Timer.Close                                       = MSP_Timer_Close,
    .Timer.Start                                       = MSP_Timer_Start,
    .Timer.Stop                                        = MSP_Timer_Stop,
    .Timer.Base.Init                                   = MSP_TimerBase_Init,
    .Timer.Base.Arm                                    = MSP_TimerBase_Arm,
    .Timer.Base.HandleRegister                         = MSP_TimerBaseHandle_Register,
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
        __ATOM_ACTIVE_BEGIN();
        fw_task_poll();
        __ATOM_ACTIVE_END();
#endif
    }
}

/** @}*/     /** framework core */

/**********************************END OF FILE*********************************/
