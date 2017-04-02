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
//struct ysf_task_control_block
//{
//    struct ysf_task_t *head;
//    struct ysf_task_t *tail;
//} static tcb = 
//{
//    .head = NULL,
//    .tail = NULL,
//};
DEFINE_SLIST_FIFO_CONTROL_BLOCK(struct ysf_task_t, tcb);
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
//    ysf_assert(IS_PTR_NULL(task));
//    
//    struct ysf_task_t *temp = tcb.head;
//    
//    if( temp == NULL )
//    {
//        return false;
//    }
//    
//    while(temp != NULL)
//    {
//        if( temp == task )
//        {
//            return true;
//        }
//        
//        temp = temp->next;
//    }

//    return false;
    ysf_sListControlBlock_isIn(tcb, task);
    
//    return false;
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
//    ysf_assert(IS_PTR_NULL(task));
//    
//    if( ysf_task_isIn(task) == false )
//    {
//        task->next = NULL;
//        
//        if(tcb.tail != NULL)
//        {
//            tcb.tail->next = task;
//            tcb.tail       = task;
//        }
//        else
//        {
//            tcb.head       = task;
//            tcb.tail       = task;
//        }
//    }
//    else
//    {
//        return YSF_ERR_INVAILD_PARAM;
//    }
//    
//    return YSF_ERR_NONE;
    ysf_sListControlBlock_push(ysf_task_isIn, tcb, task);
//    return YSF_ERR_NONE;
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
    
//    if( tcb.head == NULL )
//    {
//        tcb.tail = NULL;
//        return NULL;
//    }
//    
//    task = tcb.head;

//    tcb.head = tcb.head->next;
//    
//    if( tcb.head->next == NULL )
//    {
//        tcb.tail = NULL;
//    }

//    task->next   = NULL;
//    
//    return task;
//    
    ysf_sListControlBlock_pop(tcb, task);
//    return task;
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
//    while(ysf_task_pop() != NULL);
//    
//    return YSF_ERR_NONE;
    
    ysf_sListControlBlock_clear(ysf_task_pop);
//    while(ysf_task_pop() != NULL);
    
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
 * @param       [in/out]  *expand                   task expand param
 * @return      [in/out]  YSF_ERR_INVAILD_PTR       add failed
 * @return      [in/out]  YSF_ERR_NONE              add success
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_evtTask_create(struct ysf_task_t *task, ysf_err_t (*func)(void*, void*), void *param, void *expand)
{
    if(IS_PTR_NULL(task) || IS_PTR_NULL(func))
    {
        return YSF_ERR_INVAILD_PTR;
    }
    
    task->evt.func    = func;
    task->evt.param   = param;
    task->evt.expand  = expand;
    task->next        = NULL;
    task->taskType    = YSF_TASK_IS_EVENT_TYPE;
    
    ysf_task_push(task);
    
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
    
    task->cb.func    = func;
    task->cb.param   = param;
    task->next       = NULL;
    task->taskType   = YSF_TASK_IS_CALL_BACK_TYPE;
    
    ysf_task_push(task);
    
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
    if( task->taskType == YSF_TASK_IS_CALL_BACK_TYPE )
    {
        if( task->cb.func != NULL )
        {
            task->cb.func(task->cb.param);
        }
    }
    else if( task->taskType == YSF_TASK_IS_EVENT_TYPE )
    {   
        if( task->evt.func != NULL )
        {
            task->evt.func(task->evt.param, task->evt.expand);
        }
    }
    else
    {
        return YSF_ERR_FAIL;
    }
    
    return YSF_ERR_NONE;
}

#endif
/** @}*/     /** ysf task component */

/**********************************END OF FILE*********************************/
