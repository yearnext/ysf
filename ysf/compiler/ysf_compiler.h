/**
 ******************************************************************************
 * @file       ysf_compiler.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017年1月10日
 * @brief      编译器配置 头文件
 * @par        工作平台
 *                 Windows
 * @par        编译平台
 *                 GCC
 ******************************************************************************
 * @note
 * 1.目前仅支持IAR ARM编译器、MDK ARM编译器、GCC编译器、Visual Studio编译器。
 ******************************************************************************
 */

/**
 * @defgroup ynf配置
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_COMPILER_H__
#define __YSF_COMPILER_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
	
#if defined(__ICCARM__)
#include YSF_ICCARM_COMPILER_CONF_PATH
#elif defined(__CC_ARM)
#include YSF_ARMCC5_COMPILER_CONF_PATH
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#include YSF_ARMCC6_COMPILER_CONF_PATH
#elif defined(_MSC_BUILD)
#include YSF_VS_COMPILER_CONF_PATH
#elif defined(__GNUC__)
#include YSF_GCC_COMPILER_CONF_PATH
#elif defined(__ICCSTM8__)
#include YSF_ICC_STM8_COMPILER_CONF_PATH
#else
#include YSF_SIMULATION_COMPILER_CONF_PATH
#endif

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf 编译器配置  */

/**********************************END OF FILE*********************************/
