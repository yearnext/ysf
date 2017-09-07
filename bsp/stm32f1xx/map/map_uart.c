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
#include <string.h>
#include "map_uart.h"
#include "hal_device.h"

/* Private constants ---------------------------------------------------------*/
#ifdef USE_HAL_UART
#ifdef USE_HAL_UART1
static void Uart1_Tx_DMA_Handle(struct __DMA_HandleTypeDef * hdma);
#endif

#ifdef USE_HAL_UART2
static void Uart2_Tx_DMA_Handle(struct __DMA_HandleTypeDef * hdma);
#endif

#ifdef USE_HAL_UART3
static void Uart3_Tx_DMA_Handle(struct __DMA_HandleTypeDef * hdma);
#endif
#endif

/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define uart tx isr call back
 *******************************************************************************
 */
#ifdef USE_HAL_UART
#ifdef USE_HAL_UART1
static UART_HandleTypeDef huart1;
static DMA_HandleTypeDef hdma_usart1_tx;

static Hal_Callback_t Uart1TxCallback;
static Hal_Callback_t Uart1RxCallback;
#endif

#ifdef USE_HAL_UART2
static UART_HandleTypeDef huart2;
static DMA_HandleTypeDef hdma_usart2_tx;

static Hal_Callback_t Uart2TxCallback;
static Hal_Callback_t Uart2RxCallback;
#endif

#ifdef USE_HAL_UART3
static UART_HandleTypeDef huart3;
static DMA_HandleTypeDef hdma_usart3_tx;

static Hal_Callback_t Uart3TxCallback;
static Hal_Callback_t Uart3RxCallback;
#endif

#ifdef USE_HAL_UART4
static UART_HandleTypeDef huart4;

static Hal_Callback_t Uart4TxCallback;
static Hal_Callback_t Uart4RxCallback;
#endif

static void *Map_Uart_Find(char *s);
static hal_err_t Map_Uart_Init(void *dev, uint32_t flag);
static hal_err_t Map_Uart_Fini(void *dev);
static uint16_t Map_Uart_Write(void *dev, uint8_t pos, uint8_t *buf, uint16_t size);
static uint16_t Map_Uart_Read(void *dev, uint8_t pos, uint8_t *buf, uint16_t size);
static hal_err_t Map_Uart_Control(void *drv, uint8_t cmd, va_list args);

const struct Hal_Interface Map_Uart_Interface = 
{
    .Open = Map_Uart_Find,
    .Init = Map_Uart_Init,
    .Fini = Map_Uart_Fini,
    .Write = Map_Uart_Write, 
    .Read = Map_Uart_Read,
    .Control = Map_Uart_Control,
};
#endif

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       device option api
 *******************************************************************************
 */
