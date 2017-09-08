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
 * @file       map_uart.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-08                                                      *
 * @brief      mcu uart application component head files                       *
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
 * @defgroup map uart component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAP_UART_H__
#define __MAP_UART_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/  
#include "hal_uart.h"
    
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
#ifdef USE_HAL_UART
/**
 *******************************************************************************
 * @brief       uart1 config
 *******************************************************************************
 */
#ifdef USE_HAL_UART1
#define UART1_BAUD_RATE                                      (115200)
#define UART1_WORD_LENGTH                                    UART_WORDLENGTH_8B
#define UART1_STOP_BITS                                      UART_STOPBITS_1
#define UART1_PARITY                                         UART_PARITY_NONE
#define UART1_MODE                                           UART_MODE_TX_RX
#define UART1_HARDWARE_FLOW_CONTROL                          UART_HWCONTROL_NONE
#endif

/**
 *******************************************************************************
 * @brief       uart2 config
 *******************************************************************************
 */
#ifdef USE_HAL_UART2
#define UART2_BAUD_RATE                                      (115200)
#define UART2_WORD_LENGTH                                    UART_WORDLENGTH_8B
#define UART2_STOP_BITS                                      UART_STOPBITS_1
#define UART2_PARITY                                         UART_PARITY_NONE
#define UART2_MODE                                           UART_MODE_TX_RX
#define UART2_HARDWARE_FLOW_CONTROL                          UART_HWCONTROL_NONE
#endif

/**
 *******************************************************************************
 * @brief       uart3 config
 *******************************************************************************
 */
#ifdef USE_HAL_UART3  
#define UART3_BAUD_RATE                                      (115200)
#define UART3_WORD_LENGTH                                    UART_WORDLENGTH_8B
#define UART3_STOP_BITS                                      UART_STOPBITS_1
#define UART3_PARITY                                         UART_PARITY_NONE
#define UART3_MODE                                           UART_MODE_TX_RX
#define UART3_HARDWARE_FLOW_CONTROL                          UART_HWCONTROL_NONE
#endif

/**
 *******************************************************************************
 * @brief       uart4 config
 *******************************************************************************
 */
#ifdef USE_HAL_UART4
#define UART4_BAUD_RATE                                      (115200)
#define UART4_WORD_LENGTH                                    UART_WORDLENGTH_8B
#define UART4_STOP_BITS                                      UART_STOPBITS_1
#define UART4_PARITY                                         UART_PARITY_NONE
#define UART4_MODE                                           UART_MODE_TX_RX
#define UART4_HARDWARE_FLOW_CONTROL                          UART_HWCONTROL_NONE
#endif
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#ifdef USE_HAL_UART
extern void Map_Uart_InitComponent(void);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** map uart component */

/**********************************END OF FILE*********************************/
