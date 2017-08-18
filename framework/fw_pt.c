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
 * @brief      framework protothreads component source files                   *
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
 * @defgroup framework protothreaads component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "fw_pt.h"
#include "fw_debug.h"

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
 * @param       [in/out]  *pt                      protothreads block
 * @param       [in/out]  *str                     protothreads string
 * @param       [in/out]  *pt_thread               protothreads function handle
 * @param       [in/out]  priority                 task priority
 * @return      [in/out]  FW_ERR_INVAILD_PTR       init failed
 * @return      [in/out]  FW_ERR_NONE              init success
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_PT_Init(struct Fw_ProtoThread *pt, char *str, pt_thread ptThread, uint8_t priority)
{
    _FW_ASSERT(IS_PTR_NULL(pt));
    _FW_ASSERT(IS_PTR_NULL(str));
    _FW_ASSERT(IS_PTR_NULL(ptThread));

    pt->State     = 0;
    pt->Str       = str;
    pt->Thread    = ptThread;
    pt->UseStatus = false;

    Fw_Task_Init(&pt->Task, str, priority, (void *)ptThread, FW_PT_THREAD_TYPE_TASK);     

    Fw_Timer_Init(&pt->Timer, str);
    Fw_Timer_SetEvent(&pt->Timer, &pt->Task, FW_DELAY_EVENT, (void *)pt);
}

/**
 *******************************************************************************
 * @brief       deinit protothreads
 * @param       [in/out]  *pt                       protothreads block
 * @return      [in/out]  FW_ERR_FAIL               deinit failed
 * @return      [in/out]  FW_ERR_NONE               deinit success
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_PT_Fini(struct Fw_ProtoThread *pt)
{
    _FW_ASSERT(IS_PTR_NULL(pt));

    pt->State     = 0;
    pt->Str       = NULL;
    pt->Thread    = NULL;
    pt->UseStatus = false;
}

/**
 *******************************************************************************
 * @brief       enable protothreads
 * @param       [in/out]  *pt                       protothreads  block
 * @return      [in/out]  FW_ERR_FAIL               enable failed
 * @return      [in/out]  FW_ERR_NONE               enable success
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_PT_Open(struct Fw_ProtoThread *pt)
{
    _FW_ASSERT(IS_PTR_NULL(pt));
    _FW_ASSERT(IS_PTR_NULL(pt->Thread));

    pt->UseStatus = true;
    pt->Thread(pt, FW_INIT_EVENT);
}

/**
 *******************************************************************************
 * @brief       disable protothreads
 * @param       [in/out]  *pt                      protothreads block
 * @return      [in/out]  FW_ERR_FAIL              disable failed
 * @return      [in/out]  FW_ERR_NONE              disable success
 * @note        None
 *******************************************************************************
 */
__INLINE void Fw_PT_Close(struct Fw_ProtoThread *pt)
{
    _FW_ASSERT(IS_PTR_NULL(pt));
    _FW_ASSERT(IS_PTR_NULL(pt->Thread));
    
    pt->Thread(pt, FW_FINI_EVENT);
    pt->UseStatus = false;
}

#endif

/** @}*/     /** frameowrk protothreads component  */

/**********************************END OF FILE*********************************/
