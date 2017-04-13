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
 * @file       ysf_tick.c                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      tick component source files                                     *
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
 * @defgroup ysf tick
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_TICK_COMPONENT_PATH
#include _FW_EVENT_COMPONENT_PATH
#include _FW_TASK_COMPONENT_PATH
#include _FW_TIMER_COMPONENT_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework tick
 *******************************************************************************
 */
#if USE_YSF_TICK_API
static ysf_tick_t tick = 0;
static struct ysf_task_t tick_task;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_TICK_API
/**
 *******************************************************************************
 * @brief       tick initialization
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void ysf_tick_init( void )
{
    tick = 0;
}

/**
 *******************************************************************************
 * @brief       tick value increase
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void ysf_tick_inc( void )
{
    ENTER_CRITICAL();
    tick++;
#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
    ysf_evtTask_create(&tick_task, ysf_timer_handler, YSF_EVENT_NONE);
#endif
    EXIT_CRITICAL();
}

/**
 *******************************************************************************
 * @brief       tick value get
 * @param       [in/out]  void
 * @return      [in/out]  ysf_tick_t    now tick
 * @note        None
 *******************************************************************************
 */
ysf_tick_t ysf_tick_get( void )
{
    return tick;
}

/**
 *******************************************************************************
 * @brief       calculate the distance past the previous read tick tick
 * @param       [in/out]  void
 * @return      [in/out]  ysf_tick_t    past tick
 * @note        None
 *******************************************************************************
 */
ysf_tick_t ysf_past_tick_cal( void )
{
	static ysf_tick_t lastTick = 0;
	ysf_tick_t calTick = 0;
	
	if( tick >= lastTick )
	{
		calTick = tick - lastTick;
	}
	else
	{
		calTick = YSF_TICK_MAX - lastTick;
		calTick = calTick + tick;
	}
	
	lastTick = tick;
	
	return calTick;
}

#endif
/** @}*/     /** ysf tick component */

/**********************************END OF FILE*********************************/
