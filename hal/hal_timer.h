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
 * @file       hal_timer.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-07                                                      *
 * @brief      hal timer component head files                                   *
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
 * @defgroup hal gpio component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_TIMER_COMPONENT_H__
#define __HAL_TIMER_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/  
#include "hal_core.h"

/* Exported macro ------------------------------------------------------------*/ 
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_MCU_TIMER_COMPONENT
    #define USE_TIMER_COMPONENT                                              (1)
  
/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
    #define USE_TIMER_COMPONENT                                              (1)
#endif

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define mcu timer id
 *******************************************************************************
 */ 
enum Define_Timer_ID
{
    MCU_TICK_TIMER = 0,
    MCU_TIMER_1,
    MCU_TIMER_2,
    MCU_TIMER_3,
    MCU_TIMER_4,
    MCU_TIMER_5,
    MCU_TIMER_6,
    MCU_TIMER_7,
    MCU_TIMER_8,
    MCU_TIMER_9,
    MCU_TIMER_10,
    MCU_TIMER_11,
    MCU_TIMER_12,
    MCU_TIMER_13,
    MCU_TIMER_14,
    MCU_TIMER_15,
    MCU_TIMER_16,
    MCU_TIMER_17,
};

/**
 *******************************************************************************
 * @brief      define timer mode
 *******************************************************************************
 */ 
enum Define_Timer_Mode
{
	TIMER_TICK_MODE,
	TIMER_TIME_MODE,
	TIMER_PWM_OUTPUT_MODE,
	TIMER_PWM_INTPUT_MODE,
};

/**
 *******************************************************************************
 * @brief      define map deivce timer structure
 *******************************************************************************
 */ 
struct Hal_Timer_Device
{
    struct HalCallback Callback;
    
    uint16_t Period;
	uint16_t Prescaler;

    uint8_t Port;
    uint8_t SetMode;
};
  
/**
 *******************************************************************************
 * @brief      define set timer time mode param structure
 *******************************************************************************
 */ 
struct Hal_Timer_Param
{
	uint16_t Period;
	uint16_t Prescaler;
    uint8_t Priority;
	struct HalCallback Callback;
};

/* Exported constants --------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal component interface  */

/**********************************END OF FILE*********************************/
