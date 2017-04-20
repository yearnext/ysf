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
#define fw_buffer_init                       Core.Component.RingBuffer.Init
#define fw_buffer_write                      Core.Component.RingBuffer.Write
#define fw_buffer_read                       Core.Component.RingBuffer.Read
#define fw_buffer_getlen                     Core.Component.RingBuffer.GetLen
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
#define fw_debug_init                        Core.Component.Debug.Init
#define fw_debug_assert                      Core.Component.Debug.AssertFailed
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
#define fw_event_init                        Core.Component.Event.Init
#define fw_event_post                        Core.Component.Event.Post
#define fw_event_get                         Core.Component.Event.Read
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
#define fw_memory_init                       Core.Component.Memory.Init
#define fw_memory_malloc                     Core.Component.Memory.Malloc
#define fw_memory_free                       Core.Component.Memory.Free
#define fw_memory_is_in                      Core.Component.Memory.IsIn
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
#define fw_signal_get_info                   Core.Component.Signal.GetInfo
#define fw_signal_arm                        Core.Component.Signal.Arm
#define fw_signal_disarm                     Core.Component.Signal.Disarm
#define fw_signal_simple_init                Core.Component.Signal.Create.Simple
#define fw_signal_complex_init               Core.Component.Signal.Create.Complex
#define fw_signal_simple_ex_init             Core.Component.Signal.Create.SimpleEx
#define fw_signal_complex_ex_init            Core.Component.Signal.Create.ComplexEx
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
#define fw_tick_init                         Core.Component.Tick.Init
#define fw_tick_inc                          Core.Component.Tick.Inc
#define fw_tick_get                          Core.Component.Tick.Read
#define fw_tick_cal                          Core.Component.Tick.Cal
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
#define fw_timer_init                        Core.Component.Timer.Init
#define fw_timer_poll                        Core.Component.Timer.Handler
#define fw_timer_arm                         Core.Component.Timer.Arm
#define fw_timer_disarm                      Core.Component.Timer.Disarm
#define fw_timer_get_status                  Core.Component.Timer.GetStatus
#define fw_timer_cb_type_init                Core.Component.Timer.Create.CallBack
#define fw_timer_evt_type_init               Core.Component.Timer.Create.EventHandle
#define fw_timer_msg_type_init               Core.Component.Timer.Create.Message
#define fw_timer_cb_ex_type_init             Core.Component.Timer.Create.CallBackEx
#define fw_timer_evt_ex_type_init            Core.Component.Timer.Create.EventHandleEx
#define fw_timer_msg_ex_type_init            Core.Component.Timer.Create.MessageHandleEx
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
#define fw_task_init                         Core.Component.Task.Init
#define fw_task_poll                         Core.Component.Task.Poll
#define fw_task_add                          Core.Component.Task.Add
#define fw_task_cb_type_create               Core.Component.Task.Create.CallBack
#define fw_task_evt_type_create              Core.Component.Task.Create.EventHandle
#define fw_task_msg_type_create              Core.Component.Task.Create.MessageHandle
#define fw_task_cb_ex_type_create            Core.Component.Task.Create.CallBackEx
#define fw_task_evt_ex_type_create           Core.Component.Task.Create.EventHandleEx
#define fw_task_msg_ex_type_create           Core.Component.Task.Create.MessageHandleEx
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
#if USE_MAP_GPIO_COMPONENT
#define hal_gpio_open                        Core.Hal.GPIO.Enable
#define hal_gpio_close                       Core.Hal.GPIO.Disable
#define hal_gpio_input_init                  Core.Hal.GPIO.Input.Init
#define hal_gpio_input_fini                  Core.Hal.GPIO.Input.Fini
#define hal_gpio_input_get                   Core.Hal.GPIO.Input.Get
#define hal_gpio_output_init                 Core.Hal.GPIO.Output.Init
#define hal_gpio_output_fini                 Core.Hal.GPIO.Output.Fini
#define hal_gpio_output_set                  Core.Hal.GPIO.Output.Set
#define hal_gpio_output_clr                  Core.Hal.GPIO.Output.Clr
#define hal_gpio_output_get                  Core.Hal.GPIO.Output.Get
#define hal_gpio_output_toggle               Core.Hal.GPIO.Output.Toggle
#else
#define hal_gpio_open                        
#define hal_gpio_close                    
#define hal_gpio_input_init                
#define hal_gpio_input_fini                
#define hal_gpio_input_get                
#define hal_gpio_output_init             
#define hal_gpio_output_fini               
#define hal_gpio_output_set                
#define hal_gpio_output_clr               
#define hal_gpio_output_get               
#define hal_gpio_output_toggle             
#endif

/**
 *******************************************************************************
 * @brief        define hal timer interface
 *******************************************************************************
 */
#if USE_MAP_TIMER_COMPONENT
#define hal_timer_open                       Core.Hal.Timer.Enable
#define hal_timer_close                      Core.Hal.Timer.Disable 
#define hal_timer_start                      Core.Hal.Timer.Start
#define hal_timer_stop                       Core.Hal.Timer.Stop
#define hal_timer_base_init                  Core.Hal.Timer.Init.Base
#else
#define hal_timer_open                      
#define hal_timer_close                  
#define hal_timer_start                    
#define hal_timer_stop                      
#define hal_timer_base_init                 
#endif

/* Private typedef -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        define core interface
 *******************************************************************************
 */
typedef struct 
{
    char *Version;
    
    void (*Init)(void);
    void (*Start)(void);
    
    FrameworkComponentInterface Component;

    FrameworkHalInterface       Hal;
}CoreInterface;
/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        core interface
 *******************************************************************************
 */
extern const CoreInterface Core;

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
