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
 * @file       core.h                                                          *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      core head files                                                 *
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
 * @defgroup frameowrk core
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _FRAMEWORK_CORE_H__
#define _FRAMEWORK_CORE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
    
/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_INTERFACE_PATH
#include _HAL_PATH
#include _HAL_INTERFACE_PATH

/* Exported macro ------------------------------------------------------------*/ 
/**
 *******************************************************************************
 * @brief        define framework compiler function
 *******************************************************************************
 */
#define fw_enter_critical()                  __ENTER_CRITICAL()
#define fw_exit_critical()                   __EXIT_CRITICAL()
    
/**
 *******************************************************************************
 * @brief        define framework core interface
 *******************************************************************************
 */
#define fw_core_init                         Core.Init
#define fw_core_start                        Core.Start

/**
 *******************************************************************************
 * @brief        define framework buffer interface
 *******************************************************************************
 */
#if USE_BUFFER_COMPONENT
#define fw_buffer_init                       Core.RingBuffer.Init
#define fw_buffer_write                      Core.RingBuffer.Write
#define fw_buffer_read                       Core.RingBuffer.Read
#define fw_buffer_getlen                     Core.RingBuffer.GetLen
#else
#define fw_buffer_init                       
#define fw_buffer_write                      
#define fw_buffer_read                       
#define fw_buffer_getlen                   
#endif   

/**
 *******************************************************************************
 * @brief        define framework debug interface
 *******************************************************************************
 */
#if USE_DEBUG_COMPONENT
#define fw_debug_init                        Core.Debug.Init
#define fw_debug_assert                      Core.Debug.AssertFailed
#else
#define fw_debug_init                        
#define fw_debug_assert                      
#endif
  
/**
 *******************************************************************************
 * @brief        define framework event interface
 *******************************************************************************
 */  
#if USE_EVENT_COMPONENT
#define fw_event_init                        Core.Event.Init
#define fw_event_post                        Core.Event.Post
#define fw_event_get                         Core.Event.Read
#else
#define fw_event_init                        
#define fw_event_post                        
#define fw_event_get                         
#endif

/**
 *******************************************************************************
 * @brief        define framework memory interface
 *******************************************************************************
 */  
#if USE_MEMORY_COMPONENT
#define fw_memory_init                       Core.Memory.Init
#define fw_memory_malloc                     Core.Memory.Malloc
#define fw_memory_free                       Core.Memory.Free
#define fw_memory_is_in                      Core.Memory.IsIn
#else
#define fw_memory_init                       
#define fw_memory_malloc                     
#define fw_memory_free                      
#define fw_memory_is_in                    
#endif

/**
 *******************************************************************************
 * @brief        define framework signal interface
 *******************************************************************************
 */  
#if USE_SIGNAL_COMPONENT
#define fw_signal_get_info                   Core.Signal.GetInfo
#define fw_signal_arm                        Core.Signal.Arm
#define fw_signal_disarm                     Core.Signal.Disarm
#define fw_signal_simple_init                Core.Signal.Create.Simple
#define fw_signal_complex_init               Core.Signal.Create.Complex
#define fw_signal_simple_ex_init             Core.Signal.Create.SimpleEx
#define fw_signal_complex_ex_init            Core.Signal.Create.ComplexEx
#else
#define fw_signal_get_info                   
#define fw_signal_arm                        
#define fw_signal_disarm                     
#define fw_signal_simple_init                
#define fw_signal_complex_init               
#define fw_signal_simple_ex_init            
#define fw_signal_complex_ex_init            
#endif

/**
 *******************************************************************************
 * @brief        define framework tick interface
 *******************************************************************************
 */ 
#if USE_TICK_COMPONENT
#define fw_tick_init                         Core.Tick.Init
#define fw_tick_inc                          Core.Tick.Inc
#define fw_tick_get                          Core.Tick.Read
#define fw_tick_cal                          Core.Tick.Cal
#else
#define fw_tick_init                         
#define fw_tick_inc              
#define fw_tick_get           
#define fw_tick_cal        
#endif

/**
 *******************************************************************************
 * @brief        define framework timer interface
 *******************************************************************************
 */ 
#if USE_TIMER_COMPONENT
#define fw_timer_init                        Core.Timer.Init
#define fw_timer_poll                        Core.Timer.Handler
#define fw_timer_arm                         Core.Timer.Arm
#define fw_timer_disarm                      Core.Timer.Disarm
#define fw_timer_get_status                  Core.Timer.GetStatus
#define fw_timer_cb_type_init                Core.Timer.Create.CallBack
#define fw_timer_evt_type_init               Core.Timer.Create.EventHandle
#define fw_timer_msg_type_init               Core.Timer.Create.Message
#define fw_timer_cb_ex_type_init             Core.Timer.Create.CallBackEx
#define fw_timer_evt_ex_type_init            Core.Timer.Create.EventHandleEx
#define fw_timer_msg_ex_type_init            Core.Timer.Create.MessageHandleEx
#else
#define fw_timer_init                        
#define fw_timer_poll                 
#define fw_timer_arm                  
#define fw_timer_disarm                     
#define fw_timer_get_status                
#define fw_timer_cb_type_init              
#define fw_timer_evt_type_init             
#define fw_timer_msg_type_init              
#define fw_timer_cb_ex_type_init            
#define fw_timer_evt_ex_type_init       
#define fw_timer_msg_ex_type_init       
#endif

/**
 *******************************************************************************
 * @brief        define framework task interface
 *******************************************************************************
 */
