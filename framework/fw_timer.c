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
 * @file       fw_timer.c                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2016-07-09                                                      *
 * @brief      timer component source files                                    *
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
* @defgroup timer component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "fw_timer.h"
#include "fw_task.h"
#include "fw_tick.h"
#include "fw_linklist.h"
#include "fw_debug.h"
#include "fw_memory.h"

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      detect timer status
 *******************************************************************************
 */
#define IS_TIMER_DISABLE(timer)                            ((timer)->Cycle == 0)
#define IS_TIMER_ENABLE(timer)                             ((timer)->Cycle != 0)

/**
 *******************************************************************************
 * @brief      timer disable function
 *******************************************************************************
 */
#define TIMER_DISABLE(timer)                                ((timer)->Cycle = 0)

/* Private typedef -----------------------------------------------------------*/
#if USE_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief      timer control block
 *******************************************************************************
 */
struct Fw_Timer_Block
{
    struct
    {
        struct Fw_Timer *Head;
        struct Fw_Timer *Tail;
    }LinkList;

    uint8_t Num;
}static TimerBlock;

#endif

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief       init timer component
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_InitComponent(void)
{
    memset(&TimerBlock, 0, sizeof(TimerBlock));
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       create timer function
 * @param       [in/out]  void
 * @return      [in/out]  NO NULL     create success
 * @return      [in/out]  NULL        create failed
 * @note        None
 *******************************************************************************
 */
struct Fw_Timer *Fw_Timer_Create(void)
{
    return Fw_Mem_Alloc(_sizeof(struct Fw_Timer));
}

/**
 *******************************************************************************
 * @brief       init timer function
 * @param       [in/out]  *timer         timer block
 * @param       [in/out]  *str           timer name
 * @return      [in/out]  FW_ERR_NONE    create success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_Init(struct Fw_Timer *timer, char *str)
{
    _FW_ASSERT(IS_PTR_NULL(timer));
    
    Fw_dLinkList_Remove((struct Fw_dLinkList_Block *)&TimerBlock.LinkList,
                        (struct Fw_dLinkList*)&timer->LinkList);
    
    memset(timer, 0, sizeof(timer));
    
    timer->String = str;
	
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       deinit timer function
 * @param       [in/out]  *timer         timer block
 * @return      [in/out]  FW_ERR_NONE    deinit success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_Fini(struct Fw_Timer *timer)
{
    _FW_ASSERT(IS_PTR_NULL(timer));
    
    memset(timer, 0, sizeof(struct Fw_Timer));
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       set timer event
 * @param       [in/out]  *timer         timer block
 * @param       [in/out]  taskiId        post task id
 * @param       [in/out]  taskEvent      post task event
 * @return      [in/out]  FW_ERR_NONE    create success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_SetEvent(struct Fw_Timer *timer, struct Fw_Task *task, uint8_t taskEvent, void *taskParam)
{
    _FW_ASSERT(IS_PTR_NULL(timer));
    
    timer->Task      = task;
    timer->TaskEvent = taskEvent;
    timer->TaskParam = taskParam;

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       set timer call back
 * @param       [in/out]  *timer         timer block
 * @param       [in/out]  taskiId        post task id
 * @param       [in/out]  taskEvent      post task event
 * @return      [in/out]  FW_ERR_NONE    create success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_SetCallback(struct Fw_Timer *timer, void (*callback)(void*), void *callbackParam)
{
    _FW_ASSERT(IS_PTR_NULL(timer));
    
    timer->CallbackParam = callbackParam;
	timer->Callback      = callback;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       start timer function
 * @param       [in/out]  *timer         timer block
 * @param       [in/out]  tick           timing
 * @param       [in/out]  count          cycle count
 * @return      [in/out]  FW_ERR_NONE    create success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_Start(struct Fw_Timer *timer, uint32_t tick, int16_t count)
{
    _FW_ASSERT(IS_PTR_NULL(timer));
    
    timer->InitTick    = tick;
    timer->TimeOutTick = tick + Fw_Tick_GetInfo();
    timer->Cycle       = count;
    
    Fw_dLinkList_Push((struct Fw_dLinkList_Block *)&TimerBlock.LinkList,\
                      (struct Fw_dLinkList*)&timer->LinkList);

    TimerBlock.Num++;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       stop timer function
 * @param       [in/out]  *timer         timer block
 * @return      [in/out]  FW_ERR_NONE    create success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_Stop(struct Fw_Timer *timer)
{
    _FW_ASSERT(IS_PTR_NULL(timer));
    
    Fw_dLinkList_Remove((struct Fw_dLinkList_Block *)&TimerBlock.LinkList, \
                        (struct Fw_dLinkList*)&timer->LinkList);
    
    memset(timer, 0, sizeof(struct Fw_Timer));
    
    TimerBlock.Num--;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer delete function
 * @param       [in/out]  *timer         timer block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void TimerDelete(struct Fw_Timer *timer)
{
    //< 1. remove timer link list
    struct Fw_Timer **ctxTimer;

    if(TimerBlock.LinkList.Head == timer)
    {
        TimerBlock.LinkList.Head = timer->LinkList.Next;
    }
    else if(TimerBlock.LinkList.Tail == timer)
    {
        TimerBlock.LinkList.Tail = timer->LinkList.Last;
    }
    else
    {
        ctxTimer = (struct Fw_Timer **)&timer->LinkList.Last->LinkList.Next;
        *ctxTimer = timer->LinkList.Next;
    }

    //< 2. clear block link list param
	timer->LinkList.Last = NULL;
	timer->LinkList.Next = NULL;
	
    //< 3. sub timer num
    if(TimerBlock.Num > 0)
    {
        TimerBlock.Num--;
    }
}

/**
 *******************************************************************************
 * @brief       timer poll function
 * @param       [in/out]  *tickPtr       now tick pointer
 * @return      [in/out]  FW_ERR_NONE    create success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Timer_Poll(void *tickPtr)
{
    //< 1. init param
    uint8_t i;
    struct Fw_Timer *timer = TimerBlock.LinkList.Head;
    uint32_t tick = *((uint32_t *)tickPtr);
    
    _FW_ASSERT(IS_PTR_NULL(tickPtr));
    _FW_ASSERT(IS_PTR_NULL(timer));

    //< 2. poll timer
    for(i=0; i<TimerBlock.Num; i++)
    {
        //< 3. clear sleep timer
        if(timer->Cycle == 0)
        {
            TimerDelete(timer);
        }
        
        //< 4. detect timer is trigger
        if(timer->TimeOutTick <= tick)
        {			
            //< 5. detect timer is active
            if(timer->Cycle == FW_TIMER_CYCLE_MODE || --timer->Cycle)
            {
                timer->TimeOutTick = timer->InitTick + Fw_Tick_GetInfo();
            }
            else
            {
                TimerDelete(timer);
            }
            
            //< 6. called call back function
            if(!IS_PTR_NULL(timer->Callback))
            {
                timer->Callback(timer->CallbackParam);
            }
            
            //< 7. post event to task
            if(!IS_PTR_NULL(timer->Task))
            {
                Fw_Task_PostMessage(timer->Task, timer->TaskEvent, timer->TaskParam);
            }
            
            //< 8. clear timer block
            memset(timer, 0, sizeof(struct Fw_Timer));
        }
        
        //< 9. poll timer link list
        timer = timer->LinkList.Next;
    }
    
    return FW_ERR_NONE;
}

#endif

/** @}*/     /** ysf timer component */
 /**********************************END OF FILE*********************************/
