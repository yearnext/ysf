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
#include "hal_core.h"
    
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_MCU_UART_COMPONENT
    #define USE_UART_COMPONENT                                               (1)
  
/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
    #define USE_UART_COMPONENT                                               (1)
#endif
    
/**
 *******************************************************************************
 * @brief      define hal uart id
 *******************************************************************************
 */ 
enum Define_Uart_ID
{
    MCU_UART_1 = 0,
    MCU_UART_2,
    MCU_UART_3,
    MCU_UART_4,
    MCU_UART_5,
};
  
/**
 *******************************************************************************
 * @brief      define hal uart wordlen
 *******************************************************************************
 */ 
enum Define_Uart_WordLen
{
    MCU_UART_WORD_LEN_8B = 0,
    MCU_UART_WOED_LEN_9B,
};

/**
 *******************************************************************************
 * @brief      define hal uart stop bits
 *******************************************************************************
 */ 
enum Define_Uart_StopBits
{
    MCU_UART_STOP_BITS_0_5 = 0,
    MCU_UART_STOP_BITS_1,
    MCU_UART_STOP_BITS_1_5,
    MCU_UART_STOP_BITS_2,
};

/**
 *******************************************************************************
 * @brief      define hal uart parity
 *******************************************************************************
 */ 
enum Define_Uart_Parity
{
    MCU_UART_PARTY_NONE = 0,
    MCU_UART_PARTY_EVEN,
    MCU_UART_PARTY_ODD,
};

/**
 *******************************************************************************
 * @brief      define map deivce uart structure
 *******************************************************************************
 */ 
struct HalUartDevice
{
    uint8_t Port;
    uint8_t Group;
    
    uint8_t WordLen;
    uint8_t StopBits;
    uint8_t Parity;
    
    bool    IsEnableTx;
    bool    IsEnableRx;

    uint32_t Baud;
    
    struct HalCallback TxCallback;
    
    struct 
    {
        void (*Callback)(void*, uint8_t);
        void *Param;
    }RxCallback;
};

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_UART_COMPONENT
/**
 *******************************************************************************
 * @brief      define map api
 *******************************************************************************
 */ 
extern hal_err_t Map_Uart_Open(uint8_t);
extern hal_err_t Map_Uart_Close(uint8_t);
extern hal_err_t Map_Uart_Init(uint8_t, struct HalUartDevice*);
extern hal_err_t Map_Uart_SetTxCallback(uint8_t, void (*)(void*), void*);
extern hal_err_t Map_Uart_SetRxCallback(uint8_t, void (*)(void*, uint8_t), void*);
extern hal_err_t Map_Uart_Fini(uint8_t);
extern hal_err_t Map_Uart_SendData(uint8_t, uint8_t);
extern hal_err_t Map_Uart_ReceiveData(uint8_t, uint8_t*);

/**
 *******************************************************************************
 * @brief      define hal api
 *******************************************************************************
 */ 
extern __INLINE hal_err_t Hal_Uart_Open(struct HalUartDevice*);
extern __INLINE hal_err_t Hal_Uart_Close(struct HalUartDevice*);
extern __INLINE hal_err_t Hal_Uart_Init(struct HalUartDevice*);
extern hal_err_t Hal_Uart_SetTxCallback(struct HalUartDevice*, void (*)(void*), void*);
extern hal_err_t Hal_Uart_SetRxCallback(struct HalUartDevice*, void (*)(void*, uint8_t), void*);
extern __INLINE hal_err_t Hal_Uart_Fini(struct HalUartDevice*);
extern hal_err_t Hal_Uart_SendData(struct HalUartDevice*, uint8_t);
extern hal_err_t Hal_Uart_ReceiveData(struct HalUartDevice*, uint8_t*);
extern hal_err_t Hal_Uart_TxConnect(struct HalUartDevice*);
extern hal_err_t Hal_Uart_TxDisconnect(struct HalUartDevice*);
extern hal_err_t Hal_Uart_RxConnect(struct HalUartDevice*);
extern hal_err_t Hal_Uart_RxDisconnect(struct HalUartDevice*);
extern hal_err_t Hal_Uart_GetTxCompletFlag(struct HalUartDevice*, uint8_t*);
extern hal_err_t Hal_Uart_ClrTxCompletFlag(struct HalUartDevice*);
extern hal_err_t Hal_Uart_GetRxCompletFlag(struct HalUartDevice*, uint8_t*);
extern hal_err_t Hal_Uart_ClrRxCompletFlag(struct HalUartDevice*);

/**
 *******************************************************************************
 * @brief      define test api
 *******************************************************************************
 */ 
extern void Hal_Uart_Test_Init(void);

#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** map uart component */

/**********************************END OF FILE*********************************/
