/**
 *******************************************************************************
 *                       Copyright (C) 2017  yearnext                          *
 *                                                                             *
 *    This program is free software; you can redistribute it and/or modify     *
 *    it under the terms of the GNU General Public License as published by     *
 *    the Free Software Foundation; either version 2 of the License, or        *
 *    (at your option) any later version.                                      *
 *                                                                             *
 *    This program is distributed in the hope that it will be useful,          *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *    GNU General Public License for more details.                             *
 *                                                                             *
 *    You should have received a copy of the GNU General Public License along  *
 *    with this program; if not, write to the Free Software Foundation, Inc.,  *
 *    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.              *
 *******************************************************************************
 * @file       compiler_armcc5.h                                               *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      armcc5 compiler files                                           *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */

/**
 * @defgroup armcc5 compiler config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMPILER_ARMCC5_H__
#define __COMPILER_ARMCC5_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define function name macro 
 *******************************************************************************
 */
#ifndef __FUNCNAME__
#define __FUNCNAME__                                                   __func__
#endif

/**
 *******************************************************************************
 * @brief      disable compiler warning about anonymous structs 
 *******************************************************************************
 */
#pragma anon_unions

/**
 *******************************************************************************
 * @brief      define compiler pragma cmd
 *******************************************************************************
 */
#ifndef __PRAGMA
#define __PRAGMA(pragma)        _Pragma(#pragma)
#endif

/**
 *******************************************************************************
 * @brief      define compiler pragma cmd
 *******************************************************************************
 */
#ifndef __ASM
#define __ASM                   __asm
#endif

#ifndef __INLINE
#define __INLINE                __inline
#endif

#ifndef __STATIC_INLINE
#define __STATIC_INLINE         static __inline
#endif

#ifndef __SECTION
#define __SECTION(x)            __attribute__((section(x)))
#endif

#ifndef __UNUSED
#define __UNUSED                __attribute__((unused))
#endif

#ifndef __USED
#define __USED                  __attribute__((used))
#endif

#ifndef __WEAK
#define __WEAK                  __weak
#endif

#ifndef __WEAK
#define __IMPORT_API            __declspec(dllimport)
#endif

#ifndef __EXPORT_API
#define __EXPORT_API            __declspec(dllexport)
#endif

/**
 *******************************************************************************
 * @brief      define compiler alignment cmd 
 *******************************************************************************
 */
#ifndef __ALIGN_HEAD
#define __ALIGN_HEAD(n)         __PRAGMA(pack(push, n))
#endif

#ifndef __ALIGN_TAIL
#define __ALIGN_TAIL(n)         __PRAGMA(pack(pop))
#endif

#ifndef __PACKED_HEAD
#define __PACKED_HEAD           __packed
#endif

#ifndef __PACKED_TAIL
#define __PACKED_TAIL
#endif

/**
 *******************************************************************************
 * @brief      define compiler cmd
 *******************************************************************************
 */
#ifndef __ENTER_CRITICAL
#define __ENTER_CRITICAL()      _ST(__disable_irq();)
#endif

#ifndef __EXIT_CRITICAL
#define __EXIT_CRITICAL()       _ST(__enable_irq();)
#endif

//#ifndef __NOP
//#define __NOP                             __nop
//#endif

//#ifndef __WFI
//#define __WFI                             __wfi
//#endif

//#ifndef __WFE
//#define __WFE                             __wfe
//#endif

//#ifndef __SEV
//#define __SEV                             __sev
//#endif

//#ifndef __ISB
//#define __ISB()                           __isb(0)
//#endif

//#ifndef __DSB
//#define __DSB()                           __dsb(0)
//#endif

//#ifndef __DMB
//#define __DMB()                           __dmb(0)
//#endif

//#ifndef __REV
//#define __REV                             __rev
//#endif

//#ifndef __RBIT
//#define __RBIT                            __rbit
//#endif

//#ifndef __LDREXB
//#define __LDREXB(ptr)                     ((unsigned char ) __ldrex(ptr))
//#endif

//#ifndef __LDREXH
//#define __LDREXH(ptr)                     ((unsigned short) __ldrex(ptr))
//#endif

//#ifndef __LDREXW
//#define __LDREXW(ptr)                     ((unsigned int  ) __ldrex(ptr))
//#endif

//#ifndef __STREXB
//#define __STREXB(value, ptr)              __strex(value, ptr)
//#endif

//#ifndef __STREXH
//#define __STREXH(value, ptr)              __strex(value, ptr)
//#endif

//#ifndef __STREXW
//#define __STREXW(value, ptr)              __strex(value, ptr)
//#endif

/**
 *******************************************************************************
 * @brief      define atom opera
 *******************************************************************************
 */    
#ifndef __ATOM_ACTIVE_BEGIN
#define __ATOM_ACTIVE_BEGIN()   __ENTER_CRITICAL()
#endif

#ifndef __ATOM_ACTIVE_END
#define __ATOM_ACTIVE_END()     __EXIT_CRITICAL()
#endif

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


/**
 *******************************************************************************
 * @brief      DEFINE MCU HEAP ADDRESS
 *******************************************************************************
 */
extern unsigned int Image$$RW_IRAM1$$ZI$$Limit;

#define __HEAP_HEAD_ADDR             ((unsigned int)&Image$$RW_IRAM1$$ZI$$Limit)

#define USE_COMPILER_HEAP_ADDR                                               (1)

/**
 *******************************************************************************
 * @brief      DEFINE FRAMEOWRK MAIN FUNCTION
 *******************************************************************************
 */
extern int $Super$$main(void);

#define Fw_Main_Init __iar_data_init3
#define Fw_Main $Sub$$main

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
#define INT8_MAX                (127)
#define INT16_MAX               (32767)
#define INT32_MAX               (2147483647U)
#define INT64_MAX               (9223372036854775807LL)

#define INT8_MIN                (-128)
#define INT16_MIN               (-32768)
#define INT32_MIN               (-2147483647 - 1)
#define INT64_MIN               (-9223372036854775807LL - 1)

#define UINT8_MAX               (0xFF)
#define UINT16_MAX              (0xFFFF)
#define UINT32_MAX              (0xFFFFFFFFU)
#define UINT64_MAX              (0xFFFFFFFFFFFFFFFFULL)

#define UINT8_MIN               (0)
#define UINT16_MIN              (0)
#define UINT32_MIN              (0U)
#define UINT64_MIN              (0ULL)
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
typedef uint32_t ptr_t;
#else
typedef uint64_t _addr_t;
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** armcc5 compiler config */

/**********************************END OF FILE*********************************/
