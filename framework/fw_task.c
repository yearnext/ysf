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
#include _FW_MEMORY_COMPONENT_PATH
#include _FW_LINK_LIST_COMPONENT_PATH

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

/* Private typedef -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework task event block
 *******************************************************************************
 */
struct _Fw_Task_Event
{
    //< call back param
    void *Param;
    
    //< trigger event
    uint32_t Event;
        
    //< task id
    uint8_t TaskId;
    
    //< management component
//    uint8_t Last;
    uint8_t Next;
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

    //< task handle
    struct _Fw_Task_Handle Handle;
    
    //< user data
    void *UserData;
    
    //< trigger event num
    uint8_t EventCount;
    
    //< now task status
    bool Status;
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
    
    //< task queue
    struct
    {
        struct _Fw_Task_Event Event[FW_TASK_QUEUE_SIZE];
        
        uint8_t FreeSpaceTab[CalUseMemorySize(FW_TASK_MAX)];
        uint32_t FreeSpaceGroup;
        
        uint8_t Head;
        uint8_t Tail;
        uint8_t Size;
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
    /* F0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
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
    TaskBlock.Queue.FreeSpaceGroup = 0xFFFFFFFFUL;
    
    //< init task handle 
    for(i=0; i<FW_TASK_MAX; i++)
    {
        TaskBlock.Task[i].Handle.Type = FW_SIMPLE_TASK;
        TaskBlock.Task[i].Handle.Simple = EmptyTaskHandle;
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
    FW_Assert(IS_PTR_NULL(str));
    FW_Assert(IS_PTR_NULL(handle));
    FW_Assert(IS_INVAILD_TASK_ID(taskId));

    struct _Fw_Task_Block *nowTask     = &TaskBlock.Task[taskId];
    struct _Fw_Task_Handle *taskHandle = &TaskBlock.Task[taskId].Handle;

    taskHandle->Check = handle;
    taskHandle->Type  = type;
    
    nowTask->Name = str;
    
    nowTask->Status = true;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       delete task (disable task dispatch)
 * @param       [in/out]  taskId         task id
 * @return      [in/out]  FW_ERR_NONE    create success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_Task_Delete(uint8_t taskId)
{
    FW_Assert(IS_INVAILD_TASK_ID(taskId));
    
    struct _Fw_Task_Block *nowTask = &TaskBlock.Task[taskId];
    
    nowTask->Status = false;
    nowTask->EventCount = 0;
    nowTask->Name = NULL;
    nowTask->Handle.Type = FW_SIMPLE_TASK;
    nowTask->Handle.Simple = EmptyTaskHandle;
    
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
void SetEventQueueUseFlag(uint8_t offset)
{
    uint8_t l = offset / 8;
    uint8_t r = offset % 8;

    TaskBlock.Queue.FreeSpaceTab[l] &= ~(1 << r);
    
    if(TaskBlock.Queue.FreeSpaceTab[l] == 0x00)
    {
        TaskBlock.Queue.FreeSpaceGroup &= ~(1 << l);
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
void ClrEvenrQueueUseFlag(uint8_t offset)
{
    uint8_t l = offset / 8;
    uint8_t r = offset % 8;
    
    TaskBlock.Queue.FreeSpaceTab[l] |= 1 << r;
    TaskBlock.Queue.FreeSpaceGroup  |= 1 << l;
}

/**
 *******************************************************************************
 * @brief       get free memory id
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
uint8_t GetFreeEventSpace(void)
{
    uint8_t x = EventQueueBitMap[TaskBlock.Queue.FreeSpaceGroup];
    uint8_t y = EventQueueBitMap[TaskBlock.Queue.FreeSpaceTab[x]];
    uint8_t prio = (x << 3) | y;
    
    if(prio >= FW_TASK_QUEUE_SIZE)
    {
        return FW_TASK_QUEUE_SIZE;
    }
    
    return prio;
}

/**
 *******************************************************************************
 * @brief       write event block to event block
 * @param       [in/out]  taskId      task id
 * @param       [in/out]  *message    message address
 * @param       [in/out]  event       trigger event
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void WriteTaskEventQueue(uint8_t taskId, void *message, uint32_t event)
{
    //< 1. check the queue can write
    if(Is_TaskEventQueue_Full())
    {
        return;
    }

    uint8_t nextNode;
    struct _Fw_Task_Event *nowNode = &TaskBlock.Queue.Event[TaskBlock.Queue.Tail];
    
    //< 2. write event and message
    nowNode->Event = event;
    nowNode->Param = message;
    nowNode->TaskId = taskId;
    
    //< 3. add next node
    nextNode       = nowNode->Next;
    nowNode->Next  = GetFreeEventSpace();
    SetEventQueueUseFlag(nowNode->Next);
    
    //< 4. transfer next node
    TaskBlock.Queue.Tail = nowNode->Next;
    nowNode = &TaskBlock.Queue.Event[TaskBlock.Queue.Tail];
    
    //< 5. update next node space info
    nowNode->Next = nextNode;
    
    //< 6. inc task wait handle event num
    TaskBlock.Queue.Size++;
    TaskBlock.Task[taskId].EventCount++;
}

/**
 *******************************************************************************
 * @brief       read event from event queue about task
 * @param       [in/out]  taskId                            task id
 * @return      [in/out]  struct _Fw_Task_Event*            event address
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
struct _Fw_Task_Event* ReadTaskEventQueue(uint8_t taskId)
{
    //< 1. Check queue can read
    if(Is_TaskEventQueue_Empty())
    {
        return NULL;
    }
    
    uint8_t cursor = TaskBlock.Queue.Head;
    struct _Fw_Task_Event *nowNode = &TaskBlock.Queue.Event[cursor];
    struct _Fw_Task_Event *lastNode = nowNode;
    
    //< 2. find node
    while(1)
    {
        if(nowNode->TaskId == taskId)
        {
            break;
        }
        else
        {
            cursor = nowNode->Next;
            
            if(IS_INVAILD_TASK_QUEUE_INDEX(cursor))
            {
                return NULL;
            }
            else
            {
                lastNode = nowNode;
                nowNode = &TaskBlock.Queue.Event[cursor];
            }
        }
    }
    
    //< 3. delete node
    lastNode->Next = nowNode->Next;
    ClrEvenrQueueUseFlag(cursor);
    
    TaskBlock.Queue.Size--;
    TaskBlock.Task[taskId].EventCount--;
    
    return nowNode;
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
    FW_Assert(IS_VAILD_TASK_ID(taskId));

    WriteTaskEventQueue(taskId, (void *)(TaskBlock.Task[taskId]), event);
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
void Fw_Task_PostMessage(uint8_t taskId, void *message, uint32_t event)
{
    FW_Assert(IS_VAILD_TASK_ID(taskId));
    FW_Assert(IS_PTR_NULL(Msg));
    
    WriteTaskEventQueue(taskId, message, event);
}

/**
 *******************************************************************************
 * @brief       tsak component dispatch function
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void Fw_Task_Dispatch(void)
{
    uint8_t i;
    struct _Fw_Task_Event *event;
    struct _Fw_Task_Handle *task;

    //< 1. timer component handle
//    Fw_Timer_Poll();
    
    //< 2. find highest task
    for(i=0; i<FW_TASK_MAX; i++)
    {
        if(TaskBlock.Task[i].EventCount > 0)
        {
            task = &TaskBlock.Task[i].Handle;
            break;
        }
    }
    
    //< 3. check task status
    if(i == FW_TASK_MAX)
    {
        if(TaskBlock.FreeCount < TaskBlock.SetFreeCount)
        {
            TaskBlock.FreeCount++;
            
            return;
        }
        else
        {
            //< mcu sleep function
        }
    }
    
    //< 4. get task event
    event = ReadTaskEventQueue(i);
    
    //< 5. event handle
    switch(task->Type)
    {
        case FW_SIMPLE_TASK:
            task->Simple();
            break;
        case FW_CALL_BACK_TASK:
            task->CallBack(event->Param);
            break;
        case FW_EVENT_HANDLE_TASK:
            task->Event(event->Event);
            break;
        case FW_MESSAGE_HANDLE_TASK:
            task->Message(event->Param, event->Event);
            break;
        default:
            break;
    }
}

/**
 *******************************************************************************
 * @brief       start task component dispatch
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Task_StartDispatch(void)
{
    while(1)
    {
        Fw_Task_Dispatch();
    }
}

#endif

/** @}*/     /** framework task component */

/**********************************END OF FILE*********************************/
