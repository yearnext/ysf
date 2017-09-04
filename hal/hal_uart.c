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
 * @file       hal_uart.c                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-17                                                      *
 * @brief      hal uart component source files                                 *
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
 * @defgroup hal uart component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_uart.h"
#include "map_uart.h"

/* Exported constants --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define uart opera interface
 *******************************************************************************
 */ 
#ifdef USE_HAL_DEVICE_COMPONENT
const struct Hal_Interface Hal_Uart_Interface = 
{
    .Init = Hal_Uart_Interface_Init, 
    .Fini = Hal_Uart_Interface_Fini, 
    .Control = Hal_Uart_Interface_Control,
};
#endif

/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define uart opera interface
 *******************************************************************************
 */ 
#if USE_UART_COMPONENT
static const struct Map_Uart_Opera *map_api = (struct Map_Uart_Opera *)&map_uart_api;
#endif

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_UART_COMPONENT
/**
 *******************************************************************************
 * @brief       hal api : init device
 * @param       [in/out]  *drv            device block
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Uart_Interface_Init(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_Uart *uart = (Hal_Device_Uart *)drv;

    if(!IS_PTR_NULL(map_api->Open) && !IS_PTR_NULL(map_api->Init))
    {
        map_api->Open(uart->Config.Port);
        map_api->Init(uart->Config.Port, (void *)uart);
    }
    else
    {
        return HAL_ERR_FAIL;
    }
    
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
hal_err_t Hal_Uart_Interface_Fini(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_Uart *uart = (Hal_Device_Uart *)drv;
    
    if(!IS_PTR_NULL(map_api->Fini))
    {
        map_api->Fini(uart->Config.Port);   
    }
    else
    {
        return HAL_ERR_FAIL;
    }
    
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
hal_err_t Hal_Uart_Interface_Control(void *drv, uint8_t cmd, va_list args)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_Uart *uart = (Hal_Device_Uart *)drv;
    
    switch(cmd)
    {
        case HAL_DEVICE_OPEN_CMD:
        {
            if(!IS_PTR_NULL(map_api->Open))
            {
                map_api->Open(uart->Config.Port);
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
                map_api->Close(uart->Config.Port); 
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_INIT_CMD:
        {
            //< init device
            if(!IS_PTR_NULL(map_api->Open) && !IS_PTR_NULL(map_api->Init))
            {
                map_api->Open(uart->Config.Port);
                map_api->Init(uart->Config.Port, (void *)uart);
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
                map_api->Fini(uart->Config.Port);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_CONNECT_TX_CMD:
        {
            if(!IS_PTR_NULL(map_api->TxConnect))
            {
                map_api->TxConnect(uart->Config.Port);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_DISCONNECT_TX_CMD:
        {
            if(!IS_PTR_NULL(map_api->TxDisconnect))
            {
                map_api->TxDisconnect(uart->Config.Port);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_CONNECT_RX_CMD:
        {
            if(!IS_PTR_NULL(map_api->RxConnect))
            {
                map_api->RxConnect(uart->Config.Port);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_DISCONNECT_RX_CMD:
        {
            if(!IS_PTR_NULL(map_api->RxDisconnect))
            {
                map_api->RxDisconnect(uart->Config.Port);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_SEND_BYTE_CMD:
        {
            if(!IS_PTR_NULL(map_api->Send))
            {
                uint8_t sendData = va_arg(args, int);
                map_api->Send(uart->Config.Port, sendData);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_RECEIVE_BYTE_CMD:
        {
            if(!IS_PTR_NULL(map_api->Send))
            {
                uint8_t *recData = va_arg(args, uint8_t*);
                *recData = map_api->Receive(uart->Config.Port);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_CLR_TX_FLAG_CMD:
        {
            if(!IS_PTR_NULL(map_api->IsTxComplet))
            {
                map_api->IsTxComplet(uart->Config.Port);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_GET_TX_FLAG_CMD:
        {
            if(!IS_PTR_NULL(map_api->IsTxComplet))
            {
                bool *txFlag = va_arg(args, bool*);
                *txFlag = map_api->IsTxComplet(uart->Config.Port);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_CLR_RX_FLAG_CMD:
        {
            if(!IS_PTR_NULL(map_api->IsRxComplet))
            {
                map_api->IsRxComplet(uart->Config.Port);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_GET_RX_FLAG_CMD:
        {
            if(!IS_PTR_NULL(map_api->IsRxComplet))
            {
                bool *rxFlag = va_arg(args, bool*);
                *rxFlag = map_api->IsRxComplet(uart->Config.Port);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_SET_TX_CALLBACK_CMD:
        {
            if(!IS_PTR_NULL(map_api->SetTxCallback))
            {
                Hal_Callback_t callback;
                
                callback.Function = va_arg(args, void*);
                callback.Param = va_arg(args, void*);
                
                map_api->SetTxCallback(uart->Config.Port, callback.Tx, callback.Param);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_SET_RX_CALLBACK_CMD:
        {
            if(!IS_PTR_NULL(map_api->SetRxCallback))
            {
                Hal_Callback_t callback;
                
                callback.Function = va_arg(args, void*);
                callback.Param = va_arg(args, void*);
                
                map_api->SetRxCallback(uart->Config.Port, callback.Rx, callback.Param);
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

/** @}*/     /** hal uart component */

/**********************************END OF FILE*********************************/
