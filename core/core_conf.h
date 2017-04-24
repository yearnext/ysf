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
#define _CORE_VERSION                           "CORE_ALPHA_0.0.1_2017040132135"

/**
 *******************************************************************************
 * @brief       define core events
 *******************************************************************************
 */
#define __DEFINE_EVENT_BEGIN            typedef enum                           \
                                        {                                      \
                                            _EVENT_NONE = 0,                   \
                                            _EVENT_DELAY,                   
                                        
#define __DEFINE_EVENT_END                  _EVENT_MAX,                        \
                                        }_evt_t;

/**
 *******************************************************************************
 * @brief       REGISTER EVENTS FUNCTION
 *******************************************************************************
 */
#define __REG_EVENTS(event)                                               event,
                                    
/* Framework config ----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       core tick time(unit: ms)
 *******************************************************************************
 */
#define CORE_TICK_PERIOD                                                  (10UL)
    
/**
 *******************************************************************************
 * @brief       framwork component config flags
 * @note        1                       enable
 * @note        0                       disable
 *******************************************************************************
 */
#define USE_FRAMEWORK_COMPONENT_LIBRARY                                      (1)

/**
 *******************************************************************************
 * @brief      frameowrk component config <user config in>
 *******************************************************************************
 */
#if USE_FRAMEWORK_COMPONENT_LIBRARY
#define USE_FRAMEWORK_DEBUG                                                  (1)
#define USE_STD_LIBRARY_IN_FRAMEWORK_COMPONENT                               (0)

#define USE_FRAMEWORK_BUFFER_COMPONENT                                       (1)
#define USE_FRAMEWORK_DEBUG_COMPONENT                                        (1)
#define USE_FRAMEWORK_EVENT_COMPONENT                                        (0)
#define USE_FRAMEWORK_LINK_LIST_COMPONENT                                    (1)
#define USE_FRAMEWORK_MEMORY_MANAGEMENT_COMPONENT                            (1)
#define USE_FRAMEWORK_SIGNAL_SCAN_COMPONENT                                  (1)
#define USE_FRAMEWORK_TICK_COMPONENT                                         (1)
#define USE_FRAMEWORK_TIMER_COMPONENT                                        (1)
#define USE_FRAMEWORK_TASK_COMPONENT                                         (1)
#define USE_FRAMEWORK_PT_COMPONENT                                           (1)
#endif

/**
 *******************************************************************************
 * @brief      define use memory pool size
 *******************************************************************************
 */
#if !defined(USE_STD_LIBRARY_IN_FRAMEWORK_COMPONENT) || !USE_STD_LIBRARY_IN_FRAMEWORK_COMPONENT
#define FRAMEWORK_MEMORY_POOL_SIZE                                        (4096)

#if (FRAMEWORK_MEMORY_POOL_SIZE % 8)
#error "This memory pool is not 8 byte alignment!"
#endif

#endif

/**
 *******************************************************************************
 * @brief      define events
 *******************************************************************************
 */
__DEFINE_EVENT_BEGIN
/** register user events */

/** register user events */
__DEFINE_EVENT_END	

/* Hardware config -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define hal support mcu type
 *******************************************************************************
 */
#define USE_MCU_STM32F1xx                                                    (1)
#define USE_MCU_STM8S                                                        (2)

#define __TARGET_CHIP__                                        USE_MCU_STM32F1xx
       
/**
 *******************************************************************************
 * @brief      define constants must be defined
 *******************************************************************************
 */
