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
 * @file       fw_type.h                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-13                                                      *
 * @brief      framework type head files                                       *
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
 * @defgroup framework type
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_TYPE_H__
#define __FRAMEWORK_TYPE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _COMM_TYPE_PATH
    
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define framework error type
 *******************************************************************************
 */
#define FW_ERR_NONE                                      (_ERR_NONE)
#define FW_ERR_FAIL                                      (_ERR_FAIL)
#define FW_ERR_NOT_READY                                 (_ERR_NOT_READY)
#define FW_ERR_NOT_SUPPORT                               (_ERR_NOT_SUPPORT)
#define FW_ERR_INVAILD_PTR                               (_ERR_INVAILD_PTR)
#define FW_ERR_INVAILD_PARAM                             (_ERR_INVAILD_PARAM)
#define FW_ERR_IO                                        (_ERR_IO)
#define FW_ERR_BUG                                       (_ERR_BUG)
#define FW_ERR_UNKNOW                                    (_ERR_UNKNOW)

typedef _err_t                                           fw_err_t;
    
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** framework type  */

/**********************************END OF FILE*********************************/
