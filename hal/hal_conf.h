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
 * @file       hal_conf.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-18                                                      *
 * @brief      hal conf head files                                             *
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
 * @defgroup hal config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_CONF_H__
#define __HAL_CONF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/    
#include "core_conf.h"
    
/* Exported types ------------------------------------------------------------*/   
/**
 *******************************************************************************
 * @brief       define hal version
 *******************************************************************************
 */
#define _HAL_VERSION                              "HAL_ALPHA_0.0.1_201704132135"
 
/**
 *******************************************************************************
 * @brief        debug hal assert configuration
 *******************************************************************************
 */
#ifdef USE_HAL_DEBUG
    #include "fw_debug.h"
    #define hal_param_check(expr)                               _FW_ASSERT(expr)
#else
    #define hal_param_check(expr)
#endif
    
#define hal_assert(expr)                                   hal_param_check(expr)
   
/**
 *******************************************************************************
 * @brief define hal support mcu type
 *******************************************************************************
 */
#define USE_MCU_STM32F1xx                                                    (1)
#define USE_MCU_STM8S                                                        (2)

#define __TARGET_CHIP__                                        USE_MCU_STM32F1xx
    
/* STM32F1xx config ----------------------------------------------------------*/
#if __TARGET_CHIP__ == USE_MCU_STM32F1xx
/**
 *******************************************************************************
 * @brief config MCU type
 * @note STM32F100xB STM32F100C4, STM32F100R4, STM32F100C6, STM32F100R6,       \
         STM32F100C8, STM32F100R8, STM32F100V8, STM32F100CB,                   \
         STM32F100RB, STM32F100VB
 * @note STM32F100xE STM32F100RC, STM32F100VC, STM32F100ZC, STM32F100RD,       \
         STM32F100VD, STM32F100ZD, STM32F100RE, STM32F100VE,
         STM32F100ZE
 * @note STM32F101x6 STM32F101C4, STM32F101R4, STM32F101T4, STM32F101C6,       \
         STM32F101R6, STM32F101T6
 * @note STM32F101xB STM32F101C8, STM32F101R8, STM32F101T8, STM32F101V8,       \
         STM32F101CB, STM32F101RB, STM32F101TB, STM32F101VB
 * @note STM32F101xE STM32F101RC, STM32F101VC, STM32F101ZC, STM32F101RD,       \
         STM32F101VD, STM32F101ZD, STM32F101RE, STM32F101VE,                   \
         STM32F101ZE
 * @note STM32F101xG STM32F101RF, STM32F101VF, STM32F101ZF, STM32F101RG,       \
         STM32F101VG, STM32F101ZG
 * @note STM32F102x6 STM32F102C4, STM32F102R4, STM32F102C6, STM32F102R6
 * @note STM32F102xB STM32F102C8, STM32F102R8, STM32F102CB, STM32F102RB
 * @note STM32F103x6 STM32F103C4, STM32F103R4, STM32F103T4, STM32F103C6,       \
         STM32F103R6, STM32F103T6
 * @note STM32F103xB STM32F103C8, STM32F103R8, STM32F103T8, STM32F103V8,       \
         STM32F103CB, STM32F103RB, STM32F103TB, STM32F103VB
 * @note STM32F103xE STM32F103RC, STM32F103VC, STM32F103ZC, STM32F103RD,       \
         STM32F103VD, STM32F103ZD, STM32F103RE, STM32F103VE,                   \
         STM32F103ZE
 * @note STM32F103xG STM32F103RF, STM32F103VF, STM32F103ZF, STM32F103RG,       \
         STM32F103VG, STM32F103ZG
 * @note STM32F105xC STM32F105R8, STM32F105V8, STM32F105RB, STM32F105VB,       \
         STM32F105RC, STM32F105VC
 * @note STM32F107xC STM32F107RB, STM32F107VB, STM32F107RC, STM32F107VC
 *******************************************************************************
 */

#define STM32F103xE
//#define USE_HAL_DRIVER

/**
 *******************************************************************************
 * @brief define mcu clock freq
 *******************************************************************************
 */
#define MCU_CLOCK_FREQ                                              (72000000UL) 
#define MCU_HSE_FREQ                                                 (8000000UL) 

/**
 *******************************************************************************
 * @brief define mcu sram constants
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
 * @brief define mcu clock freq
 *******************************************************************************
 */
#define MCU_CLOCK_FREQ                                              (16000000UL) 
#define MCU_HSE_FREQ                                                 (8000000UL) 

/**
 *******************************************************************************
 * @brief define mcu sram constants
 *******************************************************************************
 */
#define MCU_SRAM_SIZE                                                        (1)
#define MCU_SRAM_HEAD_ADDR                                            (0x03FFUL)
#define MCU_SRAM_END_ADDR            (MCU_SRAM_HEAD_ADDR + MCU_SRAM_SIZE * 1024)

/**
 *******************************************************************************
 * @brief invaild define
 *******************************************************************************
 */
#else
	#error "The __TARGET_CHIP__ is not support type!"
#endif

/**
 *******************************************************************************
 * @brief define hal component config flags 
 * @note     1     enable
 * @note     0     disable
 *******************************************************************************
 */
#define USE_FRAMEWORK_HAL_LIBRARY                                            (1)

/**
 *******************************************************************************
 * @brief hal component config <user config in>
 *******************************************************************************
 */
#if USE_FRAMEWORK_HAL_LIBRARY
#define USE_HAL_DEBUG
    
#define USE_MCU_GPIO_COMPONENT
#define USE_MCU_TIMER_COMPONENT
#define USE_MCU_UART_COMPONENT
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal config */

/**********************************END OF FILE*********************************/