/* STM32F1xx config ----------------------------------------------------------*/
#if __TARGET_CHIP__ == USE_MCU_STM32F1xx
/**
 *******************************************************************************
 * @brief      config MCU type
 * @note       STM32F100xB  STM32F100C4, STM32F100R4, STM32F100C6, STM32F100R6, \
                            STM32F100C8, STM32F100R8, STM32F100V8, STM32F100CB, \
                            STM32F100RB, STM32F100VB
 * @note       STM32F100xE  STM32F100RC, STM32F100VC, STM32F100ZC, STM32F100RD, \
                            STM32F100VD, STM32F100ZD, STM32F100RE, STM32F100VE,
                            STM32F100ZE
 * @note       STM32F101x6  STM32F101C4, STM32F101R4, STM32F101T4, STM32F101C6, \
                            STM32F101R6, STM32F101T6
 * @note       STM32F101xB  STM32F101C8, STM32F101R8, STM32F101T8, STM32F101V8, \
                            STM32F101CB, STM32F101RB, STM32F101TB, STM32F101VB
 * @note       STM32F101xE  STM32F101RC, STM32F101VC, STM32F101ZC, STM32F101RD, \
                            STM32F101VD, STM32F101ZD, STM32F101RE, STM32F101VE, \
                            STM32F101ZE
 * @note       STM32F101xG  STM32F101RF, STM32F101VF, STM32F101ZF, STM32F101RG, \
                            STM32F101VG, STM32F101ZG
 * @note       STM32F102x6  STM32F102C4, STM32F102R4, STM32F102C6, STM32F102R6
 * @note       STM32F102xB  STM32F102C8, STM32F102R8, STM32F102CB, STM32F102RB
 * @note       STM32F103x6  STM32F103C4, STM32F103R4, STM32F103T4, STM32F103C6, \
                            STM32F103R6, STM32F103T6
 * @note       STM32F103xB  STM32F103C8, STM32F103R8, STM32F103T8, STM32F103V8, \
                            STM32F103CB, STM32F103RB, STM32F103TB, STM32F103VB
 * @note       STM32F103xE  STM32F103RC, STM32F103VC, STM32F103ZC, STM32F103RD, \
                            STM32F103VD, STM32F103ZD, STM32F103RE, STM32F103VE, \
                            STM32F103ZE
 * @note       STM32F103xG  STM32F103RF, STM32F103VF, STM32F103ZF, STM32F103RG, \
                            STM32F103VG, STM32F103ZG
 * @note       STM32F105xC  STM32F105R8, STM32F105V8, STM32F105RB, STM32F105VB, \
                            STM32F105RC, STM32F105VC
 * @note       STM32F107xC  STM32F107RB, STM32F107VB, STM32F107RC, STM32F107VC
 *******************************************************************************
 */
#define STM32F103xE
#define USE_HAL_DRIVER	

/**
 *******************************************************************************
 * @brief      define mcu clock freq
 *******************************************************************************
 */
#define MCU_CLOCK_FREQ                                              (72000000UL) 
#define MCU_HSE_FREQ                                                 (8000000UL)  

/**
 *******************************************************************************
 * @brief      define mcu sram constants
 *******************************************************************************
 */
#define MCU_SRAM_SIZE                                                       (64)
#define MCU_SRAM_HEAD_ADDR                                        (0x20000000UL)
#define MCU_SRAM_END_ADDR            (MCU_SRAM_HEAD_ADDR + MCU_SRAM_SIZE * 1024)
	
/* STM8S config --------------------------------------------------------------*/
#elif __TARGET_CHIP__ == USE_MCU_STM8S
#define STM8S003
	
/**
 *******************************************************************************
 * @brief      define mcu clock freq
 *******************************************************************************
 */
#define MCU_CLOCK_FREQ                                              (16000000UL) 
#define MCU_HSE_FREQ                                                 (8000000UL)  

/**
 *******************************************************************************
 * @brief      define mcu sram constants
 *******************************************************************************
 */
#define MCU_SRAM_SIZE                                                        (1)
#define MCU_SRAM_HEAD_ADDR                                            (0x03FFUL)
#define MCU_SRAM_END_ADDR            (MCU_SRAM_HEAD_ADDR + MCU_SRAM_SIZE * 1024)

/**
 *******************************************************************************
 * @brief      invaild define
 *******************************************************************************
 */
#else
	#error "The __TARGET_CHIP__ is not support type!"
#endif

/**
 *******************************************************************************
 * @brief       define hal component config flags 
 * @note        1                         enable
 * @note        0                         disable
 *******************************************************************************
 */
#define USE_FRAMEWORK_HAL_LIBRARY                                            (1)

/**
 *******************************************************************************
 * @brief      hal component config <user config in>
 *******************************************************************************
 */
#if USE_FRAMEWORK_HAL_LIBRARY
#define USE_HAL_DEBUG                                                        (1)

#define USE_MCU_GPIO_COMPONENT                                               (1)
#define USE_MCU_TIMER_COMPONENT                                              (1)
#define USE_MCU_USART_COMPONENT                                              (1)
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** core config  */

/**********************************END OF FILE*********************************/
