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
#if USE_GPIO_COMPONENT
/**
 *******************************************************************************
 * @brief      define gpio opera interface
 *******************************************************************************
 */ 
static const struct Hal_GPIO_Opera gpio_ops = 
{
    .Open = Hal_GPIO_Open,
    .Close = Hal_GPIO_Close,
    
    .Init = Hal_GPIO_Init,
    .Fini = Hal_GPIO_Fini,
    
    .Set = Hal_GPIO_Set,
    .Clr = Hal_GPIO_Clr,
    .Toggle = Hal_GPIO_Toggle,

    .GetIntput = Hal_GPIO_GetIntputStatus,
    .GetOutput = Hal_GPIO_GetOutputStatus,
        
    .Write = Hal_GPIO_Write,
    .Read = Hal_GPIO_Read,
    
    .Control = Hal_GPIO_Control,
};
#endif

#ifdef USE_HAL_DEVICE_COMPONENT
/**
 *******************************************************************************
 * @brief      define hal gpio interface
 *******************************************************************************
 */ 
static hal_err_t Hal_GPIO_Interface_Init(void *drv);
static hal_err_t Hal_GPIO_Interface_Fini(void *drv);
static hal_err_t Hal_GPIO_Interface_Write(void*, uint8_t*, uint8_t);
static hal_err_t Hal_GPIO_Interface_Read(void*, uint8_t*, uint8_t);
static hal_err_t Hal_GPIO_Interface_Control(void *drv, uint8_t cmd, va_list args);

const struct Hal_Interface Hal_GPIO_Interface = 
{
    .Init = Hal_GPIO_Interface_Init,
    .Fini = Hal_GPIO_Interface_Fini,
    .Write = Hal_GPIO_Interface_Write,
    .Read = Hal_GPIO_Interface_Read,
    .Control = Hal_GPIO_Interface_Control,
};

#endif

/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#ifdef USE_HAL_DEVICE_COMPONENT
/**
 *******************************************************************************
 * @brief       hal interface api : init device
 * @param       [in/out]  *drv           device block
 * @return      [in/out]  HAL_ERR_NONE   result
 * @note        None
 *******************************************************************************
 */
static hal_err_t Hal_GPIO_Interface_Init(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_GPIO *gpio = (Hal_Device_GPIO *)drv;
    
    map_gpio_api.Open(gpio->Port);
    map_gpio_api.Init(gpio->Port, gpio->Pin, gpio->Dir, gpio->Mode); 
    
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
static hal_err_t Hal_GPIO_Interface_Fini(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_GPIO *gpio = (Hal_Device_GPIO *)drv;
    
    map_gpio_api.Fini(gpio->Port, gpio->Pin);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal interface api : write data from device
 * @param       [in/out]  *drv           device block
 * @param       [in/out]  *cfg           config param
 * @param       [in/out]  num            write bit num
 * @return      [in/out]  HAL_ERR_NONE   result
 * @note        None
 *******************************************************************************
 */
static hal_err_t Hal_GPIO_Interface_Write(void *drv, uint8_t *cfg, uint8_t num)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(cfg));
    
    Hal_Device_GPIO *gpio = (Hal_Device_GPIO *)drv;
    struct Hal_GPIO_Param *param = (struct Hal_GPIO_Param *)cfg;
    
    map_gpio_api.Write(gpio->Port, gpio->Pin, param->RW_Data, num); 
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal interface api : read data from device
 * @param       [in/out]  *drv           device block
 * @param       [in/out]  *cfg           config param
 * @param       [in/out]  num            read bit num
 * @return      [in/out]  HAL_ERR_NONE   result
 * @note        None
 *******************************************************************************
 */
static hal_err_t Hal_GPIO_Interface_Read(void *drv, uint8_t *cfg, uint8_t num)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(cfg));
    
    Hal_Device_GPIO *gpio = (Hal_Device_GPIO *)drv;
    struct Hal_GPIO_Param *param = (struct Hal_GPIO_Param *)cfg;
    
    map_gpio_api.Read(gpio->Port, gpio->Pin, param->Dir, &param->RW_Data, num); 
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal interface api : init device
 * @param       [in/out]  *drv           device block
 * @param       [in/out]  cmd            device command
 * @param       [in/out]  ...            expand param
 * @return      [in/out]  HAL_ERR_NONE   result
 * @note        None
 *******************************************************************************
 */
