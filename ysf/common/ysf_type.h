/**
 ******************************************************************************
 * @file       ysf_type.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017年1月10日
 * @brief      ysf 数据类型头文件
 * @par        工作平台
 *                 Windows
 * @par        编译平台
 *                 GCC
 ******************************************************************************
 * @note
 * 1.XXXXX
 ******************************************************************************
 */

/**
 * @defgroup ysf数据类型配置
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_TYPE_H__
#define __YSF_TYPE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_COMPILER_PATH

/* Exported types ------------------------------------------------------------*/
typedef enum
{
   ysf_disable  = 0,
   ysf_enable = !ysf_disable,
}ysf_status_t;

/**@} */

/**
 * @name ysf 错误类型定义
 * @{
 */
enum
{
    YSF_ERR_NONE,              /** 无错误     */
    YSF_ERR_FAIL,              /** 失败错误   */
    
    YSF_ERR_NOT_READY,         /** 未就绪错误 */
    YSF_ERR_NOT_SUPPORT,       /** 不支持错误 */
    
    YSF_ERR_INVAILD_PTR,       /** 无效指针错误 */
    YSF_ERR_INVAILD_PARAM,     /** 无效参数错误 */

    YSF_ERR_IO,                /** IO错误     */
    
    YSF_ERR_BUG,               /** BUG错误    */
    YSF_ERR_UNKNOW,            /** 未知错误   */  
};

typedef int16_t ysf_err_t;
/**@} */

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf 编译器配置  */

/**********************************END OF FILE*********************************/
