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
 * @file       type.h                                                          *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      common type define head files                                   *
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
 * @defgroup common type
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMON_TYPE_H__
#define __COMMON_TYPE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "comm_path.h"
#include _COMPILER_PATH

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define error type
 *******************************************************************************
 */
enum
{
    ERR_NONE,
    ERR_FAIL,
    
    ERR_NOT_READY,
    ERR_NOT_SUPPORT,
    
    ERR_INVAILD_PTR,
    ERR_INVAILD_PARAM,

    ERR_IO,
    
    ERR_BUG,
    ERR_UNKNOW,
};

typedef int16_t _err_t;

#define FW_ERR_NONE          (0)
#define FW_ERR_FAIL          (1)
#define FW_ERR_INVAILD_PARAM (2)
#define FW_ERR_INVAILD_PTR   (3)

typedef _err_t fw_err_t;

#define HAL_ERR_NONE (0)
#define HAL_ERR_FAIL (1)
typedef _err_t hal_err_t;

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** common type  */

/**********************************END OF FILE*********************************/
