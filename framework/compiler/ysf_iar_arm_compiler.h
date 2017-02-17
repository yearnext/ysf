/**
 ******************************************************************************
 * @file       ysf_iar_arm_compiler.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017年1月10日
 * @brief      编译器配置 头文件
 * @par        工作平台
 *                 ARM
 * @par        编译平台
 *                 IAR
 ******************************************************************************
 * @note
 * 1.XXXXX
 ******************************************************************************
 */

/**
 * @defgroup ynf配置
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_IAR_ARM_COMPILER_H__
#define __YSF_IAR_ARM_COMPILER_H__

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
 * @name IAR ARM编译器配置
 * @{
 */

/**
 * @name IAR ARM包含头文件
 * @{
 */
// #include <stdarg.h>
// #include <stdint.h>
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
//    #warning The byte order of the compiler uses big endian mode!
#else
    #define COMPILER_USE_LITTLE_ENDIAN
//    #warning The byte order of the compiler uses little endian mode!
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

/**
 * @name IAR ARM编译器数据类型定义
 * @{
 */
typedef unsigned char               ysf_uint8_t;
typedef unsigned short              ysf_uint16_t;
typedef unsigned int                ysf_uint32_t;
typedef unsigned long long          ysf_uint64_t;

typedef char                        ysf_int8_t;
typedef short                       ysf_int16_t;
typedef int                         ysf_int32_t;
typedef long long                   ysf_int64_t;
/**@} */

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf 编译器配置  */

/**********************************END OF FILE*********************************/
