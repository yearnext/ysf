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
 * @file       map_spi.c                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-08                                                      *
 * @brief      mcu spi application component source files                      *
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
 * @defgroup map spi component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"
#include "stm32f1xx_ll_spi.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"

#include "comm_path.h"
#include "map_spi.h"
#include "map_gpio.h"

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define spi assert macro
 *******************************************************************************
 */
#define HAL_SPI_PORT_NUM                                             _dimof(SPI)
#define IS_SPI_PORT_INVAILD(n)                         ((n) >= HAL_SPI_PORT_NUM)

/* Private constants ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define spi register
 *******************************************************************************
 */ 
static SPI_TypeDef * const SPI[] = 
{
#ifdef SPI1
    SPI1, 
#endif
    
#ifdef SPI2
    SPI2, 
#endif
    
#ifdef SPI3
    SPI3, 
#endif
};

/**
 *******************************************************************************
 * @brief      define spi irqn
 *******************************************************************************
 */ 
static const IRQn_Type SPIIrqn[] = 
{
#ifdef SPI1
    SPI1_IRQn, 
#endif
    
#ifdef SPI2
    SPI2_IRQn, 
#endif
    
#ifdef SPI3
    SPI3_IRQn, 
#endif
};

/**
 *******************************************************************************
 * @brief      define map api
 *******************************************************************************
 */ 
void Map_SPI_Open(uint8_t);
void Map_SPI_Close(uint8_t);
void Map_SPI_Init(uint8_t, void*);
void Map_SPI_Fini(uint8_t);
void Map_SPI_SetTxCallback(uint8_t, void (*)(void*), void*);
void Map_SPI_SetRxCallback(uint8_t, void (*)(void*, uint8_t), void*);
void Map_SPI_SendData(uint8_t, uint8_t);
uint8_t Map_SPI_ReceiveData(uint8_t);
void Map_SPI_TxConnect(uint8_t);
void Map_SPI_TxDisconnect(uint8_t);
void Map_SPI_RxConnect(uint8_t);
void Map_SPI_RxDisconnect(uint8_t);
bool Map_SPI_IsTxComplet(uint8_t);
bool Map_SPI_IsRxComplet(uint8_t);

const struct Map_SPI_Opera map_spi_api = 
{
    .Open = Map_SPI_Open,
    .Close = Map_SPI_Close,
    
    .Init = Map_SPI_Init,
    .Fini = Map_SPI_Fini,
    
    .SetTxCallback = Map_SPI_SetTxCallback,
    .SetRxCallback = Map_SPI_SetRxCallback,

    .Send = Map_SPI_SendData,
    .Receive = Map_SPI_ReceiveData,
    
    .TxConnect = Map_SPI_TxConnect,
    .TxDisconnect = Map_SPI_TxDisconnect,
    
    .RxConnect = Map_SPI_RxConnect,
    .RxDisconnect = Map_SPI_RxDisconnect,
    
    .IsTxComplet = Map_SPI_IsTxComplet,
    .IsRxComplet = Map_SPI_IsRxComplet,
};

/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define uart tx isr call back
 *******************************************************************************
 */
static Hal_Callback_t SPI_Tx_Callback[HAL_SPI_PORT_NUM];
static Hal_Callback_t SPI_Rx_Callback[HAL_SPI_PORT_NUM];

/**
 *******************************************************************************
 * @brief       define uart comm flag
 *******************************************************************************
 */
static struct
{
    uint8_t TxEnable;
    uint8_t RxEnable;
}SPI_Comm_Flag[HAL_SPI_PORT_NUM];

