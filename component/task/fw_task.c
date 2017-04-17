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
#include "core_path.h"
#include _FW_PATH
#include _FW_TASK_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH
#include _FW_MEMORY_COMPONENT_PATH
#include _FW_LINK_LIST_COMPONENT_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if USE_TASK_COMPONENT
/**
 *******************************************************************************
 * @brief       task control block
 *******************************************************************************
 */
static CREATE_SINGLE_LIST_FIFO_CONTROL_BLOCK(struct TaskBlock, TaskControlBlock);
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_TASK_COMPONENT
/**
 *******************************************************************************
 * @brief       detect the task is in queue
 * @param       [in/out]  task                 will detect task
 * @return      [in/out]  true                 the task in the queue
 * @return      [in/out]  true                 the task not in the queue
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
bool task_is_in(struct TaskBlock *task)
{
    IsInSingleLinkListFifo(struct TaskBlock, TaskControlBlock, task);
    
    return false;
}

/**
 *******************************************************************************
 * @brief       pop task to queue
 * @param       [in/out]  task                 will add task
 * @return      [in/out]  FW_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
fw_err_t task_push(struct TaskBlock *task)
{
    SingleLinkListFifoPush(task_is_in, TaskControlBlock, task);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       push task from queue
 * @param       [in/out]  void
 * @return      [in/out]  struct TaskBlock *     push task addr in memory
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
struct TaskBlock *task_pop(void)
{
    struct TaskBlock *task;
    
    SingleLinkListFifoPop(TaskControlBlock, task);
    
    return task;
}

/**
 *******************************************************************************
 * @brief       task queue clear
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
fw_err_t task_clear(void)
{    
    ClearSingleLinkListFifo(task_pop);

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       task component init
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE       init finish
 * @note        None
 *******************************************************************************
 */
