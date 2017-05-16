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
 * @file       hal_interface.c                                                 * 
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-05-16                                                      *
 * @brief      hal interface source files                                      *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                  						                           *
 *******************************************************************************
 */

/**
 * @defgroup hal interface
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_interface.h"

/* Exported constants --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        hal interface config
 *******************************************************************************
 */
const struct HalInterface Hal = 
{
    .Version                                           = _HAL_VERSION,
    
#if USE_MAP_GPIO_COMPONENT
    .GPIO.Open                                         = MAP_GPIO_Open,
    .GPIO.Close                                        = MAP_GPIO_Close,
    .GPIO.Init                                         = MAP_GPIO_Init,
    .GPIO.Fini                                         = MAP_GPIO_Deinit,
    .GPIO.Input.Get                                    = MAP_GPIO_GetInputStatus,
    .GPIO.Output.Get                                   = MAP_GPIO_GetOutputStatus,
    .GPIO.Output.Set                                   = MAP_GPIO_Set,
    .GPIO.Output.Clr                                   = MAP_GPIO_Clr,
    .GPIO.Output.Toggle                                = MAP_GPIO_Toggle,
    .GPIO.Output.Cmd                                   = MAP_GPIO_OutputCmd,
#endif  

#if USE_MAP_TIMER_COMPONENT
    .Timer.Open                                        = MAP_Timer_Open,
    .Timer.Close                                       = MAP_Timer_Close,
    .Timer.Start                                       = MAP_Timer_Start,
    .Timer.Stop                                        = MAP_Timer_Stop,
    .Timer.Base.Init                                   = MAP_TimerBase_Init,
    .Timer.Base.Arm                                    = MAP_TimerBase_Arm,
    .Timer.Base.HandleRegister                         = MAP_TimerBaseHandle_Register,
#endif
}; 

/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @}*/     /** hal interface */

/**********************************END OF FILE*********************************/