#ifdef USE_HAL_UART
#ifdef USE_HAL_UART1
__STATIC_INLINE
void Map_Uart1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    /* Peripheral clock enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();
    
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    huart1.Instance = USART1;
    huart1.Init.BaudRate = UART1_BAUD_RATE;
    huart1.Init.WordLength = UART1_WORD_LENGTH;
    huart1.Init.StopBits = UART1_STOP_BITS;
    huart1.Init.Parity = UART1_PARITY;
    huart1.Init.Mode = UART1_MODE;
    huart1.Init.HwFlowCtl = UART1_HARDWARE_FLOW_CONTROL;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    hdma_usart1_tx.Instance = DMA1_Channel4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_tx.XferCpltCallback = Uart1_Tx_DMA_Handle;

    __HAL_LINKDMA(&huart1,hdmatx,hdma_usart1_tx);
    
    HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    
    HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);

    HAL_DMA_Init(&hdma_usart1_tx);
    HAL_UART_Init(&huart1);
}

__STATIC_INLINE
void Map_Uart1_Fini(void)
{
    HAL_NVIC_DisableIRQ(USART1_IRQn);
    HAL_NVIC_DisableIRQ(DMA1_Channel4_IRQn);
    
    HAL_UART_DeInit(&huart1);
    HAL_DMA_DeInit(&hdma_usart1_tx);
    
    __HAL_RCC_USART1_CLK_DISABLE();
}
#endif

#ifdef USE_HAL_UART2
__STATIC_INLINE
void Map_Uart2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    /* Peripheral clock enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();
    
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    //< init uart2
    huart2.Instance = USART2;
    huart2.Init.BaudRate = UART2_BAUD_RATE;
    huart2.Init.WordLength = UART2_WORD_LENGTH;
    huart2.Init.StopBits = UART2_STOP_BITS;
    huart2.Init.Parity = UART2_PARITY;
    huart2.Init.Mode = UART2_MODE;
    huart2.Init.HwFlowCtl = UART2_HARDWARE_FLOW_CONTROL;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    
    //< init uart2 tx dma
    hdma_usart2_tx.Instance = DMA1_Channel7;
    hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_tx.Init.Mode = DMA_NORMAL;
    hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_tx.XferCpltCallback = Uart2_Tx_DMA_Handle;

    __HAL_LINKDMA(&huart2,hdmatx,hdma_usart2_tx);
    
    HAL_NVIC_SetPriority(USART2_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
    
    HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
  
    HAL_DMA_Init(&hdma_usart2_tx);
    HAL_UART_Init(&huart2);
}

__STATIC_INLINE
void Map_Uart2_Fini(void)
{
    HAL_NVIC_DisableIRQ(USART2_IRQn);
    HAL_NVIC_DisableIRQ(DMA1_Channel7_IRQn);
    
    HAL_UART_DeInit(&huart2);
    HAL_DMA_DeInit(&hdma_usart2_tx);
    
    __HAL_RCC_USART2_CLK_DISABLE();
}
#endif

#ifdef USE_HAL_UART3
__STATIC_INLINE
void Map_Uart3_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_USART3_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();
    
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    //< init uart3
    huart3.Instance = USART3;
    huart3.Init.BaudRate = UART3_BAUD_RATE;
    huart3.Init.WordLength = UART3_WORD_LENGTH;
    huart3.Init.StopBits = UART3_STOP_BITS;
    huart3.Init.Parity = UART3_PARITY;
    huart3.Init.Mode = UART3_MODE;
    huart3.Init.HwFlowCtl = UART3_HARDWARE_FLOW_CONTROL;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    
    //< init uart3 tx dma
    hdma_usart3_tx.Instance = DMA1_Channel2;
    hdma_usart3_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart3_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart3_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart3_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart3_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart3_tx.Init.Mode = DMA_NORMAL;
    hdma_usart3_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart3_tx.XferCpltCallback = Uart3_Tx_DMA_Handle;

    __HAL_LINKDMA(&huart3,hdmatx,hdma_usart3_tx);
    
    //< config uart3 isr
    HAL_NVIC_SetPriority(USART3_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
    
    HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
    
    //< init
    HAL_DMA_Init(&hdma_usart3_tx);
    HAL_UART_Init(&huart3);
}

__STATIC_INLINE
void Map_Uart3_Fini(void)
{
    HAL_NVIC_DisableIRQ(USART3_IRQn);
    HAL_NVIC_DisableIRQ(DMA1_Channel2_IRQn);
    
    HAL_UART_DeInit(&huart3);
    HAL_DMA_DeInit(&hdma_usart3_tx);
    
    __HAL_RCC_USART3_CLK_DISABLE();
}
#endif

#ifdef USE_HAL_UART4
__STATIC_INLINE
void Map_Uart4_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_UART4_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    huart4.Instance = UART4;
    huart4.Init.BaudRate = UART4_BAUD_RATE;
    huart4.Init.WordLength = UART4_WORD_LENGTH;
    huart4.Init.StopBits = UART4_STOP_BITS;
    huart4.Init.Parity = UART4_PARITY;
    huart4.Init.Mode = UART4_MODE;
    huart4.Init.HwFlowCtl = UART4_HARDWARE_FLOW_CONTROL;
    huart4.Init.OverSampling = UART_OVERSAMPLING_16;
    
    HAL_NVIC_SetPriority(UART4_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(UART4_IRQn);
    
    HAL_UART_Init(&huart4);
}

__STATIC_INLINE
void Map_Uart4_Fini(void)
{
    HAL_NVIC_DisableIRQ(UART4_IRQn);
    HAL_UART_DeInit(&huart4);
    
    __HAL_RCC_UART4_CLK_DISABLE();
}
#endif
#endif

/**
 *******************************************************************************
 * @brief       hal device api
 *******************************************************************************
 */