fw_err_t TaskComponentInit(void)
{
    task_clear();
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       add task to task queue
 * @param       [in/out]  *task                     task block
 * @param       [in/out]  *func                     task function
 * @param       [in/out]  *param                    task param
 * @return      [in/out]  FW_ERR_INVAILD_PTR       add failed
 * @return      [in/out]  FW_ERR_NONE              add success
 * @note        None
 *******************************************************************************
 */
fw_err_t CreateCallBackTask(struct TaskBlock *task, fw_err_t (*func)(void*), void *param)
{
    if(IS_PTR_NULL(task) || IS_PTR_NULL(func))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    task->Handler.CallBack = func;
    task->Param      = param;
    task->Type       = CALL_BACK_TASK;
    
//    task->Next       = NULL;
    task_push(task);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       add task to task queue
 * @param       [in/out]  *task                     task block
 * @param       [in/out]  *func                     task function
 * @param       [in/out]  event                     task event
 * @return      [in/out]  FW_ERR_INVAILD_PTR       add failed
 * @return      [in/out]  FW_ERR_NONE              add success
 * @note        None
 *******************************************************************************
 */
fw_err_t CreateEventHandleTask(struct TaskBlock *task, fw_err_t (*func)(uint16_t), uint16_t evt)
{
    if(IS_PTR_NULL(task) || IS_PTR_NULL(func))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    task->Handler.Event = func;
    task->Event         = evt;
    task->Type          = EVENT_HANDLE_TASK;
    
//    task->Next         = NULL;
    task_push(task);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       add task to task queue
 * @param       [in/out]  *task                     task block
 * @param       [in/out]  *func                     task function
 * @param       [in/out]  *param                    task param
 * @param       [in/out]  *expand                   task expand param
 * @return      [in/out]  FW_ERR_INVAILD_PTR       add failed
 * @return      [in/out]  FW_ERR_NONE              add success
 * @note        None
 *******************************************************************************
 */
fw_err_t CreateMessageHandleTask(struct TaskBlock *task, fw_err_t (*func)(void*, uint16_t), void *param, uint16_t evt)
{
    if(IS_PTR_NULL(task) || IS_PTR_NULL(func))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    task->Handler.Message = func;
    task->Param           = param;
    task->Event           = evt;
    task->Type            = MESSAGE_HANDLE_TASK;
    
//    task->Next   = NULL;
    task_push(task);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       add task to task queue
 * @param       [in/out]  *func                     task function
 * @param       [in/out]  *param                    task param
 * @return      [in/out]  NULL                      add failed
 * @return      [in/out]  ARRDESS                   add success
 * @note        None
 *******************************************************************************
 */
struct TaskBlock *CreateCallBackExTask(fw_err_t (*func)(void*), void *param)
{
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    if(IS_PTR_NULL(func))
    {
        return NULL;
    }
    
    struct TaskBlock *task = (struct TaskBlock *)MemoryMalloc(sizeof(struct TaskBlock));
     
    if(IS_PTR_NULL(task))
    {
        return NULL;
    }
    
    task->Handler.CallBack = func;
    task->Param            = param;
    task->Type             = CALL_BACK_EX_TASK;
    
//    task->Next         = NULL;
    task_push(task);
    
    return task;
#else
    return NULL;
#endif
}

/**
 *******************************************************************************
 * @brief       add task to task queue
 * @param       [in/out]  *func                     task function
 * @param       [in/out]  event                     task event
 * @return      [in/out]  NULL                      add failed
 * @return      [in/out]  ARRDESS                   add success
 * @note        None
 *******************************************************************************
 */
struct TaskBlock *CreateEventHandleExTask(fw_err_t (*func)(uint16_t), uint16_t evt)
{
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    if(IS_PTR_NULL(func))
    {
        return NULL;
    }
    
    struct TaskBlock *task = (struct TaskBlock *)MemoryMalloc(sizeof(struct TaskBlock));
     
    if(IS_PTR_NULL(task))
    {
        return NULL;
    }
    
    task->Handler.Event = func;
    task->Event         = evt;
    task->Type          = EVENT_HANDLE_EX_TASK;
    
//    task->Next         = NULL;
    task_push(task);
    
    return task;
#else
    return NULL;
#endif
}

/**
 *******************************************************************************
 * @brief       add task to task queue
 * @param       [in/out]  *func                     task function
 * @param       [in/out]  *param                    task param
 * @param       [in/out]  *expand                   task expand param
 * @return      [in/out]  NULL                      add failed
 * @return      [in/out]  ARRDESS                   add success
 * @note        None
 *******************************************************************************
 */
struct TaskBlock *CreateMessageHandleExTask(fw_err_t (*func)(void*, uint16_t), void *param, uint16_t evt)
{
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    if(IS_PTR_NULL(func))
    {
        return NULL;
    }
    
    struct TaskBlock *task = (struct TaskBlock *)MemoryMalloc(sizeof(struct TaskBlock));
     
    if(IS_PTR_NULL(task))
    {
        return NULL;
    }
    
    task->Handler.Message = func;
    task->Param           = param;
    task->Event           = evt;
    task->Type            = MESSAGE_HANDLE_EX_TASK;
    
//    task->Next         = NULL;
    task_push(task);
    
    return task;
#else
    return NULL;
#endif
}

/**
 *******************************************************************************
 * @brief       task handler function
 * @param       [in/out]  task                will handler task
 * @return      [in/out]  FW_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
fw_err_t task_handler(struct TaskBlock *task)
{
//    if( IS_PTR_NULL(task) )
//    {
//        return FW_ERR_NONE;
//    }
    
    switch(task->Type)
    {
        case CALL_BACK_TASK:
        case CALL_BACK_EX_TASK:
            if( task->Handler.CallBack != NULL )
            {
                task->Handler.CallBack(task->Param);
            }
            break;
        case EVENT_HANDLE_TASK:
        case EVENT_HANDLE_EX_TASK:
            if( task->Handler.Event != NULL )
            {
                task->Handler.Event(task->Event);
            }
            break;
        case MESSAGE_HANDLE_TASK:
        case MESSAGE_HANDLE_EX_TASK:
            if( task->Handler.Message != NULL )
            {
                task->Handler.Message(task->Param, task->Event);
            }
            break;
//        default:
//            return FW_ERR_FAIL;
//            break;
    }
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       task poll
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE              walking
 * @note        this function is dependent on ysf memory management
 *******************************************************************************
 */
fw_err_t TaskComponentPoll(void)
{   
    // read task from the task queue    
    struct TaskBlock *task = task_pop();

    if( task == NULL )
    {
        return FW_ERR_FAIL;
    }
    
    // task trigger handler
    task_handler(task);
    
#if defined(USE_MEMORY_COMPONENT) && USE_MEMORY_COMPONENT
    if (task->Type == CALL_BACK_EX_TASK 
        || task->Type == EVENT_HANDLE_EX_TASK 
        || task->Type == MESSAGE_HANDLE_EX_TASK)
    {
        if( MemoryIsIn(task) == true )
        {
            MemoryFree(task);
        }
    }
#endif
        
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       add task to task queue
 * @param       [in/out]  *task                    task block
 * @return      [in/out]  FW_ERR_FAIL              add failed
 * @return      [in/out]  FW_ERR_NONE              add success
 * @note        this function is dependent on ysf memory management
 *******************************************************************************
 */
fw_err_t AddTaskToQueue(struct TaskBlock *task)
{   
    if( task == NULL )
    {
        return FW_ERR_FAIL;
    }
    
    task_push(task);
        
    return FW_ERR_NONE;
}

#endif
/** @}*/     /** task component */

/**********************************END OF FILE*********************************/
