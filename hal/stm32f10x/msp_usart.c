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
 * @file       msp_usart.c                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-20                                                      *
 * @brief      msp usart source files                                          *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         * 
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */
 
/**
 * @defgroup usart component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _HAL_PATH
#include _HAL_MAL_PATH
#include _HAL_USART_PATH

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define usart assert function
 *******************************************************************************
 */
#define IS_USART_ID_INVAILD(id)                        ( (id) >= MCU_USART_MAX )

#define STM32F10X_USART1_RCC_POS                                            (14)
#define STM32F10X_USART2_RCC_POS                                            (17)
#define STM32F10X_USART3_RCC_POS                                            (18)
#define STM32F10X_USART4_RCC_POS                                            (19)
#define STM32F10X_USART5_RCC_POS                                            (20)

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       enable usart1
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _usart1_open(void)
{
    _SET_BIT(RCC->APB2ENR, STM32F10X_USART1_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       disable usart1
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _usart1_close(void)
{
    _SET_BIT(RCC->APB2RSTR, STM32F10X_USART1_RCC_POS);
    _CLR_BIT(RCC->APB2RSTR, STM32F10X_USART1_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       enable usart2
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _usart2_open(void)
{
    _SET_BIT(RCC->APB1ENR, STM32F10X_USART2_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       disable usart1
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _usart2_close(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_USART2_RCC_POS);
    _CLR_BIT(RCC->APB1RSTR, STM32F10X_USART2_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       enable usart3
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _usart3_open(void)
{
    _SET_BIT(RCC->APB1ENR, STM32F10X_USART3_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       disable usart1
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _usart3_close(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_USART3_RCC_POS);
    _CLR_BIT(RCC->APB1RSTR, STM32F10X_USART3_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       enable usart4
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _usart4_open(void)
{
    _SET_BIT(RCC->APB1ENR, STM32F10X_USART4_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       disable usart1
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _usart4_close(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_USART4_RCC_POS);
    _CLR_BIT(RCC->APB1RSTR, STM32F10X_USART4_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       enable usart5
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _usart5_open(void)
{
    _SET_BIT(RCC->APB1ENR, STM32F10X_USART5_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       disable usart1
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _usart5_close(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_USART5_RCC_POS);
    _CLR_BIT(RCC->APB1RSTR, STM32F10X_USART5_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       enable usart
 * @param       [in/out]  id           usart id
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _open(uint8_t id)
{
    switch(id)
    {
        case MCU_USART_0:
            break;
        case MCU_USART_1:
            _usart1_open();
            break;
        case MCU_USART_2:
            _usart2_open();
            break;
        case MCU_USART_3:
            _usart3_open();
            break;
        case MCU_USART_4:
            _usart4_open();
            break;
        case MCU_USART_5:
            _usart5_open();
            break;
        default:
            break;
    }
}

/**
 *******************************************************************************
 * @brief       disable uasrt
 * @param       [in/out]  id           uasrt id
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _close(uint8_t id)
{
    switch(id)
    {
        case MCU_USART_0:
            break;
        case MCU_USART_1:
            _usart1_close();
            break;
        case MCU_USART_2:
            _usart2_close();
            break;
        case MCU_USART_3:
            _usart3_close();
            break;
        case MCU_USART_4:
            _usart4_close();
            break;
        case MCU_USART_5:
            _usart5_close();
            break;
        default:
            break;
    }
}

#define STM32F10X_USART1_START_POS (13)

__STATIC_INLINE
void _usart1_start(void)
{
    _SET_BIT(USART1->CR1, STM32F10X_USART1_START_POS);
}

__STATIC_INLINE
void _usart1_stop(void)
{
    _CLR_BIT(USART1->CR1, STM32F10X_USART1_START_POS);
}

__STATIC_INLINE
void _usart1_set_baud(uint32_t baud)
{
    
}

__STATIC_INLINE
void _start(uint8_t id)
{
    switch(id)
    {
        case MCU_USART_0:
            break;
        case MCU_USART_1:
            _usart1_start();
            break;
        case MCU_USART_2:
            break;
        case MCU_USART_3:
            break;
        case MCU_USART_4:
            break;
        case MCU_USART_5:
            break;
        default:
            break;
    }
}

__STATIC_INLINE
void _stop(uint8_t id)
{
    switch(id)
    {
        case MCU_USART_0:
            break;
        case MCU_USART_1:
            _usart1_stop();
            break;
        case MCU_USART_2:
            break;
        case MCU_USART_3:
            break;
        case MCU_USART_4:
            break;
        case MCU_USART_5:
            break;
        default:
            break;
    }
}

/**
 *******************************************************************************
 * @brief       usart enable
 * @param       [in/out]  id              usart id
 * @return      [in/out]  HAL_ERR_NONE    enable success
 * @return      [in/out]  HAL_ERR_FAIL    enable failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MSP_USART_Open(uint8_t id)
{
    hal_assert(IS_USART_ID_INVAILD(id));
    
    _open(id);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       usart disable
 * @param       [in/out]  id              usart id
 * @return      [in/out]  HAL_ERR_NONE    enable success
 * @return      [in/out]  HAL_ERR_FAIL    enable failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MSP_USART_Close(uint8_t id)
{
    hal_assert(IS_USART_ID_INVAILD(id));
    
    _close(id);
    
    return HAL_ERR_NONE;
}

/** @}*/     /** usart component */

/**********************************END OF FILE*********************************/
