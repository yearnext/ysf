/**
 ******************************************************************************
  * @file       ysf_pt.c
  * @author     yearnext
  * @version    1.0.0
  * @date       2017-1-10
  * @brief      ysf protothreads source file
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
 * @defgroup ysf protothreaads component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_COMPONENT_PT_PATH
#include YSF_COMPONENT_TASK_PATH
#include YSF_COMPONENT_DEBUG_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if defined(USE_YSF_PT_API) && USE_YSF_PT_API
/**
 *******************************************************************************
 * @brief       init protothreads
 * @param       [in/out]  *pt                       protothreads block
 * @param       [in/out]  pt_thread                 protothreads function
 * @return      [in/out]  YSF_ERR_INVAILD_PTR       enable failed
 * @return      [in/out]  YSF_ERR_NONE              enable success
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_pt_init(struct ysf_pt_t *pt, YSF_PT_THREAD_NAME)
{
    if(IS_PTR_NULL(pt) || IS_PTR_NULL(pt_thread))
    {
        return YSF_ERR_INVAILD_PTR;
    }
    
    pt->state     = 0;
    pt->thread    = pt_thread;
    pt->useStatus = ysf_enable;

    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       enable protothreads
 * @param       [in/out]  *task                     task block
 * @param       [in/out]  *pt                       protothreads block
 * @param       [in/out]  pt_thread                 protothreads function
 * @return      [in/out]  YSF_ERR_INVAILD_PTR       enable failed
 * @return      [in/out]  YSF_ERR_NONE              enable success
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_pt_arm(struct ysf_task_t *task, struct ysf_pt_t *pt)
{
    if(IS_PTR_NULL(task) || IS_PTR_NULL(pt))
    {
        return YSF_ERR_INVAILD_PTR;
    }
    
    ysf_smTask_create(task, pt->thread, pt, YSF_EVENT_NONE);
    
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       enable protothreads
 * @param       [in/out]  *pt                       protothreads block
 * @param       [in/out]  pt_thread                 protothreads function
 * @return      [in/out]  YSF_ERR_INVAILD_PTR       enable failed
 * @return      [in/out]  YSF_ERR_FAIL              enable failed
 * @return      [in/out]  YSF_ERR_NONE              enable success
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_pt_simp_arm(struct ysf_pt_t *pt)
{
    if(IS_PTR_NULL(pt))
    {
        return YSF_ERR_INVAILD_PTR;
    }

    if(ysf_smSimpTask_create(pt->thread, pt, YSF_EVENT_NONE) == NULL)
    {
        return YSF_ERR_FAIL;
    }
    
    return YSF_ERR_NONE;
}
 
/**
 *******************************************************************************
 * @brief       disable protothreads
 * @param       [in/out]  *pt                       protothreads block
 * @return      [in/out]  YSF_ERR_INVAILD_PTR       disable failed
 * @return      [in/out]  YSF_ERR_NONE              disable success
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_pt_disarm(struct ysf_pt_t *pt)
{
    if(IS_PTR_NULL(pt))
    {
        return YSF_ERR_INVAILD_PTR;
    }
    
    pt->useStatus = ysf_disable;
    
    return YSF_ERR_NONE;
}
#endif

/** @}*/     /** ysf protothreads component  */

/**********************************END OF FILE*********************************/
