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
#include "core_path.h"
#include _FW_PATH
#include _FW_TASK_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH
#include _FW_LINK_LIST_COMPONENT_PATH
#include _FW_TIMER_COMPONENT_PATH

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       check param
 *******************************************************************************
 */
#define IS_INVAILD_TASK_ID(id)                             ((id) >= FW_TASK_MAX)
#define IS_INVAILD_TASK_QUEUE_INDEX(index)       ((index) >= FW_TASK_QUEUE_SIZE)

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
struct _Fw_Task_Event
{
    //< management component
    struct _Fw_Task_Event *Next;
    
    //< call back param
    void *Param;
    
    //< trigger event
    uint32_t Event;
};

/**
 *******************************************************************************
 * @brief       framework task block
 *******************************************************************************
 */
struct _Fw_Task_Block
{
    //< task name
    char *Name;

    //< user data
    void *UserData;
    
    //< task event queue
    struct _Fw_Task_Event_Queue
    {
        //< event queue management component
        struct _Fw_Task_Event *Head;
        struct _Fw_Task_Event *Tail;
        
        uint8_t Num;
    }EventQueue;
    
    //< task id
    uint8_t TaskId;
    
    //< task handle
    struct _Fw_Task_Handle Handle;
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
    struct _Fw_Task_Block Task[FW_TASK_MAX];
    
//    uint8_t TaskReadyTab[CalUseMemorySize(FW_TASK_MAX)];
//    uint32_t TaskReadyGroup;
    
