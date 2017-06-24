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
 * @file       fw_event.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework event component source files
 * @par        paltform                                  
 *                 Windows
 * @par        compiler									                         
 * 				   GCC
 *******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 *******************************************************************************
 */

/**
 * @defgroup framework event component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_event.h"
#include "fw_timer.h"
#include "fw_signal.h"
#include "fw_debug.h"

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       task size
 *******************************************************************************
 */
#define FW_TASK_MAX_SIZE                                       (3 * FW_TASK_MAX)

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       event handler
 * @note        user config
 *******************************************************************************
 */
#if USE_FRAMEWORK_EVENT_COMPONENT
struct
{
    void (*Handle)(uint8_t);
}static EventHandle[FW_TASK_MAX];
#endif

/**
 *******************************************************************************
 * @brief       framework event block
 *******************************************************************************
 */
#if USE_FRAMEWORK_EVENT_COMPONENT
static struct
{
    struct
    {
        uint8_t TaskId;
        uint8_t Event;
    }Buffer[FW_TASK_MAX_SIZE];
    
    uint8_t Tail;
    uint8_t Head;
}EventQueue;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_EVENT_COMPONENT
/**
 *******************************************************************************
 * @brief       event component init
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void InitEventComponent(void)
{
    uint8_t i;
    
    for(i=0; i<FW_TASK_MAX; i++)
    {
        EventHandle[i].Handle = NULL;
    }   
    
    for(i=0; i<FW_TASK_MAX_SIZE; i++)
    {
        EventQueue.Buffer[i].TaskId = FW_EVENT_NONE;
        EventQueue.Buffer[i].Event  = 0;
    }  
    
    EventQueue.Tail = 0;
    EventQueue.Head = 0;
}

/**
 *******************************************************************************
 * @brief       register event
 * @param       [in/out]  taskId       task id
 * @param       [in/out]  evtHandle    event handle function
 * @return      [in/out]  fw_err_t     register status
 * @note        None
 *******************************************************************************
 */
fw_err_t RegisterEvent(uint8_t taskId, void (*evtHandle)(uint8_t))
{
    if( IS_PTR_NULL(evtHandle) )
    {
        return FW_ERR_FAIL;
    }
    
    if(taskId >= FW_TASK_MAX)
    {
        return FW_ERR_FAIL;
    }
    
    EventHandle[taskId].Handle = evtHandle;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       event post
 * @param       [in/out]  task     task
 * @param       [in/out]  event    event
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
inline
void PostEvent(uint8_t taskId, uint8_t event)
{
	if(EventQueue.Tail < FW_TASK_MAX_SIZE)
	{
//        _ATOM_ACTIVE_BEGIN();
		EventQueue.Buffer[EventQueue.Tail].TaskId  = taskId;
		EventQueue.Buffer[EventQueue.Tail].Event = event;
		
		EventQueue.Tail++;
//        _ATOM_ACTIVE_END();
	}
}

/**
 *******************************************************************************
 * @brief       event poll
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
inline
void PollEvent(void)
{
    while(EventQueue.Head < EventQueue.Tail)
    {
        if( !IS_PTR_NULL(EventHandle[EventQueue.Buffer[EventQueue.Head].TaskId].Handle) )
        {
            EventHandle[EventQueue.Buffer[EventQueue.Head].TaskId].Handle(EventQueue.Buffer[EventQueue.Head].Event);
        }
        
        _ATOM_ACTIVE_BEGIN();
        if(++EventQueue.Head >= EventQueue.Tail)
        {
            EventQueue.Tail = 0;
            EventQueue.Head = 0;
        }  
        _ATOM_ACTIVE_END();
        
//        log("task num is %d! \n", EventQueue.Tail - EventQueue.Head);
    }
}
#endif

/** @}*/     /** framework event component */

/**********************************END OF FILE*********************************/
