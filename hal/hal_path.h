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
 * @brief        stm32f1xx mal head files path
 *******************************************************************************
 */
#define _HAL_STM32F1XX_MAL_PATH                    "../hal/stm32f1xx/mal/stm32f1xx.h"

/**
 *******************************************************************************
 * @brief        stm32f100 mal head files path
 *******************************************************************************
 */
#define _HAL_STM32F100XB_MAL_PATH                  "../hal/stm32f1xx/mal/stm32f100xb.h"
#define _HAL_STM32F100XE_MAL_PATH                  "../hal/stm32f1xx/mal/stm32f100xe.h"

/**
 *******************************************************************************
 * @brief        stm32f101 mal head files path
 *******************************************************************************
 */
#define _HAL_STM32F101X6_MAL_PATH                  "../hal/stm32f1xx/mal/stm32f101x6.h"
#define _HAL_STM32F101XB_MAL_PATH                  "../hal/stm32f1xx/mal/stm32f101xb.h"
#define _HAL_STM32F101XE_MAL_PATH                  "../hal/stm32f1xx/mal/stm32f101xe.h"
#define _HAL_STM32F101XG_MAL_PATH                  "../hal/stm32f1xx/mal/stm32f101xg.h"

/**
 *******************************************************************************
 * @brief        stm32f102 mal head files path
 *******************************************************************************
 */
#define _HAL_STM32F102X6_MAL_PATH                  "../hal/stm32f1xx/mal/stm32f102x6.h"
#define _HAL_STM32F102XB_MAL_PATH                  "../hal/stm32f1xx/mal/stm32f102xb.h"

/**
 *******************************************************************************
 * @brief        stm32f103 mal head files path
 *******************************************************************************
 */
#define _HAL_STM32F103X6_MAL_PATH                  "../hal/stm32f1xx/mal/stm32f103x6.h"
#define _HAL_STM32F103XB_MAL_PATH                  "../hal/stm32f1xx/mal/stm32f103xb.h"
#define _HAL_STM32F103XE_MAL_PATH                  "../hal/stm32f1xx/mal/stm32f103xe.h"
#define _HAL_STM32F103XG_MAL_PATH                  "../hal/stm32f1xx/mal/stm32f103xg.h"

/**
 *******************************************************************************
 * @brief        stm32f105 mal head files path
 *******************************************************************************
 */
#define _HAL_STM32F105XC_MAL_PATH                  "../hal/stm32f1xx/mal/stm32f105xc.h"

/**
 *******************************************************************************
 * @brief        stm32f107 mal head files path
 *******************************************************************************
 */
#define _HAL_STM32F107XC_MAL_PATH                  "../hal/stm32f1xx/mal/stm32f107xc.h"

/**
 *******************************************************************************
 * @brief        system_stm32f1xx head files path
 *******************************************************************************
 */
#define _HAL_STM32F1XX_SYSTEM_PATH                 "../hal/stm32f1xx/mal/system_stm32f1xx.h"

/**
 *******************************************************************************
 * @brief        stm32f1xx cmsis head files path
 *******************************************************************************
 */
#define _HAL_STM32F1XX_CMSIS_CM3_PATH              "../hal/stm32f1xx/mal/core_cm3.h"
#define _HAL_STM32F1XX_CMSIS_OS_PATH               "../hal/stm32f1xx/mal/core_os.h"
#define _HAL_STM32F1XX_CMSIS_MATH_PATH             "../hal/stm32f1xx/mal/core_cmFunc.h"
#define _HAL_STM32F1XX_CMSIS_COMM_TABLES_PATH      "../hal/stm32f1xx/mal/arm_common_tables.h"
#define _HAL_STM32F1XX_CMSIS_CONST_STRUCTS_PATH    "../hal/stm32f1xx/mal/arm_const_structs.h"
#define _HAL_STM32F1XX_CMSIS_FUNC_PATH             "../hal/stm32f1xx/mal/core_cmFunc.h"
#define _HAL_STM32F1XX_CMSIS_INSTR_PATH            "../hal/stm32f1xx/mal/core_cmInstr.h"
#define _HAL_STM32F1XX_CMSIS_SIMD_PATH             "../hal/stm32f1xx/mal/core_cmSimd.h"
#define _HAL_STM32F1XX_CMSIS_GCC_PATH              "../hal/stm32f1xx/mal/cmsis_gcc.h"
#define _HAL_STM32F1XX_CMSIS_ARMCC_PATH            "../hal/stm32f1xx/mal/cmsis_armcc.h"
#define _HAL_STM32F1XX_CMSIS_ARMCC6_PATH           "../hal/stm32f1xx/mal/cmsis_armcc_V6.h"

/**
 *******************************************************************************
 * @brief        stm32f1xx device head files path
 *******************************************************************************
 */
#define _HAL_STM32F1XX_GPIO_PATH                   "../hal/stm32f1xx/hal_gpio.h"
#define _HAL_STM32F1XX_TIMER_PATH                  "../hal/stm32f1xx/hal_timer.h"

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
    #define _HAL_GPIO_PATH                         _HAL_STM32F1XX_GPIO_PATH
    #define _HAL_TIMER_PATH                        _HAL_STM32F1XX_TIMER_PATH
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal component path */

/**********************************END OF FILE*********************************/
