/**
 ******************************************************************************
 * @file       ysf_single_list.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017Äê2ÔÂ18ÈÕ
 * @brief      ysf single list head file
 * @par        work paltform		                             
 *                 Windows
 * @par        compiler paltform									                         
 * 				   GCC
 ******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 ******************************************************************************
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
#include "../ysf/common/ysf_type.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
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

typedef ysf_bool_t (*sListFunc)(void **, void **, void **);

struct _YSF_S_LIST_API_
{
    ysf_err_t (*init)(void**);
    ysf_err_t (*add)(void**, void **);
    ysf_err_t (*del)(void**, void **);
    ysf_err_t (*isExist)(void**, void **);
};

/* Exported variables --------------------------------------------------------*/
extern const struct _YSF_S_LIST_API_ ysf_sList;

/* Exported functions --------------------------------------------------------*/
extern ysf_bool_t ysf_slist_traversal(void**, sListFunc, void**, void**);
extern ysf_bool_t ysf_slist_module_add(void**, void**, void**);
extern ysf_bool_t ysf_slist_module_del(void**, void**, void**);
extern ysf_bool_t ysf_slist_module_isExist(void**, void**, void**);

extern ysf_err_t ysf_slist_init(void**);
extern ysf_err_t ysf_slist_add(void**, void**);
extern ysf_err_t ysf_slist_del(void**, void**);
extern ysf_err_t ysf_slist_isExist(void**, void**);
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf single list component  */

/**********************************END OF FILE*********************************/
