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
 * @file       hal_spi.h                                                       *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-07                                                      *
 * @brief      hal spi component head files                                    *
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
 * @defgroup hal spi component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_SPI_COMPONENT_H__
#define __HAL_SPI_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/  
#include "hal_path.h"
#include "hal_device.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       framework component config flags
 * @note        1                        enable
 * @note        0                        disable
 *******************************************************************************
 */
#ifdef USE_HAL_SPI_COMPONENT
    #define USE_SPI_COMPONENT                                                (1)
  
/**
 *******************************************************************************
 * @brief       user config flags
 * @note        1         enable
 * @note        0         disable
 *******************************************************************************
 */
#else
    #define USE_SPI_COMPONENT                                                (1)
#endif

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define hal SPI id
 *******************************************************************************
 */ 
enum _Hal_SPI_Port
{
    MCU_SPI_1 = 0,
    MCU_SPI_2,
    MCU_SPI_3,
    MCU_SPI_4,
    MCU_SPI_5,
};
 
/**
 *******************************************************************************
 * @brief      define hal SPI wordlen
 *******************************************************************************
 */ 
enum _Hal_SPI_Word_Len
{
    MCU_SPI_WORD_LEN_8B = 0,
    MCU_SPI_WOED_LEN_9B,
};

/**
 *******************************************************************************
 * @brief      define hal SPI stop bits
 *******************************************************************************
 */ 
enum _Hal_SPI_Stop_Bit
{
    MCU_SPI_STOP_BITS_0_5 = 0,
    MCU_SPI_STOP_BITS_1,
    MCU_SPI_STOP_BITS_1_5,
    MCU_SPI_STOP_BITS_2,
};

/**
 *******************************************************************************
 * @brief      define hal SPI parity
 *******************************************************************************
 */ 
enum _Hal_SPI_Party
{
    MCU_SPI_PARTY_NONE = 0,
    MCU_SPI_PARTY_EVEN,
    MCU_SPI_PARTY_ODD,
};

/**
 *******************************************************************************
 * @brief      define hal SPI work mode
 *******************************************************************************
 */ 
enum _Hal_SPI_Mode
{
    MCU_SPI_MASTER_MODE = 0,
    MCU_SPI_SLAVE_MODE,
};

/**
 *******************************************************************************
 * @brief      define hal SPI order mode
 *******************************************************************************
 */ 
enum _Hal_SPI_Order
{
    MCU_SPI_BIT_ORDER_MSB,
    MCU_SPI_BIT_ORDER_LSB,
};

/**
 *******************************************************************************
 * @brief      define map deivce SPI structure
 *******************************************************************************
 */
typedef struct
{
    struct
    {
        uint8_t Port;
        uint8_t Group;
        
        uint8_t Mode;
        uint8_t CommType;
        
        uint8_t Priority;
        
        uint32_t Speed;
        uint8_t BitOrder;
        uint8_t CrcOptions;
        uint8_t ClockOptions;
    }Config;
    
    Hal_Callback_t TxCallback;
    Hal_Callback_t RxCallback;

    struct Hal_SPI_Opera *Opera;
}Hal_Device_SPI;

/**
 *******************************************************************************
 * @brief      define mcu application pack opera api
 *******************************************************************************
 */
struct Map_SPI_Opera
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
#ifdef USE_HAL_DEVICE_COMPONENT
extern const struct Hal_Interface Hal_SPI_Interface;
#endif

/* Exported functions --------------------------------------------------------*/
#if USE_SPI_COMPONENT
extern hal_err_t Hal_SPI_Interface_Init(void*);
extern hal_err_t Hal_SPI_Interface_Fini(void*);
extern hal_err_t Hal_SPI_Interface_Control(void*, uint8_t, va_list);
#endif

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal component interface  */

/**********************************END OF FILE*********************************/
