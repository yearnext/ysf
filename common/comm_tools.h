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
 * @file       tools.h                                                         *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      common tools head files                                         *
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
 * @defgroup common tool component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMON_TOOLS_H__
#define __COMMON_TOOLS_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
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
#define _sizeof(type)                     (sizeof(type) / sizeof(unsigned char))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _dimof(array)                           (sizeof(array)/sizeof(array[0]))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _min(a, b)		                       	       (((a) < (b)) ? (a) : (b))
#define _max(a, b)				                       (((a) > (b)) ? (a) : (b))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define _TO_STR(name)			                        	               #name

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define CalTypeBitSize(type)             (CalTypeByteSize(type) * 8)

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */
#define CalRemainder(dividend,divisor)   ((dividend)%(divisor))

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
#define CalUseMemorySize(dividend)       (_sizeof(dividend) + CheckRemainder(dividend, 8))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */   
#define __ALIGN(size, align)           (((size) + (align) - 1) & ~((align) - 1))
#define __ALIGN_DOWN(size, align)      ((size) & ~((align) - 1))

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
#define IS_PARAM_ZERO(param)                                      ((param) == 0)

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
                                           
/**@} */
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* common tool component  */

/**********************************END OF FILE*********************************/
