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
 * @file       ysf_type.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      ysf type define head files                                      *
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
 * @defgroup ysf type
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_TYPE_H__
#define __YSF_TYPE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_COMPILER_PATH

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define ysf status type
 *******************************************************************************
 */
typedef enum
{
   ysf_disable  = 0,
   ysf_enable = !ysf_disable,
}ysf_status_t;

/**
 *******************************************************************************
 * @brief      define ysf error type
 *******************************************************************************
 */
enum
{
    YSF_ERR_NONE,
    YSF_ERR_FAIL,
    
    YSF_ERR_NOT_READY,
    YSF_ERR_NOT_SUPPORT,
    
    YSF_ERR_INVAILD_PTR,
    YSF_ERR_INVAILD_PARAM,

    YSF_ERR_IO,
    
    YSF_ERR_BUG,
    YSF_ERR_UNKNOW,
};

typedef int16_t ysf_err_t;

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf type  */

/**********************************END OF FILE*********************************/
