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
 * @file       fw_task.c                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-03-28                                                      *
 * @brief      task component source files                                     *
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
 * @defgroup framework task component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "fw_task.h"
#include "fw_debug.h"
#include "fw_linklist.h"
#include "fw_timer.h"

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       check param
 *******************************************************************************
 */
#define IS_TASK_PRIORITY_INVAILD(id)                       ((id) >= FW_TASK_MAX)
#define IS_TASK_QUEUE_INDEX_INVAILD(index)       ((index) >= FW_TASK_QUEUE_SIZE)

/**
 *******************************************************************************
 * @brief       check task event queue status
 *******************************************************************************
 */
#define Is_TaskEventQueue_Empty()                   (TaskBlock.Queue.Size <= 0)
#define Is_TaskEventQueue_Full()     (TaskBlock.Queue.Size >= FW_TASK_QUEUE_SIZE - 1)

/**
 *******************************************************************************
 * @brief       event memory use flag function
 *******************************************************************************
 */
#define SetEventQueueUseFlag(a, b, c)                   ClrBitMap((a), (b), (c))
#define ClrEvenrQueueUseFlag(a, b, c)                   SetBitMap((a), (b), (c))

/* Private typedef -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework task event block
 *******************************************************************************
 */
struct Fw_Task_Event
{
    struct
    {
        struct Fw_Task_Event *Next;
    }LinkList;
    
    void *Param;
    
    uint32_t Event;
    
    struct Fw_Task *Task;
};

/**
 *******************************************************************************
 * @brief       framework task management block
 *******************************************************************************
 */
struct Fw_TaskMgr
{
    struct
    {
        struct Fw_Task_Event *Head;
        struct Fw_Task_Event *Tail;
    }LinkList;
    
    uint8_t Num;
};

/* Private variables ---------------------------------------------------------*/
#if USE_TASK_COMPONENT
/**
 *******************************************************************************
 * @brief       framework task control block
 *******************************************************************************
 */
struct
{
    //< task block
    struct Fw_TaskMgr TaskMgrBlock[FW_TASK_MAX];
        
    //< task queue
    struct
    {
        struct Fw_Task_Event Event[FW_TASK_QUEUE_SIZE];
        
        uint8_t FreeSpaceTab[CalUseMemorySize(FW_TASK_QUEUE_SIZE)];
        uint32_t FreeSpaceGroup;
    }Queue;
    
    //< free count
    uint32_t FreeCount;
    uint32_t SetFreeCount;
    
}static TaskBlock;

/**
 *******************************************************************************
 * @brief       bit map
 *******************************************************************************
 */
const uint8_t EventQueueBitMap[] =
{
    /* 00 */ 0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 10 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 20 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 30 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 40 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 50 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 60 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 70 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 80 */ 7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 90 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* A0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* B0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* C0 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* D0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* E0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* F0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
};

#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_TASK_COMPONENT
/**
 *******************************************************************************
 * @brief       empty task handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
static void Fw_EmptyTask_Handle(void)
{
}

/**
 *******************************************************************************
 * @brief       init task component
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Task_InitComponent(void)
{
    //< init task data
    memset(&TaskBlock, 0, sizeof(TaskBlock));
    
    //< init event queue
    memset(&TaskBlock.Queue.FreeSpaceTab, 0xFF, sizeof(TaskBlock.Queue.FreeSpaceTab));
    memset(&TaskBlock.Queue.FreeSpaceGroup, 0xFF, sizeof(TaskBlock.Queue.FreeSpaceGroup));
}

/**
 *******************************************************************************
 * @brief       create new task
 * @param       [in/out]  taskId         task id
 * @param       [in/out]  str            task description
 * @param       [in/out]  handle         task function address
 * @param       [in/out]  type           task function type
 * @return      [in/out]  FW_ERR_NONE    create success
 * @note        None
 *******************************************************************************
 */
