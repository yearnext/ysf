/**
 ******************************************************************************
 * @file       ysf_single_list.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017Äê2ÔÂ18ÈÕ
 * @brief      ysf single list source file
 * @par        work paltform                                  
 *                 Windows
 * @par        compiler paltform									                         
 *                 GCC
 ******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup ysf single list component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_COMPONENT_SINGLE_LIST_PATH
#include YSF_TYPE_PATH
#include YSF_COMPONENT_DEBUG_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
ysf_err_t ysf_slist_init( void **listHead )
{
    ysf_assert(IS_PTR_NULL(listHead));

    *listHead = NULL;

    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       single list traversal function
 * @param       [in/out]  **listHead        single list head
 * @param       [in/out]  func              single list visit function
 * @param       [in/out]  **ctx             context
 * @param       [in/out]  **expand          expand
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
 * @param       [in/out]  **listHead        now single list node
 * @param       [in/out]  **ctx             wait add node
 * @param       [in/out]  **expand          expand
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

ysf_err_t ysf_slist_add( void **listHead, void **ctx )
{
    ysf_assert(IS_PTR_NULL(listHead));
    ysf_assert(IS_PTR_NULL(*ctx));

    if( ysf_slist_walk(listHead, ysf_slist_module_add, ctx, NULL) == false )
    {
        return YSF_ERR_FAIL;
    }

    return YSF_ERR_NONE;
}

ysf_err_t ysf_slist_del( void **listHead, void **ctx )
{
    ysf_assert(IS_PTR_NULL(listHead));
    ysf_assert(IS_PTR_NULL(*ctx));

    if( ysf_slist_walk(listHead, ysf_slist_module_del, ctx, NULL) == false )
    {
        return YSF_ERR_FAIL;
    }

    return YSF_ERR_NONE;
}

ysf_err_t ysf_slist_isExist( void **listHead, void **ctx )
{
    ysf_assert(IS_PTR_NULL(listHead));
    ysf_assert(IS_PTR_NULL(*ctx));

    if( ysf_slist_walk(listHead, ysf_slist_module_isExist, ctx, NULL) == false )
    {
        return YSF_ERR_FAIL;
    }

    return YSF_ERR_NONE;
}

/** @}*/     /* ysf single list component  */

/**********************************END OF FILE*********************************/
