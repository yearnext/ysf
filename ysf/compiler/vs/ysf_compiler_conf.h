/**
 ******************************************************************************
 * @file       ysf_vs_compiler.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017��1��10��
 * @brief      ���������� ͷ�ļ�
 * @par        ����ƽ̨
 *                 Windows
 * @par        ����ƽ̨
 *                 VS2015
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
#ifndef __YSF_VISUAL_STUDIO_COMPILER_H__
#define __YSF_VISUAL_STUDIO_COMPILER_H__

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
 * @name Visual Studio����ͷ�ļ�
 * @{
 */
// #include <stdarg.h>
// #include <stdint.h>
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

/**
 * @name Visual Studio��������С��ģʽ���
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
 * @name Visual Studio�������������Ͷ���
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

#if 0
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
