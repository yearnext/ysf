/**
 ******************************************************************************
  * @file       ysf_task.c
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-1-10
  * @brief      ysf_task source file
  * @par        work platform
  *                 Windows
  * @par        compiler platform
  * 				GCC
 ******************************************************************************
  * @note
  * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf task
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_COMPONENT_TASK_PATH
#include YSF_COMPONENT_DEBUG_PATH
#include YSF_COMPONENT_MEMORY_PATH
#include YSF_COMPONENT_SINGLE_LIST_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
/**
 *******************************************************************************
 * @brief       ysf task control block
 *******************************************************************************
 */
static DEFINE_SLIST_FIFO_CONTROL_BLOCK(struct ysf_task_t, tcb);
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
YSF_STATIC_INLINE
bool ysf_task_isIn(struct ysf_task_t *task)
{
    ysf_sListControlBlock_isIn(struct ysf_task_t, tcb, task);
    
    return false;
}

/**
 *******************************************************************************
 * @brief       pop task to queue
 * @param       [in/out]  task                 will add task
 * @return      [in/out]  YSF_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
YSF_STATIC_INLINE
ysf_err_t ysf_task_push(struct ysf_task_t *task)
{
    ysf_sListControlBlock_push(ysf_task_isIn, tcb, task);
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       push task from queue
 * @param       [in/out]  void
 * @return      [in/out]  struct ysf_task_t *     push task addr in memory
 * @note        this function is static inline type
 *******************************************************************************
 */
YSF_STATIC_INLINE
struct ysf_task_t *ysf_task_pop(void)
{
    struct ysf_task_t *task;
    
    ysf_sListControlBlock_pop(tcb, task);
    
    return task;
}

/**
 *******************************************************************************
 * @brief       task queue clear
 * @param       [in/out]  void
 * @return      [in/out]  YSF_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
YSF_STATIC_INLINE
ysf_err_t ysf_task_clear(void)
{    
    ysf_sListControlBlock_clear(ysf_task_pop);

//    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       ysf task component init
 * @param       [in/out]  void
 * @return      [in/out]  YSF_ERR_NONE       init finish
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_task_init(void)
{
    ysf_task_clear();
    
    return YSF_ERR_NONE;
}


/**
 *******************************************************************************
 * @brief       add task in task queue
 * @param       [in/out]  *task                     task block
 * @param       [in/out]  *func                     task function
 * @param       [in/out]  *param                    task param
 * @return      [in/out]  YSF_ERR_INVAILD_PTR       add failed
 * @return      [in/out]  YSF_ERR_NONE              add success
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_cbTask_create(struct ysf_task_t *task, ysf_err_t (*func)(void*), void *param)
{
    if(IS_PTR_NULL(task) || IS_PTR_NULL(func))
    {
        return YSF_ERR_INVAILD_PTR;
    }
    
    task->handler.cb = func;
    task->param      = param;
    task->type       = YSF_CALL_BACK_TASK;
    
//    task->next       = NULL;
    ysf_task_push(task);
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       add task in task queue
 * @param       [in/out]  *task                     task block
 * @param       [in/out]  *func                     task function
 * @param       [in/out]  event                     task event
 * @return      [in/out]  YSF_ERR_INVAILD_PTR       add failed
 * @return      [in/out]  YSF_ERR_NONE              add success
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_evtTask_create(struct ysf_task_t *task, ysf_err_t (*func)(uint16_t), uint16_t evt)
{
    if(IS_PTR_NULL(task) || IS_PTR_NULL(func))
    {
        return YSF_ERR_INVAILD_PTR;
    }
    
    task->handler.evt = func;
    task->evt         = evt;
    task->type        = YSF_STATE_MECHINE_TASK;
    
//    task->next         = NULL;
    ysf_task_push(task);
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       add task in task queue
 * @param       [in/out]  *task                     task block
 * @param       [in/out]  *func                     task function
 * @param       [in/out]  *param                    task param
 * @param       [in/out]  *expand                   task expand param
 * @return      [in/out]  YSF_ERR_INVAILD_PTR       add failed
 * @return      [in/out]  YSF_ERR_NONE              add success
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_smTask_create(struct ysf_task_t *task, ysf_err_t (*func)(void*, uint16_t), void *param, uint16_t evt)
{
    if(IS_PTR_NULL(task) || IS_PTR_NULL(func))
    {
        return YSF_ERR_INVAILD_PTR;
    }
    
    task->handler.sm = func;
    task->param      = param;
    task->evt        = evt;
    task->type       = YSF_EVENT_HANDLER_TASK;
    
//    task->next   = NULL;
    ysf_task_push(task);
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       task handler function
 * @param       [in/out]  task                 will handler task
 * @return      [in/out]  YSF_ERR_NONE         no error
 * @note        this function is static inline type
 *******************************************************************************
 */
YSF_STATIC_INLINE
ysf_err_t ysf_task_handler(struct ysf_task_t *task)
{
//    if( IS_PTR_NULL(task) )
//    {
//        return YSF_ERR_NONE;
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
//            return YSF_ERR_FAIL;
//            break;
    }
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       task poll
 * @param       [in/out]  void
 * @return      [in/out]  YSF_ERR_NONE              walking
 * @note        this function is dependent on ysf memory management
 *******************************************************************************
 */
ysf_err_t ysf_task_poll(void)
{   
    // read task from the task queue    
    struct ysf_task_t *task = ysf_task_pop();

    if( task == NULL )
    {
        return YSF_ERR_NONE;
    }
    
    // task trigger handler
    ysf_task_handler(task);

    return YSF_ERR_NONE;
}

#endif
/** @}*/     /** ysf task component */

/**********************************END OF FILE*********************************/
