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

/**
 *******************************************************************************
 * @brief      invaild define
 *******************************************************************************
 */
#else
	#error "The __TARGET_CHIP__ is not support type!"
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal config  */

/**********************************END OF FILE*********************************/
