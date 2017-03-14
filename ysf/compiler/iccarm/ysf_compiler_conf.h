/**
 ******************************************************************************
 * @file       ysf_iar_arm_compiler.h
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
 * @name IAR ARM����������
 * @{
 */

/**
 * @name IAR ARM����ͷ�ļ�
 * @{
 */
// #include <stdarg.h>
// #include <stdint.h>
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
#define ALIGN_HEAD(n)           PRAGMA(pack(push, n))
#define ALIGN_TAIL(n)           PRAGMA(pack(pop))
#define PACKED_HEAD             PRAGMA(pack(push, 1))
#define PACKED_TAIL             PRAGMA(pack(pop))
    
#define YSF_ALIGN_HEAD(n)       PRAGMA(pack(push, n))
#define YSF_ALIGN_TAIL(n)       PRAGMA(pack(pop))
#define YSF_PACKED_HEAD         PRAGMA(pack(push, 1))
#define YSF_PACKED_TAIL         PRAGMA(pack(pop))
    
/**@} */

/**
 * @name IAR ARM�������������Ͷ���
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

#if 1
typedef ysf_uint32_t                ysf_addr_t;
#else
typedef ysf_uint64_t                ysf_addr_t;
#endif

/**@} */

/**@} */

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* ysf ����������  */

/**********************************END OF FILE*********************************/