#ifdef USE_HAL_UART
static void *Map_Uart_Find(char *s)
{
#ifdef USE_HAL_UART1
    if(strcmp(s, "uart1") == 0)
    {
        return (void *)&huart1;
    }
#endif

#ifdef USE_HAL_UART2    
    if(strcmp(s, "uart2") == 0)
    {
        return (void *)&huart2;
    }
#endif  
    
#ifdef USE_HAL_UART3
    if(strcmp(s, "uart3") == 0)
    {
        return (void *)&huart3;
    }
#endif
    
#ifdef USE_HAL_UART4
    if(strcmp(s, "uart4") == 0)
    {
        return (void *)&huart4;
    }
#endif
 
    return NULL;
}

static hal_err_t Map_Uart_Init(void *dev, uint32_t flag)
{
#ifdef USE_HAL_UART1
    if(dev == (void *)&huart1)
    {
        Map_Uart1_Init();
        return HAL_ERR_NONE;
    }    
#endif
    
#ifdef USE_HAL_UART2
    if(dev == (void *)&huart2)
    {
        Map_Uart2_Init();
        return HAL_ERR_NONE;
    }
#endif
    
#ifdef USE_HAL_UART3
    if(dev == (void *)&huart3)
    {
        Map_Uart3_Init();
        return HAL_ERR_NONE;
    }
#endif
    
#ifdef USE_HAL_UART4
    if(dev == (void *)&huart4)
    {
        Map_Uart4_Init();
        return HAL_ERR_NONE;
    }
#endif

    return HAL_ERR_FAIL;
}

static hal_err_t Map_Uart_Fini(void *dev)
{
#ifdef USE_HAL_UART1
    if(dev == (void *)&huart1)
    {
        Map_Uart1_Fini();
        return HAL_ERR_NONE;
    }
#endif
    
#ifdef USE_HAL_UART2
    if(dev == (void *)&huart2)
    {
        Map_Uart2_Fini();
        return HAL_ERR_NONE;
    }
#endif
    
#ifdef USE_HAL_UART3
    if(dev == (void *)&huart3)
    {
        Map_Uart3_Fini();
        return HAL_ERR_NONE;
    }
#endif

#ifdef USE_HAL_UART4
    if(dev == (void *)&huart4)
    {
        Map_Uart4_Fini();
        return HAL_ERR_NONE;
    }
#endif
    
    return HAL_ERR_FAIL;
}

static uint16_t Map_Uart_Write(void *dev, uint8_t pos, uint8_t *buf, uint16_t size)
{
    UART_HandleTypeDef *uart = (UART_HandleTypeDef *)dev;
    
#ifdef USE_HAL_UART1
    if(dev == (void *)&huart1)
    {
        if(uart->gState != HAL_UART_STATE_BUSY_TX)
        {
            HAL_UART_Transmit_DMA(uart, buf, size);
            return size;
        }
        
        return 0;
    }
#endif
    
#ifdef USE_HAL_UART2
    if(dev == (void *)&huart2)
    {
        if(uart->gState != HAL_UART_STATE_BUSY_TX)
        {
            HAL_UART_Transmit_DMA(uart, buf, size);
            return size;
        } 
        
        return 0;
    }
#endif
    
#ifdef USE_HAL_UART3
    else if(dev == (void *)&huart3)
    {
        if(uart->gState != HAL_UART_STATE_BUSY_TX)
        {
            HAL_UART_Transmit_DMA(uart, buf, size);
            return size;
        } 
        
        return 0;
    }
#endif
    
#ifdef USE_HAL_UART4
    if(dev == (void *)&huart4)
    {
        if(uart->gState != HAL_UART_STATE_BUSY_TX)
        {
            HAL_UART_Transmit_IT(uart, buf, size);
            return size;
        }  
        
        return 0;
    }
#endif

    return 0;
}

