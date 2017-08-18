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
#if USE_UART_COMPONENT
/**
 *******************************************************************************
 * @brief      define mcu application pack gpio opera interface
 *******************************************************************************
 */ 
static struct Map_Uart_Opera *_uart_ops = NULL;

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
#endif

/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_UART_COMPONENT
/**
 *******************************************************************************
 * @brief       register hal uart module
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_Module_Register(void)
{
    Map_Uart_API_Register((void **)&_uart_ops);
}

/**
 *******************************************************************************
 * @brief       hal api : open device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Hal_Uart_Open(struct Hal_Uart_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_uart_ops));
    
    _uart_ops->Open(drv->Port); 
}

/**
 *******************************************************************************
 * @brief       hal api : close device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Hal_Uart_Close(struct Hal_Uart_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_uart_ops));

    _uart_ops->Close(drv->Port); 
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
__INLINE void Hal_Uart_Init(struct Hal_Uart_Device *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_uart_ops));
    hal_assert(IS_PTR_NULL(param));
    
    drv->Opera = (struct Hal_Uart_Opera *)&uart_ops;
    
    _uart_ops->Open(drv->Port);
    _uart_ops->Init(drv->Port, param); 
}

/**
 *******************************************************************************
 * @brief       hal api : deinit device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Hal_Uart_Fini(struct Hal_Uart_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_uart_ops));
    
    _uart_ops->Fini(drv->Port);   
    
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
__INLINE void Hal_Uart_Send(struct Hal_Uart_Device *drv, uint8_t sendData)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_uart_ops));
    
    _uart_ops->Send(drv->Port, sendData);
}

/**
 *******************************************************************************
 * @brief       hal api : uart receive data
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  recData     recevie data
 * @note        None
 *******************************************************************************
 */
__INLINE uint8_t Hal_Uart_Receive(struct Hal_Uart_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_uart_ops));

    return _uart_ops->Receive(drv->Port);
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
__INLINE void Hal_Uart_SetTxCallback(struct Hal_Uart_Device *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_uart_ops));

    Hal_Uart_InitType *config = (Hal_Uart_InitType *)param;
    
    _uart_ops->SetTxCallback(drv->Port, config->TxCallback.Callback, config->TxCallback.Param);
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
__INLINE void Hal_Uart_SetRxCallback(struct Hal_Uart_Device *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_uart_ops));

    Hal_Uart_InitType *config = (Hal_Uart_InitType *)param;
    
    _uart_ops->SetRxCallback(drv->Port, config->RxCallback.Callback, config->RxCallback.Param);
}

/**
 *******************************************************************************
 * @brief       hal api : connect uart tx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Hal_Uart_TxConnect(struct Hal_Uart_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_uart_ops));

    _uart_ops->TxConnect(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : disconnect uart tx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Hal_Uart_TxDisconnect(struct Hal_Uart_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_uart_ops));

    _uart_ops->TxDisconnect(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : connect uart rx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Hal_Uart_RxConnect(struct Hal_Uart_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_uart_ops));

    _uart_ops->RxConnect(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : disconnect uart rx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE void Hal_Uart_RxDisconnect(struct Hal_Uart_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_uart_ops));

    _uart_ops->RxDisconnect(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : check tx complet isr flag
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE bool Hal_Uart_IsTxComplet(struct Hal_Uart_Device *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_uart_ops));

    return _uart_ops->IsTxComplet(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : check rx complet isr flag
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE bool Hal_Uart_IsRxComplet(struct Hal_Uart_Device* drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(_uart_ops));
    
    return _uart_ops->IsRxComplet(drv->Port);
}

#endif

/** @}*/     /** hal uart component */

/**********************************END OF FILE*********************************/
