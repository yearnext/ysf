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
 * @brief      define gpio opera interface
 *******************************************************************************
 */ 
static const struct Hal_Uart_Opera uart_ops = 
{
    .Open = Hal_Uart_Open,
    .Close = Hal_Uart_Close,
    
    .Init = Hal_Uart_Init,
    .Fini = Hal_Uart_Fini,

    .SetTxCallback = Hal_Uart_SetTxCallback,
    .SetRxCallback = Hal_Uart_SetRxCallback,
    
    .Send = Hal_Uart_Send,
    .Receive = Hal_Uart_Receive,
    
    .TxConnect = Hal_Uart_TxConnect,
    .TxDisconnect = Hal_Uart_TxDisconnect,
    
    .RxConnect = Hal_Uart_RxConnect,
    .RxDisconnect = Hal_Uart_RxDisconnect,
    
    .IsTxComplet = Hal_Uart_IsTxComplet,
    .IsRxComplet = Hal_Uart_IsRxComplet,
};

#ifdef USE_HAL_DEVICE_COMPONENT
static hal_err_t Hal_Uart_Interface_Init(void*);
static hal_err_t Hal_Uart_Interface_Fini(void*);
static hal_err_t Hal_Uart_Interface_Write(void*, uint8_t*, uint8_t);
static hal_err_t Hal_Uart_Interface_Read(void*, uint8_t*, uint8_t);
static hal_err_t Hal_Uart_Interface_Control(void*, uint8_t, va_list);
const struct Hal_Interface Hal_Uart_Interface = 
{
    .Init = Hal_Uart_Interface_Init, 
    .Fini = Hal_Uart_Interface_Fini, 
    .Write = Hal_Uart_Interface_Write, 
    .Read = Hal_Uart_Interface_Read,
    .Control = Hal_Uart_Interface_Control,
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#ifdef USE_HAL_DEVICE_COMPONENT
static void Hal_Uart_SendData(void *drv);
static void Hal_Uart_ReceiveData(void *drv, uint8_t recData);

/**
 *******************************************************************************
 * @brief       hal api : init device
 * @param       [in/out]  *drv            device block
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
static hal_err_t Hal_Uart_Interface_Init(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_Uart *uart = (Hal_Device_Uart *)drv;
    
    //< init device
    map_uart_api.Open(uart->Config.Port);
    map_uart_api.Init(uart->Config.Port, (void *)uart);
    
    //< set uart call back
    map_uart_api.SetTxCallback(uart->Config.Port, Hal_Uart_SendData, drv);
    map_uart_api.SetRxCallback(uart->Config.Port, Hal_Uart_ReceiveData, drv);
    
    //< set hal device opera
    uart->Opera = (struct Hal_Uart_Opera *)&uart_ops;
    
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
static hal_err_t Hal_Uart_Interface_Fini(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_Uart *uart = (Hal_Device_Uart *)drv;
    
    map_uart_api.Fini(uart->Config.Port);   

    uart->Opera = NULL;
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal api : write data to device
 * @param       [in/out]  *drv            device block
 * @param       [in/out]  *buf            write data buffer
 * @param       [in/out]  size            write size
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
static hal_err_t Hal_Uart_Interface_Write(void *drv, uint8_t *buf, uint8_t size)
{
    Hal_Device_Uart *uart = (Hal_Device_Uart *)drv;
    
    hal_assert(IS_PTR_NULL(uart));
    hal_assert(IS_PTR_NULL(uart->TxBuffer));
    hal_assert(IS_PTR_NULL(buf));
    hal_assert(size == 0);
    
    if(uart->TxFlag == MCU_UART_PIPE_DISCONNECT)
    {
        return HAL_ERR_NONE;
    }
    
    Fw_Buffer_Write(uart->TxBuffer, buf, size);
    
    Hal_Uart_SendData(drv);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal api : read data from device
 * @param       [in/out]  *drv            device block
 * @param       [in/out]  *buf            read data buffer
 * @param       [in/out]  size            read size
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
static hal_err_t Hal_Uart_Interface_Read(void *drv, uint8_t *buf, uint8_t size)
{
    Hal_Device_Uart *uart = (Hal_Device_Uart *)drv;
    
    hal_assert(IS_PTR_NULL(uart));
    hal_assert(IS_PTR_NULL(uart->RxBuffer));
    hal_assert(IS_PTR_NULL(buf));
    hal_assert(size == 0);
    
    if(uart->RxFlag == MCU_UART_PIPE_DISCONNECT)
    {
        return HAL_ERR_NONE;
    }
    
    Fw_Buffer_Read(uart->RxBuffer, buf, size);
    
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
static hal_err_t Hal_Uart_Interface_Control(void *drv, uint8_t cmd, va_list args)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_Uart *uart = (Hal_Device_Uart *)drv;
    
    switch(cmd)
    {
        case HAL_DEVICE_INIT_CMD:
        {
            //< init device
            map_uart_api.Open(uart->Config.Port);
            map_uart_api.Init(uart->Config.Port, (void *)uart);
            
            //< set uart call back
            map_uart_api.SetTxCallback(uart->Config.Port, Hal_Uart_SendData, drv);
            map_uart_api.SetRxCallback(uart->Config.Port, Hal_Uart_ReceiveData, drv);
            
            //< set hal device opera
            uart->Opera = (struct Hal_Uart_Opera *)&uart_ops;
            
            break;
        }
        case HAL_DEVICE_FINI_CMD:
        {
            map_uart_api.Fini(uart->Config.Port);   

            uart->Opera = NULL;
            
            break;
        }
        case HAL_CONNECT_TX_CMD:
        {
            map_uart_api.TxConnect(uart->Config.Port);

            uart->TxFlag = MCU_UART_PIPE_CONNECT_WITH_IDLE;
            break;
        }
        case HAL_DISCONNECT_TX_CMD:
        {
            map_uart_api.TxDisconnect(uart->Config.Port);
    
            uart->TxFlag = MCU_UART_PIPE_DISCONNECT;
            break;
        }
        case HAL_CONNECT_RX_CMD:
        {
            map_uart_api.RxConnect(uart->Config.Port);

            uart->RxFlag = MCU_UART_PIPE_CONNECT_WITH_IDLE;
            break;
        }
        case HAL_DISCONNECT_RX_CMD:
        {
            map_uart_api.RxDisconnect(uart->Config.Port);
    
            uart->RxFlag = MCU_UART_PIPE_DISCONNECT;
            break;
        }
        case HAL_SEND_BYTE_CMD:
        {
            uint8_t sendData = va_arg(args, int);
            map_uart_api.Send(uart->Config.Port, sendData);
            break;
        }
        case HAL_RECEIVE_BYTE_CMD:
        {
            uint8_t *recData = va_arg(args, uint8_t*);
            *recData = map_uart_api.Receive(uart->Config.Port);
            break;
        }
//        case HAL_CLR_TX_FLAG_CMD:
//        {
//            break;
//        }
//        case HAL_GET_TX_FLAG_CMD:
//        {
//            break;
//        }
//        case HAL_CLR_RX_FLAG_CMD:
//        {
//            break;
//        }
//        case HAL_GET_RX_FLAG_CMD:
//        {
//            break;
//        }
        default:
            break;
    }
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal api : send data
 * @param       [in/out]  *drv            device block
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
static void Hal_Uart_SendData(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    Hal_Device_Uart *uart = (Hal_Device_Uart *)drv;
    
    uint8_t sendData = 0;

    //< is disconnect uart tx
    if(uart->TxFlag == MCU_UART_PIPE_DISCONNECT)
    {
        return;
    }
    
    //< 1. set uart tx flag
    uart->TxFlag = MCU_UART_PIPE_CONNECT_WITH_IDLE;
    
    //< 2. run uart tx call back
    if(!IS_PTR_NULL(uart->TxCallback.Tx))
    {
        uart->TxCallback.Tx(uart->TxCallback.Param);
    }
        
    //< 3. read send data from send buffer
    if (Fw_Buffer_Read(uart->RxBuffer, &sendData, 1) != 1)
    {    
        uart->TxFlag = MCU_UART_PIPE_CONNECT_WITH_IDLE;
        return;
    }
    
    //< 4. send data
    map_uart_api.Send(uart->Config.Port, sendData);
}

/**
 *******************************************************************************
 * @brief       hal api : receive data
 * @param       [in/out]  *drv            device block
 * @param       [in/out]  recData         receive data
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
static void Hal_Uart_ReceiveData(void *drv, uint8_t recData)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_Uart *uart = (Hal_Device_Uart *)drv;
   
    //< is disconnect uart rx
    if(uart->RxFlag == MCU_UART_PIPE_DISCONNECT)
    {
        return;
    }
    
    //< 1. set uart rx flag
    uart->RxFlag = MCU_UART_CONNECT_WITH_WORK;
        
    //< 2. write data to receive buffer
    if (Fw_Buffer_Write(uart->RxBuffer, &recData, 1) != 1)
    {
        uart->RxFlag = MCU_UART_PIPE_CONNECT_WITH_IDLE;
    }
    
    //< 3. run uart rx call back
    if(!IS_PTR_NULL(uart->RxCallback.Rx))
    {
        uart->RxCallback.Rx(uart->RxCallback.Param, recData);
    }
}
#endif

/* Exported functions --------------------------------------------------------*/
#if USE_UART_COMPONENT
/**
 *******************************************************************************
 * @brief       hal api : open device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_Open(Hal_Device_Uart *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    map_uart_api.Open(drv->Config.Port); 
}

/**
 *******************************************************************************
 * @brief       hal api : close device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_Close(Hal_Device_Uart *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    map_uart_api.Close(drv->Config.Port); 
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
void Hal_Uart_Init(Hal_Device_Uart *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(param));
    
    drv->Opera = (struct Hal_Uart_Opera *)&uart_ops;
    
    map_uart_api.Open(drv->Config.Port);
    map_uart_api.Init(drv->Config.Port, (void *)drv); 
}

/**
 *******************************************************************************
 * @brief       hal api : deinit device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_Fini(Hal_Device_Uart *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    map_uart_api.Fini(drv->Config.Port);   
    
    drv->Opera = NULL;
}

/**
 *******************************************************************************
 * @brief       hal api : uart send data
 * @param       [in/out]  *drv        device block
 * @param       [in/out]  sendData    uart send data
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_Send(Hal_Device_Uart *drv, uint8_t sendData)
{
    hal_assert(IS_PTR_NULL(drv));

    map_uart_api.Send(drv->Config.Port, sendData);
}

/**
 *******************************************************************************
 * @brief       hal api : uart receive data
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  recData     recevie data
 * @note        None
 *******************************************************************************
 */
uint8_t Hal_Uart_Receive(Hal_Device_Uart *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    return map_uart_api.Receive(drv->Config.Port);
}

/**
 *******************************************************************************
 * @brief       hal api : set uart tx call back 
 * @param       [in/out]  *drv        device block
 * @param       [in/out]  *param      config block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_SetTxCallback(Hal_Device_Uart *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));

    Hal_Device_Uart *config = (Hal_Device_Uart *)param;
    
    map_uart_api.SetTxCallback(drv->Config.Port, config->TxCallback.Tx, config->TxCallback.Param);
}

/**
 *******************************************************************************
 * @brief       hal api : set uart rx call back 
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  *param      config block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_SetRxCallback(Hal_Device_Uart *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));

    Hal_Device_Uart *config = (Hal_Device_Uart *)param;
    
    map_uart_api.SetRxCallback(drv->Config.Port, config->RxCallback.Rx, config->RxCallback.Param);
}

/**
 *******************************************************************************
 * @brief       hal api : connect uart tx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_TxConnect(Hal_Device_Uart *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    map_uart_api.TxConnect(drv->Config.Port);
    
    drv->TxFlag = MCU_UART_PIPE_CONNECT_WITH_IDLE;
}

/**
 *******************************************************************************
 * @brief       hal api : disconnect uart tx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_TxDisconnect(Hal_Device_Uart *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    map_uart_api.TxDisconnect(drv->Config.Port);
    
    drv->TxFlag = MCU_UART_PIPE_DISCONNECT;
}

/**
 *******************************************************************************
 * @brief       hal api : connect uart rx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_RxConnect(Hal_Device_Uart *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    map_uart_api.RxConnect(drv->Config.Port);
    
    drv->RxFlag = MCU_UART_PIPE_CONNECT_WITH_IDLE;
}

/**
 *******************************************************************************
 * @brief       hal api : disconnect uart rx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_RxDisconnect(Hal_Device_Uart *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    map_uart_api.RxDisconnect(drv->Config.Port);
    
    drv->RxFlag = MCU_UART_PIPE_DISCONNECT;
}

/**
 *******************************************************************************
 * @brief       hal api : check tx complet isr flag
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
bool Hal_Uart_IsTxComplet(Hal_Device_Uart *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    return map_uart_api.IsTxComplet(drv->Config.Port);
}

/**
 *******************************************************************************
 * @brief       hal api : check rx complet isr flag
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
bool Hal_Uart_IsRxComplet(Hal_Device_Uart* drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    return map_uart_api.IsRxComplet(drv->Config.Port);
}
#endif

/** @}*/     /** hal uart component */

/**********************************END OF FILE*********************************/