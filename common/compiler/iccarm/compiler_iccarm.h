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
 * @file       compiler_iccarm.h                                               *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      iar arm compiler compiler files                                 *
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
 * @defgroup iar compiler config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMPILER_ICC_ARM_H__
#define __COMPILER_ICC_ARM_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <intrinsics.h>

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define function name macro 
 *******************************************************************************
 */
#ifndef __FUNCNAME__
#define __FUNCNAME__            __func__
#endif

/**
 *******************************************************************************
 * @brief      define compiler pragma cmd
 *******************************************************************************
 */
#ifndef __PRAGMA
#define __PRAGMA(pragma)          _Pragma(#pragma)
#endif

#ifndef __ASM
#define __ASM                   __asm
#endif

#ifndef __INLINE
#define __INLINE                inline
#endif

#ifndef __STATIC_INLINE
#define __STATIC_INLINE         static inline
#endif

#ifndef __SECTION
#define __SECTION(x)            @ x
#endif

#ifndef __UNUSED
#define __UNUSED
#endif

#ifndef __USED
#define __USED
#endif

#ifndef __WEAK
#define __WEAK                  __weak
#endif

#ifndef __IMPORT_API
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
#define __PACKED_HEAD           __PRAGMA(pack(push, 1))
#endif

#ifndef __PACKED_TAIL
#define __PACKED_TAIL           __PRAGMA(pack(pop))
#endif
   
/**
 *******************************************************************************
 * @brief      define compiler critical cmd
 *******************************************************************************
 */
#ifndef __ENTER_CRITICAL
#define __ENTER_CRITICAL()      __disable_interrupt()
#endif

#ifndef __EXIT_CRITICAL
#define __EXIT_CRITICAL()       __enable_interrupt()
#endif

#ifndef __NOP
#define __NOP()                 __no_operation() 
#endif

// #ifndef __WFI
// #define __WFI()                 __ASM ("wfi")
// #endif

// #ifndef __WFE
// #define __WFE()                 __ASM ("wfe")
// #endif

// #ifndef __SEV
// #define __SEV()                 __ASM ("sev")
// #endif

// #ifndef __CLREX
// #define __CLREX()               __ASM ("clrex")
// #endif

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
#if 0
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
#pragma section="HEAP"

#define __HEAP_HEAD_ADDR                                 (__segment_end("HEAP"))

/**
 *******************************************************************************
 * @brief      DEFINE FRAMEOWRK MAIN FUNCTION
 *******************************************************************************
 */
extern int main(void);
extern void __iar_data_init3(void);

#define Fw_Main_Init __iar_data_init3
#define Fw_Main __low_level_init

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define int type
 *******************************************************************************
 */
#ifndef _STDINT
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
#ifndef _STDBOOL
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
typedef uint32_t _addr_t;
#else
typedef uint64_t _addr_t;
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* iar compiler config  */

/**********************************END OF FILE*********************************/
