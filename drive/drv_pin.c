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
 * @file       drv_pin.c                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-09-01                                                      *
 * @brief      mcu gpio pin driver software source files                       *
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
* @defgroup mcu gpio pin driver component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "drv_pin.h"

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       open pin
 * @param       [in/out]  *pin            device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void Drv_Pin_Open(struct Hal_Drv_Pin *pin)
{
    if(pin->Mode == DRV_PIN_GPIO_MODE)
    {
        if(pin->OperaDir)
        {
            Hal_Device_Control(&pin->Device, HAL_GPIO_SET_BIT_CMD);
        }
        else
        {
            Hal_Device_Control(&pin->Device, HAL_GPIO_CLR_BIT_CMD);
        }
    }
    else
    {
        if(pin->OperaDir)
        {
            if(pin->Duty > 0)
            {
                Hal_Device_Control(&pin->Device, HAL_TIMER_SET_DUTY, pin->Duty);
            }
            else
            {
                Hal_Device_Control(&pin->Device, HAL_TIMER_SET_DUTY, 1000);
            }
        }
        else
        {
            if(pin->Duty >= 1000)
            {
                Hal_Device_Control(&pin->Device, HAL_TIMER_SET_DUTY, 0);
            }
            else
            {
                Hal_Device_Control(&pin->Device, HAL_TIMER_SET_DUTY, pin->Duty);
            }
        }
    }
}

/**
 *******************************************************************************
 * @brief       close pin
 * @param       [in/out]  *pin            device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void Drv_Pin_Close(struct Hal_Drv_Pin *pin)
{
    if(pin->Mode == DRV_PIN_GPIO_MODE)
    {
        if(pin->OperaDir)
        {
            Hal_Device_Control(&pin->Device, HAL_GPIO_CLR_BIT_CMD);
        }
        else
        {
            Hal_Device_Control(&pin->Device, HAL_GPIO_SET_BIT_CMD);
        }
    }
    else
    {
        if(pin->OperaDir)
        {
            Hal_Device_Control(&pin->Device, HAL_TIMER_SET_DUTY, 0);
        }
        else
        {
            Hal_Device_Control(&pin->Device, HAL_TIMER_SET_DUTY, 1000);
        }
    }
}

/**
 *******************************************************************************
 * @brief       toggle pin
 * @param       [in/out]  *pin            device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void Drv_Pin_Toggle(struct Hal_Drv_Pin *pin)
{
    if(pin->Mode == DRV_PIN_GPIO_MODE)
    {
        Hal_Device_Control(&pin->Device, HAL_GPIO_TOGGLE_CMD);
    }
    else
    {
        if(pin->Duty > 0)
        {
            Hal_Device_Control(&pin->Device, HAL_TIMER_SET_DUTY, 0);
            
            pin->Duty = 0;
        }
        else
        {
            Hal_Device_Control(&pin->Device, HAL_TIMER_SET_DUTY, pin->SetDuty);
            
            pin->Duty = pin->SetDuty;
        }
    }
}

/**
 *******************************************************************************
 * @brief       pin timeout handle
 * @param       [in/out]  *pin            device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Drv_Pin_TimeOut_Handle(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    struct Hal_Drv_Pin *pin = (struct Hal_Drv_Pin *)drv;
    
    Drv_Pin_Toggle(pin);
    
    if(pin->BlinkCount > 0)
    {
        pin->BlinkCount--;
    }
    
    if(pin->BlinkCount)
    {
        if(pin->BlinkCount % 2)
        {
            Fw_Timer_Start(&pin->Timer, pin->BlinkTimeN, 1);
        }
        else
        {
            Fw_Timer_Start(&pin->Timer, pin->BlinkTime, 1);
        }
    }
}

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       hal api : init device
 * @param       [in/out]  *drv            device block
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
hal_err_t Drv_Pin_Init(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    struct Hal_Drv_Pin *pin = (struct Hal_Drv_Pin *)drv;
    
    Fw_Timer_Init(&pin->Timer, "Device Pin Drvier Timer");
    Fw_Timer_SetCallback(&pin->Timer, Drv_Pin_TimeOut_Handle, drv);
    
    Hal_Device_Init(&pin->Device);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal api : deinit device
 * @param       [in/out]  *drv            device block
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
hal_err_t Drv_Pin_Fini(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    struct Hal_Drv_Pin *pin = (struct Hal_Drv_Pin *)drv;
    
    Hal_Device_Fini(&pin->Device);
    Fw_Timer_Stop(&pin->Timer);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal api : device control
 * @param       [in/out]  *drv            device block
 * @param       [in/out]  cmd             control cmd
 * @param       [in/out]  args            control param
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
hal_err_t Drv_Pin_Control(void *drv, uint8_t cmd, va_list args)
{
    hal_assert(IS_PTR_NULL(drv));
    
    struct Hal_Drv_Pin *pin = (struct Hal_Drv_Pin *)drv;
    
    switch(cmd)
    {
        case HAL_DEVICE_INIT_CMD:
        {
            Hal_Device_Init(&pin->Device);
            break;
        }
        case HAL_DEVICE_FINI_CMD:
        {
            Hal_Device_Fini(&pin->Device);
            break;
        }
        case HAL_DEVICE_PIN_OPEN_CMD:
        {
            Drv_Pin_Open(pin);
            break;
        }
        case HAL_DEVICE_PIN_CLOSE_CMD:
        {
            Drv_Pin_Close(pin);
            break;
        }
        case HAL_DEVICE_PIN_SET_DUTY_CMD:
        {
            if(pin->Mode != DRV_PIN_GPIO_MODE)
            {
                uint16_t duty = (uint16_t)va_arg(args, int);
                
                Hal_Device_Control(&pin->Device, HAL_TIMER_SET_DUTY, duty);
                
                pin->SetDuty = duty;
                pin->Duty = duty;
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_PIN_SET_BLINK_CMD:
        {
            uint16_t hTime = (uint16_t)va_arg(args, int);
            uint16_t lTime = (uint16_t)va_arg(args, int);
            uint16_t count = (uint16_t)va_arg(args, int);
            
            pin->BlinkTime = hTime;
            pin->BlinkTimeN = lTime;
            pin->BlinkCount = count << 1;
            pin->BlinkCount--;
            
            Drv_Pin_Open(pin);
            Fw_Timer_Start(&pin->Timer, pin->BlinkTime, 1);
            
            break;
        }
        case HAL_DEVICE_PIN_TOGGLE_CMD:
        {
            Drv_Pin_Toggle(pin);
            break;
        }
        default:
        {
            return HAL_ERR_FAIL;
            break;
        }
    }
    
    return HAL_ERR_NONE;
}

/** @}*/     /** mcu gpio pin driver component */

/**********************************END OF FILE*********************************/
