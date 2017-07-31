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
 * @file       fw_core.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework core component source files
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
 * @defgroup framework core component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"
#include "fw_event.h"
#include "fw_signal.h"
#include "fw_timer.h"
#include "fw_tick.h"
#include "fw_debug.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       user init function 
 *******************************************************************************
 */
__STATIC_INLINE __WEAK void InitUserComponent(void) {}

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       init framework core
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void Fw_Core_Init(void)
{
#ifdef USE_FRAMEWORK_TICK_COMPONENT
	Fw_Tick_InitComponent();
#endif

#ifdef USE_FRAMEWORK_EVENT_COMPONENT
	Fw_Event_InitComponent();
#endif

#ifdef USE_FRAMEWORK_TIMER_COMPONENT
	Fw_Timer_InitComponent();
#endif

#ifdef USE_FRAMEWORK_SIGNAL_COMPONENT
	Fw_Signal_InitComponent();
#endif

#ifdef USE_FRAMEWORK_DEBUG_COMPONENT
	Fw_Debug_InitComponent();
#endif
}

/**
 *******************************************************************************
 * @brief       start component core
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        never return
 *******************************************************************************
 */
//__STATIC_INLINE
//void Fw_Core_Start(void)
//{
//	for(;;) { Fw_Event_Poll(); }
//}

#define Fw_Core_Start() _ST(Fw_Event_Poll();)

/**
 *******************************************************************************
 * @brief       main function
 * @param       [in/out]  void
 * @return      [in/out]  0
 * @note        None
 *******************************************************************************
 */
int main(void)
{
    Fw_Core_Init();
	
	InitUserComponent();

	Fw_Core_Start();
}

/** @}*/     /** framework core component */

/**********************************END OF FILE*********************************/
