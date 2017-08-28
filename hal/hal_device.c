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
 * @file       hal_device.c                                                    *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-28                                                      *
 * @brief      hal device component source files                               *
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
 * @defgroup hal device component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_device.h"

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       device open opera
 * @param       [in/out]  *drv            device type
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
__INLINE
hal_err_t Hal_Device_Init(Hal_Device_t *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    if(!IS_PTR_NULL(drv->Interface) && !IS_PTR_NULL(drv->Interface->Init))
    {
        return drv->Interface->Init(drv->Device);
    }
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       device close opera
 * @param       [in/out]  *drv            device type
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
__INLINE
hal_err_t Hal_Device_Fini(Hal_Device_t *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    if(!IS_PTR_NULL(drv->Interface) && !IS_PTR_NULL(drv->Interface->Fini))
    {
        return drv->Interface->Fini(drv->Device);
    }
    
    return HAL_ERR_NONE;
}
    
/**
 *******************************************************************************
 * @brief       device write opera
 * @param       [in/out]  *drv            device type
 * @param       [in/out]  buf             write buffer
 * @param       [in/out]  size            write size
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
__INLINE
hal_err_t Hal_Device_Write(Hal_Device_t *drv, uint8_t *buf, uint8_t size)
{
    hal_assert(IS_PTR_NULL(drv));
    
    if(!IS_PTR_NULL(drv->Interface) && !IS_PTR_NULL(drv->Interface->Write))
    {
        return drv->Interface->Write(drv->Device, buf, size);
    }
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       device read opera
 * @param       [in/out]  *drv            device type
 * @param       [in/out]  buf             read buffer
 * @param       [in/out]  size            read size
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
__INLINE
hal_err_t Hal_Device_Read(Hal_Device_t *drv, uint8_t *buf, uint8_t size)
{
    hal_assert(IS_PTR_NULL(drv));
    
    if(!IS_PTR_NULL(drv->Interface) && !IS_PTR_NULL(drv->Interface->Read))
    {
        return drv->Interface->Read(drv->Device, buf, size);
    }
    
    return HAL_ERR_NONE;
}


/**
 *******************************************************************************
 * @brief       hal device control
 * @param       [in/out]  *drv            device type
 * @param       [in/out]  cmd             control cmd
 * @param       [in/out]  ...             expand param
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
__INLINE
hal_err_t Hal_Device_Control(Hal_Device_t *drv, uint8_t cmd, ...)
{
    hal_assert(IS_PTR_NULL(drv));
    va_list args;
    hal_err_t retValue = HAL_ERR_FAIL;
    
    if(!IS_PTR_NULL(drv->Interface) && !IS_PTR_NULL(drv->Interface->Control))
    {
        va_start(args, cmd);
        retValue = drv->Interface->Control(drv->Device, cmd, args);
        va_end(args);
        
        return retValue;
    }
    
    return HAL_ERR_NONE;
}

/** @}*/     /** hal device component */

/**********************************END OF FILE*********************************/
