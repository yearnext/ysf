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

/** @}*/     /* ysf ����������  */

/**********************************END OF FILE*********************************/
