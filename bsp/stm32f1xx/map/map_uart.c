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
 * @file       map_uart.c                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-08                                                      *
 * @brief      mcu uart application component source files                     *
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
 * @defgroup map uart component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"

#include "comm_path.h"
#include "map_uart.h"
#include "map_gpio.h"

/* Private constants ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define uart register
 *******************************************************************************
 */ 
static USART_TypeDef * const Uart[] = 
{
#ifdef USART1
    USART1, 
#endif
    
#ifdef USART2
    USART2, 
#endif
    
#ifdef USART3
    USART3, 
#endif
    
#ifdef UART4
    UART4, 
#endif
    
#ifdef UART5
    UART5,
#endif
};

/**
 *******************************************************************************
 * @brief      define uart irqn
 *******************************************************************************
 */ 
static const IRQn_Type UartIrqn[] = 
{
#ifdef USART1
    USART1_IRQn, 
#endif
    
#ifdef USART2
    USART2_IRQn, 
#endif
    
#ifdef USART3
    USART3_IRQn, 
#endif
    
#ifdef UART4
    UART4_IRQn,
#endif
    
#ifdef UART5
    UART5_IRQn,
#endif
};

/**
 *******************************************************************************
 * @brief      define map api
 *******************************************************************************
 */ 
void Map_Uart_Open(uint8_t);
void Map_Uart_Close(uint8_t);
void Map_Uart_Init(uint8_t, void*);
void Map_Uart_Fini(uint8_t);
void Map_Uart_SetTxCallback(uint8_t, void (*)(void*), void*);
void Map_Uart_SetRxCallback(uint8_t, void (*)(void*, uint8_t), void*);
void Map_Uart_SendData(uint8_t, uint8_t);
uint8_t Map_Uart_ReceiveData(uint8_t);
void Map_Uart_TxConnect(uint8_t);
void Map_Uart_TxDisconnect(uint8_t);
void Map_Uart_RxConnect(uint8_t);
void Map_Uart_RxDisconnect(uint8_t);
bool Map_Uart_IsTxComplet(uint8_t);
bool Map_Uart_IsRxComplet(uint8_t);

const struct Map_Uart_Opera map_uart_api = 
{
    .Open = Map_Uart_Open,
    .Close = Map_Uart_Close,
    
    .Init = Map_Uart_Init,
    .Fini = Map_Uart_Fini,
    
    .SetTxCallback = Map_Uart_SetTxCallback,
    .SetRxCallback = Map_Uart_SetRxCallback,

    .Send = Map_Uart_SendData,
    .Receive = Map_Uart_ReceiveData,
    
    .TxConnect = Map_Uart_TxConnect,
    .TxDisconnect = Map_Uart_TxDisconnect,
    
    .RxConnect = Map_Uart_RxConnect,
    .RxDisconnect = Map_Uart_RxDisconnect,
    
    .IsTxComplet = Map_Uart_IsTxComplet,
    .IsRxComplet = Map_Uart_IsRxComplet,
};

/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define uart tx isr call back
 *******************************************************************************
 */
static struct Hal_Callback UartTxCallback[_dimof(Uart)];

/**
 *******************************************************************************
 * @brief       define uart rx isr call back
 *******************************************************************************
 */
static struct 
{
    void (*Callback)(void*, uint8_t);
    void *Param;
}UartRxCallback[_dimof(Uart)];

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define uart assert macro
 *******************************************************************************
 */
#define IS_UART_PORT_INVAILD(n)                            ((n) >= _dimof(Uart))

