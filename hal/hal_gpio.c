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
 * @file       hal_gpio.c                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-07                                                      *
 * @brief      hal gpio component source files                                 *
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
 * @defgroup hal gpio component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_gpio.h"
#include "map_gpio.h"

/* Exported constants --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define hal gpio interface
 *******************************************************************************
 */ 
#ifdef USE_HAL_DEVICE_COMPONENT
const struct Hal_Interface Hal_GPIO_Interface = 
{
    .Init = Hal_GPIO_Interface_Init,
    .Fini = Hal_GPIO_Interface_Fini,
    .Control = Hal_GPIO_Interface_Control,
};
#endif

/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define uart opera interface
 *******************************************************************************
 */ 
#if USE_GPIO_COMPONENT
static const struct Map_GPIO_Opera *map_api = (struct Map_GPIO_Opera *)&map_gpio_api;
#endif

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_GPIO_COMPONENT
/**
 *******************************************************************************
 * @brief       hal interface api : init device
 * @param       [in/out]  *drv           device block
 * @return      [in/out]  HAL_ERR_NONE   result
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_GPIO_Interface_Init(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_GPIO *gpio = (Hal_Device_GPIO *)drv;
    
    if(!IS_PTR_NULL(map_api->Open) && !IS_PTR_NULL(map_api->Init))
    {
        map_api->Open(gpio->Port);
        map_api->Init(gpio->Port, gpio->Pin, gpio->Dir, gpio->Mode);
    }
    else
    {
        return HAL_ERR_FAIL;
    }

    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal interface api : init device
 * @param       [in/out]  *drv           device block
 * @return      [in/out]  HAL_ERR_NONE   result
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_GPIO_Interface_Fini(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_GPIO *gpio = (Hal_Device_GPIO *)drv;

    if(!IS_PTR_NULL(map_api->Fini))
    {
        map_api->Fini(gpio->Port, gpio->Pin);
    }
    else
    {
        return HAL_ERR_FAIL;
    }
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal interface api : init device
 * @param       [in/out]  *drv           device block
 * @param       [in/out]  cmd            device command
 * @param       [in/out]  ...            expand param
 * @return      [in/out]  HAL_ERR_NONE   result
 * @note        [-------------------------command commit-----------------------]
 * @note        [cmd]     HAL_DEVICE_INIT_CMD
 * @note        [param]   dir            set gpio dir
 * @note        [param]   mode           set gpio mode
 * @note        [cmd]     HAL_DEVICE_FINI_CMD
 * @note        [param]   None
 * @note        [cmd]     HAL_GPIO_SET_CMD
 * @note        [param]   None
 * @note        [cmd]     HAL_GPIO_CLR_CMD
 * @note        [param]   None
 * @note        [cmd]     HAL_GPIO_WRITE_CMD
 * @note        [param]   value          write pin value
 * @note        [param]   num            write pin num
 * @note        [cmd]     HAL_GPIO_READ_CMD
 * @note        [param]   dir            read pin dir
 * @note        [param]   *value         read pin value
 * @note        [param]   num            read pin num
 * @note        [cmd]     HAL_GPIO_GET_OUTPUT_CMD
 * @note        [param]   *status        pin output status
 * @note        [cmd]     HAL_GPIO_GET_INTPUT_CMD
 * @note        [param]   *status        pin intput status
 * @note        [cmd]     HAL_GPIO_TOGGLE_CMD
 * @note        [param]   None
 *******************************************************************************
 */
hal_err_t Hal_GPIO_Interface_Control(void *drv, uint8_t cmd, va_list args)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_GPIO *gpio = (Hal_Device_GPIO *)drv;
    
    switch(cmd)
    {
        case HAL_DEVICE_OPEN_CMD:
        {
            if(!IS_PTR_NULL(map_api->Open))
            {
                map_api->Open(gpio->Port);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_CLOSE_CMD:
        {
            if(!IS_PTR_NULL(map_api->Close))
            {
                map_api->Close(gpio->Port); 
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_INIT_CMD:
        {
            if(!IS_PTR_NULL(map_api->Open) && !IS_PTR_NULL(map_api->Init))
            {
                map_api->Open(gpio->Port);
                map_api->Init(gpio->Port, gpio->Pin, gpio->Dir, gpio->Mode);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_FINI_CMD:
        {
            if(!IS_PTR_NULL(map_api->Fini))
            {
                map_api->Fini(gpio->Port, gpio->Pin);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_GPIO_SET_BIT_CMD:
        {
            if(!IS_PTR_NULL(map_api->Write))
            {
                map_api->Write(gpio->Port, gpio->Pin, 1, 1);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_GPIO_CLR_BIT_CMD:
        {
            if(!IS_PTR_NULL(map_api->Write))
            {
                map_api->Write(gpio->Port, gpio->Pin, 0, 1);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_GPIO_WRITE_CMD:
        {
            if(!IS_PTR_NULL(map_api->Write))
            {
                uint16_t value = (uint16_t)va_arg(args, int);
                uint16_t num = (uint16_t)va_arg(args, int);
                map_api->Write(gpio->Port, gpio->Pin, value, num);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_GPIO_READ_CMD:
        {
            if(!IS_PTR_NULL(map_api->Read))
            {
                uint8_t dir = *va_arg(args, uint8_t *);
                uint16_t *value = va_arg(args, uint16_t *);
                uint16_t num = *va_arg(args, uint16_t *);
                map_api->Read(gpio->Port, gpio->Pin, dir, value, 1);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_GPIO_GET_OUTPUT_CMD:
        {
            if(!IS_PTR_NULL(map_api->Read))
            {
                uint16_t *status = va_arg(args, uint16_t *);
                map_api->Read(gpio->Port, gpio->Pin, GPIO_DIR_INTPUT, status, 1); 
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_GPIO_GET_INTPUT_CMD:
        {
            if(!IS_PTR_NULL(map_api->Read))
            {
                uint16_t *status = va_arg(args, uint16_t *);
                map_api->Read(gpio->Port, gpio->Pin, GPIO_DIR_INTPUT, status, 1); 
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_GPIO_TOGGLE_CMD:
        {
            if(!IS_PTR_NULL(map_api->Toggle))
            {
                map_api->Toggle(gpio->Port, gpio->Pin); 
            }
            else
            {
                return HAL_ERR_FAIL;
            }
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
#endif

/** @}*/     /** hal gpio component */

/**********************************END OF FILE*********************************/
