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
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if defined(__ICCARM__)
#include "..\framework\compiler\ysf_iar_arm_compiler.h"
#elif defined(__CC_ARM)
#include "..\framework\compiler\ysf_mdk_compiler.h"
#elif defined(_MSC_BUILD)
#include "..\framework\compiler\ysf_vs_compiler.h"
#elif defined(__GNUC__)
#include "..\framework\compiler\ysf_gcc_compiler.h"
#else
#include "..\framework\compiler\ysf_simulation_compiler.h"
#endif

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf 编译器配置  */

/**********************************END OF FILE*********************************/