/* Private typedef -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       enable uart
 * @param       [in/out]  port            uart id
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Map_Uart_Open(uint8_t port)
{
    hal_assert(IS_UART_PORT_INVAILD(port));

    if (port == MCU_UART_1)
    {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
    }
    else if (port == MCU_UART_2)
    {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
    }
    else if (port == MCU_UART_3)
    {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
    }    
    else if (port == MCU_UART_4)
    {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);
    }    
    else
    { 
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);
    }
}

/**
 *******************************************************************************
 * @brief       disable uart
 * @param       [in/out]  port            uart id
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Map_Uart_Close(uint8_t port)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    
    LL_USART_DeInit(Uart[port]);
}

/**
 *******************************************************************************
 * @brief       uart port switch
 * @param       [in/out]  *config         device config block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void _Uart_Port_Switch(uint8_t port, Hal_Uart_Handle *dev)
{
    switch (port)
    {
        case MCU_UART_1:
            if (dev->Group == 0)
            {
                LL_GPIO_AF_DisableRemap_USART1();
            }
            else
            {
                LL_GPIO_AF_EnableRemap_USART1();
            }
            break;
        case MCU_UART_2:
            if (dev->Group == 0)
            {
                LL_GPIO_AF_DisableRemap_USART2();
            }
            else
            {
                LL_GPIO_AF_EnableRemap_USART2();
            }
            break;
        case MCU_UART_3:
            if (dev->Group == 0)
            {
                LL_GPIO_AF_DisableRemap_USART3();
            }
            else if (dev->Group == 1)
            {
                LL_GPIO_AF_RemapPartial_USART3();
            }
            else
            {
                LL_GPIO_AF_EnableRemap_USART3();
            }
            break;
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
void _Uart_GPIO_Init(uint8_t port, Hal_Uart_Handle *dev)
{
    Hal_GPIO_Handle txPort;
    Hal_GPIO_Handle rxPort;

    txPort.Dir = GPIO_DIR_HS_OUTPUT;
    txPort.Mode = GPIO_AF_PUSH_PULL_MODE;

    rxPort.Dir = GPIO_DIR_INTPUT;
    rxPort.Mode = GPIO_PULL_UP_DOWN_MODE;
    
    switch (port)
    {
        case MCU_UART_1:
            if (dev->Group == 0)
            {
                txPort.Port = MCU_PORT_A;
                txPort.Pin  = MCU_PIN_9;
                
                rxPort.Port = MCU_PORT_A;  
                rxPort.Pin  = MCU_PIN_10;
            }
            else
            {
                txPort.Port = MCU_PORT_B;
                txPort.Pin  = MCU_PIN_6;
                
                rxPort.Port = MCU_PORT_B;  
                rxPort.Pin  = MCU_PIN_7;
            }
            break;
        case MCU_UART_2:
            if (dev->Group == 0)
            {
                txPort.Port = MCU_PORT_A;
                txPort.Pin  = MCU_PIN_2;
                
                rxPort.Port = MCU_PORT_A;  
                rxPort.Pin  = MCU_PIN_3;
            }
            else
            {
                txPort.Port = MCU_PORT_D;
                txPort.Pin  = MCU_PIN_5;
                
                rxPort.Port = MCU_PORT_D;  
                rxPort.Pin  = MCU_PIN_6;
            }
            break;
        case MCU_UART_3:
            if (dev->Group == 0)
            {
                txPort.Port = MCU_PORT_B;
                txPort.Pin  = MCU_PIN_10;
                
                rxPort.Port = MCU_PORT_B;  
                rxPort.Pin  = MCU_PIN_11;
            }
            else if (dev->Group == 1)
            {
                txPort.Port = MCU_PORT_C;
                txPort.Pin  = MCU_PIN_10;
                
                rxPort.Port = MCU_PORT_C;  
                rxPort.Pin  = MCU_PIN_11;
            }
            else
            {
                txPort.Port = MCU_PORT_D;
                txPort.Pin  = MCU_PIN_8;
                
                rxPort.Port = MCU_PORT_D;  
                rxPort.Pin  = MCU_PIN_9;
            }
            break;
        default:
            break;
    }
    
    map_gpio_api.Open(txPort.Port);
    map_gpio_api.Init(txPort.Port, txPort.Pin, txPort.Dir, txPort.Mode);
    
    map_gpio_api.Open(rxPort.Port);
    map_gpio_api.Init(rxPort.Port, rxPort.Pin, rxPort.Dir, rxPort.Mode);
    
    _Uart_Port_Switch(port, dev);
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
void Map_Uart_Init(uint8_t port, void *param)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    hal_assert(IS_PTR_NULL(config));
    
    LL_USART_InitTypeDef LL_USART_InitStructure;
    Hal_Uart_Handle *dev = (Hal_Uart_Handle *)param;
    
    //< init uart gpio
    _Uart_GPIO_Init(port, dev);
    
    //< init uart baud rate
    LL_USART_InitStructure.BaudRate = dev->Baud;
    
    //< init uart word len
    if(dev->WordLen == MCU_UART_WORD_LEN_8B)
    {
        LL_USART_InitStructure.DataWidth = LL_USART_DATAWIDTH_8B;
    }
    else
    {
        LL_USART_InitStructure.DataWidth = LL_USART_DATAWIDTH_9B;
    }
    
    //< set uart stop bits
    if(dev->StopBits == MCU_UART_STOP_BITS_0_5)
    {
        LL_USART_InitStructure.StopBits = LL_USART_STOPBITS_0_5;
    }
    else if(dev->StopBits == MCU_UART_STOP_BITS_1)
    {
        LL_USART_InitStructure.StopBits = LL_USART_STOPBITS_1;
    }
    else if(dev->StopBits == MCU_UART_STOP_BITS_1_5)
    {
        LL_USART_InitStructure.StopBits = LL_USART_STOPBITS_1_5;
    }
    else
    {
        LL_USART_InitStructure.StopBits = LL_USART_STOPBITS_2;
    }
    
    //< set uart parity
	if(dev->Parity == MCU_UART_PARTY_NONE)
    {
        LL_USART_InitStructure.Parity = LL_USART_PARITY_NONE;
    }
    else if(dev->Parity == MCU_UART_PARTY_EVEN)
    {
        LL_USART_InitStructure.Parity = LL_USART_PARITY_EVEN;
    }
    else
    {
        LL_USART_InitStructure.Parity = LL_USART_PARITY_ODD;
    }
    
    //< init uart mode
    LL_USART_InitStructure.TransferDirection = LL_USART_DIRECTION_NONE;

    //< set uart tx state
    if(dev->TxConfig != MCU_UART_DISABLE_TX)
    {
        LL_USART_InitStructure.TransferDirection = LL_USART_DIRECTION_TX;
    }
    
    //< set uart rx state
    if(dev->RxConfig == MCU_UART_DISABLE_RX)
    {
        LL_USART_InitStructure.TransferDirection   |= LL_USART_DIRECTION_RX;
    }

    //< disable hardware flow control
    LL_USART_InitStructure.HardwareFlowControl = LL_USART_HWCONTROL_NONE;

    //< config uart call back
    UartTxCallback[port].Callback = dev->TxCallback.Callback;
    UartTxCallback[port].Param    = dev->TxCallback.Param;
    UartRxCallback[port].Callback = dev->RxCallback.Callback;
    UartRxCallback[port].Param    = dev->RxCallback.Param;
    
    //< init uart
    LL_USART_DeInit(Uart[port]);
    LL_USART_Init(Uart[port], &LL_USART_InitStructure);
    
    if(dev->TxConfig == MCU_UART_ENABLE_TX_ISR)
    {
        LL_USART_ClearFlag_TC(Uart[port]);
        LL_USART_EnableIT_TC(Uart[port]);
    }
    
    if(dev->RxConfig == MCU_UART_ENABLE_RX_ISR)
    {
        LL_USART_ClearFlag_RXNE(Uart[port]);
        LL_USART_EnableIT_RXNE(Uart[port]);
    }
	
    NVIC_EnableIRQ(UartIrqn[port]); 
    NVIC_SetPriority(UartIrqn[port], dev->Priority);  
    
    LL_USART_Enable(Uart[port]);
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
void Map_Uart_SetTxCallback(uint8_t port, void (*callback)(void*), void *param)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    
    UartTxCallback[port].Callback = callback;
    UartTxCallback[port].Param = param;
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
void Map_Uart_SetRxCallback(uint8_t port, void (*callback)(void*, uint8_t), void *param)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    
    UartRxCallback[port].Callback = callback;
    UartRxCallback[port].Param = param;
}

/**
 *******************************************************************************
 * @brief       deinit uart
 * @param       [in/out]  port            uart id
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_Uart_Fini(uint8_t port)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    
    LL_USART_DeInit(Uart[port]);
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
void Map_Uart_SendData(uint8_t port, uint8_t sendData)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    
    Uart[port]->DR = sendData;
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
uint8_t Map_Uart_ReceiveData(uint8_t port)
{
    hal_assert(IS_UART_PORT_INVAILD(port));

    return (uint8_t)Uart[port]->DR;
}

/**
 *******************************************************************************
 * @brief       enable uart tx
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_Uart_TxConnect(uint8_t port)
{
    hal_assert(IS_UART_PORT_INVAILD(port));

    //< enable uart tx
	Uart[port]->CR1 |= 0x08;
    
    //< clear uart tx isr flag
	Uart[port]->SR  &= ~0x40;
    
    //< enable uart tx isr
	Uart[port]->CR1 |= 0x40;
}

/**
 *******************************************************************************
 * @brief       disable uart tx
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_Uart_TxDisconnect(uint8_t port)
{
	hal_assert(IS_UART_PORT_INVAILD(port));

    //< disable uart isr
	Uart[port]->CR1 &= ~0x08;
    
    //< clear uart tx isr flag
	Uart[port]->CR1 &= ~0x40;
    
    //< disable uart tx isr
	Uart[port]->SR  &= ~0x40;
}

/**
 *******************************************************************************
 * @brief       enable uart rx
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_Uart_RxConnect(uint8_t port)
{
	hal_assert(IS_UART_PORT_INVAILD(port));

    //< enable uart rx
	Uart[port]->CR1 |= 0x04;
    
    //< clear uart rx isr flag
	Uart[port]->SR  &= ~0x20;
    
    //< enable uart rx isr flag
	Uart[port]->CR1 |= 0x20;
}

/**
 *******************************************************************************
 * @brief       disable uart rx
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_Uart_RxDisconnect(uint8_t port)
{
	hal_assert(IS_UART_PORT_INVAILD(port));

    //< disable uart rx
	Uart[port]->CR1 &= ~0x04;
    
    //< clear uart rx isr flag
	Uart[port]->CR1 &= ~0x20;
    
    //< disable uart rx isr
	Uart[port]->SR  &= ~0x20;
}

/**
 *******************************************************************************
 * @brief       get tx status
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
bool Map_Uart_IsTxComplet(uint8_t port)
{
	hal_assert(IS_UART_PORT_INVAILD(port));
    
	return (Uart[port]->SR & 0x40) ? (Uart[port]->SR &= ~0x40, true) \
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
bool Map_Uart_IsRxComplet(uint8_t port)
{
	hal_assert(IS_UART_PORT_INVAILD(port));

	return (Uart[port]->SR & 0x20) ? (Uart[port]->SR &= ~0x20, true) \
                                   : (false);
}

/**
 *******************************************************************************
 * @brief       uart1 isr handle
 * @param       [in/out]  void           
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
#ifdef USART1
void USART1_IRQHandler(void)
{
    if (Map_Uart_IsTxComplet(MCU_UART_1) == true)
    {
        if(!IS_PTR_NULL(UartTxCallback[MCU_UART_1].Callback))
        {
            UartTxCallback[MCU_UART_1].Callback(UartTxCallback[MCU_UART_1].Param);
        }
    }
    
    if (Map_Uart_IsRxComplet(MCU_UART_1) == true)
    {
        if(!IS_PTR_NULL(UartRxCallback[MCU_UART_1].Callback))
        {
            UartRxCallback[MCU_UART_1].Callback(UartRxCallback[MCU_UART_1].Param, Uart[MCU_UART_1]->DR);
        }
    }
}
#endif

/**
 *******************************************************************************
 * @brief       uart2 isr handle
 * @param       [in/out]  void           
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
#ifdef USART2
void USART2_IRQHandler(void)
{
    if (Map_Uart_IsTxComplet(MCU_UART_2) == true)
    {
        if(!IS_PTR_NULL(UartTxCallback[MCU_UART_2].Callback))
        {
            UartTxCallback[MCU_UART_2].Callback(UartTxCallback[MCU_UART_2].Param);
        }
    }
    
    if (Map_Uart_IsRxComplet(MCU_UART_2) == true)
    {
        if(!IS_PTR_NULL(UartRxCallback[MCU_UART_2].Callback))
        {
            UartRxCallback[MCU_UART_2].Callback(UartRxCallback[MCU_UART_2].Param, Uart[MCU_UART_2]->DR);
        }
    }
}
#endif

/**
 *******************************************************************************
 * @brief       uart3 isr handle
 * @param       [in/out]  void           
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
#ifdef USART3
void USART3_IRQHandler(void)
{
    if (Map_Uart_IsTxComplet(MCU_UART_3) == true)
    {
        if(!IS_PTR_NULL(UartTxCallback[MCU_UART_3].Callback))
        {
            UartTxCallback[MCU_UART_3].Callback(UartTxCallback[MCU_UART_3].Param);
        }
    }
    
    if (Map_Uart_IsRxComplet(MCU_UART_3) == true)
    {
        if(!IS_PTR_NULL(UartRxCallback[MCU_UART_3].Callback))
        {
            UartRxCallback[MCU_UART_3].Callback(UartRxCallback[MCU_UART_3].Param, Uart[MCU_UART_3]->DR);
        }
    }
}
#endif

/**
 *******************************************************************************
 * @brief       uart4 isr handle
 * @param       [in/out]  void           
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
#ifdef UART4
void UART4_IRQHandler(void)
{
    if (Map_Uart_IsTxComplet(MCU_UART_4) == true)
    {
        if(!IS_PTR_NULL(UartTxCallback[MCU_UART_4].Callback))
        {
            UartTxCallback[MCU_UART_4].Callback(UartTxCallback[MCU_UART_4].Param);
        }
    }
    
    if (Map_Uart_IsRxComplet(MCU_UART_4) == true)
    {
        if(!IS_PTR_NULL(UartRxCallback[MCU_UART_4].Callback))
        {
            UartRxCallback[MCU_UART_4].Callback(UartRxCallback[MCU_UART_4].Param, Uart[MCU_UART_4]->DR);
        }
    }  
}
#endif

/**
 *******************************************************************************
 * @brief       uart5 isr handle
 * @param       [in/out]  void           
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
#ifdef UART5
void UART5_IRQHandler(void)
{
    if (Map_Uart_IsTxComplet(MCU_UART_5) == true)
    {
        if(!IS_PTR_NULL(UartTxCallback[MCU_UART_5].Callback))
        {
            UartTxCallback[MCU_UART_5].Callback(UartTxCallback[MCU_UART_5].Param);
        }
    }
    
    if (Map_Uart_IsRxComplet(MCU_UART_5) == true)
    {
        if(!IS_PTR_NULL(UartRxCallback[MCU_UART_5].Callback))
        {
            UartRxCallback[MCU_UART_5].Callback(UartRxCallback[MCU_UART_5].Param, Uart[MCU_UART_5]->DR);
        }
    }
}
#endif

/**
 *******************************************************************************
 * @brief       hal uart unit test function
 * @param       [in/out]  void           
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Uart_Test(void)
{
//    struct Hal_Uart_Device uart = 
//    {
//        .Port = MCU_UART_2,
//        .Baud = 115200,
//        .Parity = MCU_UART_PARTY_NONE,
//        .StopBits = MCU_UART_STOP_BITS_1,
//        .WordLen = MCU_UART_WORD_LEN_8B,
//
//        .RxConfig = MCU_UART_ENABLE_RX,
//        .TxConfig = MCU_UART_ENABLE_TX,
//        
//        .Priority = 0x02,
//    };
//    
//    uint16_t i;

//    Hal_Uart_Open(&uart);
//    Hal_Uart_Init(&uart);

    while(1)
    {
//        for(i=0; i<100; i++);
//        Hal_Uart_SendData(&uart, 0xFF);
    }
}

/** @}*/     /** map uart component */

/**********************************END OF FILE*********************************/
