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
 * @file       fw_linklist.h                                                   *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-18                                                      *
 * @brief      link list component head files                                  *
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
 * @defgroup link list component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LINK_LIST_COMPONENT_H__
#define __LINK_LIST_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_LINK_LIST_COMPONENT
#if USE_FRAMEWORK_LINK_LIST_COMPONENT
#define USE_SINGLE_LIST_COMPONENT                                            (1)
#else
#define USE_SINGLE_LIST_COMPONENT                                            (0)
#endif
    
/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
#define USE_SINGLE_LIST_COMPONENT                                            (1)
#endif
    
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       single link list structure
 *******************************************************************************
 */
struct SingleList
{
    struct SingleList *Next;
    uint8_t           UserData[];
};

/**
 *******************************************************************************
 * @brief       single list interface
 *******************************************************************************
 */
#if USE_SINGLE_LIST_COMPONENT
typedef struct
{
    fw_err_t (*Init)(void**);
    bool     (*Walk)(void**, bool (*)(void**, void**, void**), void**, void**);
    fw_err_t (*Add)(void**, void **);
    fw_err_t (*Del)(void**, void **);
    fw_err_t (*IsExist)(void**, void **);
}SingleListComponentInterface;
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define single list function api
 *******************************************************************************
 */
#if USE_SINGLE_LIST_COMPONENT
extern bool SingleListWalk(void**, bool (*)(void**, void**, void**), void**, void**);
extern bool SingleListModuleAdd(void**, void**, void**);
extern bool SingleListModuleDel(void**, void**, void**);
extern bool SingleListModuleIsExist(void**, void**, void**);
extern bool SingleListModuleFindLastNode(void **, void**, void**);

extern fw_err_t InitSingleListComponent(void**);
extern fw_err_t AddNodeToSingleList(void**, void**);
extern fw_err_t DelNodeFromSingleList(void**, void**);
extern fw_err_t IsInSingleList(void**, void**);

#endif

/**
 *******************************************************************************
 * @brief       define signle link list fifo control block
 * @param       [in/out]  type          fifo type
 * @param       [in/out]  name          block name
 * @note        None
 *******************************************************************************
 */
#define CREATE_SINGLE_LIST_FIFO_CONTROL_BLOCK(type, name) struct               \
                                                         {                     \
                                                             type *Head;       \
                                                             type *Tail;       \
                                                         } name =              \
                                                         {                     \
                                                             .Head = NULL,     \
                                                             .Tail = NULL,     \
                                                         }
 
/**
 *******************************************************************************
 * @brief       detect the node is in fifo
 * @param       [in/out]  type          fifo type
 * @param       [in/out]  name          block name
 * @param       [in/out]  node          find node
 * @note        None
 *******************************************************************************
 */                                                       
#define IsInSingleLinkListFifo(type, block, node)                              \
{                                                                              \
    type *temp = block.Head;                                                   \
                                                                               \
    while(temp != NULL)                                                        \
    {                                                                          \
        if( temp == node )                                                     \
        {                                                                      \
            return true;                                                       \
        }                                                                      \
                                                                               \
        temp = temp->Next;                                                     \
    }                                                                          \
}

/**
 *******************************************************************************
 * @brief       fifo push
 * @param       [in/out]  isInFunc      repeated judgment
 * @param       [in/out]  name          block name
 * @param       [in/out]  node          find node
 * @note        None
 *******************************************************************************
 */    
#define PushSingleLinkListFifoNode(isInFunc, block, pushData)                  \
{                                                                              \
    if( isInFunc(pushData) == false )                                          \
    {                                                                          \
        pushData->Next = NULL;                                                 \
                                                                               \
        if(block.Tail != NULL)                                                 \
        {                                                                      \
            block.Tail->Next = pushData;                                       \
            block.Tail       = pushData;                                       \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            block.Head       = pushData;                                       \
            block.Tail       = pushData;                                       \
        }                                                                      \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        return FW_ERR_INVAILD_PARAM;                                           \
    }                                                                          \
}

/**
 *******************************************************************************
 * @brief       fifo pop
 * @param       [in/out]  block         block name
 * @param       [in/out]  popData       pop data
 * @note        None
 *******************************************************************************
 */   
