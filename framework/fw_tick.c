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
 * @file       fw_tick.c                                                       *
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
 * @defgroup tick component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_TICK_COMPONENT_PATH
#include _FW_TASK_COMPONENT_PATH
#include _FW_TIMER_COMPONENT_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define tick variable
 *******************************************************************************
 */
#if USE_TICK_COMPONENT
static uint32_t         tick = 0;

static struct TaskBlock TickTask;

#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_TICK_COMPONENT
/**
 *******************************************************************************
 * @brief       tick initialization
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void InitTickComponent(void)
{
    tick = 0;
    InitSimpleTask(&TickTask, PollTimerComponent);
}

/**
 *******************************************************************************
 * @brief       tick value increase
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void IncTick(void)
{
    tick++;
    
#if defined(USE_TASK_COMPONENT) && USE_TASK_COMPONENT
    ArmTaskModule(&TickTask);
#endif
}

/**
 *******************************************************************************
 * @brief       tick value get
 * @param       [in/out]  void
 * @return      [in/out]  ysf_tick_t    now tick
 * @note        None
 *******************************************************************************
 */
uint32_t GetTick( void )
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
uint32_t CalPastTick( void )
{
	static uint32_t lastTick = 0;
	uint32_t calTick = 0;
	
	if( tick >= lastTick )
	{
		calTick = tick - lastTick;
	}
	else
	{
		calTick = TICK_VALUE_MAX - lastTick;
		calTick = calTick + tick;
	}
	
	lastTick = tick;
	
	return calTick;
}

#endif
/** @}*/     /** tick component */

/**********************************END OF FILE*********************************/
