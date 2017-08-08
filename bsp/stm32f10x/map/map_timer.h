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
 * @file       map_timer.h                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-08                                                      *
 * @brief      mcu timer application component head files                      *
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
 * @defgroup map timer component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAP_TIMER_H__
#define __MAP_TIMER_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/  
#include "hal_path.h"
    
/* Exported macro ------------------------------------------------------------*/
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
 * @brief      define set timer time mode param structure
 *******************************************************************************
 */ 
struct TimerTimeModeConfig
{
	uint16_t Period;
	uint16_t Prescaler;
	struct HalCallback Callback;
};

/**
 *******************************************************************************
 * @brief      define map deivce timer structure
 *******************************************************************************
 */ 
struct HalTimerDevice
{
    struct HalCallback Callback;
    
    uint16_t Period;
	uint16_t Prescaler;

    uint8_t Port;
    uint8_t SetMode;
};

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define map api
 *******************************************************************************
 */ 
extern hal_err_t Map_Timer_Open(uint8_t);
extern hal_err_t Map_Timer_Close(uint8_t);
extern hal_err_t Map_Timer_Init(uint8_t, uint8_t, void*);
extern hal_err_t Map_Timer_SetUpCallback(uint8_t, void (*)(void*), void*);
extern hal_err_t Map_Timer_Start(uint8_t);
extern hal_err_t Map_Timer_Stop(uint8_t);

/**
 *******************************************************************************
 * @brief      define hal api
 *******************************************************************************
 */ 
extern __INLINE hal_err_t Hal_Timer_Open(struct HalTimerDevice*);
extern __INLINE hal_err_t Hal_Timer_Close(struct HalTimerDevice*);
extern __INLINE hal_err_t Hal_Timer_Init(struct HalTimerDevice*);
extern __INLINE hal_err_t Hal_Timer_SetUpCallback(struct HalTimerDevice*);
extern __INLINE hal_err_t Hal_Timer_Start(struct HalTimerDevice*);
extern __INLINE hal_err_t Hal_Timer_Stop(struct HalTimerDevice*);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** map timer component */

/**********************************END OF FILE*********************************/
