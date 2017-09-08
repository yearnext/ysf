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
#include "fw_memory.h"
#include "fw_linklist.h"

#include "hal_gpio.h"
#include "hal_timer.h"
#include "hal_uart.h"

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
struct Hal_Device_Block
{
    struct
    {
        struct Hal_Device_Block *Last;
        struct Hal_Device_Block *Next;
    }LinkList;
    
    struct Hal_Interface *Interface;
    uint8_t Type;
};

/**
 *******************************************************************************
 * @brief      timer control block
 *******************************************************************************
 */
struct
{
    struct
    {
        struct Hal_Device_Block *Head;
        struct Hal_Device_Block *Tail;
    }LinkList;

    uint8_t Num;
}static DevMgr;

/* Private functions ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       device block find
 * @param       [in/out]  type                              device type
 * @return      [in/out]  struct Hal_Device_Block *         device block address
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
struct Hal_Device_Block *Hal_Device_Find(uint8_t type)
{
    struct Hal_Device_Block *dev = DevMgr.LinkList.Head;
    
    //< find device is in list
    while(1)
    {
        if(dev->Type == type)
        {
            return dev;
        }
        
        if(dev->LinkList.Next == NULL)
        {
            return NULL;
        }
        
        dev = dev->LinkList.Next;
    }
}

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       device register opera
 * @param       [in/out]  type            device type
 * @param       [in/out]  *interface      device interface
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Device_Register(uint8_t type, struct Hal_Interface *interface)
{
    struct Hal_Device_Block *dev = DevMgr.LinkList.Head;
    struct Hal_Device_Block *newDev;
    
    //< find device is in list
    while(1)
    {
        if(dev->Type == type)
        {
            return HAL_ERR_NONE;
        }
        
        if(dev->LinkList.Next == NULL)
        {
            break;
        }
        
        dev = dev->LinkList.Next;
    }
    
    //< alloc memory
    newDev = Fw_Mem_Alloc(sizeof(struct Hal_Device_Block));
    
    if(IS_PTR_NULL(newDev))
    {
        return HAL_ERR_FAIL;
    }
    
    //< add node to list
    newDev->Interface = interface;
    newDev->Type      = type;
    
    if (Fw_dLinkList_Push((struct Fw_dLinkList_Block *)&DevMgr.LinkList,
                          (struct Fw_dLinkList *)&newDev->LinkList)
        == FW_ERR_NONE)
    {
        if(DevMgr.Num < 0xFF)
        {
            DevMgr.Num++;
        }
    }

    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       device unregister opera
 * @param       [in/out]  type            device type
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Device_Unregister(uint8_t type)
{
    struct Hal_Device_Block *dev = DevMgr.LinkList.Head;
    
    //< find device is in list
    while(1)
    {
        if(dev->Type == type)
        {
            break;
        }
        
        if(dev->LinkList.Next == NULL)
        {
            return HAL_ERR_FAIL;
        }
        
        dev = dev->LinkList.Next;
    }

    if (Fw_dLinkList_Remove((struct Fw_dLinkList_Block *)&DevMgr.LinkList,
                            (struct Fw_dLinkList *)&dev->LinkList)
        == FW_ERR_NONE)
    {
        if(DevMgr.Num > 0)
        {
            DevMgr.Num--;
        }
    }
    
    Fw_Mem_Free(dev);

    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       device open opera
 * @param       [in/out]  *dev            device block
 * @param       [in/out]  type            device type
 * @param       [in/out]  *param          param body
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Device_Froce_Open(Hal_Device_t *dev, uint8_t type, void *param)
{
    hal_assert(IS_PTR_NULL(dev));
    
    struct Hal_Device_Block *devBlock;
        
    //< check device is lock
    if(dev->Lock == HAL_DEVICE_LOCK)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_LOCK;
        return HAL_ERR_FAIL;
    }
    
    //< check device is init
    if(dev->State == HAL_DEVICE_INIT_STATE)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_INITED;
        return HAL_ERR_FAIL;
    }
    
    //< get device block
    Hal_Device_Lock(dev);
    
    devBlock = Hal_Device_Find(type);

    if(IS_PTR_NULL(devBlock))
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_UNREGISTER;
        goto _DEVICE_OPTION_FAIL;
    }
    
    //< open device
    dev->Interface = devBlock->Interface;
    dev->Device    = param;
    
    Hal_Device_Unlock(dev);
    
    return HAL_ERR_NONE;
    
_DEVICE_OPTION_FAIL:
    Hal_Device_Unlock(dev);
    
    return HAL_ERR_FAIL;
}

/**
 *******************************************************************************
 * @brief       device open opera
 * @param       [in/out]  *dev            device block
 * @param       [in/out]  type            device type
 * @param       [in/out]  *name           device name
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Device_Open(Hal_Device_t *dev, uint8_t type, char *name)
{
    hal_assert(IS_PTR_NULL(dev));
    
    struct Hal_Device_Block *devBlock;
        
    //< check device is lock
    if(dev->Lock == HAL_DEVICE_LOCK)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_LOCK;
        return HAL_ERR_FAIL;
    }
    
    //< check device is init
    if(dev->State == HAL_DEVICE_INIT_STATE)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_INITED;
        return HAL_ERR_FAIL;
    }
    
    //< get device block
    Hal_Device_Lock(dev);
    
    devBlock = Hal_Device_Find(type);

    if(IS_PTR_NULL(devBlock))
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_UNREGISTER;
        goto _DEVICE_OPTION_FAIL;
    }
    
    //< open device
    dev->Interface = devBlock->Interface;
    
    if(!IS_PTR_NULL(dev->Interface) && !IS_PTR_NULL(dev->Interface->Open))
    {
        dev->Device = dev->Interface->Open(name);
    }
    else
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_NOT_SUPPORT;
        goto _DEVICE_OPTION_FAIL;
    }
    
    Hal_Device_Unlock(dev);
    
    return HAL_ERR_NONE;
    
_DEVICE_OPTION_FAIL:
    Hal_Device_Unlock(dev);
    
    return HAL_ERR_FAIL;
}

/**
 *******************************************************************************
 * @brief       device open opera
 * @param       [in/out]  *dev            device type
 * @param       [in/out]  flag            device config flag
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Device_Init(Hal_Device_t *dev, uint32_t flag)
{
    hal_assert(IS_PTR_NULL(dev));

    //< check device is lock
    if(dev->Lock == HAL_DEVICE_LOCK)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_LOCK;
        return HAL_ERR_FAIL;
    }
    
    //< check device is init
    if(dev->State == HAL_DEVICE_INIT_STATE)
    {
        dev->ErrCode = HAL_DEVICE_ERR_CODE_INITED;
        return HAL_ERR_FAIL;
    }
    
    Hal_Device_Lock(dev);
    
    //< init device
    dev->Flag = flag;
    
    if(!IS_PTR_NULL(dev->Interface) && !IS_PTR_NULL(dev->Interface->Init))
    {
        dev->Interface->Init(dev->Device, dev->Flag);
        
        dev->State = HAL_DEVICE_INIT_STATE;
    }
    
    Hal_Device_Unlock(dev);
    
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
    hal_err_t flag;
    
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
        Hal_Device_Lock(dev);
        
        flag = dev->Interface->Fini(dev->Device);
        
        dev->State = HAL_DEVICE_UNINIT_STATE;
        
        Hal_Device_Unlock(dev);
        
        return flag;
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
        Hal_Device_Lock(dev);
        
        dev->Interface->Write(dev->Device, pos, buf, size);
        
        Hal_Device_Unlock(dev);
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
        Hal_Device_Lock(dev);
        
        dev->Interface->Read(dev->Device, pos, buf, size);
        
        Hal_Device_Unlock(dev);
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
        Hal_Device_Lock(dev);
        
        va_start(args, cmd);
        retValue = dev->Interface->Control(dev->Device, cmd, args);
        va_end(args);
        
        Hal_Device_Unlock(dev);
        
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

void Hal_Device_InitComponent(void)
{
    Hal_GPIO_InitComponent();
    Hal_Uart_InitComponent();
    Hal_Timer_InitComponent();
}

/** @}*/     /** hal device component */

/**********************************END OF FILE*********************************/
