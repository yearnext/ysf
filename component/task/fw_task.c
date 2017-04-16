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
 * @brief      framework task component source files                           *
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
#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
/**
 *******************************************************************************
 * @brief       ysf task control block
 *******************************************************************************
 */
static DEFINE_SLIST_FIFO_CONTROL_BLOCK(struct ysf_task_t, TaskControlBlock);
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
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
bool ysf_task_isIn(struct ysf_task_t *task)
{
    ysf_sListFIFO_isIn(struct ysf_task_t, TaskControlBlock, task);
    
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
fw_err_t ysf_task_push(struct ysf_task_t *task)
{
    ysf_sListFIFO_push(ysf_task_isIn, TaskControlBlock, task);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       push task from queue
 * @param       [in/out]  void
 * @return      [in/out]  struct ysf_task_t *     push task addr in memory
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
struct ysf_task_t *ysf_task_pop(void)
{
    struct ysf_task_t *task;
    
    ysf_sListFIFO_pop(TaskControlBlock, task);
    
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
fw_err_t ysf_task_clear(void)
{    
    ysf_sListFIFO_clear(ysf_task_pop);

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       ysf task component init
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE       init finish
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_task_init(void)
{
    ysf_task_clear();
    
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
fw_err_t ysf_cbTask_create(struct ysf_task_t *task, fw_err_t (*func)(void*), void *param)
{
    if(IS_PTR_NULL(task) || IS_PTR_NULL(func))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    task->handler.cb = func;
    task->param      = param;
    task->type       = YSF_CALL_BACK_TASK;
    
//    task->next       = NULL;
    ysf_task_push(task);
    
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
struct ysf_task_t *ysf_cbSimpTask_create(fw_err_t (*func)(void*), void *param)
{
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API 
    if(IS_PTR_NULL(func))
    {
        return NULL;
    }
    
    struct ysf_task_t *task = (struct ysf_task_t *)ysf_memory_malloc(sizeof(struct ysf_task_t));
     
    if(IS_PTR_NULL(task))
    {
        return NULL;
    }
    
    task->handler.cb = func;
    task->param      = param;
    task->type       = YSF_CALL_BACK_TASK;
    
//    task->next         = NULL;
    ysf_task_push(task);
    
    return task;
#else
    return NULL;
#endif
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
fw_err_t ysf_evtTask_create(struct ysf_task_t *task, fw_err_t (*func)(uint16_t), uint16_t evt)
{
    if(IS_PTR_NULL(task) || IS_PTR_NULL(func))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    task->handler.evt = func;
    task->evt         = evt;
    task->type        = YSF_EVENT_HANDLER_TASK;
    
//    task->next         = NULL;
    ysf_task_push(task);
    
    return FW_ERR_NONE;
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
struct ysf_task_t *ysf_evtSimpTask_create(fw_err_t (*func)(uint16_t), uint16_t evt)
{
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API 
    if(IS_PTR_NULL(func))
    {
        return NULL;
    }
    
    struct ysf_task_t *task = (struct ysf_task_t *)ysf_memory_malloc(sizeof(struct ysf_task_t));
     
    if(IS_PTR_NULL(task))
    {
        return NULL;
    }
    
    task->handler.evt = func;
    task->evt         = evt;
    task->type        = YSF_EVENT_HANDLER_TASK;
    
//    task->next         = NULL;
    ysf_task_push(task);
    
    return task;
#else
    return NULL;
#endif
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
fw_err_t ysf_smTask_create(struct ysf_task_t *task, fw_err_t (*func)(void*, uint16_t), void *param, uint16_t evt)
{
    if(IS_PTR_NULL(task) || IS_PTR_NULL(func))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    task->handler.sm = func;
    task->param      = param;
    task->evt        = evt;
    task->type       = YSF_STATE_MECHINE_TASK;
    
//    task->next   = NULL;
    ysf_task_push(task);
    
    return FW_ERR_NONE;
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
struct ysf_task_t *ysf_smSimpTask_create(fw_err_t (*func)(void*, uint16_t), void *param, uint16_t evt)
{
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API 
    if(IS_PTR_NULL(func))
    {
        return NULL;
    }
    
    struct ysf_task_t *task = (struct ysf_task_t *)ysf_memory_malloc(sizeof(struct ysf_task_t));
     
    if(IS_PTR_NULL(task))
    {
        return NULL;
    }
    
    task->handler.sm = func;
    task->param      = param;
    task->evt        = evt;
    task->type       = YSF_STATE_MECHINE_TASK;
    
//    task->next         = NULL;
    ysf_task_push(task);
    
    return task;
#else
    return NULL;
#endif
}

/**
 *******************************************************************************
 * @brief       task handler function
 * @param       [in/out]  task                 will handler task
 * @return      [in/out]  FW_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
fw_err_t ysf_task_handler(struct ysf_task_t *task)
{
//    if( IS_PTR_NULL(task) )
//    {
//        return FW_ERR_NONE;
//    }
    
    switch(task->type)
    {
        case YSF_CALL_BACK_TASK:
            if( task->handler.cb != NULL )
            {
                task->handler.cb(task->param);
            }
            break;
        case YSF_EVENT_HANDLER_TASK:
            if( task->handler.evt != NULL )
            {
                task->handler.evt(task->evt);
            }
            break;
        case YSF_STATE_MECHINE_TASK:
            if( task->handler.sm != NULL )
            {
                task->handler.sm(task->param, task->evt);
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
fw_err_t ysf_task_poll(void)
{   
    // read task from the task queue    
    struct ysf_task_t *task = ysf_task_pop();

    if( task == NULL )
    {
        return FW_ERR_NONE;
    }
    
    // task trigger handler
    ysf_task_handler(task);
    
#if defined(USE_YSF_MEMORY_API) && USE_YSF_MEMORY_API
        if( ysf_memory_is_in(task) == true )
        {
            ysf_memory_free(task);
        }
#endif
        
    return FW_ERR_NONE;
}

#endif
/** @}*/     /** ysf task component */

/**********************************END OF FILE*********************************/
