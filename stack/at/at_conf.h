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
 * @brief      ysf hal conf head files                                         *
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
 * @defgroup ysf hal config
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
/**
 *******************************************************************************
 * @brief     CHIP CHECK
 *******************************************************************************
 */    
#ifndef __TARGET_CHIP__
    #define __TARGET_CHIP__ 
#endif
  
/**
 *******************************************************************************
 * @brief      INCLUDE HAL COMPONENT
 *******************************************************************************
 */    
//#if __TARGET_CHIP__ == USE_MCU_STM32F1xx
//    #define HAL_PATH "../framework/hal/stm32f1xx/hal.h"
//#else
//    #error "TARGET CHIP IS NOT CONFIG, PLEASE CONFIG IT!"
//#endif
    
/**
 *******************************************************************************
 * @brief      INCLUDE YSF DEBUG COMPONENT
 *******************************************************************************
 */
#if defined(USE_YSF_DEBUG_COMPONENT) && USE_YSF_DEBUG_COMPONENT
    #include "ysf_path.h"
    #include YSF_COMPONENT_DEBUG_PATH
#endif

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      DEFINE HAL COMPONENT CONFIG SWITCH
 *******************************************************************************
 */
#define USE_HAL_GPIO_COMPONENT                                               (1)
#define USE_HAL_TIMER_COMPONENT                                              (1)
#define USE_HAL_UART_COMPONENT                                               (1)

/**
 *******************************************************************************
 * @brief      DEFINE HAL ASSERT
 *******************************************************************************
 */
#if defined(USE_YSF_DEBUG_COMPONENT) && USE_YSF_DEBUG_COMPONENT
#define hal_assert(expr) ysf_assert(expr)
#else
#define hal_assert(expr) 
#endif

#ifndef IS_PTR_NULL
#define IS_PTR_NULL(ptr) ((ptr) == NULL)
#endif
 
/* Exported types ------------------------------------------------------------*/    
/**
 *******************************************************************************
 * @brief      DEFINE HAL ERROR TYPE
 *******************************************************************************
 */
typedef enum
{
    HAL_ERR_NONE,
    HAL_ERR_FAIL,

    HAL_ERR_INVAILD_PTR,
    HAL_ERR_INVAILD_PARAM,
}hal_err_t;

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal config  */

/**********************************END OF FILE*********************************/
