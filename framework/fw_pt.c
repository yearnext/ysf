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
 * @file       fw_pt.c                                                         *
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
 * @defgroup protothreaads component
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
#if USE_PT_COMPONENT
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
fw_err_t _pt_init(struct ProtoThreads *pt, _PT_THREAD_NAME)
{
    fw_assert(IS_PTR_NULL(pt));
    fw_assert(IS_PTR_NULL(pt_thread));

    pt->State     = 0;
    pt->Thread    = pt_thread;
    pt->UseStatus = true;

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
fw_err_t _pt_arm(struct TaskBlock *task, struct ProtoThreads *pt)
{
    fw_assert(IS_PTR_NULL(pt));
    
    fw_task_msg_create(task, pt->Thread, pt, FW_EVENT_NONE);
    
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
fw_err_t _pt_disarm(struct ProtoThreads *pt)
{
    fw_assert(IS_PTR_NULL(pt));

    pt->UseStatus = false;
    
    return FW_ERR_NONE;
}
#endif

/** @}*/     /** protothreads component  */

/**********************************END OF FILE*********************************/
