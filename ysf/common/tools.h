/**
 ******************************************************************************
 * @file       ysf_commtools.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017年1月10日
 * @brief      ysf 通用工具配置头文件
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
 * @defgroup ysf 通用工具配置
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_COMMON_TOOLS_H__
#define __YSF_COMMON_TOOLS_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/**
 * @name ynf 应用工具
 * @{
 */
/** 变量名转换字符串宏 */
#define Name2String(name)    (#name)

/** 计算类型所占内存的字节大小 */
#define YSF_CalTypeByteSize(type) (sizeof(type) / sizeof(unsigned char))

/** 计算类型所占内存的位数大小 */
#define YSF_CalTypeBitSize(type)  (YSF_CalTypeByteSize(type) * 8)

/** 计算余数 */
#define YSF_CalRemainder(dividend,divisor) ((dividend)%(divisor))

/** 计算是否存在余数 */
#define YSF_CheckRemainder(dividend,divisor) ((((dividend)%(divisor)) != 0 ) \
                                             ? (1) : (0))
                                             
/**@} */
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf 通用工具配置  */

/**********************************END OF FILE*********************************/
