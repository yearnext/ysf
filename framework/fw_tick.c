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
#include "fw_tick.h"
#include "fw_task.h"
#include "fw_timer.h"
#include "hal_timer.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define tick variable
 *******************************************************************************
 */
#if USE_TICK_COMPONENT
static volatile uint32_t SystemTick = 0;
static struct Fw_Task Fw_Tick_Task;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void Fw_Tick_Handle(void *param);

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
void Fw_Tick_InitComponent(void)
{
    struct Hal_Timer_Device tickTimer;
    struct Hal_Timer_Config timerConfig;
        
    SystemTick = 0;
    
    Fw_Task_Init(&Fw_Tick_Task, "Framework Tick Task", 0, (void *)Fw_Timer_Poll, FW_CALL_BACK_TYPE_TASK);
    
    tickTimer.Port = MCU_TICK_TIMER;
    
    timerConfig.Callback.Callback = Fw_Tick_Handle;
    timerConfig.Callback.Param = NULL;
    timerConfig.Mode = TIMER_TICK_MODE;
    timerConfig.Period = 1;
    timerConfig.Prescaler = 1;
    timerConfig.Priority = 1;

    Hal_Timer_Init(&tickTimer, (void *)&timerConfig);
    Hal_Timer_Start(&tickTimer);
}

/**
 *******************************************************************************
 * @brief       tick value increase
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
static void Fw_Tick_Handle(void *param)
{
    SystemTick++;
    
    Fw_Task_PostMessage(&Fw_Tick_Task, FW_TICK_EVENT, (void *)&SystemTick);
}

/**
 *******************************************************************************
 * @brief       tick value get
 * @param       [in/out]  void
 * @return      [in/out]  tick    now tick
 * @note        None
 *******************************************************************************
 */
uint32_t Fw_Tick_GetInfo(void)
{
    return SystemTick;
}

/**
 *******************************************************************************
 * @brief       cal past tick
 * @param       [in/out]  lastTick    last tick
 * @param       [in/out]  nowTick     now tick
 * @return      [in/out]  uint32_t    tick
 * @note        None
 *******************************************************************************
 */
__INLINE uint32_t Fw_GetPastTick(uint32_t lastTick, uint32_t nowTick)
{
    uint32_t calTick;

    if (nowTick < lastTick)
    {
        calTick = UINT32_MAX - lastTick;
        calTick = calTick + nowTick;
    }
    else
    {
        calTick = nowTick - lastTick;
    }
    
    return calTick;
}

#endif
/** @}*/     /** framework tick component */

/**********************************END OF FILE*********************************/