/* Private typedef -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       enable spi
 * @param       [in/out]  port            uart id
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Map_SPI_Open(uint8_t port)
{
    hal_assert(IS_SPI_PORT_INVAILD(port));

#ifdef SPI1
    if (port == MCU_SPI_1)
    {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
    }
#endif
    
#ifdef SPI2
    else if (port == MCU_SPI_2)
    {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
    }
#endif
    
#ifdef SPI3
    else if (port == MCU_SPI_3)
    {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI3);
    }
#endif
    else
    {
        //< do nothing
    }
}

/**
 *******************************************************************************
 * @brief       disable spi
 * @param       [in/out]  port            uart id
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Map_SPI_Close(uint8_t port)
{
    hal_assert(IS_SPI_PORT_INVAILD(port));
    
    LL_SPI_DeInit(SPI[port]);
}

/**
 *******************************************************************************
 * @brief       spi port switch
 * @param       [in/out]  *config         device config block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void _SPI_Port_Switch(uint8_t port, Hal_SPI_Handle *dev)
{
    switch (port)
    {
#ifdef SPI1
        case MCU_SPI_1:
            if (dev->Group == 0)
            {
                LL_GPIO_AF_DisableRemap_SPI1();
            }
            else
            {
                LL_GPIO_AF_EnableRemap_SPI1();
            }
            break;
#endif

#if defined(SPI3) && defined(AFIO_MAPR_SPI3_REMAP)      
        case MCU_SPI_3:
            if (dev->Group == 0)
            {
                LL_GPIO_AF_DisableRemap_SPI3();
            }
            else
            {
                LL_GPIO_AF_EnableRemap_SPI3();
            }
            break;
#endif
        default:
            break;
    }
}

/**
 *******************************************************************************
 * @brief       uart gpio init
 * @param       [in/out]  *config         set param
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void _SPI_GPIO_Init(uint8_t port, Hal_SPI_Handle *dev)
{
//    Hal_Device_GPIO txPort;
//    Hal_Device_GPIO rxPort;
//    Hal_Device_GPIO sckPort;
//    Hal_Device_GPIO cssPort;
//
//    //< config mcu spi mosi port
//    if(dev->TxConfig != MCU_SPI_DISABLE_TX)
//    {
//        txPort.Dir = GPIO_DIR_HS_OUTPUT;
//        txPort.Mode = GPIO_AF_PUSH_PULL_MODE;
//    }
//    
//    //< config mcu spi miso port
//    if(dev->RxConfig != MCU_SPI_DISABLE_RX)
//    {
//        rxPort.Dir = GPIO_DIR_INTPUT;
//        rxPort.Mode = GPIO_PULL_UP_DOWN_MODE;
//    }
//    
//    //< config mcu spi sck port
//    if(dev->SckConfig != MCU_SPI_DISABLE_SCK)
//    {
//        if(dev->Mode == MCU_SPI_MASTER_MODE)
//        {
//            sckPort.Dir = GPIO_DIR_HS_OUTPUT;
//            sckPort.Mode = GPIO_AF_PUSH_PULL_MODE;
//        }
//        else
//        {
//            sckPort.Dir = GPIO_DIR_INTPUT;
//            sckPort.Mode = GPIO_PULL_UP_DOWN_MODE;
//        }
//
//    }
//    
//    //< config mcu spi css port
//    if(dev->CssConfig != MCU_SPI_DISABLE_CSS)
//    {
//        if(dev->Mode == MCU_SPI_MASTER_MODE)
//        {        
//            cssPort.Dir = GPIO_DIR_HS_OUTPUT;
//            cssPort.Mode = GPIO_AF_PUSH_PULL_MODE;
//        }
//        else
//        {
//                    
//            cssPort.Dir = GPIO_DIR_INTPUT;
//            cssPort.Mode = GPIO_PULL_UP_DOWN_MODE;
//        }
//    }
//    
//    switch (port)
//    {
//        case MCU_SPI_1:
//            if (dev->Group == 0)
//            {
//                txPort.Port = MCU_PORT_A;
//                txPort.Pin  = MCU_PIN_7;
//                
//                rxPort.Port = MCU_PORT_A;  
//                rxPort.Pin  = MCU_PIN_6;
//                
//                //< config mcu spi sck port
//                if(dev->SckConfig != MCU_SPI_DISABLE_SCK)
//                {
//                    sckPort.Port = MCU_PORT_A;
//                    sckPort.Pin = MCU_PIN_5;
//                }
//                
//                //< config mcu spi css port
//                if(dev->CssConfig != MCU_SPI_DISABLE_CSS)
//                {      
//                    cssPort.Port = MCU_PORT_A;
//                    cssPort.Pin = MCU_PIN_4;
//                }
//            }
//            else
//            {
//                txPort.Port = MCU_PORT_B;
//                txPort.Pin  = MCU_PIN_5;
//                
//                rxPort.Port = MCU_PORT_B;  
//                rxPort.Pin  = MCU_PIN_4;
//                
//                //< config mcu spi sck port
//                if(dev->SckConfig != MCU_SPI_DISABLE_SCK)
//                {
//                    sckPort.Port = MCU_PORT_B;
//                    sckPort.Pin = MCU_PIN_3;
//                }
//                
//                //< config mcu spi css port
//                if(dev->CssConfig != MCU_SPI_DISABLE_CSS)
//                {      
//                    cssPort.Port = MCU_PORT_A;
//                    cssPort.Pin = MCU_PIN_15;
//                }
//            }
//            break;
//        case MCU_SPI_2:
//            txPort.Port = MCU_PORT_B;
//            txPort.Pin  = MCU_PIN_14;
//            
//            rxPort.Port = MCU_PORT_B;  
//            rxPort.Pin  = MCU_PIN_15;
//            
//            //< config mcu spi sck port
//            if(dev->SckConfig != MCU_SPI_DISABLE_SCK)
//            {
//                sckPort.Port = MCU_PORT_B;
//                sckPort.Pin = MCU_PIN_13;
//            }
//            
//            //< config mcu spi css port
//            if(dev->CssConfig != MCU_SPI_DISABLE_CSS)
//            {      
//                cssPort.Port = MCU_PORT_B;
//                cssPort.Pin = MCU_PIN_12;
//            }
//            break;
//        case MCU_SPI_3:
//            if (dev->Group == 0)
//            {
//                txPort.Port = MCU_PORT_B;
//                txPort.Pin  = MCU_PIN_5;
//                
//                rxPort.Port = MCU_PORT_B;  
//                rxPort.Pin  = MCU_PIN_4;
//                
//                //< config mcu spi sck port
//                if(dev->SckConfig != MCU_SPI_DISABLE_SCK)
//                {
//                    sckPort.Port = MCU_PORT_B;
//                    sckPort.Pin = MCU_PIN_3;
//                }
//                
//                //< config mcu spi css port
//                if(dev->CssConfig != MCU_SPI_DISABLE_CSS)
//                {      
//                    cssPort.Port = MCU_PORT_A;
//                    cssPort.Pin = MCU_PIN_15;
//                }
//            }
//            else
//            {
//                txPort.Port = MCU_PORT_C;
//                txPort.Pin  = MCU_PIN_12;
//                
//                rxPort.Port = MCU_PORT_C;  
//                rxPort.Pin  = MCU_PIN_11;
//                
//                //< config mcu spi sck port
//                if(dev->SckConfig != MCU_SPI_DISABLE_SCK)
//                {
//                    sckPort.Port = MCU_PORT_C;
//                    sckPort.Pin = MCU_PIN_10;
//                }
//                
//                //< config mcu spi css port
//                if(dev->CssConfig != MCU_SPI_DISABLE_CSS)
//                {      
//                    cssPort.Port = MCU_PORT_A;
//                    cssPort.Pin = MCU_PIN_4;
//                }
//            }
//            break;
//        default:
//            break;
//    }
//    
//    if(dev->TxConfig != MCU_SPI_DISABLE_TX)
//    {
//        map_gpio_api.Open(txPort.Port);
//        map_gpio_api.Init(txPort.Port, txPort.Pin, txPort.Dir, txPort.Mode);
//    }
//    
//    if(dev->RxConfig != MCU_SPI_DISABLE_RX)
//    {
//        map_gpio_api.Open(rxPort.Port);
//        map_gpio_api.Init(rxPort.Port, rxPort.Pin, rxPort.Dir, rxPort.Mode);
//    }
//        //< config mcu spi sck port
//    if(dev->SckConfig != MCU_SPI_DISABLE_SCK)
//    {
//        map_gpio_api.Open(sckPort.Port);
//        map_gpio_api.Init(sckPort.Port, sckPort.Pin, sckPort.Dir, sckPort.Mode);
//    }
//    
//    //< config mcu spi css port
//    if(dev->CssConfig != MCU_SPI_DISABLE_CSS)
//    {
//        map_gpio_api.Open(cssPort.Port);
//        map_gpio_api.Init(cssPort.Port, cssPort.Pin, cssPort.Dir, cssPort.Mode);
//    }
    
    Hal_Device_GPIO txPort;
    Hal_Device_GPIO rxPort;
    Hal_Device_GPIO sckPort;

    txPort.Dir = GPIO_DIR_HS_OUTPUT;
    txPort.Mode = GPIO_AF_PUSH_PULL_MODE;    
    rxPort.Dir = GPIO_DIR_INTPUT;
    rxPort.Mode = GPIO_PULL_UP_DOWN_MODE;
    sckPort.Dir = GPIO_DIR_HS_OUTPUT;
    sckPort.Mode = GPIO_AF_PUSH_PULL_MODE;

    switch (port)
    {
        case MCU_SPI_1:
            txPort.Port = MCU_PORT_A;
            txPort.Pin  = MCU_PIN_7;
            
            rxPort.Port = MCU_PORT_A;  
            rxPort.Pin  = MCU_PIN_6;
            
            sckPort.Port = MCU_PORT_A;
            sckPort.Pin = MCU_PIN_5;
            break;
        case MCU_SPI_2:
            txPort.Port = MCU_PORT_B;
            txPort.Pin  = MCU_PIN_14;
            
            rxPort.Port = MCU_PORT_B;  
            rxPort.Pin  = MCU_PIN_15; 

            sckPort.Port = MCU_PORT_B;
            sckPort.Pin = MCU_PIN_13;
            break;
        case MCU_SPI_3:
            txPort.Port = MCU_PORT_B;
            txPort.Pin  = MCU_PIN_5;

            rxPort.Port = MCU_PORT_B;  
            rxPort.Pin  = MCU_PIN_4;

            sckPort.Port = MCU_PORT_B;
            sckPort.Pin = MCU_PIN_3;
            break;
        default:
            break;
    }
    
    map_gpio_api.Open(txPort.Port);
    map_gpio_api.Init(txPort.Port, txPort.Pin, txPort.Dir, txPort.Mode);
    
    map_gpio_api.Open(rxPort.Port);
    map_gpio_api.Init(rxPort.Port, rxPort.Pin, rxPort.Dir, rxPort.Mode);
    
    map_gpio_api.Open(sckPort.Port);
    map_gpio_api.Init(sckPort.Port, sckPort.Pin, sckPort.Dir, sckPort.Mode);
    
    _SPI_Port_Switch(port, dev);
}

/**
 *******************************************************************************
 * @brief       init uart
 * @param       [in/out]  port            uart id
 * @param       [in/out]  *config         set param
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_SPI_Init(uint8_t port, void *param)
{
    hal_assert(IS_SPI_PORT_INVAILD(port));
    hal_assert(IS_PTR_NULL(param));
    
    LL_SPI_InitTypeDef LL_SPI_InitStructure;
    Hal_SPI_Handle *dev = (Hal_SPI_Handle *)param;
    
    //< init spi gpio
    _SPI_GPIO_Init(port, dev);
    
    LL_SPI_InitStructure.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV256;
    
    if(dev->BitOrder == MCU_SPI_BIT_ORDER_MSB)
    {
        LL_SPI_InitStructure.BitOrder = LL_SPI_MSB_FIRST;
    }
    else
    {
        LL_SPI_InitStructure.BitOrder = LL_SPI_LSB_FIRST;
    }
    
    LL_SPI_InitStructure.ClockPhase = LL_SPI_PHASE_1EDGE;
    
    if(dev->ClockOptions == 0)
    {   
        LL_SPI_InitStructure.ClockPolarity = LL_SPI_POLARITY_LOW;
    }
    else
    {
        LL_SPI_InitStructure.ClockPolarity = LL_SPI_POLARITY_HIGH;
    }
    
    LL_SPI_InitStructure.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
    LL_SPI_InitStructure.CRCPoly = 0x00;
    
    LL_SPI_InitStructure.DataWidth = LL_SPI_DATAWIDTH_8BIT;        
    LL_SPI_InitStructure.Mode = LL_SPI_MODE_MASTER;
    LL_SPI_InitStructure.NSS = LL_SPI_NSS_SOFT;
    LL_SPI_InitStructure.TransferDirection = LL_SPI_FULL_DUPLEX;
        
    //< config uart call back
    SPI_Tx_Callback[port].Tx    = dev->TxCallback.Tx;
    SPI_Tx_Callback[port].Param = dev->TxCallback.Param;
    SPI_Rx_Callback[port].Rx    = dev->RxCallback.Rx;
    SPI_Rx_Callback[port].Param = dev->RxCallback.Param;
    
    //< init uart
    LL_SPI_DeInit(SPI[port]);
    LL_SPI_Init(SPI[port], &LL_SPI_InitStructure);
    
    //< clear spi it
    _CLR_BIT(SPI[port]->SR, SPI_SR_TXE_Pos);
    LL_SPI_EnableIT_TXE(SPI[port]);

    _CLR_BIT(SPI[port]->SR, SPI_SR_RXNE_Pos);
    LL_SPI_EnableIT_RXNE(SPI[port]);
	
    NVIC_EnableIRQ(SPIIrqn[port]); 
    NVIC_SetPriority(SPIIrqn[port], dev->Priority);  
    
    LL_SPI_Enable(SPI[port]);
}

/**
 *******************************************************************************
 * @brief       set uart tx call back
 * @param       [in/out]  port            uart id
 * @param       [in/out]  *callback       call back function
 * @param       [in/out]  *param          call back param
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_SPI_SetTxCallback(uint8_t port, void (*callback)(void*), void *param)
{
    hal_assert(IS_SPI_PORT_INVAILD(port));
    
    SPI_Tx_Callback[port].Tx = callback;
    SPI_Tx_Callback[port].Param = param;
}

/**
 *******************************************************************************
 * @brief       set uart rx call back
 * @param       [in/out]  port            uart id
 * @param       [in/out]  *callback       call back function
 * @param       [in/out]  *param          call back param
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_SPI_SetRxCallback(uint8_t port, void (*callback)(void*, uint8_t), void *param)
{
    hal_assert(IS_SPI_PORT_INVAILD(port));
    
    SPI_Rx_Callback[port].Rx = callback;
    SPI_Rx_Callback[port].Param = param;
}

/**
 *******************************************************************************
 * @brief       deinit uart
 * @param       [in/out]  port            uart id
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_SPI_Fini(uint8_t port)
{
    hal_assert(IS_SPI_PORT_INVAILD(port));
    
    LL_SPI_DeInit(SPI[port]);
}

/**
 *******************************************************************************
 * @brief       send data
 * @param       [in/out]  port            uart id
 * @param       [in/out]  sendData        send data
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_SPI_SendData(uint8_t port, uint8_t sendData)
{
    hal_assert(IS_SPI_PORT_INVAILD(port));
    
    if (SPI_Comm_Flag[port].TxEnable == 1)
    {
        SPI[port]->DR = sendData;
    }
}

/**
 *******************************************************************************
 * @brief       receive data
 * @param       [in/out]  port            uart id
 * @param       [in/out]  *sendData       receive data            
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
uint8_t Map_SPI_ReceiveData(uint8_t port)
{
    hal_assert(IS_SPI_PORT_INVAILD(port));

    if (SPI_Comm_Flag[port].RxEnable == 1)
    {
        return (uint8_t)SPI[port]->DR;
    }
    
    return 0xFF;
}

/**
 *******************************************************************************
 * @brief       enable uart tx
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_SPI_TxConnect(uint8_t port)
{
    hal_assert(IS_SPI_PORT_INVAILD(port));

    if (SPI_Comm_Flag[port].TxEnable == 0)
    {
        SPI[port]->SR  &= ~SPI_SR_TXE_Msk;
        SPI[port]->CR1 |= SPI_SR_TXE_Msk;
        
        SPI_Comm_Flag[port].TxEnable = 1;
    }
}

/**
 *******************************************************************************
 * @brief       disable uart tx
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_SPI_TxDisconnect(uint8_t port)
{
	hal_assert(IS_SPI_PORT_INVAILD(port));

    if(SPI_Comm_Flag[port].TxEnable == 1)
    {
        SPI[port]->CR1 &= ~SPI_SR_TXE_Msk;
        SPI[port]->SR  &= ~SPI_SR_TXE_Msk;
        
        SPI_Comm_Flag[port].TxEnable = 0;
    }
}

/**
 *******************************************************************************
 * @brief       enable uart rx
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_SPI_RxConnect(uint8_t port)
{
	hal_assert(IS_SPI_PORT_INVAILD(port));

    if(SPI_Comm_Flag[port].TxEnable == 0)
    {
        SPI[port]->SR  &= ~SPI_SR_RXNE_Msk;
        SPI[port]->CR1 |= SPI_SR_RXNE_Msk;
        
        SPI_Comm_Flag[port].RxEnable = 1;
    }
}

/**
 *******************************************************************************
 * @brief       disable uart rx
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_SPI_RxDisconnect(uint8_t port)
{
	hal_assert(IS_SPI_PORT_INVAILD(port));

    if(SPI_Comm_Flag[port].RxEnable == 1)
    {
        SPI[port]->SR  &= ~SPI_SR_RXNE_Msk;
        SPI[port]->CR1 &= ~SPI_SR_RXNE_Msk;
        
        SPI_Comm_Flag[port].RxEnable = 0;
    }
}

/**
 *******************************************************************************
 * @brief       get tx status
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
bool Map_SPI_IsTxComplet(uint8_t port)
{
	hal_assert(IS_SPI_PORT_INVAILD(port));
    
	return (SPI[port]->SR & SPI_SR_TXE_Msk) ? (SPI[port]->SR &= ~SPI_SR_TXE_Msk, true) \
                                            : (false);
}

/**
 *******************************************************************************
 * @brief       clear tx flag
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
bool Map_SPI_IsRxComplet(uint8_t port)
{
	hal_assert(IS_SPI_PORT_INVAILD(port));

	return (SPI[port]->SR & SPI_SR_RXNE_Msk) ? (SPI[port]->SR &= ~SPI_SR_RXNE_Msk, true) \
                                             : (false);
}

/**
 *******************************************************************************
 * @brief       spi1 isr handle
 * @param       [in/out]  void           
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
#ifdef SPI1
void SPI1_IRQHandler(void)
{
    if (Map_SPI_IsTxComplet(MCU_SPI_1) == true)
    {
        if(!IS_PTR_NULL(SPI_Tx_Callback[MCU_SPI_1].Tx))
        {
            SPI_Tx_Callback[MCU_SPI_1].Tx(SPI_Tx_Callback[MCU_SPI_1].Param);
        }
    }
    
    if (Map_SPI_IsRxComplet(MCU_SPI_1) == true)
    {
        if(!IS_PTR_NULL(SPI_Rx_Callback[MCU_SPI_1].Rx))
        {
            SPI_Rx_Callback[MCU_SPI_1].Rx(SPI_Rx_Callback[MCU_SPI_1].Param, SPI[MCU_SPI_1]->DR);
        }
    }
}
#endif

/**
 *******************************************************************************
 * @brief       spi2 isr handle
 * @param       [in/out]  void           
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
#ifdef SPI2
void SPI2_IRQHandler(void)
{
    if (Map_SPI_IsTxComplet(MCU_SPI_2) == true)
    {
        if(!IS_PTR_NULL(SPI_Tx_Callback[MCU_SPI_2].Tx))
        {
            SPI_Tx_Callback[MCU_SPI_2].Tx(SPI_Tx_Callback[MCU_SPI_2].Param);
        }
    }
    
    if (Map_SPI_IsRxComplet(MCU_SPI_2) == true)
    {
        if(!IS_PTR_NULL(SPI_Rx_Callback[MCU_SPI_2].Rx))
        {
            SPI_Rx_Callback[MCU_SPI_2].Rx(SPI_Rx_Callback[MCU_SPI_2].Param, SPI[MCU_SPI_2]->DR);
        }
    }
}
#endif

/**
 *******************************************************************************
 * @brief       spi3 isr handle
 * @param       [in/out]  void           
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
#ifdef SPI3
void SPI3_IRQHandler(void)
{
    if (Map_SPI_IsTxComplet(MCU_SPI_3) == true)
    {
        if(!IS_PTR_NULL(SPI_Tx_Callback[MCU_SPI_3].Tx))
        {
            SPI_Tx_Callback[MCU_SPI_3].Tx(SPI_Tx_Callback[MCU_SPI_3].Param);
        }
    }
    
    if (Map_SPI_IsRxComplet(MCU_SPI_3) == true)
    {
        if(!IS_PTR_NULL(SPI_Rx_Callback[MCU_SPI_3].Rx))
        {
            SPI_Rx_Callback[MCU_SPI_3].Rx(SPI_Rx_Callback[MCU_SPI_3].Param, SPI[MCU_SPI_3]->DR);
        }
    }
}
#endif

/** @}*/     /** map spi component */

/**********************************END OF FILE*********************************/
