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
 * @file       fw_timer.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2016-07-09
 * @brief      framework timer component source files
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

/* Includes ------------------------------------------------------------------*/
#include "fw_timer.h"
#include "fw_queue.h"
#include "fw_debug.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       MACRO
 *******************************************************************************
 */
#define IsTimerEnable(timer)                                ((timer).Count != 0)

/**
 *******************************************************************************
 * @brief       MACRO
 *******************************************************************************
 */
#define DisableTimer(timer)                               _ST((timer).Count = 0;)

/* Private typedef -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework timer structure
 *******************************************************************************
 */
#if USE_FRAMEWORK_TIMER_COMPONENT
struct Timer_Block
{
	void     (*Hook)(uint8_t);
    uint32_t TimeOutTick;
    uint32_t Tick;
	int16_t  Count;
    uint8_t  TaskId;
    uint8_t  TaskEvent;
}static Timer[Timer_Max];
#endif

/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief       timer component init
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Timer_InitComponent(void)
{
    uint8_t i;
    
    for( i=0; i<Timer_Max; i++ )
    {
    	Timer[i].Hook        = NULL;
        Timer[i].TaskId      = 0;
        Timer[i].TimeOutTick = 0;
        Timer[i].Tick        = 0;
        Timer[i].Count       = 0;
        Timer[i].TaskEvent   = FW_EVENT_NONE;
    }
    
    Fw_Event_Register(FW_TICK_TASK, Fw_Timer_Poll);
}

/**
 *******************************************************************************
 * @brief       init timer
 * @param       [in/out]  timerId     timer id
 * @param       [in/out]  taskId      task id
 * @param       [in/out]  taskEvent   task event
 * @param       [in/out]  hook        hook function
 * @return      [in/out]  fw_err_t    init status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_Init(uint8_t timerId, uint8_t taskId, uint8_t taskEvent, void (*hook)(uint8_t))
{
    if(timerId >= Timer_Max)
    {
        return FW_ERR_FAIL;
    }

    if(taskId >= FW_TASK_MAX)
    {
        return FW_ERR_FAIL;
    }

    if(taskEvent >= FW_EVENT_MAX)
    {
        return FW_ERR_FAIL;
    }

    Timer[timerId].Hook      = hook;
    Timer[timerId].TaskEvent = taskEvent;
    Timer[timerId].TaskId    = taskId;

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       start timer
 * @param       [in/out]  timerId     timer id
 * @param       [in/out]  count       work count
 * @param       [in/out]  tick        set time
 * @return      [in/out]  fw_err_t    return start status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_Start(uint8_t timerId, int16_t count, uint32_t tick)
{
    if(timerId >= Timer_Max)
    {
        return FW_ERR_FAIL;
    }
    
//    _ATOM_ACTIVE_BEGIN();   
    
    if(!IsTimerEnable(Timer[timerId]))
    {
        Timer[timerId].Count = count;
        Timer[timerId].Tick  = tick;
        Timer[timerId].TimeOutTick = Timer[timerId].Tick;

        if(!IS_PTR_NULL(Timer[timerId].Hook))
        {
        	Timer[timerId].Hook(FW_BEGIN_EVENT);
        }
    }
    
//    _ATOM_ACTIVE_END();
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       force start timer
 * @param       [in/out]  timerId     timer id
 * @param       [in/out]  count       work count
 * @param       [in/out]  tick        set time
 * @return      [in/out]  fw_err_t    return start status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_ForceStart(uint8_t timerId, int16_t count, uint32_t tick)
{
    if(timerId >= Timer_Max)
    {
        return FW_ERR_FAIL;
    }

//    _ATOM_ACTIVE_BEGIN();    
    
    Timer[timerId].Count       = count;
    Timer[timerId].Tick        = tick;
    Timer[timerId].TimeOutTick = Timer[timerId].Tick;
    
    if(!IS_PTR_NULL(Timer[timerId].Hook))
    {
    	Timer[timerId].Hook(FW_BEGIN_EVENT);
    }

//    _ATOM_ACTIVE_END();
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       stop timer
 * @param       [in/out]  timerId     timer id
 * @return      [in/out]  fw_err_t    opera status
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_Stop(uint8_t timerId)
{
    if(timerId >= Timer_Max)
    {
        return FW_ERR_FAIL;
    }
    
//    _ATOM_ACTIVE_BEGIN();
    
    DisableTimer(Timer[timerId]);
    
//    _ATOM_ACTIVE_END();  
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get timer status
 * @param       [in/out]  timerId      timer id
 * @param       [in/out]  *status      now timer status
 * @return      [in/out]  fw_err_t     return flags
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_GetStatus(uint8_t timerId, int16_t *status)
{
    if(timerId >= Timer_Max)
    {
        return FW_ERR_FAIL;
    }

	*status = Timer[timerId].Count;

	return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer component handler
 * @param       [in/out]  event    trigger event
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Timer_Poll(uint8_t event)
{
    static uint32_t lastTick = 0;
    uint32_t nowTick = Fw_Tick_GetInfo();
    uint32_t tick = Fw_Tick_CalPastTick(lastTick, nowTick);
    uint8_t i;

    lastTick = nowTick;
    
    for(i=0; i<Timer_Max; i++)
    {        
        if(IsTimerEnable(Timer[i]))
        {
            if( Timer[i].TimeOutTick <= tick )
            {
            	if(Timer[i].Count > 0)
                {
                    --Timer[i].Count;
                }

                if(!IS_PTR_NULL(Timer[i].Hook))
                {
                	if(Timer[i].Count == 0)
                	{
                	    Timer[i].Hook(FW_END_EVENT);
                	}
					else
					{
						Timer[i].Hook(FW_TIMEOUT_EVENT);
					}
                }

                Timer[i].TimeOutTick = Timer[i].Tick;
                
                Fw_Event_Post(Timer[i].TaskId, Timer[i].TaskEvent); 
            }
            else
            {
                Timer[i].TimeOutTick -= tick;
            }
        }
    }
}
#endif

/** @}*/    /** framework event component */

/**********************************END OF FILE*********************************/
