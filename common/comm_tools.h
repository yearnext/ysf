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
#define CalTypeByteSize(type)            (sizeof(type) / sizeof(unsigned char))

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
#define IS_PTR_NULL(ptr)                 ((ptr) == ((void *)0))

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */  
#define INLINE_STATEMENT(n)              do                                    \
                                         {                                     \
                                             n                                 \
                                         }while(0)

/**
 *******************************************************************************
 * @brief      MACRO
 *******************************************************************************
 */                                           
#define INLINE_PARAM_CHECK(n)            INLINE_STATEMENT( if(n) {return _ERR_INVAILD_PARAM;} )

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
