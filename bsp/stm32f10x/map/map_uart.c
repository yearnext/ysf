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
#include "stm32f10x.h"
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
    USART1, USART2, USART3, UART4, UART5,
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
static struct HalCallback UartTxCallback[_dimof(Uart)];

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
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_Uart_Open(uint8_t port)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    
    if (port == MCU_UART_1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    }
    else if (port == MCU_UART_2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    }
    else if (port == MCU_UART_3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    }    
    else if (port == MCU_UART_4)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    }    
    else
    { 
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
    }
    
	return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       enable uart
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
__INLINE hal_err_t Hal_Uart_Open(struct HalUartDevice *dev)
{
    hal_assert(IS_PTR_NULL(dev));
    
	return Map_Uart_Open(dev->Port);
}

/**
 *******************************************************************************
 * @brief       disable uart
 * @param       [in/out]  port            uart id
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_Uart_Close(uint8_t port)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    
    if (port == MCU_UART_1)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
    }
    else if (port == MCU_UART_2)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE);
    }
    else if (port == MCU_UART_3)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE);
    }    
    else if (port == MCU_UART_4)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, DISABLE);
    }    
    else
    { 
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, DISABLE);
    }
      
	return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       disable uart
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
__INLINE hal_err_t Hal_Uart_Close(struct HalUartDevice *dev)
{
    hal_assert(IS_PTR_NULL(dev));
    
	return Map_Uart_Close(dev->Port);
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
void _Uart_Port_Switch(struct HalUartDevice *dev)
{
    switch (dev->Port)
    {
        case MCU_UART_1:
            if (dev->Group == 0)
            {
                GPIO_PinRemapConfig(GPIO_Remap_USART1, DISABLE);
            }
            else
            {
                GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
            }
            break;
        case MCU_UART_2:
            if (dev->Group == 0)
            {
                GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
            }
            else
            {
                GPIO_PinRemapConfig(GPIO_Remap_USART2, DISABLE);
            }
            break;
        case MCU_UART_3:
            if (dev->Group == 0)
            {
                GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, DISABLE);
                GPIO_PinRemapConfig(GPIO_FullRemap_USART3, DISABLE);
            }
            else if (dev->Group == 1)
            {
                GPIO_PinRemapConfig(GPIO_FullRemap_USART3, DISABLE);
                GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
            }
            else
            {
                GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, DISABLE);
                GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);
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
void _Uart_GPIO_Init(struct HalUartDevice *dev)
{
    struct HalGPIODevice TxPort;
    struct HalGPIODevice RxPort;
    
    TxPort.IO = GPIO_HS_OUTPUT;
    TxPort.Mode = GPIO_AF_PUSH_PULL_MODE;

    RxPort.IO = GPIO_HS_OUTPUT;
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
    
    Hal_GPIO_Open(&TxPort);
    Hal_GPIO_Init(&TxPort);
    
    Hal_GPIO_Open(&RxPort);
    Hal_GPIO_Init(&RxPort);
    
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
hal_err_t Map_Uart_Init(uint8_t port, struct HalUartDevice *dev)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    hal_assert(IS_PTR_NULL(config));
    
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    //< init uart gpio
    _Uart_GPIO_Init(dev);
    
    //< init uart baud rate
	USART_InitStructure.USART_BaudRate = dev->Baud;
    
    //< init uart word len
    if(dev->WordLen == MCU_UART_WORD_LEN_8B)
    {
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    }
    else
    {
        USART_InitStructure.USART_WordLength = USART_WordLength_9b;
    }
    
    //< set uart stop bits
    if(dev->StopBits == MCU_UART_STOP_BITS_0_5)
    {
        USART_InitStructure.USART_StopBits = USART_StopBits_0_5;
    }
    else if(dev->StopBits == MCU_UART_STOP_BITS_1)
    {
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
    }
    else if(dev->StopBits == MCU_UART_STOP_BITS_1_5)
    {
        USART_InitStructure.USART_StopBits = USART_StopBits_1_5;
    }
    else
    {
        USART_InitStructure.USART_StopBits = USART_StopBits_2;
    }
    
    //< set uart parity
	if(dev->Parity == MCU_UART_PARTY_NONE)
    {
        USART_InitStructure.USART_Parity = USART_Parity_No;
    }
    else if(dev->Parity == MCU_UART_PARTY_EVEN)
    {
        USART_InitStructure.USART_Parity = USART_Parity_Even;
    }
    else
    {
        USART_InitStructure.USART_Parity = USART_Parity_Odd;
    }
    
    //< set uart tx state
    if(dev->IsEnableTx == true)
    {
        USART_InitStructure.USART_Mode    = USART_Mode_Tx;
    }
    
    //< set uart rx state
    if(dev->IsEnableRx == true)
    {
        USART_InitStructure.USART_Mode   |= USART_Mode_Rx;
    }

    //< disable hardware flow control
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    //< config uart call back
    UartTxCallback[port].Callback = dev->TxCallback.Callback;
    UartTxCallback[port].Param    = dev->TxCallback.Param;
    UartRxCallback[port].Callback = dev->RxCallback.Callback;
    UartRxCallback[port].Param    = dev->RxCallback.Param;
    
    //< init uart
    USART_DeInit(Uart[port]);
    USART_Init(Uart[port], &USART_InitStructure);
    
    USART_ClearITPendingBit(Uart[port], USART_IT_TC);
    USART_ITConfig(Uart[port], USART_IT_TC, ENABLE);
    
    USART_ClearITPendingBit(Uart[port], USART_IT_RXNE);
    USART_ITConfig(Uart[port], USART_IT_RXNE, ENABLE);
    	
    NVIC_InitStructure.NVIC_IRQChannel = UartIrqn[port];
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    USART_Cmd(Uart[port], ENABLE);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       init uart
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
__INLINE hal_err_t Hal_Uart_Init(struct HalUartDevice *dev)
{
    hal_assert(IS_PTR_NULL(dev));
        
    return Map_Uart_Init(dev->Port, dev);
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
hal_err_t Map_Uart_SetTxCallback(uint8_t port, void (*callback)(void*), void *param)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    
    UartTxCallback[port].Callback = callback;
    UartTxCallback[port].Param = param;
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       set uart tx call back
 * @param       [in/out]  *dev            device block
 * @param       [in/out]  *callback       call back function
 * @param       [in/out]  *param          call back param
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Uart_SetTxCallback(struct HalUartDevice *dev, void (*callback)(void*), void *param)
{
    hal_assert(IS_PTR_NULL(dev));
    
    UartTxCallback[dev->Port].Callback = callback;
    UartTxCallback[dev->Port].Param = param;
    
    return HAL_ERR_NONE;
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
hal_err_t Map_Uart_SetRxCallback(uint8_t port, void (*callback)(void*, uint8_t), void *param)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    
    UartRxCallback[port].Callback = callback;
    UartRxCallback[port].Param = param;
    
    return HAL_ERR_NONE;
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
hal_err_t Hal_Uart_SetRxCallback(struct HalUartDevice *dev, void (*callback)(void*, uint8_t), void *param)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    
    UartRxCallback[dev->Port].Callback = callback;
    UartRxCallback[dev->Port].Param = param;
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       deinit uart
 * @param       [in/out]  port            uart id
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_Uart_Fini(uint8_t port)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    
    USART_DeInit(Uart[port]);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       deinit uart
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
__INLINE hal_err_t Hal_Uart_Fini(struct HalUartDevice *dev)
{
    hal_assert(IS_PTR_NULL(dev));
    
    return Map_Uart_Fini(dev->Port);
}

/**
 *******************************************************************************
 * @brief       enable uart tx
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Uart_TxConnect(struct HalUartDevice *dev)
{
	hal_assert(IS_PTR_NULL(dev));

	Uart[dev->Port]->CR1 |= 0x08;
	Uart[dev->Port]->SR  &= ~0x40;
	Uart[dev->Port]->CR1 |= 0x40;

    dev->IsEnableTx       = true;
    
	return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       disable uart tx
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Uart_TxDisconnect(struct HalUartDevice *dev)
{
	hal_assert(IS_PTR_NULL(dev));

	Uart[dev->Port]->CR1 &= ~0x08;
	Uart[dev->Port]->CR1 &= ~0x40;
	Uart[dev->Port]->SR  &= ~0x40;
    
    dev->IsEnableTx       = false;

	return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       enable uart rx
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Uart_RxConnect(struct HalUartDevice *dev)
{
	hal_assert(IS_PTR_NULL(dev));

	Uart[dev->Port]->CR1 |= 0x04;
	Uart[dev->Port]->SR  &= ~0x20;
	Uart[dev->Port]->CR1 |= 0x20;
    
    dev->IsEnableRx       = true;

	return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       disable uart rx
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Uart_RxDisconnect(struct HalUartDevice *dev)
{
	hal_assert(IS_PTR_NULL(dev));

	Uart[dev->Port]->CR1 &= ~0x04;
	Uart[dev->Port]->CR1 &= ~0x20;
	Uart[dev->Port]->SR  &= ~0x20;
    
    dev->IsEnableRx       = false;

	return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get tx status
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Uart_GetTxCompletFlag(struct HalUartDevice *dev, uint8_t *flag)
{
	hal_assert(IS_PTR_NULL(dev));
	hal_assert(IS_PTR_NULL(flag));

	*flag = (Uart[dev->Port]->SR & 0x40) ? (1) : (0);

	return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       clear tx flag
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Uart_ClrTxCompletFlag(struct HalUartDevice *dev)
{
	hal_assert(IS_PTR_NULL(dev));

	Uart[dev->Port]->SR &= ~0x40;

	return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       get rx status
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Uart_GetRxCompletFlag(struct HalUartDevice *dev, uint8_t *flag)
{
	hal_assert(IS_PTR_NULL(dev));
	hal_assert(IS_PTR_NULL(flag));

	*flag = (Uart[dev->Port]->SR & 0x20) ? (1) : (0);

	return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       clear uart rx status
 * @param       [in/out]  *dev            device block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Uart_ClrRxCompletFlag(struct HalUartDevice *dev)
{
	hal_assert(IS_PTR_NULL(dev));

	Uart[dev->Port]->SR &= ~0x20;

	return HAL_ERR_NONE;
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
hal_err_t Map_Uart_SendData(uint8_t port, uint8_t sendData)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    
    Uart[port]->DR = sendData;
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       send data
 * @param       [in/out]  *dev            device block
 * @param       [in/out]  sendData        send data
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Uart_SendData(struct HalUartDevice *dev, uint8_t sendData)
{
    hal_assert(IS_PTR_NULL(dev));
    
    Uart[dev->Port]->DR = sendData;
    
    return HAL_ERR_NONE;
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
hal_err_t Map_Uart_ReceiveData(uint8_t port, uint8_t *sendData)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    hal_assert(IS_PTR_NULL(sendData));
    
    *sendData = Uart[port]->DR;
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       receive data
 * @param       [in/out]  *dev            device block
 * @param       [in/out]  *sendData       receive data            
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Uart_ReceiveData(struct HalUartDevice *dev, uint8_t *sendData)
{
    hal_assert(IS_PTR_NULL(dev));
    hal_assert(IS_PTR_NULL(sendData));
    
    *sendData = Uart[dev->Port]->DR;
    
    return HAL_ERR_NONE;
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

void Hal_Uart_Test_Init(void)
{
    struct HalUartDevice uart = 
    {
        .Port = MCU_UART_2,
        .Baud = 115200,
        .Parity = MCU_UART_PARTY_NONE,
        .StopBits = MCU_UART_STOP_BITS_1,
        .WordLen = MCU_UART_WORD_LEN_8B,

        .IsEnableRx = true,
        .IsEnableTx = true,
    };
    
    uint16_t i;

    Hal_Uart_Open(&uart);
    Hal_Uart_Init(&uart);
    
    Hal_Uart_SendData(&uart, 0xFF);
    
    while(1)
    {
        for(i=0; i<100; i++);
    }
}

#endif

/** @}*/     /** map uart component */

/**********************************END OF FILE*********************************/
