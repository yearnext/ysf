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
#if USE_UART_COMPONENT
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
    USART1_IRQn, USART2_IRQn, USART3_IRQn, UART4_IRQn, UART5_IRQn,
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
#endif

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define uart assert macro
 *******************************************************************************
 */
#define IS_UART_PORT_INVAILD(n) ((n) >= _dimof(Uart))

/* Private typedef -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_UART_COMPONENT
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
void _Uart_Port_Switch(struct Hal_Uart_Device *dev)
{
    switch (dev->Port)
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
void _Uart_GPIO_Init(struct Hal_Uart_Device *dev)
{
    Map_GPIO_InitType TxPort;
    Map_GPIO_InitType RxPort;
    
    TxPort.Dir = GPIO_DIR_HS_OUTPUT;
    TxPort.Mode = GPIO_AF_PUSH_PULL_MODE;

    RxPort.Dir = GPIO_DIR_INTPUT;
    RxPort.Mode = GPIO_PULL_UP_DOWN_MODE;
    
    switch (dev->Port)
    {
        case MCU_UART_1:
            if (dev->Group == 0)
            {
                TxPort.Port = MCU_PORT_A;
                TxPort.Pin  = MCU_PIN_9;
                
                RxPort.Port = MCU_PORT_A;  
                RxPort.Pin  = MCU_PIN_10;
            }
            else
            {
                TxPort.Port = MCU_PORT_B;
                TxPort.Pin  = MCU_PIN_6;
                
                RxPort.Port = MCU_PORT_B;  
                RxPort.Pin  = MCU_PIN_7;
            }
            break;
        case MCU_UART_2:
            if (dev->Group == 0)
            {
                TxPort.Port = MCU_PORT_A;
                TxPort.Pin  = MCU_PIN_2;
                
                RxPort.Port = MCU_PORT_A;  
                RxPort.Pin  = MCU_PIN_3;
            }
            else
            {
                TxPort.Port = MCU_PORT_D;
                TxPort.Pin  = MCU_PIN_5;
                
                RxPort.Port = MCU_PORT_D;  
                RxPort.Pin  = MCU_PIN_6;
            }
            break;
        case MCU_UART_3:
            if (dev->Group == 0)
            {
                TxPort.Port = MCU_PORT_B;
                TxPort.Pin  = MCU_PIN_10;
                
                RxPort.Port = MCU_PORT_B;  
                RxPort.Pin  = MCU_PIN_11;
            }
            else if (dev->Group == 1)
            {
                TxPort.Port = MCU_PORT_C;
                TxPort.Pin  = MCU_PIN_10;
                
                RxPort.Port = MCU_PORT_C;  
                RxPort.Pin  = MCU_PIN_11;
            }
            else
            {
                TxPort.Port = MCU_PORT_D;
                TxPort.Pin  = MCU_PIN_8;
                
                RxPort.Port = MCU_PORT_D;  
                RxPort.Pin  = MCU_PIN_9;
            }
            break;
        default:
            break;
    }
    
    Map_GPIO_Open(TxPort.Port);
    Map_GPIO_Init(TxPort.Port, TxPort.Pin, TxPort.Dir, TxPort.Mode);
    
    Map_GPIO_Open(RxPort.Port);
    Map_GPIO_Init(RxPort.Port, RxPort.Pin, RxPort.Dir, RxPort.Mode);
    
    _Uart_Port_Switch(dev);
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
    
    //< init uart gpio
    _Uart_GPIO_Init(dev);
    
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
    hal_assert(IS_PTR_NULL(sendData));
    
    return (uint8_t)Uart[port]->DR;
}


/**
 *******************************************************************************
 * @brief       uart1 isr handle
 * @param       [in/out]  void           
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void USART1_IRQHandler(void)
{
    if (Uart[MCU_UART_1]->SR & 0x20)
    {
        if(!IS_PTR_NULL(UartTxCallback[MCU_UART_1].Callback))
        {
            UartTxCallback[MCU_UART_1].Callback(UartTxCallback[MCU_UART_1].Param);
        }
        
        Uart[MCU_UART_1]->SR &= ~0x40;
    }
    
    if (Uart[MCU_UART_1]->SR & 0x20)
    {
        if(!IS_PTR_NULL(UartRxCallback[MCU_UART_1].Callback))
        {
            UartRxCallback[MCU_UART_1].Callback(UartRxCallback[MCU_UART_1].Param, Uart[MCU_UART_1]->DR);
        }
        
        Uart[MCU_UART_1]->SR &= ~0x20;
    }
}

/**
 *******************************************************************************
 * @brief       uart2 isr handle
 * @param       [in/out]  void           
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void USART2_IRQHandler(void)
{
    if (Uart[MCU_UART_2]->SR & 0x40)
    {
        if(!IS_PTR_NULL(UartTxCallback[MCU_UART_2].Callback))
        {
            UartTxCallback[MCU_UART_2].Callback(UartTxCallback[MCU_UART_2].Param);
        }
        
        Uart[MCU_UART_2]->SR &= ~0x20;
    }
    
    if (Uart[MCU_UART_2]->SR & 0x20)
    {
        if(!IS_PTR_NULL(UartRxCallback[MCU_UART_2].Callback))
        {
            UartRxCallback[MCU_UART_2].Callback(UartRxCallback[MCU_UART_2].Param, Uart[MCU_UART_2]->DR);
        }
        
        Uart[MCU_UART_2]->SR &= ~0x20;
    }
}

/**
 *******************************************************************************
 * @brief       uart3 isr handle
 * @param       [in/out]  void           
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void USART3_IRQHandler(void)
{
    if (Uart[MCU_UART_3]->SR & 0x40)
    {
        if(!IS_PTR_NULL(UartTxCallback[MCU_UART_3].Callback))
        {
            UartTxCallback[MCU_UART_3].Callback(UartTxCallback[MCU_UART_3].Param);
        }
        
        Uart[MCU_UART_3]->SR &= ~0x40;
    }
    
    if (Uart[MCU_UART_3]->SR & 0x20)
    {
        if(!IS_PTR_NULL(UartRxCallback[MCU_UART_3].Callback))
        {
            UartRxCallback[MCU_UART_3].Callback(UartRxCallback[MCU_UART_3].Param, Uart[MCU_UART_3]->DR);
        }
        
        Uart[MCU_UART_3]->SR &= ~0x20;
    }
}

///**
// *******************************************************************************
// * @brief       uart4 isr handle
// * @param       [in/out]  void           
// * @return      [in/out]  void
// * @note        None
// *******************************************************************************
// */
//void UART4_IRQHandler(void)
//{
//    if (USART_GetITStatus(Uart[MCU_UART_4], USART_IT_TC) == SET)
//    {
//        if(!IS_PTR_NULL(UartTxCallback[MCU_UART_4].Callback))
//        {
//            UartTxCallback[MCU_UART_4].Callback(UartTxCallback[MCU_UART_4].Param);
//        }
//    }
//    
//    if (USART_GetITStatus(Uart[MCU_UART_4], USART_IT_RXNE) == SET)
//    {
//        if(!IS_PTR_NULL(UartRxCallback[MCU_UART_4].Callback))
//        {
//            UartRxCallback[MCU_UART_4].Callback(UartRxCallback[MCU_UART_4].Param, Uart[MCU_UART_4]->DR);
//        }
//    }  
//}
//
///**
// *******************************************************************************
// * @brief       uart5 isr handle
// * @param       [in/out]  void           
// * @return      [in/out]  void
// * @note        None
// *******************************************************************************
// */
//void UART5_IRQHandler(void)
//{
//    if (USART_GetITStatus(Uart[MCU_UART_5], USART_IT_TC) == SET)
//    {
//        if(!IS_PTR_NULL(UartTxCallback[MCU_UART_5].Callback))
//        {
//            UartTxCallback[MCU_UART_5].Callback(UartTxCallback[MCU_UART_5].Param);
//        }
//    }
//    
//    if (USART_GetITStatus(Uart[MCU_UART_5], USART_IT_RXNE) == SET)
//    {
//        if(!IS_PTR_NULL(UartRxCallback[MCU_UART_5].Callback))
//        {
//            UartRxCallback[MCU_UART_5].Callback(UartRxCallback[MCU_UART_5].Param, Uart[MCU_UART_5]->DR);
//        }
//    }
//}

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
    struct Hal_Uart_Device uart = 
    {
        .Port = MCU_UART_2,
        .Baud = 115200,
        .Parity = MCU_UART_PARTY_NONE,
        .StopBits = MCU_UART_STOP_BITS_1,
        .WordLen = MCU_UART_WORD_LEN_8B,

        .RxConfig = MCU_UART_ENABLE_RX,
        .TxConfig = MCU_UART_ENABLE_TX,
        
        .Priority = 0x02,
    };
    
    uint16_t i;

//    Hal_Uart_Open(&uart);
//    Hal_Uart_Init(&uart);

    while(1)
    {
        for(i=0; i<100; i++);
//        Hal_Uart_SendData(&uart, 0xFF);
    }
}

#endif

/** @}*/     /** map uart component */

/**********************************END OF FILE*********************************/
