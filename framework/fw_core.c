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
 * @file       fw_core.c                                                       * 
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      framework core interface source files                           *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                  						                           *
 *******************************************************************************
 */

/**
 * @defgroup framework core interface
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_core.h"

/* Exported macro ------------------------------------------------------------*/ 
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
static volatile uint16_t SystemIsrLock = 0;

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       user application init
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__WEAK void App_User_Init(void)
{
    
}

/**
 *******************************************************************************
 * @brief       init core
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Core_Init(void)
{   
    //< init system isr lock
    SystemIsrLock = 0;
    
    Atom_Active_Begin();
    
#ifdef USE_FRAMEWORK_TASK_COMPONENT 
    Fw_Task_InitComponent();
#endif
    
#ifdef USE_FRAMEWORK_TICK_COMPONENT 
    Fw_Tick_InitComponent();
#endif
    
#ifdef USE_FRAMEWORK_TIMER_COMPONENT  
    Fw_Timer_InitComponent();
#endif

#ifdef USE_FRAMEWORK_MEMORY_MANAGEMENT_COMPONENT 
    Fw_Mem_InitComponent();
#endif

#ifdef USE_FRAMEWORK_DEBUG_COMPONENT
    Fw_Debug_InitComponent();
    Fw_Debug_PutMcuInfo();
#endif

    //< init user application
    App_User_Init();
    
    Atom_Active_End();
}

/**
 *******************************************************************************
 * @brief       start core
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Core_Start(void)
{
    for(;;)
    {
#ifdef USE_FRAMEWORK_TASK_COMPONENT
        Fw_Task_Dispatch();
#endif
    }
}

/**
 *******************************************************************************
 * @brief       enter critical
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Atom_Active_Begin(void)
{
    if(SystemIsrLock == 0)
    {
        __ATOM_ACTIVE_BEGIN();
        
        SystemIsrLock++;
    }
    else if(SystemIsrLock < 0xFFFF)
    {
        SystemIsrLock++;
    }
    else
    {
        //< do nothing!
    }
}

/**
 *******************************************************************************
 * @brief       exit critical
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Atom_Active_End(void)
{
    if(SystemIsrLock == 1)
    {
        SystemIsrLock--;
        
        __ATOM_ACTIVE_END();
    }
    else if(SystemIsrLock > 0)
    {
        SystemIsrLock--;
    }
    else
    {
        //< do nothing!
    }
}

#if USE_FRAMEWORK_COMPONENT
/**
 *******************************************************************************
 * @brief       main function
 * @param       [in/out]  void
 * @return      [in/out]  int     never return
 * @note        None
 *******************************************************************************
 */
int main(void)
{
    Fw_Core_Init();

    Fw_Core_Start();
    
    return 0;
}
#endif

void HardFault_Handler(void)
{
    return;
}

/** @}*/     /** framework core interface */

/**********************************END OF FILE*********************************/