#define PopSingleLinkListFifoNode(block, popData)                              \
{                                                                              \
    if( block.Head == NULL )                                                   \
    {                                                                          \
        block.Tail = NULL;                                                     \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    popData       = block.Head;                                                \
    block.Head    = block.Head->Next;                                          \
    popData->Next = NULL;                                                      \
                                                                               \
    if( block.Head == NULL )                                                   \
    {                                                                          \
        block.Tail = NULL;                                                     \
    }                                                                          \
}

/**
 *******************************************************************************
 * @brief       fifo clear
 * @param       [in/out]  sListPOPFunc    fifo pop function
 * @param       [in/out]  popData         pop data
 * @note        None
 *******************************************************************************
 */
#define ClearSingleLinkListFifo(sListPOPFunc)                                  \
{                                                                              \
    while(sListPOPFunc() != NULL);                                             \
}

/**
 *******************************************************************************
 * @brief       delete link list in link list fifo
 * @param       [in/out]  controlBlock    link list control block
 * @param       [in/out]  lastLinkList    last link list
 * @param       [in/out]  nowLinkList     now link list
 * @note        None
 *******************************************************************************
 */
#define DeleteInSignalLinkList(controlBlock, lastLinkList, nowLinkList)        \
{                                                                              \
    if( IsSingleLinkListHead(controlBlock, nowLinkList) )                      \
    {                                                                          \
        UpdateSingleLinkListHead(controlBlock, nowLinkList->Next);             \
                                                                               \
        nowLinkList->Next  = NULL;                                             \
        nowLinkList        = GetSingleLinkListHead(controlBlock);              \
    }                                                                          \
    else if( IsSingleLinkListTail(controlBlock, nowLinkList) )                 \
    {                                                                          \
        lastLinkList->Next = NULL;                                             \
        nowLinkList->Next  = NULL;                                             \
                                                                               \
        UpdateSingleLinkListTail(controlBlock, lastLinkList);                  \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        lastLinkList->Next = nowLinkList->Next;                                \
        nowLinkList->Next  = NULL;                                             \
        nowLinkList        = lastLinkList->Next;                               \
    }                                                                          \
}

/**
 *******************************************************************************
 * @brief       get single link list by id
 * @param       [in/out]  controlBlock    link list control block
 * @param       [in/out]  nowLinkList     now link list
 * @param       [in/out]  id              link list id
 * @note        None
 *******************************************************************************
 */
#define GetSingleLinkListById(controlBlock, nowLinkList, id)                   \
{                                                                              \
    uint8_t i;                                                                 \
                                                                               \
    (nowLinkList) = controlBlock.Head;                                         \
                                                                               \
    for(i=1; i<id; i++)                                                        \
    {                                                                          \
        if((nowLinkList)->Next != NULL)                                        \
        {                                                                      \
            (nowLinkList) = (nowLinkList)->Next;                               \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            (nowLinkList) = NULL;                                              \
            break;                                                             \
        }                                                                      \
    }                                                                          \
}

/**
 *******************************************************************************
 * @brief       fifo clear
 * @param       [in/out]  block         block name
 * @note        None
 *******************************************************************************
 */
#define GetSingleLinkListHead(block)                              ((block).Head)

/**
 *******************************************************************************
 * @brief       fifo clear
 * @param       [in/out]  block         block name
 * @note        None
 *******************************************************************************
 */
#define GetSingleLinkListTail(block)                              ((block).Tail)

/**
 *******************************************************************************
 * @brief       fifo clear
 * @param       [in/out]  block         block name
 * @param       [in/out]  node          node
 * @note        None
 *******************************************************************************
 */
#define UpdateSingleLinkListHead(block, node)            ((block).Head = (node))

/**
 *******************************************************************************
 * @brief       fifo clear
 * @param       [in/out]  block         block name
 * @param       [in/out]  node          node
 * @note        None
 *******************************************************************************
 */
#define UpdateSingleLinkListTail(block, node)            ((block).Tail = (node))

/**
 *******************************************************************************
 * @brief       fifo clear
 * @param       [in/out]  block         block name
 * @param       [in/out]  node          node
 * @note        None
 *******************************************************************************
 */
#define IsSingleLinkListHead(block, node)               ((block).Head == (node))

/**
 *******************************************************************************
 * @brief       fifo clear
 * @param       [in/out]  block         block name
 * @param       [in/out]  node          node
 * @note        None
 *******************************************************************************
 */
#define IsSingleLinkListTail(block, node)               ((block).Tail == (node))

/**
 *******************************************************************************
 * @brief       fifo clear
 * @param       [in/out]  block         block name
 * @note        None
 *******************************************************************************
 */
#define IsSingleLinkListHeadEmpty(block)                  ((block).Head == NULL)

/**
 *******************************************************************************
 * @brief       fifo clear
 * @param       [in/out]  block         block name
 * @note        None
 *******************************************************************************
 */
#define IsSingleLinkListTailEmpty(block, node)            ((block).Tail == NULL)

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** link list component */

/**********************************END OF FILE*********************************/