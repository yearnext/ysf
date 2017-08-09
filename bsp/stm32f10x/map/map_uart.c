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
#include "map_uart.h"
#include "comm_path.h"

/* Private constants ---------------------------------------------------------*/
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
    void (*Callback)(void*, uint16_t);
    void *Param;
}UartRxCallback[_dimof(Uart)];

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define uart assert macro
 *******************************************************************************
 */
#define IS_UART_PORT_INVAILD(n) ((n) >= _dimof(Uart))

/* Private typedef -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
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
 * @brief       init uart
 * @param       [in/out]  port            uart id
 * @param       [in/out]  *config         set param
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_Uart_Init(uint8_t port, struct HalUartConfig *config)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    hal_assert(IS_PTR_NULL(config));
    
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
	USART_InitStructure.USART_BaudRate    = config->Baud;
	USART_InitStructure.USART_WordLength  = config->WordLen;
	USART_InitStructure.USART_StopBits    = config->StopBits;
	USART_InitStructure.USART_Parity      = config->Parity;
//	USART_InitStructure.USART_Mode        = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    UartTxCallback[port].Callback = config->TxCallback.Callback;
    UartTxCallback[port].Param    = config->TxCallback.Param;
    UartRxCallback[port].Callback = config->RxCallback.Callback;
    UartRxCallback[port].Param    = config->RxCallback.Param;
    
    USART_DeInit(Uart[port]);
    USART_Init(Uart[port], &USART_InitStructure);
    USART_ClearITPendingBit(Uart[port], USART_IT_TC);
    USART_ClearITPendingBit(Uart[port], USART_IT_RXNE);
//    USART_ITConfig(Uart[port], USART_IT_TC, ENABLE);
//    USART_ITConfig(Uart[port], USART_IT_RXNE, ENABLE);
    	
    NVIC_InitStructure.NVIC_IRQChannel = UartIrqn[port];
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
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
    
    struct HalUartConfig config;
    
    config.Baud = dev->Baud;
    config.WordLen = dev->WordLen;
    config.StopBits = dev->StopBits;
    config.Parity = dev->Parity;
    
    config.TxCallback.Callback = dev->TxCallback.Callback;
    config.TxCallback.Param    = dev->TxCallback.Param;
    config.RxCallback.Callback = dev->RxCallback.Callback;
    config.RxCallback.Param    = dev->RxCallback.Param;
    
    return Map_Uart_Init(dev->Port, &config);
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
hal_err_t Map_Uart_SetRxCallback(uint8_t port, void (*callback)(void*, uint16_t), void *param)
{
    hal_assert(IS_UART_PORT_INVAILD(port));
    
    UartRxCallback[port].Callback = callback;
    UartRxCallback[port].Param = param;
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       set uart rx call back
 * @param       [in/out]  *dev            device block
 * @param       [in/out]  *callback       call back function
 * @param       [in/out]  *param          call back param
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Uart_SetRxCallback(struct HalUartDevice *dev, void (*callback)(void*, uint16_t), void *param)
{
    hal_assert(IS_PTR_NULL(dev));
    
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
hal_err_t Map_Uart_SendData(uint8_t port, uint16_t sendData)
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
hal_err_t Hal_Uart_SendData(struct HalUartDevice *dev, uint16_t sendData)
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
hal_err_t Map_Uart_ReceiveData(uint8_t port, uint16_t *sendData)
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
hal_err_t Hal_Uart_ReceiveData(struct HalUartDevice *dev, uint16_t *sendData)
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
    if (USART_GetITStatus(Uart[MCU_UART_1], USART_IT_TC) == SET)
    {
        if(!IS_PTR_NULL(UartTxCallback[MCU_UART_1].Callback))
        {
            UartTxCallback[MCU_UART_1].Callback(UartTxCallback[MCU_UART_1].Param);
        }
    }
    
    if (USART_GetITStatus(Uart[MCU_UART_1], USART_IT_RXNE) == SET)
    {
        if(!IS_PTR_NULL(UartRxCallback[MCU_UART_1].Callback))
        {
            UartRxCallback[MCU_UART_1].Callback(UartRxCallback[MCU_UART_1].Param, USART_ReceiveData(Uart[MCU_UART_1]));
        }
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
    if (USART_GetITStatus(Uart[MCU_UART_2], USART_IT_TC) == SET)
    {
        if(!IS_PTR_NULL(UartTxCallback[MCU_UART_2].Callback))
        {
            UartTxCallback[MCU_UART_2].Callback(UartTxCallback[MCU_UART_2].Param);
        }
    }
    
    if (USART_GetITStatus(Uart[MCU_UART_2], USART_IT_RXNE) == SET)
    {
        if(!IS_PTR_NULL(UartRxCallback[MCU_UART_2].Callback))
        {
            UartRxCallback[MCU_UART_2].Callback(UartRxCallback[MCU_UART_2].Param, USART_ReceiveData(Uart[MCU_UART_2]));
        }
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
    if (USART_GetITStatus(Uart[MCU_UART_3], USART_IT_TC) == SET)
    {
        if(!IS_PTR_NULL(UartTxCallback[MCU_UART_3].Callback))
        {
            UartTxCallback[MCU_UART_3].Callback(UartTxCallback[MCU_UART_3].Param);
        }
    }
    
    if (USART_GetITStatus(Uart[MCU_UART_3], USART_IT_RXNE) == SET)
    {
        if(!IS_PTR_NULL(UartRxCallback[MCU_UART_3].Callback))
        {
            UartRxCallback[MCU_UART_3].Callback(UartRxCallback[MCU_UART_3].Param, USART_ReceiveData(Uart[MCU_UART_3]));
        }
    }
}

/**
 *******************************************************************************
 * @brief       uart4 isr handle
 * @param       [in/out]  void           
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void UART4_IRQHandler(void)
{
    if (USART_GetITStatus(Uart[MCU_UART_4], USART_IT_TC) == SET)
    {
        if(!IS_PTR_NULL(UartTxCallback[MCU_UART_4].Callback))
        {
            UartTxCallback[MCU_UART_4].Callback(UartTxCallback[MCU_UART_4].Param);
        }
    }
    
    if (USART_GetITStatus(Uart[MCU_UART_4], USART_IT_RXNE) == SET)
    {
        if(!IS_PTR_NULL(UartRxCallback[MCU_UART_4].Callback))
        {
            UartRxCallback[MCU_UART_4].Callback(UartRxCallback[MCU_UART_4].Param, USART_ReceiveData(Uart[MCU_UART_4]));
        }
    }  
}

/**
 *******************************************************************************
 * @brief       uart5 isr handle
 * @param       [in/out]  void           
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void UART5_IRQHandler(void)
{
    if (USART_GetITStatus(Uart[MCU_UART_5], USART_IT_TC) == SET)
    {
        if(!IS_PTR_NULL(UartTxCallback[MCU_UART_5].Callback))
        {
            UartTxCallback[MCU_UART_5].Callback(UartTxCallback[MCU_UART_5].Param);
        }
    }
    
    if (USART_GetITStatus(Uart[MCU_UART_5], USART_IT_RXNE) == SET)
    {
        if(!IS_PTR_NULL(UartRxCallback[MCU_UART_5].Callback))
        {
            UartRxCallback[MCU_UART_5].Callback(UartRxCallback[MCU_UART_5].Param, USART_ReceiveData(Uart[MCU_UART_5]));
        }
    }
}

/** @}*/     /** map uart component */

/**********************************END OF FILE*********************************/
