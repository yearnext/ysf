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
 * @file       ysf_single_list.c                                               *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-18                                                      *
 * @brief      single list component source files                              *
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
 * @defgroup ysf single list component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_TYPE_PATH
#include _FW_LINK_LIST_COMPONENT_PATH
#include _FW_DEBUG_COMPONENT_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if defined(USE_YSF_SINGLE_LIST_API) && USE_YSF_SINGLE_LIST_API
/**
 *******************************************************************************
 * @brief       single list init
 * @param       [in/out]  **listHead    single list node head
 * @return      [in/out]  FW_ERR_NONE  init success
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_slist_init( void **listHead )
{
    ysf_assert(IS_PTR_NULL(listHead));

    *listHead = NULL;

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       single list traversal function
 * @param       [in/out]  **listHead    single list head
 * @param       [in/out]  func          single list visit function
 * @param       [in/out]  **ctx         context
 * @param       [in/out]  **expand      expand
 * @return      [in/out]  true          visit success
 * @return      [in/out]  false         visit failed
 * @note        None
 *******************************************************************************
 */
bool ysf_slist_walk(void **listHead,
                    sListFunc func,
                    void **ctx,
                    void **expand)
{
    bool status = false;
    struct ysf_sList_t **sList = (struct ysf_sList_t **)listHead;

    while(1)
    {
        status = func((void **)sList, ctx, expand);

        if( status == true || *sList == NULL )
        {
            break;
        }

        sList = (struct ysf_sList_t **)(&((struct ysf_sList_t *)(*sList))->next);
    }

    return status;
}

/**
 *******************************************************************************
 * @brief       add node to signle list
 * @param       [in/out]  **listHead    now single list node
 * @param       [in/out]  **ctx         wait add node
 * @param       [in/out]  **expand      expand
 * @return      [in/out]  true          add node success
 * @return      [in/out]  false         add node failed
 * @note        None
 *******************************************************************************
 */
