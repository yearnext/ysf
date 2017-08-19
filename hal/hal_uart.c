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

/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       hal api : open device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_Open(Hal_Uart_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_uart_api));
    
    map_uart_api.Open(drv->Port); 
}

/**
 *******************************************************************************
 * @brief       hal api : close device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_Close(Hal_Uart_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_uart_api));

    map_uart_api.Close(drv->Port); 
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
void Hal_Uart_Init(Hal_Uart_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_uart_api));
    hal_assert(IS_PTR_NULL(param));
    
    drv->Opera = (struct Hal_Uart_Opera *)&uart_ops;
    
    map_uart_api.Open(drv->Port);
    map_uart_api.Init(drv->Port, (void *)drv); 
}

/**
 *******************************************************************************
 * @brief       hal api : deinit device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_Fini(Hal_Uart_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_uart_api));
    
    map_uart_api.Fini(drv->Port);   
    
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
void Hal_Uart_Send(Hal_Uart_Handle *drv, uint8_t sendData)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_uart_api));
    
    map_uart_api.Send(drv->Port, sendData);
}

/**
 *******************************************************************************
 * @brief       hal api : uart receive data
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  recData     recevie data
 * @note        None
 *******************************************************************************
 */
uint8_t Hal_Uart_Receive(Hal_Uart_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_uart_api));

    return map_uart_api.Receive(drv->Port);
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
void Hal_Uart_SetTxCallback(Hal_Uart_Handle *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_uart_api));

    Hal_Uart_Handle *config = (Hal_Uart_Handle *)param;
    
    map_uart_api.SetTxCallback(drv->Port, config->TxCallback.Callback, config->TxCallback.Param);
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
void Hal_Uart_SetRxCallback(Hal_Uart_Handle *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_uart_api));

    Hal_Uart_Handle *config = (Hal_Uart_Handle *)param;
    
    map_uart_api.SetRxCallback(drv->Port, config->RxCallback.Callback, config->RxCallback.Param);
}

/**
 *******************************************************************************
 * @brief       hal api : connect uart tx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_TxConnect(Hal_Uart_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_uart_api));

    map_uart_api.TxConnect(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : disconnect uart tx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_TxDisconnect(Hal_Uart_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_uart_api));

    map_uart_api.TxDisconnect(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : connect uart rx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_RxConnect(Hal_Uart_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_uart_api));

    map_uart_api.RxConnect(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : disconnect uart rx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_RxDisconnect(Hal_Uart_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_uart_api));

    map_uart_api.RxDisconnect(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : check tx complet isr flag
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
bool Hal_Uart_IsTxComplet(Hal_Uart_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_uart_api));

    return map_uart_api.IsTxComplet(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : check rx complet isr flag
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
bool Hal_Uart_IsRxComplet(Hal_Uart_Handle* drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_uart_api));
    
    return map_uart_api.IsRxComplet(drv->Port);
}

/** @}*/     /** hal uart component */

/**********************************END OF FILE*********************************/
