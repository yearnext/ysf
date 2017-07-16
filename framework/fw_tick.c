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
void Fw_Tick_Init(void)
{
    SystemTick = 0;
}

/**
 *******************************************************************************
 * @brief       tick value increase
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Tick_Handle(void)
{
    SystemTick++;
    
    Fw_Task_PostMessage(FW_TICK_TASK, (void *)&SystemTick, FW_TICK_EVENT);
}

/**
 *******************************************************************************
 * @brief       tick value get
 * @param       [in/out]  void
 * @return      [in/out]  tick    now tick
 * @note        None
 *******************************************************************************
 */
uint32_t Fw_GetTick(void)
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
uint32_t Fw_GetPastTick(uint32_t lastTick, uint32_t nowTick)
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