static hal_err_t Hal_GPIO_Interface_Control(void *drv, uint8_t cmd, va_list args)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_GPIO *gpio = (Hal_Device_GPIO *)drv;
    
    switch(cmd)
    {
        case HAL_DEVICE_INIT_CMD:
        {
            uint8_t dir = *va_arg(args, uint8_t *);
            uint8_t mode = *va_arg(args, uint8_t *);

            map_gpio_api.Init(gpio->Port, gpio->Pin, dir, mode);
            break;
        }
        case HAL_DEVICE_FINI_CMD:
        {
            map_gpio_api.Fini(gpio->Port, gpio->Pin);
            break;
        }
        case HAL_GPIO_INIT_CMD:
        {
            uint8_t dir = *va_arg(args, uint8_t *);
            uint8_t mode = *va_arg(args, uint8_t *);

            map_gpio_api.Init(gpio->Port, gpio->Pin, dir, mode);
            break;
        }
        case HAL_GPIO_FINI_CMD:
        {
            map_gpio_api.Fini(gpio->Port, gpio->Pin);
            break;
        }
        case HAL_GPIO_SET_CMD:
        {
            map_gpio_api.Write(gpio->Port, gpio->Pin, 1, 1);
            break;
        }
        case HAL_GPIO_CLR_CMD:
        {
            map_gpio_api.Write(gpio->Port, gpio->Pin, 0, 1);
            break;
        }
        case HAL_GPIO_WRITE_CMD:
        {
            uint16_t value = (uint16_t)va_arg(args, int);
            uint16_t num = (uint16_t)va_arg(args, int);
            map_gpio_api.Write(gpio->Port, gpio->Pin, value, num);
            break;
        }
        case HAL_GPIO_READ_CMD:
        {
            uint8_t dir = *va_arg(args, uint8_t *);
            uint16_t *value = va_arg(args, uint16_t *);
            uint16_t num = *va_arg(args, uint16_t *);
            map_gpio_api.Read(gpio->Port, gpio->Pin, dir, value, 1);
            break;
        }
        case HAL_GPIO_GET_OUTPUT_CMD:
        {
            uint16_t *status = va_arg(args, uint16_t *);
            map_gpio_api.Read(gpio->Port, gpio->Pin, GPIO_DIR_INTPUT, status, 1); 
            break;
        }
        case HAL_GPIO_GET_INTPUT_CMD:
        {
            uint16_t *status = va_arg(args, uint16_t *);
            map_gpio_api.Read(gpio->Port, gpio->Pin, GPIO_DIR_INTPUT, status, 1); 
            break;
        }
        case HAL_GPIO_TOGGLE_CMD:
        {
            Hal_GPIO_Toggle(gpio);
            break;
        }
        default:
            break;
    }
    
    return HAL_ERR_NONE;
}
#endif

#if USE_GPIO_COMPONENT
/**
 *******************************************************************************
 * @brief       hal api : open device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_GPIO_Open(Hal_Device_GPIO *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    map_gpio_api.Open(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : close device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_GPIO_Close(Hal_Device_GPIO *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    map_gpio_api.Close(drv->Port); 
}

/**
 *******************************************************************************
 * @brief       hal api : init device
 * @param       [in/out]  *drv        device block
 * @param       [in/out]  *param      device config param
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_GPIO_Init(Hal_Device_GPIO *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    drv->Opera = (struct Hal_GPIO_Opera *)&gpio_ops;
    
    map_gpio_api.Open(drv->Port);
    map_gpio_api.Init(drv->Port, drv->Pin, drv->Dir, drv->Mode); 
}

/**
 *******************************************************************************
 * @brief       hal api : deinit device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_GPIO_Fini(Hal_Device_GPIO *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    map_gpio_api.Fini(drv->Port, drv->Pin); 
    
    drv->Opera = NULL;
    drv->Port = 0;
    drv->Pin = 0;
}

/**
 *******************************************************************************
 * @brief       hal api : write data to device
 * @param       [in/out]  *drv        device block
 * @param       [in/out]  *param      config param
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_GPIO_Write(Hal_Device_GPIO *drv, uint8_t *wrData, uint8_t wrNum)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(wrData));

    return map_gpio_api.Write(drv->Port, drv->Pin, *((uint16_t *)wrData), wrNum); 
}

/**
 *******************************************************************************
 * @brief       hal api : read data from device
 * @param       [in/out]  *drv        device block
 * @param       [in/out]  *param      config param
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_GPIO_Read(Hal_Device_GPIO *drv, uint8_t *rdData, uint8_t rdNum)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(rdData));

    return map_gpio_api.Read(drv->Port, drv->Pin, GPIO_DIR_INTPUT, (uint16_t *)rdData, rdNum); 
}

/**
 *******************************************************************************
 * @brief       hal api : set pin
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_GPIO_Set(Hal_Device_GPIO *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    map_gpio_api.Write(drv->Port, drv->Pin, 1, 1); 
}

/**
 *******************************************************************************
 * @brief       hal api : reset pin
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_GPIO_Clr(Hal_Device_GPIO *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    map_gpio_api.Write(drv->Port, drv->Pin, 0, 1); 
}

/**
 *******************************************************************************
 * @brief       hal api : get gpio intput status
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  status      pin status
 * @note        None
 *******************************************************************************
 */
