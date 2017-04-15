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
 * @file       ysf_pt.c                                                        *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-21                                                      *
 * @brief      protothreads component source files                             *
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
 * @defgroup ysf protothreaads component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_PT_COMPONENT_PATH
#include _FW_TASK_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH

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
 * @return      [in/out]  FW_ERR_INVAILD_PTR       enable failed
 * @return      [in/out]  FW_ERR_NONE              enable success
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_pt_init(struct ysf_pt_t *pt, YSF_PT_THREAD_NAME)
{
    if(IS_PTR_NULL(pt) || IS_PTR_NULL(pt_thread))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    pt->state     = 0;
    pt->thread    = pt_thread;
    pt->useStatus = true;

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       enable protothreads
 * @param       [in/out]  *task                     task block
 * @param       [in/out]  *pt                       protothreads block
 * @param       [in/out]  pt_thread                 protothreads function
 * @return      [in/out]  FW_ERR_INVAILD_PTR       enable failed
 * @return      [in/out]  FW_ERR_NONE              enable success
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_pt_arm(struct ysf_task_t *task, struct ysf_pt_t *pt)
{
    if(IS_PTR_NULL(task) || IS_PTR_NULL(pt))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    ysf_smTask_create(task, pt->thread, pt, FW_EVENT_NONE);
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       enable protothreads
 * @param       [in/out]  *pt                       protothreads block
 * @param       [in/out]  pt_thread                 protothreads function
 * @return      [in/out]  FW_ERR_INVAILD_PTR       enable failed
 * @return      [in/out]  FW_ERR_FAIL              enable failed
 * @return      [in/out]  FW_ERR_NONE              enable success
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_pt_simp_arm(struct ysf_pt_t *pt)
{
    if(IS_PTR_NULL(pt))
    {
        return FW_ERR_INVAILD_PTR;
    }

    if(ysf_smSimpTask_create(pt->thread, pt, FW_EVENT_NONE) == NULL)
    {
        return FW_ERR_FAIL;
    }
    
    return FW_ERR_NONE;
}
 
/**
 *******************************************************************************
 * @brief       disable protothreads
 * @param       [in/out]  *pt                       protothreads block
 * @return      [in/out]  FW_ERR_INVAILD_PTR       disable failed
 * @return      [in/out]  FW_ERR_NONE              disable success
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_pt_disarm(struct ysf_pt_t *pt)
{
    if(IS_PTR_NULL(pt))
    {
        return FW_ERR_INVAILD_PTR;
    }
    
    pt->useStatus = false;
    
    return FW_ERR_NONE;
}
#endif

/** @}*/     /** ysf protothreads component  */

/**********************************END OF FILE*********************************/
