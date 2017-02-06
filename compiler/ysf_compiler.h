/**
 ******************************************************************************
 * @file       ysf_compiler.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017ƒÍ1‘¬10»’
 * @brief      ±‡“Î∆˜≈‰÷√ Õ∑Œƒº˛
 * @par        π§◊˜∆ΩÃ®
 *                 Windows
 * @par        ±‡“Î∆ΩÃ®
 *                 GCC
 ******************************************************************************
 * @note
 * 1.ƒø«∞Ωˆ÷ß≥÷IAR ARM±‡“Î∆˜°¢MDK ARM±‡“Î∆˜°¢GCC±‡“Î∆˜°¢Visual Studio±‡“Î∆˜°£
 ******************************************************************************
 */

/**
 * @defgroup ynf≈‰÷√
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
 * @name ±‡“Î∆˜≈‰÷√
 * @{
 */

/**
 * @name IAR ARM±‡“Î∆˜≈‰÷√
 * @{
 */
#if defined(__ICCARM__)
/**
 * @name IAR ARM∞¸∫¨Õ∑Œƒº˛
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
/**@} */

/**
 * @name IAR ARM±‡“Î∆˜∫Í
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
 * @name IAR ARM±‡“Î∆˜◊÷Ω⁄∂‘∆Î≈‰÷√
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
 * @name ARM Compiler 5±‡“Î∆˜≈‰÷√
 * @{
 */

#elif defined(__CC_ARM)
/**
 * @name ARM Compiler 5∞¸∫¨Õ∑Œƒº˛
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
/**@} */

/**
 * @name ARM Compiler 5±‡“Î∆˜∫Í
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
 * @name ARM Compiler 5±‡“Î∆˜◊÷Ω⁄∂‘∆Î≈‰÷√
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
 * @name ARM Compiler 6±‡“Î∆˜≈‰÷√
 * @{
 */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
/**
 * @name ARM Compiler 6∞¸∫¨Õ∑Œƒº˛
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
/**@} */

/**
 * @name ARM Compiler 6±‡“Î∆˜∫Í
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
 * @name ARM Compiler 6±‡“Î∆˜◊÷Ω⁄∂‘∆Î≈‰÷√
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
 * @name Visual Studio±‡“Î∆˜≈‰÷√
 * @{
 */
#elif defined(_MSC_BUILD)
/**
 * @name Visual Studio∞¸∫¨Õ∑Œƒº˛
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
/**@} */

/**
 * @name Visual Studio±‡“Î∆˜∫Ø ˝√˚≥∆
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
 * @name Visual Studio±‡“Î∆˜◊÷Ω⁄∂‘∆Î≈‰÷√
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
 * @name GCC±‡“Î∆˜≈‰÷√
 * @{
 */
#elif defined(__GNUC__)
/**
 * @name GCC±‡“Î∆˜∞¸∫¨Õ∑Œƒº˛
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
/**@} */

/**
 * @name GCC±‡“Î∆˜∫Ø ˝√˚≥∆
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
 * @name GCC±‡“Î∆˜◊÷Ω⁄∂‘∆Î≈‰÷√
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

/** @}*/     /* ysf ±‡“Î∆˜≈‰÷√  */

/**********************************END OF FILE*********************************/
