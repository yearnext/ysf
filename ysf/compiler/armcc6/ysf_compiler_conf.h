/**
 ******************************************************************************
 * @file       ysf_mdk_compiler.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017��1��10��
 * @brief      ���������� ͷ�ļ�
 * @par        ����ƽ̨
 *                 ARM
 * @par        ����ƽ̨
 *                 MDK
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
#ifndef __YSF_ARMCC6_COMPILER_H__
#define __YSF_ARMCC6_COMPILER_H__

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
 * @name ARM Compiler 6����������
 * @{
 */
/**
 * @name ARM Compiler 6����ͷ�ļ�
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
    
/**@} */

/**
 * @name ARM Compiler 6��������
 * @{
 */
#define USE_ARM_CLANG_COMPILER

#pragma clang diagnostic ignored "-Wpadded" 
#pragma clang diagnostic ignored "-Wunused-parameter" 
#pragma clang diagnostic ignored "-Wswitch-enum" 
#pragma clang diagnostic ignored "-Warmcc-pragma-anon-unions"
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wunreachable-code-break"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wmissing-noreturn"

#define __FUNCNAME__            __func__
#define __YSF_FUNCNAME__        __func__

#define PRAGMA(pragma)          _Pragma(#pragma)

#if !defined(__CORTEX_M)
#define __ASM                   __asm
#define __INLINE                __inline
#define __STATIC_INLINE         static __inline
#endif

#define YSF_ASM                 __asm
#define YSF_INLINE              __inline
#define YSF_STATIC_INLINE       static __inline

#define YSF_SECTION(x)          __attribute__((section(x)))
#define YSF_UNUSED              __attribute__((unused))
#define YSF_USED                __attribute__((used))
#define YSF_WEAK                __weak
#define YSF_IMPORT_API          __declspec(dllimport)
#define YSF_EXPORT_API          __declspec(dllexport)

#define YSF_ENTER_CRITICAL()    __ASM volatile ("cpsid i" : : : "memory")
#define YSF_EXIT_CRITICAL()     __ASM volatile ("cpsie i" : : : "memory")

/**
 * @name ARM Compiler 6��������С��ģʽ���
 * @{
 */
#if __BYTE_ORDER__==__ORDER_BIG_ENDIAN__
    #define COMPILER_USE_BIG_ENDIAN
//    #warning The byte order of the compiler uses big endian mode!
#else
    #define COMPILER_USE_LITTLE_ENDIAN
//    #warning The byte order of the compiler uses little endian mode!
#endif
/**@} */

/**@} */

/**
 * @name ARM Compiler 6�������ֽڶ�������
 * @{
 */
#define ALIGN_HEAD(n)           PRAGMA(pack(push, n))
#define ALIGN_TAIL(n)           PRAGMA(pack(pop))
#define PACKED_HEAD             
#define PACKED_TAIL

#define YSF_ALIGN_HEAD(n)       PRAGMA(pack(push, n))
#define YSF_ALIGN_TAIL(n)       PRAGMA(pack(pop))
#define YSF_PACKED_HEAD         
#define YSF_PACKED_TAIL

/**@} */

#ifndef __stdint_h
/**
 * @name ARM Compiler 6�������������Ͷ���
 * @{
 */
typedef unsigned char           uint8_t;
typedef unsigned short          uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long long      uint64_t;

typedef char                    int8_t;
typedef short                   int16_t;
typedef int                     int32_t;
typedef long long               int64_t;

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

#ifndef __bool_true_false_are_defined
typedef enum
{
    false = 0,
    true = !false,
}bool;
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#if 1
typedef uint32_t ysf_addr_t;
#else
typedef uint64_t ysf_addr_t;
#endif
/**@} */

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf ����������  */

/**********************************END OF FILE*********************************/
