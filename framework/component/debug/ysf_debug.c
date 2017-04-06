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
 * @file       ysf_debug.c                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      debug component source files                                    *
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
 * @defgroup ysf debug
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_COMPONENT_DEBUG_PATH
#include YSF_TYPE_PATH

/* Private define ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_YSF_DEBUG_API
/**
 *******************************************************************************
 * @brief       ysf debug component initialization
 * @param       [in/out]  void
 * @return      [in/out]  YSF_ERR_NONE    without exception
 * @note        None
 *******************************************************************************
 */
ysf_err_t ysf_debug_init( void )
{
    return YSF_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       ysf assert failed handler
 * @param       [in/out]  *file           assertion failed file name
 * @param       [in/out]  line            assertion failed file line
 * @return      [in/out]  none
 * @note        None
 *******************************************************************************
 */
void ysf_assert_failed(uint8_t* file, uint32_t line)
{
    YSF_ENTER_CRITICAL();
    while(1);
//    YSF_EXIT_CRITICAL();
}
#endif

/** @}*/     /** ysf debug component */

/**********************************END OF FILE*********************************/
