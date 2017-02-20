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
#include "../ysf/component/list/ysf_single_list.h"
#include "../ysf/common/ysf_type.h"
#include "../ysf/component/debug/ysf_debug.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
const struct _YSF_S_LIST_API_ ysf_sList =
{
    .init        = ysf_slist_init,
    .add         = ysf_slist_add,
    .del         = ysf_slist_del,
    .isExist     = ysf_slist_isExist,
};

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
ysf_err_t ysf_slist_init( void **listHead )
{
    ysf_assert(IS_PTR_NULL(listHead));

    *listHead = YSF_NULL;

    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       single list traversal function
 * @param       [in/out]  **listHead        single list head
 * @param       [in/out]  func              single list visit function
 * @param       [in/out]  **ctx             context
 * @param       [in/out]  **expand          expand
 * @return      [in/out]  YSF_TRUE          visit success
 * @return      [in/out]  YSF_FALSE         visit failed
 * @note        None
 *******************************************************************************
 */
ysf_bool_t ysf_slist_traversal(void **listHead,
                               sListFunc func,
                               void **ctx,
                               void **expand)
{
    ysf_bool_t status = YSF_FALSE;
    ysf_s_list_t **sList = (ysf_s_list_t **)listHead;

    while(1)
    {
        status = func((void **)sList, ctx, expand);

        if( status == YSF_TRUE || *sList == YSF_NULL )
        {
            break;
        }

        sList = (ysf_s_list_t **)(&((ysf_s_list_t *)(*sList))->next);
    }

    return status;
}

/**
 *******************************************************************************
 * @brief       add node to signle list
 * @param       [in/out]  **listHead        now single list node
 * @param       [in/out]  **ctx             wait add node
 * @param       [in/out]  **expand          expand
 * @return      [in/out]  YSF_TRUE          add node success
 * @return      [in/out]  YSF_FALSE         add node failed
 * @note        None
 *******************************************************************************
 */
ysf_bool_t ysf_slist_module_add( void **node, void **ctx, void **expand )
{
    ysf_assert(IS_PTR_NULL(*ctx));

    ysf_bool_t status = YSF_FALSE;
    ysf_s_list_t *temp = (ysf_s_list_t *)(*ctx);

    if( *node == YSF_NULL )
    {
        temp->next = YSF_NULL;
        *node = *ctx;

        status = YSF_TRUE;
    }
    else  if( *node == *ctx )
    {
        temp = ((ysf_s_list_t *)(*node))->next;

        *node = *ctx;
        ((ysf_s_list_t *)(*node))->next = temp;

        status = YSF_TRUE;
    }
    else
    {
        /** do nothing! */
    }

    return status;
}

ysf_bool_t ysf_slist_module_del( void **node, void **ctx, void **expand )
{
    ysf_assert(IS_PTR_NULL(*ctx));

    ysf_s_list_t *now = (ysf_s_list_t *)(*node);
    ysf_s_list_t *next = (ysf_s_list_t *)(*ctx);

    ysf_bool_t status = YSF_FALSE;

    if( now == YSF_NULL )
    {
        return YSF_FALSE;
    }

    if( *node == *ctx )
    {
        *node = now->next;

        status = YSF_TRUE;
    }
    else if( now->next == *ctx )
    {
        now->next  = next->next;
        next->next = YSF_NULL;

        status = YSF_TRUE;
    }
    else
    {
        /** do nothing! */
    }

    return status;
}

ysf_bool_t ysf_slist_module_isExist( void **node, void **ctx, void **expand )
{
    ysf_assert(IS_PTR_NULL(*ctx));

    ysf_bool_t status = YSF_FALSE;

    if( *node == YSF_NULL )
    {
        return YSF_FALSE;
    }

    if( *node == *ctx )
    {
        status = YSF_TRUE;
    }

    return status;
}

ysf_bool_t ysf_slist_module_findLastNode( void **node, void **ctx, void **expand )
{
    ysf_bool_t status = YSF_FALSE;

    ysf_s_list_t *now = (ysf_s_list_t *)(*node);

    if( *node == YSF_NULL )
    {
        return YSF_FALSE;
    }

    if( now->next == ctx )
    {
        *expand = now;
        return YSF_TRUE;
    }

    return status;
}

ysf_err_t ysf_slist_add( void **listHead, void **ctx )
{
    ysf_assert(IS_PTR_NULL(listHead));
    ysf_assert(IS_PTR_NULL(*ctx));

    if( ysf_slist_traversal(listHead, ysf_slist_module_add, ctx, YSF_NULL) == YSF_FALSE)
    {
        return YSF_ERR_FAIL;
    }

    return YSF_ERR_NONE;
}

ysf_err_t ysf_slist_del( void **listHead, void **ctx )
{
    ysf_assert(IS_PTR_NULL(listHead));
    ysf_assert(IS_PTR_NULL(*ctx));

    if( ysf_slist_traversal(listHead, ysf_slist_module_del, ctx, YSF_NULL) == YSF_FALSE)
    {
        return YSF_ERR_FAIL;
    }

    return YSF_ERR_NONE;
}

ysf_err_t ysf_slist_isExist( void **listHead, void **ctx )
{
    ysf_assert(IS_PTR_NULL(listHead));
    ysf_assert(IS_PTR_NULL(*ctx));

    if( ysf_slist_traversal(listHead, ysf_slist_module_isExist, ctx, YSF_NULL) == YSF_FALSE)
    {
        return YSF_ERR_FAIL;
    }

    return YSF_ERR_NONE;
}

/** @}*/     /* ysf single list component  */

/**********************************END OF FILE*********************************/
