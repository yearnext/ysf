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
 * @file       hal_uart.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-07                                                      *
 * @brief      hal uart component head files                                   *
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
 * @defgroup hal uart component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_UART_COMPONENT_H__
#define __HAL_UART_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/  
#include "hal_core.h"
#include "fw_buffer.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_HAL_UART_COMPONENT
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
    
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define hal uart id
 *******************************************************************************
 */ 
enum _Hal_Uart_Id
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
enum _Hal_UArt_Word_Len
{
    MCU_UART_WORD_LEN_8B = 0,
    MCU_UART_WOED_LEN_9B,
};

/**
 *******************************************************************************
 * @brief      define hal uart stop bits
 *******************************************************************************
 */ 
enum _Hal_Uart_Stop_Bits
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
enum _Hal_Uart_Party
{
    MCU_UART_PARTY_NONE = 0,
    MCU_UART_PARTY_EVEN,
    MCU_UART_PARTY_ODD,
};

/**
 *******************************************************************************
 * @brief      define hal uart Transfer Direction
 *******************************************************************************
 */ 
enum _Hal_Uart_Transfer_Config
{
    MCU_UART_DISABLE_TX = 0,
    MCU_UART_ENABLE_TX = 1,
    MCU_UART_ENABLE_TX_ISR = 2,
    
    MCU_UART_DISABLE_RX = 0,
    MCU_UART_ENABLE_RX = 1,
    MCU_UART_ENABLE_RX_ISR = 2,
};

/**
 *******************************************************************************
 * @brief      define map deivce uart structure
 *******************************************************************************
 */
struct Hal_Uart_Opera;
typedef struct
{
    Hal_Callback_t TxCallback;
    Hal_Callback_t RxCallback;
    
    struct _Hal_Uart_Config
    {
        uint8_t Port;
        uint8_t Group;
        
        uint8_t WordLen;
        uint8_t StopBits;
        uint8_t Parity;
        
        uint8_t TxConfig;
        uint8_t RxConfig;

        uint8_t Priority;
        
        uint32_t Baud;
    }Config;
}Hal_Device_Uart;

/**
 *******************************************************************************
 * @brief      define mcu application pack opera api
 *******************************************************************************
 */
struct Map_Uart_Opera
{
    void (*Open)(uint8_t);
    void (*Close)(uint8_t);
    
    void (*Init)(uint8_t, void*);
    void (*Fini)(uint8_t);
    
    void (*SetTxCallback)(uint8_t, void (*)(uint8_t, void*), void*);
    void (*SetRxCallback)(uint8_t, void (*)(uint8_t, void*, uint8_t), void*);

    void (*Send)(uint8_t, uint8_t);
    uint8_t (*Receive)(uint8_t);
    
    void (*TxConnect)(uint8_t);
    void (*TxDisconnect)(uint8_t);
    
    void (*RxConnect)(uint8_t);
    void (*RxDisconnect)(uint8_t);
    
    bool (*IsTxComplet)(uint8_t);
    bool (*IsRxComplet)(uint8_t);
};

/* Exported constants --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define hal gpio interface
 *******************************************************************************
 */ 
#ifdef USE_HAL_DEVICE_COMPONENT
extern const struct Hal_Interface Hal_Uart_Interface;
#endif

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define hal gpio apis
 *******************************************************************************
 */ 
#if USE_UART_COMPONENT
extern void Hal_Uart_Open(Hal_Device_Uart*);
extern void Hal_Uart_Close(Hal_Device_Uart*);
extern void Hal_Uart_Init(Hal_Device_Uart*);
extern void Hal_Uart_Fini(Hal_Device_Uart*);
extern void Hal_Uart_Send(Hal_Device_Uart*, uint8_t);
extern uint8_t Hal_Uart_Receive(Hal_Device_Uart*);
extern void Hal_Uart_SetTxCallback(Hal_Device_Uart*, void*);
extern void Hal_Uart_SetRxCallback(Hal_Device_Uart*, void*);
extern void Hal_Uart_TxConnect(Hal_Device_Uart*);
extern void Hal_Uart_TxDisconnect(Hal_Device_Uart*);
extern void Hal_Uart_RxConnect(Hal_Device_Uart*);
extern void Hal_Uart_RxDisconnect(Hal_Device_Uart*);
extern bool Hal_Uart_IsTxComplet(Hal_Device_Uart*);
extern bool Hal_Uart_IsRxComplet(Hal_Device_Uart*);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal component interface  */

/**********************************END OF FILE*********************************/
