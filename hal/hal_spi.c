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
#if USE_SPI_COMPONENT
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
#endif

#ifdef USE_HAL_DEVICE_COMPONENT
static hal_err_t Hal_SPI_Interface_Init(void*);
static hal_err_t Hal_SPI_Interface_Fini(void*);
static hal_err_t Hal_SPI_Interface_Control(void*, uint8_t, va_list);
const struct Hal_Interface Hal_SPI_Interface = 
{
    .Init = Hal_SPI_Interface_Init, 
    .Fini = Hal_SPI_Interface_Fini, 
    .Write = NULL, 
    .Read = NULL,
    .Control = Hal_SPI_Interface_Control,
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#ifdef USE_HAL_DEVICE_COMPONENT
/**
 *******************************************************************************
 * @brief       hal api : init device
 * @param       [in/out]  *drv            device block
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
static hal_err_t Hal_SPI_Interface_Init(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_SPI *spi = (Hal_Device_SPI *)drv;
    
    //< init device
    map_spi_api.Open(spi->Config.Port);
    map_spi_api.Init(spi->Config.Port, drv);
    
    //< set hal device opera
    spi->Opera = (struct Hal_SPI_Opera *)&spi_ops;
    
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
static hal_err_t Hal_SPI_Interface_Fini(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_SPI *spi = (Hal_Device_SPI *)drv;
    
    map_spi_api.Fini(spi->Config.Port);   

    spi->Opera = NULL;
    
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
static hal_err_t Hal_SPI_Interface_Control(void *drv, uint8_t cmd, va_list args)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_SPI *spi = (Hal_Device_SPI *)drv;
    
    switch(cmd)
    {
        case HAL_DEVICE_INIT_CMD:
        {
            //< init device
            map_spi_api.Open(spi->Config.Port);
            map_spi_api.Init(spi->Config.Port, drv);
            
            //< set hal device opera
            spi->Opera = (struct Hal_SPI_Opera *)&spi_ops;
            
            break;
        }
        case HAL_DEVICE_FINI_CMD:
        {
            map_spi_api.Fini(spi->Config.Port);   

            spi->Opera = NULL;
            
            break;
        }
        case HAL_CONNECT_TX_CMD:
        {
            map_spi_api.TxConnect(spi->Config.Port);
            break;
        }
        case HAL_DISCONNECT_TX_CMD:
        {
            map_spi_api.TxDisconnect(spi->Config.Port);
            break;
        }
        case HAL_CONNECT_RX_CMD:
        {
            map_spi_api.RxConnect(spi->Config.Port);
            break;
        }
        case HAL_DISCONNECT_RX_CMD:
        {
            map_spi_api.RxDisconnect(spi->Config.Port);
            break;
        }
        case HAL_SEND_BYTE_CMD:
        {
            uint8_t sendData = va_arg(args, int);
            map_spi_api.Send(spi->Config.Port, sendData);
            break;
        }
        case HAL_RECEIVE_BYTE_CMD:
        {
            uint8_t *recData = va_arg(args, uint8_t*);
            *recData = map_spi_api.Receive(spi->Config.Port);
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
#endif

/* Exported functions --------------------------------------------------------*/
#if USE_SPI_COMPONENT
/**
 *******************************************************************************
 * @brief       hal api : open device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_SPI_Open(Hal_Device_SPI *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));
    
    map_spi_api.Open(drv->Config.Port); 
}

/**
 *******************************************************************************
 * @brief       hal api : close device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_SPI_Close(Hal_Device_SPI *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    map_spi_api.Close(drv->Config.Port); 
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
void Hal_SPI_Init(Hal_Device_SPI *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));
    hal_assert(IS_PTR_NULL(param));
    
    drv->Opera = (struct Hal_SPI_Opera *)&spi_ops;
    
    map_spi_api.Open(drv->Config.Port);
    map_spi_api.Init(drv->Config.Port, (void *)drv); 
}

/**
 *******************************************************************************
 * @brief       hal api : deinit device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_SPI_Fini(Hal_Device_SPI *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));
    
    map_spi_api.Fini(drv->Config.Port);   
    
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
void Hal_SPI_Send(Hal_Device_SPI *drv, uint8_t sendData)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));
    
    map_spi_api.Send(drv->Config.Port, sendData);
}

/**
 *******************************************************************************
 * @brief       hal api : uart receive data
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  recData     recevie data
 * @note        None
 *******************************************************************************
 */
uint8_t Hal_SPI_Receive(Hal_Device_SPI *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    return map_spi_api.Receive(drv->Config.Port);
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
void Hal_SPI_SetTxCallback(Hal_Device_SPI *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    Hal_Device_SPI *config = (Hal_Device_SPI *)param;
    
    map_spi_api.SetTxCallback(drv->Config.Port, config->TxCallback.Tx, config->TxCallback.Param);
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
void Hal_SPI_SetRxCallback(Hal_Device_SPI *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    Hal_Device_SPI *config = (Hal_Device_SPI *)param;
    
    map_spi_api.SetRxCallback(drv->Config.Port, config->RxCallback.Rx, config->RxCallback.Param);
}

/**
 *******************************************************************************
 * @brief       hal api : connect uart tx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_SPI_TxConnect(Hal_Device_SPI *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    map_spi_api.TxConnect(drv->Config.Port);
}

/**
 *******************************************************************************
 * @brief       hal api : disconnect uart tx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_SPI_TxDisconnect(Hal_Device_SPI *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    map_spi_api.TxDisconnect(drv->Config.Port);
}

/**
 *******************************************************************************
 * @brief       hal api : connect uart rx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_SPI_RxConnect(Hal_Device_SPI *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    map_spi_api.RxConnect(drv->Config.Port);
}

/**
 *******************************************************************************
 * @brief       hal api : disconnect uart rx opera
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_SPI_RxDisconnect(Hal_Device_SPI *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    map_spi_api.RxDisconnect(drv->Config.Port);
}

/**
 *******************************************************************************
 * @brief       hal api : check tx complet isr flag
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
bool Hal_SPI_IsTxComplet(Hal_Device_SPI *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));

    return map_spi_api.IsTxComplet(drv->Config.Port);
}

/**
 *******************************************************************************
 * @brief       hal api : check rx complet isr flag
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
bool Hal_SPI_IsRxComplet(Hal_Device_SPI* drv)
{
    hal_assert(IS_PTR_NULL(drv));
    hal_assert(IS_PTR_NULL(map_spi_api));
    
    return map_spi_api.IsRxComplet(drv->Config.Port);
}
#endif

/** @}*/     /** hal spi component */

/**********************************END OF FILE*********************************/