bool Hal_GPIO_GetIntputStatus(Hal_Device_GPIO *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    uint16_t status = 0;
    
    map_gpio_api.Read(drv->Port, drv->Pin, GPIO_DIR_INTPUT, &status, 1); 
    
    return (status == 0) ? (false) : (true);
}

/**
 *******************************************************************************
 * @brief       hal api : get gpio output status
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  status      pin status
 * @note        None
 *******************************************************************************
 */
bool Hal_GPIO_GetOutputStatus(Hal_Device_GPIO *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    uint16_t status = 0;
    
    map_gpio_api.Read(drv->Port, GPIO_DIR_OUTPUT, drv->Pin, &status, 1); 
    
    return (status == 0) ? (false) : (true);
}

/**
 *******************************************************************************
 * @brief       hal api : gpio toggle opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_GPIO_Toggle(Hal_Device_GPIO *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    uint16_t status = 0;
    
    map_gpio_api.Read(drv->Port, drv->Pin, GPIO_DIR_OUTPUT, &status, 1); 
    
    if(status == 1)
    {
        map_gpio_api.Write(drv->Port, drv->Pin, 0, 1); 
    }
    else
    {
        map_gpio_api.Write(drv->Port, drv->Pin, 1, 1); 
    }
}

/**
 *******************************************************************************
 * @brief       hal api : gpio control opera
 * @param       [in/out]  *drv        device block
 * @param       [in/out]  cmd         control command
 * @param       [in/out]  *param      control param
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_GPIO_Control(Hal_Device_GPIO *drv, uint8_t cmd, void *param)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(param));

    switch(cmd)
    {
        case HAL_GPIO_CMD_OPEN:
        {
            map_gpio_api.Open(drv->Port);
            break;
        }
        case HAL_GPIO_CMD_CLOSE:
        {
            map_gpio_api.Close(drv->Port);
            break;
        }
        case HAL_GPIO_CMD_INIT:
        {
            Hal_Device_GPIO *config = (Hal_Device_GPIO *)param;
            
            map_gpio_api.Init(drv->Port, drv->Pin, config->Dir, config->Mode);
            break;
        }
        case HAL_GPIO_CMD_FINI:
        {
            map_gpio_api.Fini(drv->Port, drv->Pin);
            break;
        }
        case HAL_GPIO_CMD_SET:
        {
            map_gpio_api.Write(drv->Port, drv->Pin, 1, 1);
            break;
        }
        case HAL_GPIO_CMD_CLEAR:
        {
            map_gpio_api.Write(drv->Port, drv->Pin, 0, 1);
            break;
        }
        case HAL_GPIO_CMD_GET_INTPUT:
        {   
            map_gpio_api.Read(drv->Port, drv->Pin, GPIO_DIR_INTPUT, (uint16_t *)param, 1);
            break;
        }
        case HAL_GPIO_CMD_GET_OUTPUT:
        {
            map_gpio_api.Read(drv->Port, drv->Pin, GPIO_DIR_OUTPUT, (uint16_t *)param, 1);
            break;
        }
        case HAL_GPIO_CMD_TOGGLE:
        {
            Hal_GPIO_Toggle(drv);
            break;
        }
        case HAL_GPIO_CMD_WRITE:
        {
            struct Hal_GPIO_Param *config = (struct Hal_GPIO_Param *)param;
            
            map_gpio_api.Write(drv->Port, drv->Pin, config->RW_Data, config->Num);
            break;
        }
        case HAL_GPIO_CMD_READ:
        {
            struct Hal_GPIO_Param *config = (struct Hal_GPIO_Param *)param;
            
            map_gpio_api.Read(drv->Port, config->Dir, drv->Pin, &config->RW_Data, config->Num); 
            break;
        }
        default:
        {
            break;
        }
    }
}
#endif

/** @}*/     /** hal gpio component */

/**********************************END OF FILE*********************************/
