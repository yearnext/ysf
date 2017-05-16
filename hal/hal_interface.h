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
 * @file       hal_interface.h                                                 *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-18                                                      *
 * @brief      hal interface head files                                        *
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
 * @defgroup hal interface
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_INTERFACE_H__
#define __HAL_INTERFACE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/  
#include "core_path.h"
#include _HAL_PATH
#include _HAL_GPIO_PATH   
#include _HAL_TIMER_PATH    

/* Exported macro ------------------------------------------------------------*/ 
/**
 *******************************************************************************
 * @brief        define hal gpio interface
 *******************************************************************************
 */
#if USE_MAP_GPIO_COMPONENT
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
#if USE_MAP_TIMER_COMPONENT
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

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        define hal interface
 *******************************************************************************
 */
struct HalInterface
{
    char *Version;
    
#if USE_MAP_GPIO_COMPONENT
    MAP_GPIO_Interface GPIO;
#endif  

#if USE_MAP_TIMER_COMPONENT
    MAP_Timer_Interface Timer;
#endif
};

/* Exported constants --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        hal interface
 *******************************************************************************
 */ 
extern const struct HalInterface Hal;

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal interface  */

/**********************************END OF FILE*********************************/
