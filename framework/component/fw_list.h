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
 * @file       ysf_single_list.h                                               *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-18                                                      *
 * @brief      ysf single list head files                                      *
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_SINGLE_LIST_H__
#define __YSF_SINGLE_LIST_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_conf.h"
#include "core_path.h"
#include _COMM_TYPE_PATH

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf config
 *******************************************************************************
 */
#ifdef USE_YSF_SINGLE_LIST_COMPONENT
#if USE_YSF_SINGLE_LIST_COMPONENT
#define USE_YSF_SINGLE_LIST_API (1)
#else
#define USE_YSF_SINGLE_LIST_API (0)
#endif
    
/**
 *******************************************************************************
 * @brief       user config
 *******************************************************************************
 */
#else
#define USE_YSF_SINGLE_LIST_API (1)
#endif
    
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf single list type
 *******************************************************************************
 */
struct ysf_sList_t
{
    struct ysf_sList_t *next;
    uint8_t            user_data[];
};

/**
 *******************************************************************************
 * @brief       ysf single list fifo type
 *******************************************************************************
 */
struct ysf_sListFifo_t
{
    struct ysf_sList_t *head;
    struct ysf_sList_t *tail;
};

/**
 *******************************************************************************
 * @brief       define visit list function type
 *******************************************************************************
 */
typedef bool (*sListFunc)(void **, void **, void **);

/**
 *******************************************************************************
 * @brief       ysf single list api
 *******************************************************************************
 */
#if defined(USE_YSF_SINGLE_LIST_API) && USE_YSF_SINGLE_LIST_API
struct YSF_SLIST_API
{
    fw_err_t (*init)(void**);
    fw_err_t (*add)(void**, void **);
    fw_err_t (*del)(void**, void **);
    fw_err_t (*isExist)(void**, void **);
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define single list function interface
 *******************************************************************************
 */
#if defined(USE_YSF_SINGLE_LIST_API) && USE_YSF_SINGLE_LIST_API
extern bool ysf_slist_walk(void**, sListFunc, void**, void**);
extern bool ysf_slist_module_add(void**, void**, void**);
extern bool ysf_slist_module_del(void**, void**, void**);
extern bool ysf_slist_module_isExist(void**, void**, void**);
extern bool ysf_slist_module_findLastNode(void **, void**, void**);

extern fw_err_t ysf_slist_init(void**);
extern fw_err_t ysf_slist_add(void**, void**);
extern fw_err_t ysf_slist_del(void**, void**);
extern fw_err_t ysf_slist_isExist(void**, void**);

extern fw_err_t ysf_sListFifo_walk(struct ysf_sListFifo_t**, sListFunc, void**, void**);
extern bool ysf_sListFifo_isIn(struct ysf_sListFifo_t*, struct ysf_sList_t*);
extern fw_err_t ysf_sListFifo_push(struct ysf_sListFifo_t*, struct ysf_sList_t*);
extern fw_err_t ysf_sListFifo_pop(struct ysf_sListFifo_t*, struct ysf_sList_t*);
extern fw_err_t ysf_sListFifo_clear(struct ysf_sListFifo_t *);
extern fw_err_t ysf_sListFifo_init(struct ysf_sListFifo_t*);

#define DEFINE_SLIST_FIFO_CONTROL_BLOCK(type, name) struct                     \
                                                    {                          \
                                                        type *head;            \
                                                        type *tail;            \
                                                    } name =                   \
                                                    {                          \
                                                        .head = NULL,          \
                                                        .tail = NULL,          \
                                                    }
                                                    
#define ysf_sListFIFO_isIn(type, block, node)                                  \
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

#define ysf_sListFIFO_push(isInFunc, block, node)                              \
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

#define ysf_sListFIFO_pop(block, popData)                                      \
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

#define ysf_sListFIFO_clear(sListPOPFunc)                                      \
{                                                                              \
    while(sListPOPFunc() != NULL);                                             \
}

#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf single list component  */

/**********************************END OF FILE*********************************/
