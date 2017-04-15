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
 * @file       core_conf.h                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      core config head files                                          *
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
 * @defgroup core config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CORE_CONF_H__
#define __CORE_CONF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/    
/* Define const config -------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define version
 *******************************************************************************
 */
#define _CORE_VERSION                   "CORE_ALPHA_0.0.1_2017040132135
#define _FRAMEWORK_VERSION              "FRAMEWORK_ALPHA_0.0.3_2017040132135"
#define _HAL_VERSION                    "HAL_ALPHA_0.0.1_201704132135"
#define _STACK_VERSION                  "STACK_ALPHA_0.0.1_201704132135"

/**
 *******************************************************************************
 * @brief       define core events
 *******************************************************************************
 */
#define __DEFINE_EVENT_START            typedef enum                           \
                                        {                                      \
                                            _EVENT_NONE = 0,                   \
                                            _PT_DELAY_EVENT,                   
                                        
#define __DEFINE_EVENT_END                  _EVENT_MAX,                        \
                                        }_evt_t;

/**
 *******************************************************************************
 * @brief       REGISTER EVENTS FUNCTION
 *******************************************************************************
 */
#define __REG_EVENTS(event)             event,
                                    
/* Framework config ----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       core tick time(unit: ms)
 *******************************************************************************
 */
#define _CORE_TICK_PERIOD               (10)
    
/**
 *******************************************************************************
 * @brief       framwork component config
 * @note        1             enable
 * @note        0             disable
 *******************************************************************************
 */
#define USE_STD_LIBRARY                                                      (0)
#define USE_FRAMEWORK_BUFFER_COMPONENT                                       (1)
#define USE_FRAMEWORK_DEBUG_COMPONENT                                        (1)
#define USE_FRAMEWORK_EVENT_COMPONENT                                        (0)
#define USE_FRAMEWORK_SINGLE_LIST_COMPONENT                                  (1)
#define USE_FRAMEWORK_MEMORY_MANAGEMENT_COMPONENT                            (1)
#define USE_FRAMEWORK_SIGNAL_SCAN_COMPONENT                                  (1)
#define USE_FRAMEWORK_TICK_COMPONENT                                         (1)
#define USE_FRAMEWORK_TIMER_COMPONENT                                        (1)
#define USE_FRAMEWORK_TASK_COMPONENT                                         (1)
#define USE_FRAMEWORK_PROTOTHREADS_COMPONENT                                 (1)
                                                                        
/**
 *******************************************************************************
 * @brief      define events
 *******************************************************************************
 */
__DEFINE_EVENT_START

__REG_EVENTS(_USER_EVENT)

__DEFINE_EVENT_END	

/* Hardware config -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define support mcu type
 *******************************************************************************
 */
#define USE_MCU_STM32F1xx                                                    (1)
#define USE_MCU_STM8S                                                        (2)

/**
 *******************************************************************************
 * @brief       define use mcu type
 *******************************************************************************
 */
#define __TARGET_CHIP__                                        USE_MCU_STM32F1xx
        
/**
 *******************************************************************************
 * @brief      define constants must be defined
 *******************************************************************************
 */
/* STM32F1xx config ----------------------------------------------------------*/
#if __TARGET_CHIP__ == USE_MCU_STM32F1xx
	#define STM32F103xE
	
/**
 *******************************************************************************
 * @brief      define mcu clock freq
 *******************************************************************************
 */
	#define MCU_CLOCK_FREQ                                          (72000000UL) 
	#define MCU_HSE_FREQ                                             (8000000UL)  

/**
 *******************************************************************************
 * @brief      define mcu sram constants
 *******************************************************************************
 */
	#define MCU_SRAM_SIZE                                                   (64)
	#define MCU_SRAM_HEAD_ADDR                                    (0x20000000UL)
	#define MCU_SRAM_END_ADDR        (MCU_SRAM_HEAD_ADDR + MCU_SRAM_SIZE * 1024)
	
/* STM8S config --------------------------------------------------------------*/
#elif __TARGET_CHIP__ == USE_MCU_STM8S
    #define STM8S003
	
/**
 *******************************************************************************
 * @brief      define mcu clock freq
 *******************************************************************************
 */
	#define MCU_CLOCK_FREQ                                          (16000000UL) 
	#define MCU_HSE_FREQ                                             (8000000UL)  

/**
 *******************************************************************************
 * @brief      define mcu sram constants
 *******************************************************************************
 */
	#define MCU_SRAM_SIZE                                                    (1)
	#define MCU_SRAM_HEAD_ADDR                                        (0x03FFUL)
	#define MCU_SRAM_END_ADDR        (MCU_SRAM_HEAD_ADDR + MCU_SRAM_SIZE * 1024)
#else
	#error "The __TARGET_CHIP__ is not support type!"
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** core config  */

/**********************************END OF FILE*********************************/