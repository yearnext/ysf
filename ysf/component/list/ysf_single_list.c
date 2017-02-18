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
/**
 *******************************************************************************
 * @brief       ysf single list type
 *******************************************************************************
 */
typedef struct _YSF_SINGLE_LIST_TYPE_
{
    void     *next;
    ysf_u8_t data[];
}ysf_s_list_t;

/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
const ysf_sList_func_list_t ysf_sList =
{
    .addNode = ysf_slist_add,
    .delNode = ysf_slist_del,
};

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
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
    ysf_assert(IS_PTR_NULL(listHead));

    ysf_bool_t status = YSF_FALSE;
    ysf_s_list_t **sList = (ysf_s_list_t **)listHead;

    while(1)
    {
        status = func((void **)listHead, ctx, expand);

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
ysf_bool_t ysf_slist_add( void **listHead, void **ctx, void **expand )
{
    ysf_assert(IS_PTR_NULL(*ctx));

    ysf_bool_t status = YSF_FALSE;

    if( *listHead == YSF_NULL )
    {
        *listHead = *ctx;

        status = YSF_TRUE;
    }

    return status;
}

/**
 *******************************************************************************
 * @brief       del node from signle list
 * @param       [in/out]  **listHead        now single list node
 * @param       [in/out]  **ctx             wait del node
 * @param       [in/out]  **expand          expand
 * @return      [in/out]  YSF_TRUE          del node success
 * @return      [in/out]  YSF_FALSE         del node failed
 * @note        None
 *******************************************************************************
 */
ysf_bool_t ysf_slist_del( void **listHead, void **ctx, void **expand )
{
    ysf_assert(IS_PTR_NULL(*ctx));

    ysf_s_list_t *now = (ysf_s_list_t *)(*listHead);
    ysf_s_list_t *next = (ysf_s_list_t *)(*ctx);

    ysf_bool_t status = YSF_FALSE;

    if( *listHead == *ctx )
    {
        *listHead = now->next;

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

/** @}*/     /* ysf single list component  */

/**********************************END OF FILE*********************************/
