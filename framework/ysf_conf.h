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
 * @file       ysf_conf.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-18                                                      *
 * @brief      ysf config head files                                           *
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
 * @defgroup ysf config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_CONF_H__
#define __YSF_CONF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf tick time(unit: ms)
 *******************************************************************************
 */
#define YSF_TICK_PERIOD_TIME        (10)
    
/**
 *******************************************************************************
 * @brief       EVENT PACKAGE
 *******************************************************************************
 */
#define _YSF_DEFINE_EVENT_START     enum ysf_evt_enum                          \
                                    {                                          \
                                        YSF_EVENT_NONE = 0,                    \
                                        YSF_PT_DELAY_EVENT,                   
                                        
#define _YSF_DEFINE_EVENT_END           YSF_EVENT_MAX,                         \
                                    };

/**
 *******************************************************************************
 * @brief       EVENT REGISTER FUNCTION
 *******************************************************************************
 */
#define RegistrarionEvent(event)    event,
                                    
/* YSF config ----------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       YSF COMPONENT CONFIG
 * @note        1             enable
 * @note        0             disable
 *******************************************************************************
 */
#define USE_STD_LIBRARY                                                      (0)
#define USE_YSF_BUFFER_COMPONENT                                             (1)
#define USE_YSF_DEBUG_COMPONENT                                              (1)
#define USE_YSF_EVENT_COMPONENT                                              (0)
#define USE_YSF_SINGLE_LIST_COMPONENT                                        (1)
#define USE_YSF_MEMORY_MANAGEMENT_COMPONENT                                  (1)
#define USE_YSF_SIGNAL_SCAN_COMPONENT                                        (1)
#define USE_YSF_TICK_COMPONENT                                               (1)
#define USE_YSF_TIMER_COMPONENT                                              (1)
#define USE_YSF_TASK_COMPONENT                                               (1)
#define USE_YSF_PROTOTHREADS_COMPONENT                                       (1)
                                                                        
/**
 *******************************************************************************
 * @brief      EVENTS DEFINE
 *******************************************************************************
 */
_YSF_DEFINE_EVENT_START
_YSF_DEFINE_EVENT_END	

/**
 *******************************************************************************
 * @brief       YSF VERSION CONFIG
 *******************************************************************************
 */
#define YSF_VERSION "YSF_DEBUG_0.0.2_201704052135"

/**
 *******************************************************************************
 * @brief       CHOOSE YOUR CHIP SERIES
 *******************************************************************************
 */
#define USE_MCU_STM32F1xx (1)
#define USE_MCU_STM8S     (2)

#define __TARGET_CHIP__   USE_MCU_STM32F1xx
        
/**
 *******************************************************************************
 * @brief      DEFINE CHIP NEED TO MACRO
 *******************************************************************************
 */
/* STM32F1xx config ----------------------------------------------------------*/
#if __TARGET_CHIP__ == USE_MCU_STM32F1xx
/**
 *******************************************************************************
 * @brief      DEFINE MCU CLOCK SPEED
 *******************************************************************************
 */
#define MCU_CLOCK_FREQ ((uint32_t)72000000) 
#define MCU_HSE_FREQ   ((uint32_t)8000000)  

/**
 *******************************************************************************
 * @brief      DEFINE MCU RAM SIZE
 *******************************************************************************
 */
#define MCU_SRAM_SIZE         64
#define MCU_SRAM_END_ADDR     ((uint32_t)((uint32_t)0x20000000 + MCU_SRAM_SIZE * 1024))

/**
 *******************************************************************************
 * @brief      DEFINE MCU CLOCK MODEL
 *******************************************************************************
 */
#define STM32F103xE
/* STM8S config --------------------------------------------------------------*/
#elif __TARGET_CHIP__ == USE_MCU_STM8S
    #define STM8S003
#else
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf config  */

/**********************************END OF FILE*********************************/
