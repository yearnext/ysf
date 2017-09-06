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
 * @brief       device register opera
 * @param       [in/out]  *dev            device type
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
__INLINE
hal_err_t Hal_Device_Register(Hal_Device_t *dev, void *device, struct Hal_Interface *interface)
{
    hal_assert(IS_PTR_NULL(dev));
    
    dev->Device = device;
    dev->Interface = interface;
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       device unregister opera
 * @param       [in/out]  *dev            device type
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
__INLINE 
hal_err_t Hal_Device_Unregister(Hal_Device_t *dev)
{
    hal_assert(IS_PTR_NULL(dev));

    dev->Device = NULL;
    dev->Interface = NULL;
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       device open opera
 * @param       [in/out]  *dev            device type
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
__INLINE
hal_err_t Hal_Device_Init(Hal_Device_t *dev)
{
    hal_assert(IS_PTR_NULL(dev));
    
    if(dev->Lock == HAL_DEVICE_LOCK)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_LOCK;
        return HAL_ERR_FAIL;
    }
    
    if(dev->State == HAL_DEVICE_INIT_STATE)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_INITED;
        return HAL_ERR_FAIL;
    }
    
    if(!IS_PTR_NULL(dev->Interface) && !IS_PTR_NULL(dev->Interface->Init))
    {
        dev->Interface->Init(dev->Device);
        
        dev->State = HAL_DEVICE_INIT_STATE;
    }
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       device close opera
 * @param       [in/out]  *dev            device type
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
__INLINE
hal_err_t Hal_Device_Fini(Hal_Device_t *dev)
{
    hal_assert(IS_PTR_NULL(dev));
    
    if(dev->Lock == HAL_DEVICE_LOCK)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_LOCK;
        return HAL_ERR_FAIL;
    }
    
    if(dev->State == HAL_DEVICE_UNINIT_STATE)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_UNINIT;
        return HAL_ERR_FAIL;
    }
    
    if(!IS_PTR_NULL(dev->Interface) && !IS_PTR_NULL(dev->Interface->Fini))
    {
        return dev->Interface->Fini(dev->Device);
    }
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       device write opera
 * @param       [in/out]  *dev            device type
 * @param       [in/out]  pos             opera pos
 * @param       [in/out]  *buf            opera buffer
 * @param       [in/out]  size            opera buffer size
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
__INLINE
hal_err_t Hal_Device_Write(Hal_Device_t *dev, uint8_t pos, uint8_t *buf, uint8_t size)
{
    hal_assert(IS_PTR_NULL(dev));
    
    if(dev->Lock == HAL_DEVICE_LOCK)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_LOCK;
        return HAL_ERR_FAIL;
    }
    
    if(dev->State != HAL_DEVICE_INIT_STATE)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_UNINIT;
        return HAL_ERR_FAIL;
    }
    
    if(!IS_PTR_NULL(dev->Interface) && !IS_PTR_NULL(dev->Interface->Write))
    {
        dev->Interface->Write(dev->Device, pos, buf, size);
    }
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       device read opera
 * @param       [in/out]  *dev            device type
 * @param       [in/out]  pos             opera pos
 * @param       [in/out]  *buf            opera buffer
 * @param       [in/out]  size            opera buffer size
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
__INLINE
hal_err_t Hal_Device_Read(Hal_Device_t *dev, uint8_t pos, uint8_t *buf, uint8_t size)
{
    hal_assert(IS_PTR_NULL(dev));
    
    if(dev->Lock == HAL_DEVICE_LOCK)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_LOCK;
        return HAL_ERR_FAIL;
    }
    
    if(dev->State != HAL_DEVICE_INIT_STATE)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_UNINIT;
        return HAL_ERR_FAIL;
    }
    
    if(!IS_PTR_NULL(dev->Interface) && !IS_PTR_NULL(dev->Interface->Read))
    {
        dev->Interface->Read(dev->Device, pos, buf, size);
    }
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal device control
 * @param       [in/out]  *dev            device type
 * @param       [in/out]  cmd             control cmd
 * @param       [in/out]  ...             expand param
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
__INLINE
hal_err_t Hal_Device_Control(Hal_Device_t *dev, uint8_t cmd, ...)
{
    hal_assert(IS_PTR_NULL(dev));
    va_list args;
    hal_err_t retValue = HAL_ERR_FAIL;
    
    if(dev->Lock == HAL_DEVICE_LOCK)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_LOCK;
        return HAL_ERR_FAIL;
    }
    
    if(dev->State == HAL_DEVICE_UNINIT_STATE)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_UNINIT;
        return HAL_ERR_FAIL;
    }
    
    if(!IS_PTR_NULL(dev->Interface) && !IS_PTR_NULL(dev->Interface->Control))
    {
        va_start(args, cmd);
        retValue = dev->Interface->Control(dev->Device, cmd, args);
        va_end(args);
        
        return retValue;
    }
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal device lock
 * @param       [in/out]  *dev            device type
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
__INLINE
hal_err_t Hal_Device_Lock(Hal_Device_t *dev)
{
    hal_assert(IS_PTR_NULL(dev));
    
    dev->Lock = HAL_DEVICE_LOCK;
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal device unlock
 * @param       [in/out]  *dev            device type
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
__INLINE
hal_err_t Hal_Device_Unlock(Hal_Device_t *dev)
{
    hal_assert(IS_PTR_NULL(dev));
    
    dev->Lock = HAL_DEVICE_UNLOCK;
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal get device error code
 * @param       [in/out]  *dev            device type
 * @return      [in/out]  errCode         result
 * @note        None
 *******************************************************************************
 */
__INLINE
uint8_t Hal_Device_GetErrCode(Hal_Device_t *dev)
{
    hal_assert(IS_PTR_NULL(dev));
    
    uint8_t errCode = dev->ErrCode;
    
    dev->ErrCode = HAL_DEVICE_ERR_CODE_NONE;
    
    return errCode;
}

/** @}*/     /** hal device component */

/**********************************END OF FILE*********************************/