#if USE_TASK_COMPONENT
#define fw_task_init                         Core.Task.Init
#define fw_task_poll                         Core.Task.Poll
#define fw_task_add                          Core.Task.Add
#define fw_task_cb_type_create               Core.Task.Create.CallBack
#define fw_task_evt_type_create              Core.Task.Create.EventHandle
#define fw_task_msg_type_create              Core.Task.Create.MessageHandle
#define fw_task_cb_ex_type_create            Core.Task.Create.CallBackEx
#define fw_task_evt_ex_type_create           Core.Task.Create.EventHandleEx
#define fw_task_msg_ex_type_create           Core.Task.Create.MessageHandleEx
#else
#define fw_task_init                         
#define fw_task_poll                         
#define fw_task_add                          
#define fw_task_cb_type_create               
#define fw_task_evt_type_create              
#define fw_task_msg_type_create             
#define fw_task_cb_ex_type_create            
#define fw_task_evt_ex_type_create           
#define fw_task_msg_ex_type_create           
#endif

/**
 *******************************************************************************
 * @brief        define framework protothreads interface
 *******************************************************************************
 */
#if USE_PT_COMPONENT
#define fw_pt_init                           _pt_init
#define fw_pt_deinit                         _pt_deinit
#define fw_pt_arm                            _pt_arm
#define fw_pt_arm_ex                         _pt_arm_ex
#define fw_pt_disarm                         _pt_disarm
#define fw_pt_begin                          _pt_begin
#define fw_pt_entry                          _pt_entry
#define fw_pt_wait                           _pt_wait
#define fw_pt_wfe                            _pt_wfe
#define fw_pt_delay                          _pt_delay
#define fw_pt_exit                           _pt_exit
#define fw_pt_end                            _pt_end
#else
#define fw_pt_init
#define fw_pt_deinit
#define fw_pt_arm
#define fw_pt_arm_ex
#define fw_pt_disarm
#define fw_pt_begin
#define fw_pt_entry
#define fw_pt_wait
#define fw_pt_wfe
#define fw_pt_delay
#define fw_pt_exit
#define fw_pt_end 
#endif

/**
 *******************************************************************************
 * @brief        define hal gpio interface
 *******************************************************************************
 */
#if USE_MSP_GPIO_COMPONENT
#define hal_gpio_open                        Hal.GPIO.Open
#define hal_gpio_close                       Hal.GPIO.Close
#define hal_gpio_init                        Hal.GPIO.Init
#define hal_gpio_fini                        Hal.GPIO.Fini
#define hal_gpio_input_get                   Hal.GPIO.Input.Get
#define hal_gpio_output_set                  Hal.GPIO.Output.Set
#define hal_gpio_output_clr                  Hal.GPIO.Output.Clr
#define hal_gpio_output_get                  Hal.GPIO.Output.Get
#define hal_gpio_output_toggle               Hal.GPIO.Output.Toggle
#define hal_gpio_output_cmd                  Hal.GPIO.Output.Cmd
#else
#define hal_gpio_open
#define hal_gpio_close
#define hal_gpio_init
#define hal_gpio_fini
#define hal_gpio_input_get
#define hal_gpio_output_set
#define hal_gpio_output_clr
#define hal_gpio_output_get
#define hal_gpio_output_toggle
#define hal_gpio_output_cmd      
#endif

/**
 *******************************************************************************
 * @brief        define hal timer interface
 *******************************************************************************
 */
#if USE_MSP_TIMER_COMPONENT
#define hal_timer_open                       Hal.Timer.Open
#define hal_timer_close                      Hal.Timer.Close 
#define hal_timer_start                      Hal.Timer.Start
#define hal_timer_stop                       Hal.Timer.Stop
#define hal_timer_base_init                  Hal.Timer.Base.Init
#define hal_timer_base_handle_register       Hal.Timer.Base.HandleRegister
#define hal_timer_base_arm                   Hal.Timer.Base.Arm
#else
#define hal_timer_open
#define hal_timer_close
#define hal_timer_start
#define hal_timer_stop
#define hal_timer_base_init
#define hal_timer_base_handle_register
#define hal_timer_base_arm
#endif

/* Private typedef -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        define core interface
 *******************************************************************************
 */
struct CoreInterface
{
    char *Version;
    
    void (*Init)(void);
    void (*Start)(void);
    
#if USE_BUFFER_COMPONENT
    RingBufferComponentInterface RingBuffer;
#endif

//#if USE_MEMORY_MANAGEMENT_COMPONENT
//    MemoryManagementComponentInterface MemoryManagement;
//#endif

#if USE_DEBUG_COMPONENT
    DebugComponentInterface Debug;
#endif
    
#if USE_EVENT_COMPONENT
    EventComponentInterface Event;
#endif

//#if USE_SINGLE_LIST_COMPONENT
//    SingleListComponentInterface SingleLinkList;
//#endif

#if USE_MEMORY_COMPONENT
    MemoryComponentInterface Memory;
#endif
    
#if USE_SIGNAL_COMPONENT
    SignalComponentInterface Signal;
#endif   

#if USE_TICK_COMPONENT
    TickComponentInterface Tick;
#endif

#if USE_TIMER_COMPONENT
    TimerComponentInterface Timer;
#endif

#if USE_TASK_COMPONENT
    TaskComponentInterfact Task;
#endif
};

/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        core interface
 *******************************************************************************
 */
extern const struct CoreInterface Core;
extern const struct HalInterface Hal;

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        core api
 *******************************************************************************
 */
void InitCoreScheduling(void);
void StartCoreScheduling(void);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework core interface */

/**********************************END OF FILE*********************************/
