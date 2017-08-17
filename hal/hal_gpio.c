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
__INLINE void Hal_GPIO_Open(struct Hal_GPIO_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));

    _gpio_ops->Open(drv->Port); 
}

/**
 *******************************************************************************
 * @brief       hal api : close device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Hal_GPIO_Close(struct Hal_GPIO_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));

    _gpio_ops->Close(drv->Port); 
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
__INLINE void Hal_GPIO_Init(struct Hal_GPIO_Device *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));

    drv->Opera = (struct Hal_GPIO_Opera *)&gpio_ops;
    
    _gpio_ops->Open(drv->Port);
    _gpio_ops->Init(drv->Port, drv->Pin, drv->Dir, drv->Mode); 
}

/**
 *******************************************************************************
 * @brief       hal api : deinit device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Hal_GPIO_Fini(struct Hal_GPIO_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    
    _gpio_ops->Fini(drv->Port, drv->Pin); 
    
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
__INLINE void Hal_GPIO_Write(struct Hal_GPIO_Device *drv, uint8_t *wrData, uint8_t wrNum)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    hal_assert(IS_PTR_NULL(param));

    _gpio_ops->Write(drv->Port, drv->Pin, *((uint16_t *)wrData), wrNum); 
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
__INLINE void Hal_GPIO_Read(struct Hal_GPIO_Device *drv, uint8_t *rdData, uint8_t rdNum)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    hal_assert(IS_PTR_NULL(param));

    _gpio_ops->Read(drv->Port, GPIO_DIR_INTPUT, drv->Pin, (uint16_t *)rdData, rdNum); 
}

/**
 *******************************************************************************
 * @brief       hal api : set pin
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Hal_GPIO_Set(struct Hal_GPIO_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));

    _gpio_ops->Write(drv->Port, drv->Pin, 1, 1); 
}

/**
 *******************************************************************************
 * @brief       hal api : reset pin
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Hal_GPIO_Clr(struct Hal_GPIO_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));

    _gpio_ops->Write(drv->Port, drv->Pin, 0, 1); 
}

/**
 *******************************************************************************
 * @brief       hal api : get gpio intput status
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  status      pin status
 * @note        None
 *******************************************************************************
 */
__INLINE bool Hal_GPIO_GetIntputStatus(struct Hal_GPIO_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));

    uint16_t status = 0;
    
    _gpio_ops->Read(drv->Port, GPIO_DIR_INTPUT, drv->Pin, &status, 1); 
    
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
__INLINE bool Hal_GPIO_GetOutputStatus(struct Hal_GPIO_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));

    uint16_t status = 0;
    
    _gpio_ops->Read(drv->Port, GPIO_DIR_OUTPUT, drv->Pin, &status, 1); 
    
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
__INLINE void Hal_GPIO_Toggle(struct Hal_GPIO_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));

    uint16_t status = 0;
    
    _gpio_ops->Read(drv->Port, GPIO_DIR_OUTPUT, drv->Pin, &status, 1); 
    
    if(status == 1)
    {
        _gpio_ops->Write(drv->Port, drv->Pin, 0, 1); 
    }
    else
    {
        _gpio_ops->Write(drv->Port, drv->Pin, 1, 1); 
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
__INLINE void Hal_GPIO_Control(struct Hal_GPIO_Device *drv, uint8_t cmd, void *param)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_gpio_ops));
    hal_assert(IS_PTR_NULL(param));

    switch(cmd)
    {
        case HAL_GPIO_CMD_OPEN:
        {
            _gpio_ops->Open(drv->Port);
            break;
        }
        case HAL_GPIO_CMD_CLOSE:
        {
            _gpio_ops->Close(drv->Port);
            break;
        }
        case HAL_GPIO_CMD_INIT:
        {
            struct Hal_GPIO_Config *config = (struct Hal_GPIO_Config *)param;
            
            _gpio_ops->Init(drv->Port, drv->Pin, config->Dir, config->Mode);
            break;
        }
        case HAL_GPIO_CMD_FINI:
        {
            _gpio_ops->Fini(drv->Port, drv->Pin);
            break;
        }
        case HAL_GPIO_CMD_SET:
        {
            _gpio_ops->Write(drv->Port, drv->Pin, 1, 1);
            break;
        }
        case HAL_GPIO_CMD_CLEAR:
        {
            _gpio_ops->Write(drv->Port, drv->Pin, 0, 1);
            break;
        }
        case HAL_GPIO_CMD_GET_INTPUT:
        {   
            _gpio_ops->Read(drv->Port, GPIO_DIR_INTPUT, drv->Pin, (uint16_t *)param, 1);
            break;
        }
        case HAL_GPIO_CMD_GET_OUTPUT:
        {
            _gpio_ops->Read(drv->Port, GPIO_DIR_OUTPUT, drv->Pin, (uint16_t *)param, 1);
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
            
            _gpio_ops->Write(drv->Port, drv->Pin, config->RWData, config->Num);
            break;
        }
        case HAL_GPIO_CMD_READ:
        {
            struct Hal_GPIO_Config *config = (struct Hal_GPIO_Config *)param;
            
            _gpio_ops->Read(drv->Port, config->Dir, drv->Pin, &config->RWData, config->Num); 
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
