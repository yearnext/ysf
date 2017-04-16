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
}SingleListInterface;
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

extern fw_err_t SingleListInit(void**);
extern fw_err_t SingleListAdd(void**, void**);
extern fw_err_t SingleListDel(void**, void**);
extern fw_err_t SingleListIsExits(void**, void**);

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
                                                             type *head;       \
                                                             type *tail;       \
                                                         } name =              \
                                                         {                     \
                                                             .head = NULL,     \
                                                             .tail = NULL,     \
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
#define SingleListFifoIsIn(type, block, node)                                  \
{                                                                              \
    type *temp = block.head;                                                   \
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
#define SingleListFifoPush(isInFunc, block, pushData)                          \
{                                                                              \
    if( isInFunc(pushData) == false )                                          \
    {                                                                          \
        pushData->Next = NULL;                                                 \
                                                                               \
        if(block.tail != NULL)                                                 \
        {                                                                      \
            block.tail->Next = pushData;                                       \
            block.tail       = pushData;                                       \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            block.head       = pushData;                                       \
            block.tail       = pushData;                                       \
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
 * @param       [in/out]  name          block name
 * @param       [in/out]  popData       pop data
 * @note        None
 *******************************************************************************
 */   
#define SingleListFifoPop(block, popData)                                      \
{                                                                              \
    if( block.head == NULL )                                                   \
    {                                                                          \
        block.tail = NULL;                                                     \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    popData       = block.head;                                                \
    block.head    = block.head->Next;                                          \
    popData->Next = NULL;                                                      \
                                                                               \
    if( block.head == NULL )                                                   \
    {                                                                          \
        block.tail = NULL;                                                     \
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
#define SingleListFifoClear(sListPOPFunc)                                      \
{                                                                              \
    while(sListPOPFunc() != NULL);                                             \
}

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** link list component */

/**********************************END OF FILE*********************************/
