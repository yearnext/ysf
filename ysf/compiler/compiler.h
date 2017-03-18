/**
 ******************************************************************************
 * @file       compiler.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017Äê1ÔÂ10ÈÕ
 * @brief      compiler head file
 * @par        work platform
 *                 Windows
 * @par        compiler platform
 *                 GCC
 ******************************************************************************
 * @note
 * 1.currenly support only the armcc5 compiler, armcc6 compiler and iararm compiler
 ******************************************************************************
 */

/**
 * @defgroup compiler config
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

/** @}*/     /** compiler config  */

/**********************************END OF FILE*********************************/
