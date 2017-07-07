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
 * @file       fw_timer.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2016-07-09
 * @brief      framework timer component head files
 * @par        paltform
 *                  Windows
 * @par        compiler
 *                  GCC
 *******************************************************************************
 * @note
 * 1.XXXXX
 *******************************************************************************
 */

/**
 * @defgroup framework timer component
 * @{
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_TIMER_H__
#define __FRAMEWORK_TIMER_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"
#include "fw_tick.h"
#include "fw_event.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       comp timer set time
 *******************************************************************************
 */
#define FW_TIME_SET(time)                                ((time)/FW_TICK_PREIOD)
  
/**
 *******************************************************************************
 * @brief       comp timer set time
 *******************************************************************************
 */
#define FW_TIMER_PERIOD_MODE                                                (-1)

/**
 *******************************************************************************
 * @brief       compatible the old framework timer apis
 *******************************************************************************
 */
#if USE_FRAMEWORK_TIMER_COMPONENT
#define ArmTimerModule(taskId, timerId, time)      _ST(Fw_Timer_Init(timerId, taskId, FW_DELAY_EVENT, NULL); \
	                                                   Fw_Timer_Start(timerId, 1, time);)

#define ForceArmTimerModule(taskId, timerId, time) _ST(Fw_Timer_Init(timerId, taskId, FW_DELAY_EVENT, NULL); \
		                                               Fw_Timer_ForceStart(timerId, 1, time);)

#define DisarmTimerModule(timerId)                 _ST(Fw_Timer_Stop(timerId);)
#else
#define ArmTimerModule(taskId, timerId, time)
#define ForceArmTimerModule(taskId, timerId, time)
#define DisarmTimerModule(timerId)
#endif
     
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       timer component api
 *******************************************************************************
 */
#if USE_FRAMEWORK_TIMER_COMPONENT
extern void     InitTimerComponent(void);
extern void     PollTimerComponent(uint8_t);

extern fw_err_t Fw_Timer_Init(uint8_t, uint8_t, uint8_t, void (*)(uint8_t));
extern fw_err_t Fw_Timer_Start(uint8_t, int16_t, uint32_t);
extern fw_err_t Fw_Timer_ForceStart(uint8_t, int16_t, uint32_t);
extern fw_err_t Fw_Timer_Stop(uint8_t);
extern fw_err_t Fw_Timer_GetStatus(uint8_t, int16_t*);
#endif

/* Define to prevent recursive inclusion -------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /* end include define */

/** @}*/    /** framework event component */

/**********************************END OF FILE*********************************/
