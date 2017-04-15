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
 * @brief      framework link list component head files                        *
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
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_LINK_LIST_H__
#define __FRAMEWORK_LINK_LIST_H__

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
#define USE_FRAMEWORK_SINGLE_LIST_API                                        (1)
#else
#define USE_FRAMEWORK_SINGLE_LIST_API                                        (0)
#endif
    
/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
#define USE_FRAMEWORK_SINGLE_LIST_API                                        (1)
#endif
    
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework single link list type
 *******************************************************************************
 */
struct fw_slinklist_t
{
    struct fw_slinklist_t *next;
    uint8_t               user_data[];
};

/**
 *******************************************************************************
 * @brief       framework single link list fifo type
 *******************************************************************************
 */
struct fw_slinklist_fifo_t
{
    struct fw_slinklist_t *head;
    struct fw_slinklist_t *tail;
};

///**
// *******************************************************************************
// * @brief       define visit list function type
// *******************************************************************************
// */
//typedef bool (*SLinkListFunc)(void **, void **, void **);

/**
 *******************************************************************************
 * @brief       ysf single list api
 *******************************************************************************
 */
#if USE_FRAMEWORK_SINGLE_LIST_API
struct FRAMEWORK_SINGLE_LINK_LIST_API
{
    fw_err_t (*Init)(void**);
    bool     (*Walk)(void**, bool (*)(void**, void**, void**), void**, void**);
    fw_err_t (*Add)(void**, void **);
    fw_err_t (*Del)(void**, void **);
    fw_err_t (*IsExist)(void**, void **);
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define single list function interface
 *******************************************************************************
 */
#if USE_FRAMEWORK_SINGLE_LIST_API
extern bool fw_slinklist_walk(void**, bool (*)(void**, void**, void**), void**, void**);
extern bool fw_slinklist_module_add(void**, void**, void**);
extern bool fw_slinklist_module_del(void**, void**, void**);
extern bool fw_slinklist_module_isExist(void**, void**, void**);
extern bool fw_slinklist_module_findLastNode(void **, void**, void**);

extern fw_err_t fw_slinklist_init(void**);
extern fw_err_t fw_slinklist_add(void**, void**);
extern fw_err_t fw_slinklist_del(void**, void**);
extern fw_err_t fw_slinklist_isExist(void**, void**);

/**
 *******************************************************************************
 * @brief       define signle link list fifo control block
 * @param       [in/out]  type          fifo type
 * @param       [in/out]  name          block name
 * @note        None
 *******************************************************************************
 */
#define DEFINE_SINGLE_LINK_LIST_FIFO_BLOCK(type, name) struct                  \
                                                       {                       \
                                                           type *head;         \
                                                           type *tail;         \
                                                       } name =                \
                                                       {                       \
                                                           .head = NULL,       \
                                                           .tail = NULL,       \
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
#define fw_slinklistfifo_isIn(type, block, node)                               \
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
        temp = temp->next;                                                     \
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
#define fw_slinklistfifo_push(isInFunc, block, node)                           \
{                                                                              \
    if( isInFunc(node) == false )                                              \
    {                                                                          \
        node->next = NULL;                                                     \
                                                                               \
        if(block.tail != NULL)                                                 \
        {                                                                      \
            block.tail->next = node;                                           \
            block.tail       = node;                                           \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            block.head       = node;                                           \
            block.tail       = node;                                           \
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
#define fw_slinklistfifo_pop(block, popData)                                   \
{                                                                              \
    if( block.head == NULL )                                                   \
    {                                                                          \
        block.tail = NULL;                                                     \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    popData       = block.head;                                                \
    block.head    = block.head->next;                                          \
    popData->next = NULL;                                                      \
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
#define fw_slinklistfifo_clear(sListPOPFunc)                                   \
{                                                                              \
    while(sListPOPFunc() != NULL);                                             \
}

#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework link list component */

/**********************************END OF FILE*********************************/
