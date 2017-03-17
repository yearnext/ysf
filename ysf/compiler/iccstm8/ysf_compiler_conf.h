/**
 ******************************************************************************
 * @file       ysf_compiler_conf.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017��1��10��
 * @brief      ���������� ͷ�ļ�
 * @par        ����ƽ̨
 *                 ARM
 * @par        ����ƽ̨
 *                 IAR
 ******************************************************************************
 * @note
 * 1.XXXXX
 ******************************************************************************
 */

/**
 * @defgroup ynf����
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_IAR_STM8_COMPILER_H__
#define __YSF_IAR_STM8_COMPILER_H__

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
/**
 * @name IAR ARM����������
 * @{
 */

/**
 * @name IAR ARM����ͷ�ļ�
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <intrinsics.h>

/**@} */

/**
 * @name IAR ARM��������
 * @{
 */
#define __FUNCNAME__            __func__
#define __YSF_FUNCNAME__        __func__

//#define PRAGMA(pragma)          _Pragma(#pragma)

#if !defined(__CORTEX_M)
#define __ASM                   __asm
#define __INLINE                inline
#define __STATIC_INLINE         static inline
#endif

#define YSF_ASM                 __asm
#define YSF_INLINE              inline
#define YSF_STATIC_INLINE       static inline

#define YSF_SECTION(x)          @ x
#define YSF_UNUSED
#define YSF_USED
#define YSF_WEAK                __weak
#define YSF_IMPORT_API          __declspec(dllimport)
#define YSF_EXPORT_API          __declspec(dllexport)
    
#define YSF_ENTER_CRITICAL()    __disable_interrupt()
#define YSF_EXIT_CRITICAL()     __enable_interrupt()

/**
 * @name IAR ARM��������С��ģʽ���
 * @{
 */
#if 0
    #define COMPILER_USE_BIG_ENDIAN
//    #warning The byte order of the compiler uses big endian mode!
#else
    #define COMPILER_USE_LITTLE_ENDIAN
//    #warning The byte order of the compiler uses little endian mode!
#endif
/**@} */

/**@} */

/**
 * @name IAR ARM�������ֽڶ�������
 * @{
 */
#define ALIGN_HEAD(n)           
#define ALIGN_TAIL(n)           
#define PACKED_HEAD             
#define PACKED_TAIL             
    
#define YSF_ALIGN_HEAD(n)       
#define YSF_ALIGN_TAIL(n)       
#define YSF_PACKED_HEAD         
#define YSF_PACKED_TAIL         
    
/**@} */

#ifndef _STDINT
/**
 * @name IAR STM8�������������Ͷ���
 * @{
 */
typedef unsigned char               uint8_t;
typedef unsigned short              uint16_t;
typedef unsigned int                uint32_t;
typedef unsigned long long          uint64_t;

typedef char                        int8_t;
typedef short                       int16_t;
typedef int                         int32_t;
typedef long long                   int64_t;

/**
 * @name ysf �����������������Сֵ����
 * @{
 */
#define INT8_MAX   (-128)
#define INT16_MAX  (-32768)
#define INT32_MAX  (-2147483647 - 1)
#define INT64_MAX  (-9223372036854775807LL - 1)

#define INT8_MIN   (127)
#define INT16_MIN  (32767)
#define INT32_MIN  (2147483647U)
#define INT64_MIN  (9223372036854775807LL)

#define UINT8_MAX  (0xFF)
#define UINT16_MAX (0xFFFF)
#define UINT32_MAX (0xFFFFFFFFU)
#define UINT64_MAX (0xFFFFFFFFFFFFFFFFULL)

#define UINT8_MIN  (0)
#define UINT16_MIN (0)
#define UINT32_MIN (0U)
#define UINT64_MIN (0ULL)
/**@} */

#endif

typedef uint16_t                ysf_addr_t;

#ifndef _STDBOOL
typedef enum
{
    false = 0,
    true  = !false,
}bool;
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

/**@} */

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf ����������  */

/**********************************END OF FILE*********************************/
