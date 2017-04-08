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
 * @file       hal.h                                                           *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-03-04                                                      *
 * @brief      hal head files                                                  *
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
 * @defgroup hal component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_HAL_H__
#define __YSF_HAL_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Hal path macro ------------------------------------------------------------*/
#define YSF_MAL_PATH          "../framework/hal/stm32f1xx/mal/stm32f1xx.h"
#define YSF_MSP_GPIO_PATH     "../framework/hal/stm32f1xx/gpio.h"
#define YSF_MSP_TIMER_PATH    "../framework/hal/stm32f1xx/timer.h"
#define YSF_MAL_CORE_CM3_PATH "../framework/hal/stm32f1xx/mal/cmsis/core_cm3.h"
#define YSF_MAL_START_UP_PATH "../framework/hal/stm32f1xx/startup/system_stm32f1xx.h"
   
/* Includes ------------------------------------------------------------------*/  
#include YSF_MAL_PATH
#include YSF_MSP_GPIO_PATH
#include YSF_MSP_TIMER_PATH

/* Exported macro ------------------------------------------------------------*/
#define USE_HAL_API (1)
    
/* Exported types ------------------------------------------------------------*/
#if USE_HAL_API
struct YSF_MSP_API
{
#if defined(USE_MSP_GPIO_API) && USE_MSP_GPIO_API
    struct MSP_GPIO_API gpio;
#endif
        
#if defined(USE_MSP_TIMER_API) && USE_MSP_TIMER_API
    struct MSP_TIMER_API timer;
#endif
};
    
struct YSF_MAP_API
{
#if defined(USE_MAP_GPIO_API) && USE_MAP_GPIO_API
    struct MAP_GPIO_API gpio;
#endif
        
#if defined(USE_MAP_TIMER_API) && USE_MAP_TIMER_API
    struct MAP_TIMER_API timer;
#endif
};
#endif

/* Exported variables --------------------------------------------------------*/
#if USE_HAL_API
extern const struct YSF_MSP_API msp;
extern const struct YSF_MAP_API map;
#endif

/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* hal component  */

/**********************************END OF FILE*********************************/
