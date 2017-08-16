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
 * @brief      define mcu application pack gpio opera interface
 *******************************************************************************
 */ 
static struct Map_GPIO_Opera *_gpio_ops = NULL;

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

/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_GPIO_COMPONENT
/**
 *******************************************************************************
 * @brief       register hal gpio module
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_GPIO_Module_Register(void)
{
    Map_GPIO_API_Register((void **)&_gpio_ops);
}

/**
 *******************************************************************************
 * @brief       hal api : open device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_GPIO_Open(Hal_Device_t *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    
    struct Hal_GPIO_Device *gpio = (struct Hal_GPIO_Device *)&drv->Device;
    
    _gpio_ops->Open(gpio->Port); 
}

/**
 *******************************************************************************
 * @brief       hal api : close device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_GPIO_Close(Hal_Device_t *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    
    struct Hal_GPIO_Device *gpio = (struct Hal_GPIO_Device *)&drv->Device;
    
    _gpio_ops->Close(gpio->Port); 
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
void Hal_GPIO_Init(Hal_Device_t *drv, uint8_t dir, uint8_t mode)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    hal_assert(IS_PTR_NULL(param));
    
    struct Hal_GPIO_Device *gpio = (struct Hal_GPIO_Device *)&drv->Device;

    gpio->Opera = (struct Hal_GPIO_Opera *)&gpio_ops;
    
    _gpio_ops->Open(gpio->Port);
    _gpio_ops->Init(gpio->Port, gpio->Pin, dir, mode); 
}

/**
 *******************************************************************************
 * @brief       hal api : deinit device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_GPIO_Fini(Hal_Device_t *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    
    struct Hal_GPIO_Device *gpio = (struct Hal_GPIO_Device *)&drv->Device;
    
    gpio->Opera = NULL;
    gpio->Port = 0;
    gpio->Pin = 0;
    
    _gpio_ops->Fini(gpio->Port, gpio->Pin); 
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
void Hal_GPIO_Write(Hal_Device_t *drv, uint16_t wrData, uint8_t wrNum)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    hal_assert(IS_PTR_NULL(param));
    
    struct Hal_GPIO_Device *gpio = (struct Hal_GPIO_Device *)&drv->Device;

    _gpio_ops->Write(gpio->Port, gpio->Pin, wrData, wrNum); 
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
void Hal_GPIO_Read(Hal_Device_t *drv, uint8_t dir, uint16_t *rdData, uint8_t rdNum)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    hal_assert(IS_PTR_NULL(param));
    
    struct Hal_GPIO_Device *gpio = (struct Hal_GPIO_Device *)&drv->Device;

    _gpio_ops->Read(gpio->Port, dir, gpio->Pin, rdData, rdNum); 
}

/**
 *******************************************************************************
 * @brief       hal api : set pin
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_GPIO_Set(Hal_Device_t *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    
    struct Hal_GPIO_Device *gpio = (struct Hal_GPIO_Device *)&drv->Device;
    
    _gpio_ops->Write(gpio->Port, gpio->Pin, 1, 1); 
}

/**
 *******************************************************************************
 * @brief       hal api : reset pin
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_GPIO_Clr(Hal_Device_t *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    
    struct Hal_GPIO_Device *gpio = (struct Hal_GPIO_Device *)&drv->Device;
    
    _gpio_ops->Write(gpio->Port, gpio->Pin, 0, 1); 
}

/**
 *******************************************************************************
 * @brief       hal api : get gpio intput status
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  status      pin status
 * @note        None
 *******************************************************************************
 */
bool Hal_GPIO_GetIntputStatus(Hal_Device_t *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    
    struct Hal_GPIO_Device *gpio = (struct Hal_GPIO_Device *)&drv->Device;
    uint16_t status = 0;
    
    _gpio_ops->Read(gpio->Port, GPIO_DIR_INTPUT, gpio->Pin, &status, 1); 
    
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
bool Hal_GPIO_GetOutputStatus(Hal_Device_t *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    
    struct Hal_GPIO_Device *gpio = (struct Hal_GPIO_Device *)&drv->Device;
    uint16_t status = 0;
    
    _gpio_ops->Read(gpio->Port, GPIO_DIR_OUTPUT, gpio->Pin, &status, 1); 
    
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
void Hal_GPIO_Toggle(Hal_Device_t *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    
    struct Hal_GPIO_Device *gpio = (struct Hal_GPIO_Device *)&drv->Device;
    uint16_t status = 0;
    
    _gpio_ops->Read(gpio->Port, GPIO_DIR_OUTPUT, gpio->Pin, &status, 1); 
    
    if(status == 1)
    {
        _gpio_ops->Write(gpio->Port, gpio->Pin, 0, 1); 
    }
    else
    {
        _gpio_ops->Write(gpio->Port, gpio->Pin, 1, 1); 
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
void Hal_GPIO_Control(Hal_Device_t *drv, uint8_t cmd, void *param)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    hal_assert(IS_PTR_NULL(param));
    
    struct Hal_GPIO_Device *gpio = (struct Hal_GPIO_Device *)&drv->Device;
    
    switch(cmd)
    {
        case HAL_GPIO_CMD_OPEN:
        {
            _gpio_ops->Open(gpio->Port);
            break;
        }
        case HAL_GPIO_CMD_CLOSE:
        {
            _gpio_ops->Close(gpio->Port);
            break;
        }
        case HAL_GPIO_CMD_INIT:
        {
            struct Hal_GPIO_Config *config = (struct Hal_GPIO_Config *)param;
            
            _gpio_ops->Init(gpio->Port, gpio->Pin, config->Dir, config->Mode);
            break;
        }
        case HAL_GPIO_CMD_FINI:
        {
            _gpio_ops->Fini(gpio->Port, gpio->Pin);
            break;
        }
        case HAL_GPIO_CMD_SET:
        {
            _gpio_ops->Write(gpio->Port, gpio->Pin, 1, 1);
            break;
        }
        case HAL_GPIO_CMD_CLEAR:
        {
            _gpio_ops->Write(gpio->Port, gpio->Pin, 0, 1);
            break;
        }
        case HAL_GPIO_CMD_GET_INTPUT:
        {   
            _gpio_ops->Read(gpio->Port, GPIO_DIR_INTPUT, gpio->Pin, (uint16_t *)param, 1);
            break;
        }
        case HAL_GPIO_CMD_GET_OUTPUT:
        {
            _gpio_ops->Read(gpio->Port, GPIO_DIR_OUTPUT, gpio->Pin, (uint16_t *)param, 1);
            break;
        }
        case HAL_GPIO_CMD_TOGGLE:
        {
            Hal_GPIO_Toggle(drv);
            break;
        }
        case HAL_GPIO_CMD_WRITE:
        {
            struct Hal_GPIO_Config *config = (struct Hal_GPIO_Config *)param;
            
            _gpio_ops->Write(gpio->Port, gpio->Pin, config->RWData, config->Num);
            break;
        }
        case HAL_GPIO_CMD_READ:
        {
            struct Hal_GPIO_Config *config = (struct Hal_GPIO_Config *)param;
            
            _gpio_ops->Read(gpio->Port, config->Dir, gpio->Pin, &config->RWData, config->Num); 
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
