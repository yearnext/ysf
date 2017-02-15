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
//#include <stdbool.h>
//#include <stdlib.h>
//#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
/**
 * @name ysf 基本数据类型定义
 * @{
 */
typedef unsigned char               ysf_uint8_t;
typedef unsigned short              ysf_uint16_t;
typedef unsigned int                ysf_uint32_t;
typedef unsigned long long          ysf_uint64_t;

typedef char                        ysf_int8_t;
typedef short                       ysf_int16_t;
typedef int                         ysf_int32_t;
typedef long long                   ysf_int64_t;

typedef ysf_uint8_t                 ysf_u8_t;
typedef ysf_uint16_t                ysf_u16_t;
typedef ysf_uint32_t                ysf_u32_t;

typedef volatile ysf_uint8_t        ysf_vu8_t;
typedef volatile ysf_uint16_t       ysf_vu16_t;
typedef volatile ysf_uint32_t       ysf_vu32_t;

typedef const ysf_uint8_t           ysf_cu8_t;
typedef const ysf_uint16_t          ysf_cu16_t;
typedef const ysf_uint32_t          ysf_cu32_t;

typedef volatile const ysf_uint8_t  ysf_vcu8_t;
typedef volatile const ysf_uint16_t ysf_vcu16_t;
typedef volatile const ysf_uint32_t ysf_vcu32_t;

typedef ysf_int8_t                  ysf_s8_t;
typedef ysf_int16_t                 ysf_s16_t;
typedef ysf_int32_t                 ysf_s32_t;

typedef volatile ysf_int8_t         ysf_vs8_t;
typedef volatile ysf_int16_t        ysf_vs16_t;
typedef volatile ysf_int32_t        ysf_vs32_t;

typedef const ysf_int8_t            ysf_cs8_t;
typedef const ysf_int16_t           ysf_cs16_t;
typedef const ysf_int32_t           ysf_cs32_t;

typedef volatile const ysf_int8_t   ysf_vcs8_t;
typedef volatile const ysf_int16_t  ysf_vcs16_t;
typedef volatile const ysf_int32_t  ysf_vcs32_t;

/**@} */

/**
 * @name ysf 布尔类型定义
 * @{
 */
#define YSF_FALSE 0
#define YSF_TRUE  1

typedef enum _YSF_BOOL_TYPE_
{
   ysf_false = 0,
   ysf_true = 1,
}ysf_bool_t;

/**@} */

/**
 * @name ysf 错误类型定义
 * @{
 */
typedef enum _YSF_ERR_TYPE_
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
}ysf_err_t;
/**@} */

/**
 * @name ysf 空指针定义
 * @{
 */
#define YSF_NULL ((void *)0)

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf 编译器配置  */

/**********************************END OF FILE*********************************/
