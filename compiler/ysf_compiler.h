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
/**
 * @name ����������
 * @{
 */

/**
 * @name IAR ARM����������
 * @{
 */
#if defined(__ICCARM__)
/**
 * @name IAR ARM����ͷ�ļ�
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
/**@} */

/**
 * @name IAR ARM��������
 * @{
 */
#define __FUNCNAME__            __func__
#define __YSF_FUNCNAME__        __func__

#define PRAGMA(pragma)          _Pragma(#pragma)

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
/**@} */

/**
 * @name IAR ARM�������ֽڶ�������
 * @{
 */
#define PACKED_HEAD(n)          PRAGMA(data_alignment = n)
#define PACKED_TAIL(n)
#define PACKED(type)            PRAGMA(data_alignment = 1) type;
#define ALIGNMENT(n,type)       PRAGMA(data_alignment = 1) type;

#define YSF_PACKED_HEAD(n)      PRAGMA(data_alignment = n)
#define YSF_PACKED_TAIL(n)
#define PACKED(type)            PRAGMA(data_alignment = n) type;
#define ALIGNMENT(n,type)       PRAGMA(data_alignment = n) type;
/**@} */

/**@} */

/**
 * @name ARM Compiler 5����������
 * @{
 */

#elif defined(__CC_ARM)
/**
 * @name ARM Compiler 5����ͷ�ļ�
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
/**@} */

/**
 * @name ARM Compiler 5��������
 * @{
 */
#define __FUNCNAME__            __func__
#define __YSF_FUNCNAME__        __func__

#define PRAGMA(pragma)

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
/**@} */

/**
 * @name ARM Compiler 5�������ֽڶ�������
 * @{
 */
#define PACKED_HEAD(n)          __attribute__ ((aligned(n)))
#define PACKED_TAIL(n)
#define PACKED(type)            __attribute__ ((aligned(1))) type;
#define ALIGNMENT(n,type)       __attribute__ ((aligned(n))) type;

#define YSF_PACKED_HEAD(n)      __attribute__ ((aligned(n)))
#define YSF_PACKED_TAIL(n)
#define YSF_PACKED(type)        __attribute__ ((aligned(1))) type;
#define YSF_ALIGNMENT(n,type)   __attribute__ ((aligned(n))) type;
/**@} */

/**@} */

/**
 * @name ARM Compiler 6����������
 * @{
 */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
/**
 * @name ARM Compiler 6����ͷ�ļ�
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
/**@} */

/**
 * @name ARM Compiler 6��������
 * @{
 */
#define __FUNCNAME__            __func__
#define __YSF_FUNCNAME__        __func__

#define PRAGMA(pragma)

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
/**@} */

/**
 * @name ARM Compiler 6�������ֽڶ�������
 * @{
 */
#define PACKED_HEAD(n)          __attribute__ ((aligned(n)))
#define PACKED_TAIL(n)
#define PACKED(type)            __attribute__ ((aligned(1))) type;
#define ALIGNMENT(n,type)       __attribute__ ((aligned(n))) type;

#define YSF_PACKED_HEAD(n)      __attribute__ ((aligned(n)))
#define YSF_PACKED_TAIL(n)
#define YSF_PACKED(type)        __attribute__ ((aligned(1))) type;
#define YSF_ALIGNMENT(n,type)   __attribute__ ((aligned(n))) type;
/**@} */

/**@} */

/**
 * @name Visual Studio����������
 * @{
 */
#elif defined(_MSC_BUILD)
/**
 * @name Visual Studio����ͷ�ļ�
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
/**@} */

/**
 * @name Visual Studio��������������
 * @{
 */
#define __FUNCNAME__            __func__
#define __YSF_FUNCNAME__        __func__

#define PRAGMA(pragma)          __pragma(#pragma)

#if !defined(__CORTEX_M)
#define __ASM
#define __INLINE                inline
#define __STATIC_INLINE         static inline
#endif

#define YSF_ASM
#define YSF_INLINE              inline
#define YSF_STATIC_INLINE       static inline

#define YSF_SECTION(x)
#define YSF_UNUSED
#define YSF_USED
#define YSF_WEAK
#define YSF_IMPORT_API          __declspec(dllimport)
#define YSF_EXPORT_API          __declspec(dllexport)
/**@} */

/**
 * @name Visual Studio�������ֽڶ�������
 * @{
 */
#define PACKED_HEAD(n)          PRAGMA(pack(push, n))
#define PACKED_TAIL(n)          PRAGMA(pack(pop))
#define PACKED(type)            PRAGMA(pack(push, 1)) \
                                    type;               \
                                PRAGMA(pack(pop))
#define ALIGNMENT(n,type)       PRAGMA(pack(push, n)) \
                                    type;               \
                                PRAGMA(pack(pop))

#define YSF_PACKED_HEAD(n)      PRAGMA(pack(push, n))
#define YSF_PACKED_TAIL(n)      PRAGMA(pack(pop))
#define YSF_PACKED(type)        PRAGMA(pack(push, 1)) \
                                    type;               \
                                PRAGMA(pack(pop))
#define YSF_ALIGNMENT(n,type)   PRAGMA(pack(push, n)) \
                                    type;               \
                                PRAGMA(pack(pop))

/**@} */

/**
 * @name GCC����������
 * @{
 */
#elif defined(__GNUC__)
/**
 * @name GCC����������ͷ�ļ�
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
/**@} */

/**
 * @name GCC��������������
 * @{
 */
#define __FUNCNAME__            __func__
#define __YSF_FUNCNAME__        __func__

#define PRAGMA(pragma)

#if !defined(__CORTEX_M)
#define __ASM                   __asm
#define __INLINE                inline
#define __STATIC_INLINE         static inline
#endif

#define YSF_ASM                 __asm
#define YSF_INLINE              inline
#define YSF_STATIC_INLINE       static inline

#define YSF_SECTION(x)          __attribute__((section(x)))
#define YSF_UNUSED              __attribute__((unused))
#define YSF_USED                __attribute__((used))
#define YSF_WEAK                __attribute__((weak))
#define YSF_IMPORT_API          __declspec(dllimport)
#define YSF_EXPORT_API          __declspec(dllexport)
/**@} */

/**
 * @name GCC�������ֽڶ�������
 * @{
 */
#define PACKED_HEAD(n)          __attribute__ ((aligned(n)))
#define PACKED_TAIL(n)
#define PACKED(type)            __attribute__ ((aligned(1))) type;
#define ALIGNMENT(n,type)       __attribute__ ((aligned(n))) type;

#define YSF_PACKED_HEAD(n)      __attribute__ ((aligned(n)))
#define YSF_PACKED_TAIL(n)
#define YSF_PACKED(type)        __attribute__ ((aligned(1))) type;
#define YSF_ALIGNMENT(n,type)   __attribute__ ((aligned(n))) type;
/**@} */

/**@} */

#else
	#error  ysf unsupported compilers!
#endif

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf ����������  */

/**********************************END OF FILE*********************************/
