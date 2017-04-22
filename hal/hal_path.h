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
 * @file       hal_path.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-03-07                                                      *
 * @brief      hal path head files                                             *
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
 * @defgroup path
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_PATH_H__
#define __HAL_PATH_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Define hal component path-------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        common head files path
 *******************************************************************************
 */
#define _HAL_CORE_PATH                             "../hal/hal.h"
#define _HAL_CONF_PATH                             "../hal/hal_conf.h"
#define _HAL_TYPE_PATH                             "../hal/hal_type.h"
#define _HAL_INTERFACE_PATH                        "../hal/hal_interface.h"

/**
 *******************************************************************************
 * @brief        stm32f10x device head files path
 *******************************************************************************
 */
#define _HAL_STM32F10X_MAL_PATH                    "../hal/stm32f10x/stm32f10x.h"
#define _HAL_STM32F10X_GPIO_PATH                   "../hal/stm32f10x/msp_gpio.h"
#define _HAL_STM32F10X_TIMER_PATH                  "../hal/stm32f10x/msp_timer.h"
#define _HAL_STM32F10x_USART_PATH                  "../hal/stm32f10x/msp_usart.h"

/* Includes ------------------------------------------------------------------*/
#include _HAL_CONF_PATH
#include _HAL_TYPE_PATH

/* Define hal component path-------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        hal device head files path
 *******************************************************************************
 */
#if __TARGET_CHIP__ == USE_MCU_STM32F1xx
    #define _HAL_MAL_PATH                          _HAL_STM32F10X_MAL_PATH
    #define _HAL_GPIO_PATH                         _HAL_STM32F10X_GPIO_PATH
    #define _HAL_TIMER_PATH                        _HAL_STM32F10X_TIMER_PATH
	#define _HAL_USART_PATH                        _HAL_STM32F10X_USART_PATH
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal component path */

/**********************************END OF FILE*********************************/
