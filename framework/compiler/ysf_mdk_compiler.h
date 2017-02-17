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
#ifndef __YSF_MDK_COMPILER_H__
#define __YSF_MDK_COMPILER_H__

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
 * @name ARM Compiler 5����������
 * @{
 */
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6010050)
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

/**
 * @name ARM Compiler 5�������������Ͷ���
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
#define PACKED_HEAD(n)          __attribute__ ((aligned(n)))
#define PACKED_TAIL(n)
#define PACKED(type)            __attribute__ ((aligned(1))) type;
#define ALIGNMENT(n,type)       __attribute__ ((aligned(n))) type;

#define YSF_PACKED_HEAD(n)      __attribute__ ((aligned(n)))
#define YSF_PACKED_TAIL(n)
#define YSF_PACKED(type)        __attribute__ ((aligned(1))) type;
#define YSF_ALIGNMENT(n,type)   __attribute__ ((aligned(n))) type;
/**@} */

/**
 * @name ARM Compiler 6�������������Ͷ���
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
#else
#endif

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf ����������  */

/**********************************END OF FILE*********************************/