static uint16_t Map_Uart_Read(void *dev, uint8_t pos, uint8_t *buf, uint16_t size)
{
    UART_HandleTypeDef *uart = (UART_HandleTypeDef *)dev;

    HAL_UART_AbortReceive_IT(uart);
    
    HAL_UART_Receive_IT(uart, &buf[pos], size);
    
    return size;
}

static hal_err_t Map_Uart_Control(void *drv, uint8_t cmd, va_list args)
{
    return HAL_ERR_NONE;
}
#endif

/**
 *******************************************************************************
 * @brief       uart isr handle
 *******************************************************************************
 */
#ifdef USE_HAL_UART
#ifdef USE_HAL_UART1
static void Uart1_Tx_DMA_Handle(struct __DMA_HandleTypeDef * hdma)
{
    /* Disable the channel */
    __HAL_DMA_DISABLE(hdma);
    
    if(!IS_PTR_NULL(Uart1TxCallback.Function))
    {
        Uart1TxCallback.Tx(HAL_DEVICE_TX_COMPLET_EVENT, Uart1TxCallback.Param);
    }
}
#endif

#ifdef USE_HAL_UART2
static void Uart2_Tx_DMA_Handle(struct __DMA_HandleTypeDef * hdma)
{
    /* Disable the channel */
    __HAL_DMA_DISABLE(hdma);
    
    if(!IS_PTR_NULL(Uart2TxCallback.Function))
    {
        Uart2TxCallback.Tx(HAL_DEVICE_TX_COMPLET_EVENT, Uart2TxCallback.Param);
    }
}
#endif

#ifdef USE_HAL_UART3
static void Uart3_Tx_DMA_Handle(struct __DMA_HandleTypeDef * hdma)
{
    /* Disable the channel */
    __HAL_DMA_DISABLE(hdma);
    
    if(!IS_PTR_NULL(Uart3TxCallback.Function))
    {
        Uart3TxCallback.Tx(HAL_DEVICE_TX_COMPLET_EVENT, Uart3TxCallback.Param);
    }
}
#endif

#ifdef USE_HAL_UART4
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart == &huart4)
    {
        if(!IS_PTR_NULL(Uart4TxCallback.Function))
        {
            Uart4TxCallback.Tx(HAL_DEVICE_TX_COMPLET_EVENT, Uart4TxCallback.Param);
        }
    }
}
#endif

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#ifdef USE_HAL_UART1
    if(huart == (void *)&huart1)
    {
        if(!IS_PTR_NULL(Uart1RxCallback.Function))
        {
            Uart1RxCallback.Rx(HAL_DEVICE_TX_COMPLET_EVENT, Uart1RxCallback.Param);
            return;
        }
    }
#endif
    
#ifdef USE_HAL_UART2
    if(huart == (void *)&huart2)
    {
        if(!IS_PTR_NULL(Uart2RxCallback.Function))
        {
            Uart2RxCallback.Rx(HAL_DEVICE_TX_COMPLET_EVENT, Uart2RxCallback.Param);
            return;
        }
    }
    #endif
    
#ifdef USE_HAL_UART3
    if(huart == (void *)&huart3)
    {
        if(!IS_PTR_NULL(Uart3RxCallback.Function))
        {
            Uart3RxCallback.Rx(HAL_DEVICE_TX_COMPLET_EVENT, Uart3RxCallback.Param);
            return;
        }
    }
#endif
    
#ifdef USE_HAL_UART4
    if(huart == (void *)&huart4)
    {
        if(!IS_PTR_NULL(Uart4RxCallback.Function))
        {
            Uart4RxCallback.Rx(HAL_DEVICE_TX_COMPLET_EVENT, Uart4RxCallback.Param);
            return;
        }
    }
#endif
    
    return;
}
#endif

/** @}*/     /** map uart component */

/**********************************END OF FILE*********************************/
