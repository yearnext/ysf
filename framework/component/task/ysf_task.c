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

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
/**
 *******************************************************************************
 * @brief       ysf task control block
 *******************************************************************************
 */
struct ysf_task_control_block
{
    struct ysf_task_t *head;
    struct ysf_task_t *tail;
} static tcb = 
{
    .head = NULL,
    .tail = NULL,
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if defined(USE_YSF_TASK_API) && USE_YSF_TASK_API
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
    tcb.head = NULL;
    tcb.tail = NULL;
    
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
ysf_err_t ysf_task_add(struct ysf_task_t *task, void *func, void *param, void *expand)
{
    if(IS_PTR_NULL(task) || IS_PTR_NULL(func))
    {
        return YSF_ERR_INVAILD_PTR;
    }
    
    task->func = (ysf_err_t (*)(void*, void*))func;
    task->param   = param;
    task->expand  = expand;
    task->next    = NULL;
    
    if(tcb.head == NULL)
    {
        tcb.head = task;
        tcb.tail = task;
    
        return YSF_ERR_NONE;
    }
    
    tcb.tail->next = task;
    tcb.tail       = task;
    
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
    struct ysf_task_t *task = tcb.head;
    
    if(tcb.head == NULL)
    {
        return YSF_ERR_FAIL;
    } 

    if( task->next == NULL )
    {
		tcb.head   = NULL;
        tcb.tail   = NULL;
    }
	else
	{
		tcb.head   = task->next;    
        task->next = NULL;
	}

    if( task->func != NULL )
    {
        task->func(task->param, task->expand);
    }

    return YSF_ERR_FAIL;
}

#endif
/** @}*/     /** ysf task component */

/**********************************END OF FILE*********************************/
