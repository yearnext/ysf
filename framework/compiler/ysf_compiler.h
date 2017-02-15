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
/**
 * @name 编译器配置
 * @{
 */

/**
 * @name IAR ARM编译器配置
 * @{
 */
#if defined(__ICCARM__)
/**
 * @name IAR ARM包含头文件
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
/**@} */

/**
 * @name IAR ARM编译器宏
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

/**
 * @name IAR ARM编译器大小端模式检测
 * @{
 */
#if 0
    #define COMPILER_USE_BIG_ENDIAN
    #warning The byte order of the compiler uses big endian mode!
#else
    #define COMPILER_USE_LITTLE_ENDIAN
    #warning The byte order of the compiler uses little endian mode!
#endif
/**@} */

/**@} */

/**
 * @name IAR ARM编译器字节对齐配置
 * @{
 */
#define PACKED_HEAD(n)          PRAGMA(data_alignment = n)
#define PACKED_TAIL(n)
#define PACKED(type)            PRAGMA(data_alignment = 1) type;
#define ALIGNMENT(n,type)       PRAGMA(data_alignment = 1) type;

#define YSF_PACKED_HEAD(n)      PRAGMA(data_alignment = n)
#define YSF_PACKED_TAIL(n)
#define YSF_PACKED(type)        PRAGMA(data_alignment = n) type;
#define YSF_ALIGNMENT(n,type)   PRAGMA(data_alignment = n) type;
/**@} */

/**@} */

/**
 * @name ARM Compiler 5编译器配置
 * @{
 */

#elif defined(__CC_ARM)
/**
 * @name ARM Compiler 5包含头文件
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
/**@} */

/**
 * @name ARM Compiler 5编译器宏
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

/**
 * @name ARM Compiler 6编译器大小端模式检测
 * @{
 */
#if __BYTE_ORDER__==__ORDER_BIG_ENDIAN__
    #define COMPILER_USE_BIG_ENDIAN
    #warning The byte order of the compiler uses big endian mode!
#else
    #define COMPILER_USE_LITTLE_ENDIAN
    #warning The byte order of the compiler uses little endian mode!
#endif
/**@} */

/**@} */

/**
 * @name ARM Compiler 5编译器字节对齐配置
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
 * @name ARM Compiler 6编译器配置
 * @{
 */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
/**
 * @name ARM Compiler 6包含头文件
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
/**@} */

/**
 * @name ARM Compiler 6编译器宏
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

/**
 * @name ARM Compiler 6编译器大小端模式检测
 * @{
 */
#if __BYTE_ORDER__==__ORDER_BIG_ENDIAN__
    #define COMPILER_USE_BIG_ENDIAN
    #warning The byte order of the compiler uses big endian mode!
#else
    #define COMPILER_USE_LITTLE_ENDIAN
    #warning The byte order of the compiler uses little endian mode!
#endif
/**@} */

/**@} */

/**
 * @name ARM Compiler 6编译器字节对齐配置
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
 * @name Visual Studio编译器配置
 * @{
 */
#elif defined(_MSC_BUILD)
/**
 * @name Visual Studio包含头文件
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
/**@} */

/**
 * @name Visual Studio编译器函数名称
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

/**
 * @name Visual Studio编译器大小端模式检测
 * @{
 */
#if __BYTE_ORDER__==__ORDER_BIG_ENDIAN__
    #define COMPILER_USE_BIG_ENDIAN
    #warning The byte order of the compiler uses big endian mode!
#else
    #define COMPILER_USE_LITTLE_ENDIAN
    #warning The byte order of the compiler uses little endian mode!
#endif
/**@} */

/**@} */

/**
 * @name Visual Studio编译器字节对齐配置
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
 * @name GCC编译器配置
 * @{
 */
#elif defined(__GNUC__)
/**
 * @name GCC编译器包含头文件
 * @{
 */
#include <stdarg.h>
#include <stdint.h>
/**@} */

/**
 * @name GCC编译器函数名称
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

/**
 * @name GCC编译器大小端模式检测
 * @{
 */
#if __BYTE_ORDER__==__ORDER_BIG_ENDIAN__
    #define COMPILER_USE_BIG_ENDIAN
    #warning The byte order of the compiler uses big endian mode!
#else
    #define COMPILER_USE_LITTLE_ENDIAN
    #warning The byte order of the compiler uses little endian mode!
#endif
/**@} */

/**@} */

/**
 * @name GCC编译器字节对齐配置
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
/**
 * @name 不支持的编译器宏
 * @{
 */
#define __FUNCNAME__           
#define __YSF_FUNCNAME__       

#define PRAGMA(pragma)         

#if !defined(__CORTEX_M)
#define __ASM                   
#define __INLINE                
#define __STATIC_INLINE         static
#endif

#define YSF_ASM                 
#define YSF_INLINE              
#define YSF_STATIC_INLINE       static

#define YSF_SECTION(x)         
#define YSF_UNUSED
#define YSF_USED
#define YSF_WEAK                
#define YSF_IMPORT_API         
#define YSF_EXPORT_API          

/**
 * @name 不支持的编译器大小端模式检测
 * @{
 */
#if 0
    #define COMPILER_USE_BIG_ENDIAN
    #warning The byte order of the compiler uses big endian mode!
#else
    #define COMPILER_USE_LITTLE_ENDIAN
    #warning The byte order of the compiler uses little endian mode!
#endif
/**@} */

/**@} */

/**
 * @name 不支持的编译器字节对齐配置
 * @{
 */
#define PACKED_HEAD(n)          
#define PACKED_TAIL(n)
#define PACKED(type)            type;
#define ALIGNMENT(n,type)       type;

#define YSF_PACKED_HEAD(n)      
#define YSF_PACKED_TAIL(n)
#define YSF_PACKED(type)        type;
#define YSF_ALIGNMENT(n,type)   type;
/**@} */

/**@} */
#endif

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf 编译器配置  */

/**********************************END OF FILE*********************************/
