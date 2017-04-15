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
 * @file       fw_linklist.c                                                   *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-18                                                      *
 * @brief      framework link list source files                                *
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
 * @defgroup framework link list component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH
#include _FW_LINK_LIST_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_SINGLE_LIST_API
/**
 *******************************************************************************
 * @brief       single link list init
 * @param       [in/out]  **listHead    single link list node head
 * @return      [in/out]  FW_ERR_NONE  init success
 * @note        None
 *******************************************************************************
 */
fw_err_t fw_slinklist_init( void **listHead )
{
    fw_assert(IS_PTR_NULL(listHead));

    *listHead = NULL;

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       single link list traversal function
 * @param       [in/out]  **listHead    single link list head
 * @param       [in/out]  func          single link list visit function
 * @param       [in/out]  **ctx         context
 * @param       [in/out]  **expand      expand
 * @return      [in/out]  true          visit success
 * @return      [in/out]  false         visit failed
 * @note        None
 *******************************************************************************
 */
bool fw_slinklist_walk(void **listHead, bool (*func)(void**, void**, void**),
                       void **ctx,      void **expand)
{
    bool status = false;
    struct fw_slinklist_t **sList = (struct fw_slinklist_t **)listHead;

    while(1)
    {
        status = func((void **)sList, ctx, expand);

        if( status == true || *sList == NULL )
        {
            break;
        }

        sList = (struct fw_slinklist_t **)(&((struct fw_slinklist_t *)(*sList))->next);
    }

    return status;
}

/**
 *******************************************************************************
 * @brief       add node to signle list
 * @param       [in/out]  **listHead    now single link list node
 * @param       [in/out]  **ctx         wait add node
 * @param       [in/out]  **expand      expand
 * @return      [in/out]  true          add node success
 * @return      [in/out]  false         add node failed
 * @note        None
 *******************************************************************************
 */
bool fw_slinklist_module_add( void **node, void **ctx, void **expand )
{
    fw_assert(IS_PTR_NULL(*ctx));

    bool status = false;
    struct fw_slinklist_t *temp = (struct fw_slinklist_t *)(*ctx);
    
    if( *node == NULL )
    {
        temp->next = NULL;
        *node = *ctx;

        status = true;
    }
    else  if( *node == *ctx )
    {
        temp = ((struct fw_slinklist_t *)(*node))->next;

        *node = *ctx;
        ((struct fw_slinklist_t *)(*node))->next = temp;

        status = true;
    }
    else
    {
        /** do nothing! */
    }

    return status;
}

/**
 *******************************************************************************
 * @brief       delete node to signle list
 * @param       [in/out]  **listHead    now single link list node
 * @param       [in/out]  **ctx         wait delete node
 * @param       [in/out]  **expand      expand
 * @return      [in/out]  true          delete node success
 * @return      [in/out]  false         delete node failed
 * @note        None
 *******************************************************************************
 */
bool fw_slinklist_module_del( void **node, void **ctx, void **expand )
{
    fw_assert(IS_PTR_NULL(*ctx));

    struct fw_slinklist_t *now = (struct fw_slinklist_t *)(*node);
    struct fw_slinklist_t *next = (struct fw_slinklist_t *)(*ctx);

    bool status = false;
    
    if( now == NULL )
    {
        return false;
    }

    if( *node == *ctx )
    {
        *node = now->next;

        status = true;
    }
    else if( now->next == *ctx )
    {
        now->next  = next->next;
        next->next = NULL;

        status = true;
    }
    else
    {
        /** do nothing! */
    }

    return status;
}

/**
 *******************************************************************************
 * @brief       detection node is in signle list
 * @param       [in/out]  **listHead    now single link list node
 * @param       [in/out]  **ctx         wait detection node
 * @param       [in/out]  **expand      expand
 * @return      [in/out]  true          detection node is in list
 * @return      [in/out]  false         detection node is in list
 * @note        None
 *******************************************************************************
 */
bool fw_slinklist_module_isExist( void **node, void **ctx, void **expand )
{
    fw_assert(IS_PTR_NULL(*ctx));

    bool status = false;

    if( *node == NULL )
    {
        return false;
    }

    if( *node == *ctx )
    {
        status = true;
    }

    return status;
}

/**
 *******************************************************************************
 * @brief       find the last node of the node 
 * @param       [in/out]  **listHead    now single link list node
 * @param       [in/out]  **ctx         find node
 * @param       [in/out]  **expand      find node
 * @return      [in/out]  true          detection node is in list
 * @return      [in/out]  false         detection node not in list
 * @note        None
 *******************************************************************************
 */
bool fw_slinklist_module_findLastNode( void **node, void **ctx, void **expand )
{
    bool status = false;

    struct fw_slinklist_t *now = (struct fw_slinklist_t *)(*node);

    if( *node == NULL )
    {
        return false;
    }

    if( ((void *)now->next) == ctx )
    {
        *expand = now;
        return true;
    }

    return status;
}

/**
 *******************************************************************************
 * @brief       add node to signle list
 * @param       [in/out]  **listHead    now single link list node
 * @param       [in/out]  **ctx         wait add node
 * @return      [in/out]  FW_ERR_FAIL  add node failed
 * @return      [in/out]  FW_ERR_NONE  add node success
 * @note        None
 *******************************************************************************
 */
fw_err_t fw_slinklist_add( void **listHead, void **ctx )
{
    fw_assert(IS_PTR_NULL(listHead));
    fw_assert(IS_PTR_NULL(*ctx));

    if( fw_slinklist_walk(listHead, fw_slinklist_module_add, ctx, NULL) == false )
    {
        return FW_ERR_FAIL;
    }

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       detele node to signle list
 * @param       [in/out]  **listHead    now single link list node
 * @param       [in/out]  **ctx         wait detele node
 * @return      [in/out]  FW_ERR_FAIL  detele node failed
 * @return      [in/out]  FW_ERR_NONE  detele node success
 * @note        None
 *******************************************************************************
 */
fw_err_t fw_slinklist_del( void **listHead, void **ctx )
{
    fw_assert(IS_PTR_NULL(listHead));
    fw_assert(IS_PTR_NULL(*ctx));

    if( fw_slinklist_walk(listHead, fw_slinklist_module_del, ctx, NULL) == false )
    {
        return FW_ERR_FAIL;
    }

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       detection node is in signle list
 * @param       [in/out]  **listHead    now single link list node
 * @param       [in/out]  **ctx         wait detection node
 * @return      [in/out]  FW_ERR_FAIL  node not in list
 * @return      [in/out]  FW_ERR_NONE  node is in list
 * @note        None
 *******************************************************************************
 */
fw_err_t fw_slinklist_isExist( void **listHead, void **ctx )
{
    fw_assert(IS_PTR_NULL(listHead));
    fw_assert(IS_PTR_NULL(*ctx));

    if( fw_slinklist_walk(listHead, fw_slinklist_module_isExist, ctx, NULL) == false )
    {
        return FW_ERR_FAIL;
    }

    return FW_ERR_NONE;
}

#endif

/** @}*/     /** framework link list component */

/**********************************END OF FILE*********************************/