bool ysf_slist_module_add( void **node, void **ctx, void **expand )
{
    ysf_assert(IS_PTR_NULL(*ctx));

    bool status = false;
    struct ysf_sList_t *temp = (struct ysf_sList_t *)(*ctx);
    
    if( *node == NULL )
    {
        temp->next = NULL;
        *node = *ctx;

        status = true;
    }
    else  if( *node == *ctx )
    {
        temp = ((struct ysf_sList_t *)(*node))->next;

        *node = *ctx;
        ((struct ysf_sList_t *)(*node))->next = temp;

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
 * @param       [in/out]  **listHead    now single list node
 * @param       [in/out]  **ctx         wait delete node
 * @param       [in/out]  **expand      expand
 * @return      [in/out]  true          delete node success
 * @return      [in/out]  false         delete node failed
 * @note        None
 *******************************************************************************
 */
bool ysf_slist_module_del( void **node, void **ctx, void **expand )
{
    ysf_assert(IS_PTR_NULL(*ctx));

    struct ysf_sList_t *now = (struct ysf_sList_t *)(*node);
    struct ysf_sList_t *next = (struct ysf_sList_t *)(*ctx);

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
 * @param       [in/out]  **listHead    now single list node
 * @param       [in/out]  **ctx         wait detection node
 * @param       [in/out]  **expand      expand
 * @return      [in/out]  true          detection node is in list
 * @return      [in/out]  false         detection node is in list
 * @note        None
 *******************************************************************************
 */
bool ysf_slist_module_isExist( void **node, void **ctx, void **expand )
{
    ysf_assert(IS_PTR_NULL(*ctx));

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
 * @param       [in/out]  **listHead    now single list node
 * @param       [in/out]  **ctx         find node
 * @param       [in/out]  **expand      find node
 * @return      [in/out]  true          detection node is in list
 * @return      [in/out]  false         detection node not in list
 * @note        None
 *******************************************************************************
 */
bool ysf_slist_module_findLastNode( void **node, void **ctx, void **expand )
{
    bool status = false;

    struct ysf_sList_t *now = (struct ysf_sList_t *)(*node);

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
 * @param       [in/out]  **listHead    now single list node
 * @param       [in/out]  **ctx         wait add node
 * @return      [in/out]  FW_ERR_FAIL  add node failed
 * @return      [in/out]  FW_ERR_NONE  add node success
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_slist_add( void **listHead, void **ctx )
{
    ysf_assert(IS_PTR_NULL(listHead));
    ysf_assert(IS_PTR_NULL(*ctx));

    if( ysf_slist_walk(listHead, ysf_slist_module_add, ctx, NULL) == false )
    {
        return FW_ERR_FAIL;
    }

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       detele node to signle list
 * @param       [in/out]  **listHead    now single list node
 * @param       [in/out]  **ctx         wait detele node
 * @return      [in/out]  FW_ERR_FAIL  detele node failed
 * @return      [in/out]  FW_ERR_NONE  detele node success
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_slist_del( void **listHead, void **ctx )
{
    ysf_assert(IS_PTR_NULL(listHead));
    ysf_assert(IS_PTR_NULL(*ctx));

    if( ysf_slist_walk(listHead, ysf_slist_module_del, ctx, NULL) == false )
    {
        return FW_ERR_FAIL;
    }

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       detection node is in signle list
 * @param       [in/out]  **listHead    now single list node
 * @param       [in/out]  **ctx         wait detection node
 * @return      [in/out]  FW_ERR_FAIL  node not in list
 * @return      [in/out]  FW_ERR_NONE  node is in list
 * @note        None
 *******************************************************************************
 */
fw_err_t ysf_slist_isExist( void **listHead, void **ctx )
{
    ysf_assert(IS_PTR_NULL(listHead));
    ysf_assert(IS_PTR_NULL(*ctx));

    if( ysf_slist_walk(listHead, ysf_slist_module_isExist, ctx, NULL) == false )
    {
        return FW_ERR_FAIL;
    }

    return FW_ERR_NONE;
}
#endif

// 遍历函数
fw_err_t ysf_sListFifo_walk(struct ysf_sListFifo_t **sListFifo, sListFunc func, void **param, void **expand)
{
    ysf_assert(IS_PTR_NULL(sListFifo));
    ysf_assert(IS_PTR_NULL(func));

    struct ysf_sList_t **temp = (struct ysf_sList_t **)(&((struct ysf_sListFifo_t *)(*sListFifo))->head);
    bool status = false;
    
    while(*temp != NULL && status == false)
    {
        status = func((void **)temp, param, expand);
        
        temp = (struct ysf_sList_t **)(&((struct ysf_sList_t *)(*temp))->next);
    }
    
    return FW_ERR_NONE;
}

// 检测是否存在于链表中
bool ysf_sListFifo_isIn(struct ysf_sListFifo_t *sListFifo, struct ysf_sList_t *findData)
{
    ysf_assert(IS_PTR_NULL(sListFifo));
    ysf_assert(IS_PTR_NULL(findData));
    
    struct ysf_sList_t *temp = sListFifo->head;
    
    if( temp == NULL )
    {
        return false;
    }
    
    while(temp != NULL)
    {
        if( temp == findData )
        {
            return true;
        }
        
        temp = temp->next;
    }

    return false;
}

// 入栈
fw_err_t ysf_sListFifo_push(struct ysf_sListFifo_t *sListFifo, struct ysf_sList_t *wrData)
{
    ysf_assert(IS_PTR_NULL(sListFifo));
    ysf_assert(IS_PTR_NULL(wrData));
    
//    if( sListFifo->tail == NULL )
//    {
//        sListFifo->head = wrData;
//        sListFifo->tail = wrData;
//    }
//    else
//    {
//        sListFifo->tail->next = wrData;
//        sListFifo->tail       = wrData;
//    }
    
    if( ysf_sListFifo_isIn(sListFifo, wrData) == false )
    {
        wrData->next = NULL;
        
        if(sListFifo->tail != NULL)
        {
            sListFifo->tail->next = wrData;
            sListFifo->tail       = wrData;
        }
        else
        {
            sListFifo->head = wrData;
            sListFifo->tail = wrData;
        }
    }
    else
    {
        return FW_ERR_INVAILD_PARAM;
    }
    
    return FW_ERR_NONE;
}

// 出栈
fw_err_t ysf_sListFifo_pop(struct ysf_sListFifo_t *sListFifo, struct ysf_sList_t *rdData)
{
    ysf_assert(IS_PTR_NULL(sListFifo));
    ysf_assert(IS_PTR_NULL(rdData));

    rdData = sListFifo->head;
    
//    if( sListFifo->head->next == NULL )
//    {
//        sListFifo->head = NULL;
//        sListFifo->tail = NULL;
//    }
//    else
//    {
//        sListFifo->head = sListFifo->head->next;
//    }
    
    sListFifo->head = sListFifo->head->next;
    
    if( sListFifo->head->next == NULL )
    {
        sListFifo->tail = NULL;
    }

    rdData->next        = NULL;
    
    return FW_ERR_NONE;
}

// 清空链表fifo
fw_err_t ysf_sListFifo_clear(struct ysf_sListFifo_t *sListFifo)
{
    ysf_assert(IS_PTR_NULL(sListFifo));
    
    struct ysf_sList_t *status = NULL;
    
    do
    {
        ysf_sListFifo_pop(sListFifo, status);
    }while(status != NULL);
    
    return FW_ERR_NONE;
}

// 链表fifo初始化
fw_err_t ysf_sListFifo_init(struct ysf_sListFifo_t *sListFifo)
{
    ysf_assert(IS_PTR_NULL(sListFifo));

    ysf_sListFifo_clear(sListFifo);
    
    return FW_ERR_NONE;
}

/** @}*/     /** ysf single list component  */

/**********************************END OF FILE*********************************/
