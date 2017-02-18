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
typedef ysf_bool_t (*sListFunc)(void **, void **, void **);

typedef struct
{
    sListFunc addNode;
    sListFunc delNode;
}ysf_sList_func_list_t;

/* Exported variables --------------------------------------------------------*/
extern const ysf_sList_func_list_t ysf_sList;

/* Exported functions --------------------------------------------------------*/
extern ysf_bool_t ysf_single_list_traversal(void**, sListFunc, void**, void**);
extern ysf_bool_t ysf_slist_add( void**, void**, void** );
extern ysf_bool_t ysf_slist_del( void**, void**, void** );

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf single list component  */

/**********************************END OF FILE*********************************/
