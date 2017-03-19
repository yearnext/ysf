/**
 ******************************************************************************
 * @file       compiler_armcc6.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-1-10
 * @brief      armcc6 compiler head file
 * @par        work platform
 *                 ARM
 * @par        compiler platform
 *                 MDK
 ******************************************************************************
 * @note
 * 1.XXXXX
 ******************************************************************************
 */

/**
 * @defgroup armcc6 compiler config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_COMPILER_ARMCC6_H__
#define __YSF_COMPILER_ARMCC6_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_conf.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      disable something for compiler warning
 *******************************************************************************
 */
#pragma clang diagnostic ignored "-Wpadded" 
#pragma clang diagnostic ignored "-Wunused-parameter" 
#pragma clang diagnostic ignored "-Wswitch-enum" 
#pragma clang diagnostic ignored "-Warmcc-pragma-anon-unions"
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wunreachable-code-break"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wmissing-noreturn"

/**
 *******************************************************************************
 * @brief      DEFINE MCU HEAP ADDRESS
 *******************************************************************************
 */
extern unsigned int Image$$RW_IRAM1$$ZI$$Limit;

#define MCU_HEAP_HEAD_ADDR    (Image$$RW_IRAM1$$ZI$$Limit)
#define MCU_HEAP_TAIL_ADDR    (MCU_SRAM_END_ADDR)
#define MCU_HEAP_SIZE         (MCU_HEAP_TAIL_ADDR - MCU_HEAP_HEAD_ADDR) 

/**
 *******************************************************************************
 * @brief      define function name macro 
 *******************************************************************************
 */
#define __FUNCNAME__            __func__
#define __YSF_FUNCNAME__        __func__

/**
 *******************************************************************************
 * @brief      define compiler pragma cmd
 *******************************************************************************
 */
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

/**
 *******************************************************************************
 * @brief      define compiler alignment cmd 
 *******************************************************************************
 */
#define ALIGN_HEAD(n)           PRAGMA(pack(push, n))
#define ALIGN_TAIL(n)           PRAGMA(pack(pop))
#define PACKED_HEAD             
#define PACKED_TAIL

#define YSF_ALIGN_HEAD(n)       PRAGMA(pack(push, n))
#define YSF_ALIGN_TAIL(n)       PRAGMA(pack(pop))
#define YSF_PACKED_HEAD         
#define YSF_PACKED_TAIL

/**
 *******************************************************************************
 * @brief      define compiler critical cmd
 *******************************************************************************
 */
#define YSF_ENTER_CRITICAL()    __ASM volatile ("cpsid i" : : : "memory")
#define YSF_EXIT_CRITICAL()     __ASM volatile ("cpsie i" : : : "memory")

/**
 *******************************************************************************
 * @brief      size the end mode detection
 *******************************************************************************
 */
#if __BYTE_ORDER__==__ORDER_BIG_ENDIAN__
    #define COMPILER_USE_BIG_ENDIAN
//    #warning The byte order of the compiler uses big endian mode!
#else
    #define COMPILER_USE_LITTLE_ENDIAN
//    #warning The byte order of the compiler uses little endian mode!
#endif

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define int type
 *******************************************************************************
 */
#ifndef __stdint_h
typedef unsigned char           uint8_t;
typedef unsigned short          uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long long      uint64_t;

typedef char                    int8_t;
typedef short                   int16_t;
typedef int                     int32_t;
typedef long long               int64_t;

/**
 *******************************************************************************
 * @brief      define int max value and min value
 *******************************************************************************
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
#endif

/**
 *******************************************************************************
 * @brief      define bool type
 *******************************************************************************
 */
#ifndef __bool_true_false_are_defined
typedef enum
{
    false = 0,
    true = !false,
}bool;
#endif

/**
 *******************************************************************************
 * @brief      define NULL
 *******************************************************************************
 */
#ifndef NULL
#define NULL ((void *)0)
#endif

/**
 *******************************************************************************
 * @brief      define addr type
 *******************************************************************************
 */
#if 1
typedef uint32_t ysf_addr_t;
#else
typedef uint64_t ysf_addr_t;
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* armcc6 compiler config  */

/**********************************END OF FILE*********************************/
