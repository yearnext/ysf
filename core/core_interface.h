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
 * @file       ysf.h                                                           *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-03-07                                                      *
 * @brief      ysf head files                                                  *
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
 * @defgroup yearnext software framework
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YSF_H__
#define __YSF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "conf.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define component path
 *******************************************************************************
 */
#define COMMON_PATH                                    "../ysf/common/path.h"
#define FRAMEWORK_PATH                                 "../ysf/framework/path.h"
#define HAL_PATH                                       "../ysf/hal/path.h"

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** ysf path config  */

/**********************************END OF FILE*********************************/
