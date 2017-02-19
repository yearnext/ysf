/**
 ******************************************************************************
 * @file       ysf_compiler.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017��1��10��
 * @brief      ���������� ͷ�ļ�
 * @par        ����ƽ̨
 *                 Windows
 * @par        ����ƽ̨
 *                 GCC
 ******************************************************************************
 * @note
 * 1.Ŀǰ��֧��IAR ARM��������MDK ARM��������GCC��������Visual Studio��������
 ******************************************************************************
 */

/**
 * @defgroup ynf����
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
#include "../ysf/compiler/iccarm/ysf_compiler_conf.h"
#elif defined(__CC_ARM)
#include "../ysf/compiler/mdk/ysf_compiler_conf.h"
#elif defined(_MSC_BUILD)
#include "../ysf/compiler/vs/ysf_compiler_conf.h"
#elif defined(__GNUC__)
#include "../ysf/compiler/gcc/ysf_compiler_conf.h"
#else
#include "../ysf/compiler/simulation/ysf_compiler_conf.h"
#endif

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf ����������  */

/**********************************END OF FILE*********************************/
