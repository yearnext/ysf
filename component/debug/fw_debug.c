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
 * @file       fw_debug.c                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-01-10                                                      *
 * @brief      framework debug component source files                          *
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
 * @defgroup framework debug component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _FW_TYPE_PATH
#include _FW_DEBUG_COMPONENT_PATH

/* Private define ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_FRAMEWORK_DEBUG_API
/**
 *******************************************************************************
 * @brief       framework debug component initialization
 * @param       [in/out]  void
 * @return      [in/out]  FW_ERR_NONE    without exception
 * @note        None
 *******************************************************************************
 */
fw_err_t fw_debug_init( void )
{
    return FW_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       framework assert failed handler
 * @param       [in/out]  *file           assertion failed file name
 * @param       [in/out]  line            assertion failed file line
 * @return      [in/out]  none
 * @note        None
 *******************************************************************************
 */
void fw_assert_failed(uint8_t* file, uint32_t line)
{
    ENTER_CRITICAL();
    while(1);
//    EXIT_CRITICAL();
}
#endif

/** @}*/     /** framework debug component */

/**********************************END OF FILE*********************************/
