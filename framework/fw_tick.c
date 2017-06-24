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
 * @file       fw_tick.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework tick component source files
 * @par        paltform                                  
 *                 Windows
 * @par        compiler									                         
 * 			       GCC
 *******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 *******************************************************************************
 */

/**
 * @defgroup framework tick component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_tick.h"
#include "fw_event.h"
#include "fw_queue.h"
#include "fw_debug.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework tick
 *******************************************************************************
 */
static volatile uint32_t Tick = 0;

/**
 *******************************************************************************
 * @brief       framework tick
 *******************************************************************************
 */
//static uint32_t TickBuffer[10];

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       tick component init
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void InitTickComponent( void )
{
	Tick = 0;
    
//	Fw_Queue_Init(FW_TICK_QUEUE, (uint8_t *)&TickBuffer, CalTypeByteSize(TickBuffer));
}

/**
 *******************************************************************************
 * @brief       tick update
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void IncTick(void)
{
//    _ATOM_ACTIVE_BEGIN();
    
    Tick++;
    
    PostEvent(FW_TICK_TASK, FW_TICK_EVENT);
    
//    if(Fw_Queue_PutData(FW_TICK_QUEUE, (uint8_t *)&Tick, CalTypeByteSize(Tick)) == FW_ERR_FAIL)
//    {
//        log("Write Tick To Fifo Is Fail! \n");
//    }
    
//    _ATOM_ACTIVE_END();
}

/**
 *******************************************************************************
 * @brief       get tick
 * @param       [in/out]  void
 * @return      [in/out]  uint32_t    tick
 * @note        None
 *******************************************************************************
 */
uint32_t GetTick(void)
{
	return Tick;
}

/**
 *******************************************************************************
 * @brief       cal past tick
 * @param       [in/out]  void
 * @return      [in/out]  uint32_t    tick
 * @note        None
 *******************************************************************************
 */
uint32_t CalPastTick(void)
{
    static uint32_t lastTick = 0;
    uint32_t calTick;
    
    _ATOM_ACTIVE_BEGIN();
    
    if (Tick < lastTick)
    {
        calTick = UINT32_MAX - lastTick;
        calTick = calTick + Tick;
    }
    else
    {
        calTick = Tick - lastTick;
    }
    
    lastTick = Tick;
    
    _ATOM_ACTIVE_END();

    return calTick;
}


/** @}*/     /** framework tick component */

/**********************************END OF FILE*********************************/
