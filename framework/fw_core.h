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
 * @file       fw_core.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017-01-10
 * @brief      framework core head files
 * @par        paltform
 *                 Windows
 * @par        compiler
 *                 GCC
 *******************************************************************************
 * @note
 * 1.XXXXX
 *******************************************************************************
 */

/**
 * @defgroup framework core
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_CORE_H__
#define __FRAMEWORK_CORE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <intrinsics.h>
#include "fw_conf.h"

/* Framework debug -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      debug config
 *******************************************************************************
 */    
#define USE_GLOBAL_DEBUG                                                     (1)
    
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define base type
 *******************************************************************************
 */
#ifndef _STDINT
typedef unsigned char           uint8_t;
typedef unsigned int            uint16_t;
typedef unsigned long           uint32_t;

typedef signed char             int8_t;
typedef signed int              int16_t;
typedef signed long             int32_t;   
#endif

/**
 *******************************************************************************
 * @brief       define bool type
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
 * @brief       define framework error type
 *******************************************************************************
 */
typedef enum
{
    FW_ERR_NONE,
    FW_ERR_FAIL,
    
    FW_ERR_NOT_READY,
    FW_ERR_NOT_SUPPORT,
    
    FW_ERR_INVAILD_PTR,
    FW_ERR_INVAILD_PARAM,

    FW_ERR_IO,
    FW_ERR_SPILL,
    FW_ERR_BUG,
    FW_ERR_UNKNOW,
}fw_err_t;

/**
 *******************************************************************************
 * @brief       define null
 *******************************************************************************
 */
#ifndef NULL
#define NULL ((void *)0)
#endif

/**
 *******************************************************************************
 * @note        define interrupt function
 *******************************************************************************
 */
#define _ENTER_CRITICAL()                                  __disable_interrupt()
#define _EXIT_CRITICAL()                                    __enable_interrupt()

#define _ATOM_ACTIVE_BEGIN()                                   _ENTER_CRITICAL()
#define _ATOM_ACTIVE_END()                                      _EXIT_CRITICAL()

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define Name2String(name)                (#name)

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define CalTypeByteSize(type)            (sizeof(type) / sizeof(unsigned char))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define CalTypeBitSize(type)                        (CalTypeByteSize(type) >> 3)

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define CalRemainder(dividend,divisor)                    ((dividend)%(divisor))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define CheckRemainder(dividend,divisor) ((((dividend)%(divisor)) != 0 ) \
                                             ? (1) : (0))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */    
#define IS_PTR_NULL(ptr)                                  ((ptr) == ((void *)0))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */                                           
#define _PARAM_CHECK(n)                         _ST(if((n)) return FW_ERR_FAIL;)

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */  
#define _INLINE_STATEMENT(n)             do                                    \
                                         {                                     \
                                             n                                 \
                                         }while(0)

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */ 
#define _MACRO_ACTIVE(code)                                               {code}
                                         
/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */ 
#define _ST(code)                                            _MACRO_ACTIVE(code)
                                         
/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */     
#define _SET_BIT(REG, BIT)                               ((REG) |= (1 << (BIT)))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */     
#define _CLR_BIT(REG, BIT)                              ((REG) &= ~(1 << (BIT)))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */     
#define _READ_BIT(REG, BIT)                               ((REG) & (1 << (BIT)))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */  
#define _SET_REG(REG, VAL)                                      ((REG) |= (VAL))
     
/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */  
#define _CLR_REG(REG, VAL)                                     ((REG) &= ~(VAL))
 
/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */ 
#define _GET_REG(REG, VAL)                                       ((REG) & (VAL))
                                             
/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */     
#define _CLEAR_REG(REG)                                          ((REG) = (0))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */     
#define _WRITE_REG(REG, VAL)                                     ((REG) = (VAL))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */     
#define _READ_REG(REG)                                                   ((REG))
                                             
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework core */

/**********************************END OF FILE*********************************/
