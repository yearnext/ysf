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
#include "fw_path.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_FRAMEWORK_LINK_LIST_COMPONENT
#define USE_SINGLE_LIST_COMPONENT                                            (1)
  
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

struct Fw_sLinkList
{
    struct Fw_sLinkList *Next;
    uint8_t             UserData[];
};

struct Fw_sLinkList_Block
{
    struct Fw_sLinkList *Head;
    struct Fw_sLinkList *Tail;
};

struct Fw_dLinkList
{
    struct Fw_dLinkList *Next;
    struct Fw_dLinkList *Last;
};

struct Fw_dLinkList_Block
{
    struct Fw_dLinkList *Head;
    struct Fw_dLinkList *Tail;
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define single list function api
 *******************************************************************************
 */
#if USE_SINGLE_LIST_COMPONENT
/**
 *******************************************************************************
 * @brief       the old api
 *******************************************************************************
 */
extern bool SingleListWalk(void**, bool (*)(void**, void**, void**), void**, void**);
extern bool SingleListModuleAdd(void**, void**, void**);
extern bool SingleListModuleDel(void**, void**, void**);
extern bool SingleListModuleIsExist(void**, void**, void**);
extern bool SingleListModuleFindLastNode(void **, void**, void**);

extern fw_err_t InitSingleListComponent(void**);
extern fw_err_t AddNodeToSingleList(void**, void**);
extern fw_err_t DelNodeFromSingleList(void**, void**);
extern fw_err_t IsInSingleList(void**, void**);

/**
 *******************************************************************************
 * @brief       the new api apply single link list
 *******************************************************************************
 */
extern __INLINE void Fw_sLinkList_Init(struct Fw_sLinkList*);
extern __INLINE fw_err_t Fw_sLinkList_Push(struct Fw_sLinkList_Block*, struct Fw_sLinkList*);
extern __INLINE fw_err_t Fw_sLinkList_Pop(struct Fw_sLinkList_Block*, struct Fw_sLinkList**);
extern __INLINE fw_err_t Fw_sLinkList_Remove(struct Fw_sLinkList_Block*, struct Fw_sLinkList*);

/**
 *******************************************************************************
 * @brief       the new api apply double link list
 *******************************************************************************
 */
extern __INLINE void Fw_dLinkList_Init(struct Fw_dLinkList*);
extern __INLINE fw_err_t Fw_dLinkList_Push(struct Fw_dLinkList_Block*, struct Fw_dLinkList*);
extern __INLINE fw_err_t Fw_dLinkList_Pop(struct Fw_dLinkList_Block*, struct Fw_dLinkList**);
extern __INLINE fw_err_t Fw_dLinkList_Remove(struct Fw_dLinkList_Block*, struct Fw_dLinkList*);
extern __INLINE bool Fw_sLinkList_IsEmpty(struct Fw_sLinkList_Block*);
extern __INLINE bool Fw_dLinkList_IsEmpty(struct Fw_dLinkList_Block*);

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
#define p_PushLinkListNode(block, node) _ST(                                   \
    (node)->Next = NULL;                                                       \
                                                                               \
    if((block)->Head == NULL && (block)->Tail == NULL)                         \
    {                                                                          \
        (block)->Tail = node;                                                  \
        (block)->Head = node;                                                  \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        (block)->Tail->Next = node;                                            \
        (block)->Tail       = node;                                            \
    }                                                                          \
)                                                                       

/**
 *******************************************************************************
 * @brief       fifo pop
 * @param       [in/out]  block         block name
 * @param       [in/out]  popData       pop data
 * @note        None
 *******************************************************************************
 */   
#define p_PopLinkListNode(block, node) _ST(                                    \
    if((block)->Head == (block)->Tail)                                         \
    {                                                                          \
        (node)        = (block)->Head;                                         \
        (block)->Tail = NULL;                                                  \
        (block)->Head = NULL;                                                  \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        (node) = (block)->Head;                                                \
        (block)->Head = (node)->Next;                                          \
    }                                                                          \
                                                                               \
    (node)->Next = NULL;                                                       \
)   

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