    //< task queue
    struct
    {
        struct _Fw_Task_Event Event[FW_TASK_QUEUE_SIZE];
        
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
static void EmptyTaskHandle(void)
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
void Fw_Task_Init(void)
{
    uint8_t i;
    
    //< init task data
    memset(&TaskBlock, 0, sizeof(TaskBlock));
    
    //< init event queue
    memset(&TaskBlock.Queue.FreeSpaceTab, 0xFF, sizeof(TaskBlock.Queue.FreeSpaceTab));
    memset(&TaskBlock.Queue.FreeSpaceGroup, 0xFF, sizeof(TaskBlock.Queue.FreeSpaceGroup));
    
    //< init task handle 
    for(i=0; i<FW_TASK_MAX; i++)
    {
        TaskBlock.Task[i].Handle.Type   = FW_SIMPLE_TASK;
        TaskBlock.Task[i].Handle.Simple = EmptyTaskHandle;
        TaskBlock.Task[i].TaskId        = i;
    }
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
fw_err_t Fw_Task_Create(uint8_t taskId, char *str, void *handle, enum _Fw_Task_Type type)
{
    _FW_ASSERT(IS_PTR_NULL(str));
    _FW_ASSERT(IS_PTR_NULL(handle));
    _FW_ASSERT(IS_INVAILD_TASK_ID(taskId));

    struct _Fw_Task_Block *nowTask     = &TaskBlock.Task[taskId];
    struct _Fw_Task_Handle *taskHandle = &TaskBlock.Task[taskId].Handle;

    taskHandle->Check = handle;
    taskHandle->Type  = type;
    
    nowTask->Name = str;
    
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
struct _Fw_Task_Event *EventAlloc(void)
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
void EventFree(struct _Fw_Task_Event *event)
{
    uint32_t offset = (uint32_t)event - (uint32_t)&TaskBlock.Queue.Event;
    offset = offset / sizeof(struct _Fw_Task_Event);
    
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
void WriteTaskEventQueue(struct _Fw_Task_Block *task, void *message, uint32_t event)
{
    //< 1. check param
    struct _Fw_Task_Event *nowNode = EventAlloc();
    struct _Fw_Task_Event_Queue *queue;
    
    _FW_ASSERT(IS_PTR_NULL(task));
    _FW_ASSERT(IS_PTR_NULL(nowNode));
    
    //< 2. init queue
    queue = &task->EventQueue;
    
    //< 3. update event info
    nowNode->Event = event;
    nowNode->Param = message;
    
    //< 4. add event to queue
//    if(queue->Head == NULL && queue->Tail == NULL)
//    {
//        queue->Tail = nowNode;
//        queue->Head = nowNode;
//    }   
//    else
//    {
//        queue->Tail->Next = nowNode;
//        queue->Tail       = nowNode;
//    }
    p_PushLinkListNode(queue, nowNode);
    
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
fw_err_t ReadTaskEventQueue(struct _Fw_Task_Block *task, struct _Fw_Task_Event *event)
{
    //< 1. check task is vaild
    _FW_ASSERT(IS_PTR_NULL(task));

    //< 2. check queue is vaild
    struct _Fw_Task_Event_Queue *queue = &task->EventQueue;
    
    _FW_ASSERT(IS_PTR_NULL(queue->Head));
    _FW_ASSERT(IS_PTR_NULL(queue->Tail));
    
    //< 3. get event
    struct _Fw_Task_Event *getEvent = NULL;
    
//    if(queue->Head == queue->Tail)
//    {
//        getEvent = queue->Head;
//        
//        queue->Head = NULL;
//        queue->Tail = NULL;
//    }
//    else
//    {
//        getEvent = queue->Head;
//        queue->Head = getEvent->Next;
//    }
    p_PopLinkListNode(queue, getEvent);
    
    //< 4. clear event count
    if(queue->Num > 0)
    {
        queue->Num--;
    }
    
    //< 5. write to buffer
    event->Event = getEvent->Event;
    event->Param = getEvent->Param;
    
    //< 6. free memory
    getEvent->Next = NULL;
    EventFree(getEvent);
    
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
void Fw_Task_PostEvent(uint8_t taskId, uint32_t event)
{
    _FW_ASSERT(IS_INVAILD_TASK_ID(taskId));

    WriteTaskEventQueue(&TaskBlock.Task[taskId], (void *)(&TaskBlock.Task[taskId]), event);
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
void Fw_Task_PostMessage(uint8_t taskId, uint32_t event, void *message)
{
    _FW_ASSERT(IS_INVAILD_TASK_ID(taskId));
    _FW_ASSERT(IS_PTR_NULL(message));
    
    WriteTaskEventQueue(&TaskBlock.Task[taskId], message, event);
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
bool SleepTaskHandle(uint8_t taskId)
{
    if(taskId >= FW_TASK_MAX)
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
void TaskHandle(struct _Fw_Task_Block *task)
{
    struct _Fw_Task_Event event;

    if(ReadTaskEventQueue(task, &event) == FW_ERR_FAIL)
    {
        task->EventQueue.Num = 0;
        
        return;
    }
    
    switch(task->Handle.Type)
    {
        case FW_SIMPLE_TASK:
            task->Handle.Simple();
            break;
        case FW_CALL_BACK_TASK:
            task->Handle.CallBack(event.Param);
            break;
        case FW_EVENT_HANDLE_TASK:
            task->Handle.Event(event.Event);
            break;
        case FW_MESSAGE_HANDLE_TASK:
            task->Handle.Message(event.Param, event.Event);
            break;
        default:
            break;
    }
}

/**
 *******************************************************************************
 * @brief       tsak component dispatch function
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Task_Dispatch(void)
{
    uint8_t i;
    struct _Fw_Task_Block *task = NULL;

    //< 1. find highest task
    for(i=0; i<FW_TASK_MAX; i++)
    {
        if(TaskBlock.Task[i].EventQueue.Num > 0)
        {
            task = &TaskBlock.Task[i];
            break;
        }
    }
    
    //< 2. check task status
    if(SleepTaskHandle(i) == true)
    {
        return;
    }
    
    //< 3. task handle
    TaskHandle(task);
}

#endif

/** @}*/     /** framework task component */

/**********************************END OF FILE*********************************/
