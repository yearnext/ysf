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
 * @file       hal_spi.c                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-17                                                      *
 * @brief      hal spi component source files                                  *
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
 * @defgroup hal spi component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_spi.h"
#include "map_spi.h"

/* Exported constants --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define gpio opera interface
 *******************************************************************************
 */ 
static const struct Hal_SPI_Opera spi_ops = 
{
    .Open = Hal_SPI_Open,
    .Close = Hal_SPI_Close,
    
    .Init = Hal_SPI_Init,
    .Fini = Hal_SPI_Fini,

    .SetTxCallback = Hal_SPI_SetTxCallback,
    .SetRxCallback = Hal_SPI_SetRxCallback,
    
    .Send = Hal_SPI_Send,
    .Receive = Hal_SPI_Receive,
    
    .TxConnect = Hal_SPI_TxConnect,
    .TxDisconnect = Hal_SPI_TxDisconnect,
    
    .RxConnect = Hal_SPI_RxConnect,
    .RxDisconnect = Hal_SPI_RxDisconnect,
    
    .IsTxComplet = Hal_SPI_IsTxComplet,
    .IsRxComplet = Hal_SPI_IsRxComplet,
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
void Hal_SPI_Open(Hal_SPI_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));
    
    map_spi_api.Open(drv->Port); 
}

/**
 *******************************************************************************
 * @brief       hal api : close device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_SPI_Close(Hal_SPI_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    map_spi_api.Close(drv->Port); 
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
void Hal_SPI_Init(Hal_SPI_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));
    hal_assert(IS_PTR_NULL(param));
    
    drv->Opera = (struct Hal_SPI_Opera *)&spi_ops;
    
    map_spi_api.Open(drv->Port);
    map_spi_api.Init(drv->Port, (void *)drv); 
}

/**
 *******************************************************************************
 * @brief       hal api : deinit device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_SPI_Fini(Hal_SPI_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));
    
    map_spi_api.Fini(drv->Port);   
    
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
void Hal_SPI_Send(Hal_SPI_Handle *drv, uint8_t sendData)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));
    
    map_spi_api.Send(drv->Port, sendData);
}

/**
 *******************************************************************************
 * @brief       hal api : uart receive data
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  recData     recevie data
 * @note        None
 *******************************************************************************
 */
uint8_t Hal_SPI_Receive(Hal_SPI_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    return map_spi_api.Receive(drv->Port);
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
void Hal_SPI_SetTxCallback(Hal_SPI_Handle *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    Hal_SPI_Handle *config = (Hal_SPI_Handle *)param;
    
    map_spi_api.SetTxCallback(drv->Port, config->TxCallback.Callback, config->TxCallback.Param);
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
void Hal_SPI_SetRxCallback(Hal_SPI_Handle *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    Hal_SPI_Handle *config = (Hal_SPI_Handle *)param;
    
    map_spi_api.SetRxCallback(drv->Port, config->RxCallback.Callback, config->RxCallback.Param);
}

/**
 *******************************************************************************
 * @brief       hal api : connect uart tx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_SPI_TxConnect(Hal_SPI_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    map_spi_api.TxConnect(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : disconnect uart tx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_SPI_TxDisconnect(Hal_SPI_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    map_spi_api.TxDisconnect(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : connect uart rx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_SPI_RxConnect(Hal_SPI_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    map_spi_api.RxConnect(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : disconnect uart rx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_SPI_RxDisconnect(Hal_SPI_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    map_spi_api.RxDisconnect(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : check tx complet isr flag
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
bool Hal_SPI_IsTxComplet(Hal_SPI_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    return map_spi_api.IsTxComplet(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : check rx complet isr flag
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
bool Hal_SPI_IsRxComplet(Hal_SPI_Handle* drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));
    
    return map_spi_api.IsRxComplet(drv->Port);
}

/** @}*/     /** hal spi component */

/**********************************END OF FILE*********************************/