__INLINE fw_err_t Fw_Task_Init(struct Fw_Task *task, char *str, uint8_t priority, void *handle, enum _Fw_Task_Type type)
{
    _FW_ASSERT(IS_PTR_NULL(str));
    _FW_ASSERT(IS_PTR_NULL(handle));
    _FW_ASSERT(IS_TASK_PRIORITY_INVAILD(priority));

    task->Handle.Config = handle;
    task->Handle.Type   = type;
    task->Str           = str;
    task->Priority      = priority;
    task->Status        = 1;
    
    log("%s Create Success! \r\n", str);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       set memory is used
 * @param       [in/out]  offset      memory id
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void ClrBitMap(uint8_t offset, uint8_t *tab, uint32_t *group)
{
    uint8_t l = offset / 8;
    uint8_t r = offset % 8;

    tab[l] &= ~(1 << r);
    
    if(tab[l] == 0x00)
    {
        *group &= ~(1 << l);
    }
}

/**
 *******************************************************************************
 * @brief       set memory is unused
 * @param       [in/out]  offset      memory id
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void SetBitMap(uint8_t offset, uint8_t *tab, uint32_t *group)
{
    uint8_t l = offset / 8;
    uint8_t r = offset % 8;
    
    tab[l] |= 1 << r;
    *group |= 1 << l;
}

/**
 *******************************************************************************
 * @brief       get free memory address
 * @param       [in/out]  void
 * @return      [in/out]  address    event space address
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
struct Fw_Task_Event *EventAlloc(void)
{
    uint8_t x = EventQueueBitMap[TaskBlock.Queue.FreeSpaceGroup];
    uint8_t y = EventQueueBitMap[TaskBlock.Queue.FreeSpaceTab[x]];
    uint8_t prio = (x << 3) | y;
    
    if(prio >= FW_TASK_QUEUE_SIZE)
    {
        return NULL;
    }
    
    SetEventQueueUseFlag(prio, (uint8_t *)&TaskBlock.Queue.FreeSpaceTab, &TaskBlock.Queue.FreeSpaceGroup);
    return &TaskBlock.Queue.Event[prio];
}

/**
 *******************************************************************************
 * @brief       free memory
 * @param       [in/out]  *event     memory address
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void EventFree(struct Fw_Task_Event *event)
{
    uint32_t offset = (uint32_t)event - (uint32_t)&TaskBlock.Queue.Event;
    offset = offset / sizeof(struct Fw_Task_Event);
    
    ClrEvenrQueueUseFlag(offset, (uint8_t *)&TaskBlock.Queue.FreeSpaceTab, &TaskBlock.Queue.FreeSpaceGroup);
}

/**
 *******************************************************************************
 * @brief       write event block to event block
 * @param       [in/out]  *task       task block
 * @param       [in/out]  *message    message address
 * @param       [in/out]  event       trigger event
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void WriteTaskEventQueue(struct Fw_Task *task, uint32_t event, void *message)
{
    //< 1. check param
    struct Fw_Task_Event *nowNode = EventAlloc();
    struct Fw_TaskMgr *queue;
    
    _FW_ASSERT(IS_PTR_NULL(nowNode));
    _FW_ASSERT(IS_TASK_PRIORITY_INVAILD(task->Priority));
    
    //< 2. init queue
    queue = &TaskBlock.TaskMgrBlock[task->Priority];
    
    //< 3. update event info
    nowNode->Event = event;
    nowNode->Param = message;
    nowNode->Task  = task;
    
    //< 4. add event to queue
    Fw_sLinkList_Push((struct Fw_sLinkList_Block *)&queue->LinkList,
                      (struct Fw_sLinkList*)&nowNode->LinkList);
    
    //< 5. inc task wait handle event num
    if(queue->Num < 255)
    {
        queue->Num++;
    }
}

/**
 *******************************************************************************
 * @brief       read event from event queue about task
 * @param       [in/out]  *task          task block
 * @param       [in/out]  *event         get event buffer
 * @return      [in/out]  FW_ERR_NONE    no error
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
fw_err_t ReadTaskEventQueue(uint8_t priority, struct Fw_Task_Event **event)
{
    //< 1. check task is vaild
    _FW_ASSERT(IS_TASK_PRIORITY_INVAILD(priority));
    _FW_ASSERT(IS_PTR_NULL(event));
    
    //< 2. check queue is vaild
    struct Fw_TaskMgr *queue = &TaskBlock.TaskMgrBlock[priority];
    
    //< 3. get event
    Fw_sLinkList_Pop((struct Fw_sLinkList_Block *)&queue->LinkList,
                     (struct Fw_sLinkList**)event);
    
    //< 4. clear event count
    if(queue->Num > 0)
    {
        queue->Num--;
    }

    //< 5. free memory
    EventFree((struct Fw_Task_Event *)*event);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       post event
 * @param       [in/out]  taskId    task id
 * @param       [in/out]  event     post event
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Task_PostEvent(struct Fw_Task *task, uint32_t event)
{
    _FW_ASSERT(IS_PTR_NULL(task));

    if(task->Status == 0)
    {
        WriteTaskEventQueue(task, event, NULL);
    }
}

/**
 *******************************************************************************
 * @brief       post message
 * @param       [in/out]  taskId       task id
 * @param       [in/out]  *message     message address
 * @param       [in/out]  event        trigger event
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Task_PostMessage(struct Fw_Task *task, uint32_t event, void *message)
{
    _FW_ASSERT(IS_PTR_NULL(task));
    
    if(task->Status)
    {
        WriteTaskEventQueue(task, event, message);
    }
}


/**
 *******************************************************************************
 * @brief       sleep task handle
 * @param       [in/out]  taskId       task id
 * @return      [in/out]  true         sleep wake state
 * @return      [in/out]  false        not sleep state
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
bool Fw_SleepTask_Handle(uint8_t priority)
{
    if(priority >= FW_TASK_MAX)
    {
        if(TaskBlock.FreeCount < TaskBlock.SetFreeCount)
        {
            TaskBlock.FreeCount++;
        }
        else
        {
            //< wait done
            
            return true;
        }
    }
    else
    {
        TaskBlock.FreeCount = 0;
    }
    
    return false;
}

/**
 *******************************************************************************
 * @brief       task handle
 * @param       [in/out]  task         task block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void EventHandle(struct Fw_Task_Event *event)
{
    switch(event->Task->Handle.Type)
    {
        case FW_SIMPLE_TYPE_TASK:
            event->Task->Handle.Simple();
            break;
        case FW_CALL_BACK_TYPE_TASK:
            event->Task->Handle.CallBack(event->Param);
            break;
        case FW_EVENT_HANDLE_TYPE_TASK:
            event->Task->Handle.Event(event->Event);
            break;
        case FW_MESSAGE_HANDLE_TYPE_TASK:
            event->Task->Handle.Message(event->Event, event->Param);
            break;
        default:
            break;
    }
}

/**
 *******************************************************************************
 * @brief       task component dispatch function
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Task_Dispatch(void)
{
    uint8_t i;
    struct Fw_Task_Event *event = NULL;

    //< 1. find highest task
    for(i=0; i<FW_TASK_MAX; i++)
    {
        if(TaskBlock.TaskMgrBlock[i].Num > 0)
        {
            ReadTaskEventQueue(i, (struct Fw_Task_Event **)&event);
            break;
        }
    }
    
    //< 2. check task status
    if(Fw_SleepTask_Handle(i) == true)
    {
        return;
    }
    
    //< 3. event handle
    if(IS_PTR_NULL(event) && event->Task->Status == 0)
    {
        Fw_EmptyTask_Handle();
    }
    else
    {
        EventHandle(event);
    }
}

/**
 *******************************************************************************
 * @brief       start task dispatch
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Task_Enable(struct Fw_Task *task)
{
    _FW_ASSERT(IS_PTR_NULL(task));
    
    task->Status = 1;
}

/**
 *******************************************************************************
 * @brief       stop task dispatch
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_Task_Disable(struct Fw_Task *task)
{
    _FW_ASSERT(IS_PTR_NULL(task));
    
    task->Status = 0;
}

#endif

/** @}*/     /** framework task component */

/**********************************END OF FILE*********************************/
