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
#include "ysf_path.h"
#include YSF_TYPE_PATH

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ysf single list type
 *******************************************************************************
 */
struct ysf_sList_t
{
    struct ysf_sList_t *next;
    uint8_t        data[];
};

typedef bool (*sListFunc)(void **, void **, void **);

struct YSF_SLIST_API
{
    ysf_err_t (*init)(void**);
    ysf_err_t (*add)(void**, void **);
    ysf_err_t (*del)(void**, void **);
    ysf_err_t (*isExist)(void**, void **);
};

/* Exported variables --------------------------------------------------------*/
extern const struct YSF_SLIST_API ysf_sList;

/* Exported functions --------------------------------------------------------*/
extern bool ysf_slist_walk(void**, sListFunc, void**, void**);
extern bool ysf_slist_module_add(void**, void**, void**);
extern bool ysf_slist_module_del(void**, void**, void**);
extern bool ysf_slist_module_isExist(void**, void**, void**);
extern bool ysf_slist_module_findLastNode(void **, void**, void**);

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
