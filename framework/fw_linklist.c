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
 * @brief      framework link list component source files                      *
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
#if USE_SINGLE_LIST_COMPONENT
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
bool SingleListWalk(void **listHead, bool (*func)(void**, void**, void**),
                    void **ctx,      void **expand)
{
    _FW_ASSERT(IS_PTR_NULL(listHead));
    _FW_ASSERT(IS_PTR_NULL(*listHead));
    _FW_ASSERT(IS_PTR_NULL(func));
    
    bool status = false;
    struct SingleList **sList = (struct SingleList **)listHead;

    while(1)
    {
        status = func((void **)sList, ctx, expand);

        if( status == true || *sList == NULL )
        {
            break;
        }

        sList = (struct SingleList **)(&((struct SingleList *)(*sList))->Next);
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
bool SingleListModuleAdd(void **node, void **ctx, void **expand)
{
    _FW_ASSERT(IS_PTR_NULL(*ctx));

    bool status = false;
    struct SingleList *temp = (struct SingleList *)(*ctx);
    
    if (*node == NULL)
    {
        temp->Next = NULL;
        *node = *ctx;

        status = true;
    }
    else if (*node == *ctx)
    {
        temp = ((struct SingleList *)(*node))->Next;

        *node = *ctx;
        ((struct SingleList *)(*node))->Next = temp;

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
bool SingleListModuleDel( void **node, void **ctx, void **expand )
{
    _FW_ASSERT(IS_PTR_NULL(*ctx));

    struct SingleList *now = (struct SingleList *)(*node);
    struct SingleList *next = (struct SingleList *)(*ctx);

    bool status = false;
    
    if( now == NULL )
    {
        return false;
    }

    if( *node == *ctx )
    {
        *node = now->Next;

        status = true;
    }
    else if( now->Next == *ctx )
    {
        now->Next  = next->Next;
        next->Next = NULL;

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
bool SingleListModuleIsExist( void **node, void **ctx, void **expand )
{
    _FW_ASSERT(IS_PTR_NULL(*ctx));

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
bool SingleListModuleFindLastNode(void **node, void **ctx, void **expand)
{
    bool status = false;

    struct SingleList *now = (struct SingleList *)(*node);

    if (*node == NULL)
    {
        return false;
    }

    if (((void *)now->Next) == ctx)
    {
        *expand = now;
        return true;
    }

    return status;
}

/**
 *******************************************************************************
 * @brief       single link list init
 * @param       [in/out]  **listHead    single link list node head
 * @return      [in/out]  FW_ERR_NONE  init success
 * @note        None
 *******************************************************************************
 */
fw_err_t InitSingleListComponent( void **listHead )
{
    _FW_ASSERT(IS_PTR_NULL(listHead));

    *listHead = NULL;

    return FW_ERR_NONE;
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
fw_err_t AddNodeToSingleList( void **listHead, void **ctx )
{
    _FW_ASSERT(IS_PTR_NULL(listHead));
    _FW_ASSERT(IS_PTR_NULL(*ctx));

    if( SingleListWalk(listHead, SingleListModuleAdd, ctx, NULL) == false )
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
fw_err_t DelNodeFromSingleList( void **listHead, void **ctx )
{
    _FW_ASSERT(IS_PTR_NULL(listHead));
    _FW_ASSERT(IS_PTR_NULL(*ctx));

    if( SingleListWalk(listHead, SingleListModuleDel, ctx, NULL) == false )
    {
        return FW_ERR_FAIL;
    }

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       detection node is in signle list
 * @param       [in/out]  **listHead   now single link list node
 * @param       [in/out]  **ctx        wait detection node
 * @return      [in/out]  FW_ERR_FAIL  node not in list
 * @return      [in/out]  FW_ERR_NONE  node is in list
 * @note        None
 *******************************************************************************
 */
fw_err_t IsInSingleList( void **listHead, void **ctx )
{
    _FW_ASSERT(IS_PTR_NULL(listHead));
    _FW_ASSERT(IS_PTR_NULL(*ctx));

    if( SingleListWalk(listHead, SingleListModuleIsExist, ctx, NULL) == false )
    {
        return FW_ERR_FAIL;
    }

    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       Init single link list
 * @param       [in/out]  *node        node address
 * @return      [in/out]  FW_ERR_FAIL  init failed
 * @return      [in/out]  FW_ERR_NONE  init success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_sLinkList_Init(struct Fw_sLinkList *node)
{
    _FW_ASSERT(IS_PTR_NULL(node));
    
    node->Next = NULL;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       Init double link list
 * @param       [in/out]  *node        node address
 * @return      [in/out]  FW_ERR_FAIL  init failed
 * @return      [in/out]  FW_ERR_NONE  init success
 * @note        None
 *******************************************************************************
 */
fw_err_t Fw_dLinkList_Init(struct Fw_dLinkList *node)
{
    _FW_ASSERT(IS_PTR_NULL(node));
    
    node->Last = NULL;
    node->Next = NULL;
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       add node to link list tail
 * @param       [in/out]  *block       link list management block address
 * @param       [in/out]  *node        node address
 * @return      [in/out]  FW_ERR_FAIL  add failed
 * @return      [in/out]  FW_ERR_NONE  add success
 * @note        application in fifo link list
 *******************************************************************************
 */
fw_err_t Fw_dLinkList_Push(struct Fw_LinkList_Block *block, struct Fw_dLinkList *node)
{
    _FW_ASSERT(IS_PTR_NULL(block));
    _FW_ASSERT(IS_PTR_NULL(node));
    _FW_ASSERT(!IS_PTR_NULL(node->Next));
    _FW_ASSERT(!IS_PTR_NULL(node->Last));

    if(IS_PTR_NULL(block->Head))
    {
        block->Tail = node;                                                  
        block->Head = node;
    }
    else if(IS_PTR_NULL(block->Tail))
    {
        return FW_ERR_BUG;
    }
    else
    {
        block->Tail->Next = node;                                            
        block->Tail       = node;     
    }
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       delete node from link list head
 * @param       [in/out]  *block       link list management block address
 * @param       [in/out]  *node        node address
 * @return      [in/out]  FW_ERR_FAIL  delete failed
 * @return      [in/out]  FW_ERR_NONE  delete success
 * @note        application in fifo link list
 *******************************************************************************
 */
fw_err_t Fw_dLinkList_Pop(struct Fw_LinkList_Block *block, struct Fw_dLinkList **node)
{
    _FW_ASSERT(IS_PTR_NULL(block));
    _FW_ASSERT(IS_PTR_NULL(*node));
    _FW_ASSERT(IS_PTR_NULL(block->Head));
    _FW_ASSERT(IS_PTR_NULL(block->Tail));
    
    if(block->Head == block->Tail)
    {
        *node = block->Head;
        
        block->Tail = NULL;
        block->Head = NULL;
    }
    else
    {
        *node = block->Head;
        
        block->Head = block->Head->Next;
        
        ((struct Fw_dLinkList *)(*node))->Next = NULL;
        ((struct Fw_dLinkList *)(*node))->Last = NULL;
    }
    
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       remove node from link list
 * @param       [in/out]  *block       link list management block address
 * @param       [in/out]  *node        node address
 * @return      [in/out]  FW_ERR_FAIL  remove failed
 * @return      [in/out]  FW_ERR_NONE  remove success
 * @note        application in fifo link list
 *******************************************************************************
 */
fw_err_t Fw_dLinkList_Remove(struct Fw_LinkList_Block *block, struct Fw_dLinkList *node)
{
    _FW_ASSERT(IS_PTR_NULL(block));
    _FW_ASSERT(IS_PTR_NULL(node));
    _FW_ASSERT(IS_PTR_NULL(block->Head));
    _FW_ASSERT(IS_PTR_NULL(block->Tail));
    
    struct Fw_dLinkList *ptr = block->Head;
    
    //< is link list head
    if(ptr == node)
    {
        block->Head = block->Head->Next;
        
        node->Next = NULL;
        node->Last = NULL;
        
        return FW_ERR_NONE;
    }

    //< poll link list
    while(ptr->Next != NULL)
    {
        ptr = ptr->Next;
        
        //< remove handle
        if(ptr == node)
        {
            ptr->Last = ptr->Next;
            
            node->Next = NULL;
            node->Last = NULL;
            
            return FW_ERR_NONE;
        }
    }
    
    //< is link list tail
    if(ptr == node)
    {
        block->Tail = block->Tail->Last;
        
        node->Next = NULL;
        node->Last = NULL;
    }
    else
    {
        return FW_ERR_FAIL;
    }        
      
    return FW_ERR_NONE;
}

#endif

/** @}*/     /** framework link list component */

/**********************************END OF FILE*********************************/
