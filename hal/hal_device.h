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
 * @file       hal_device.h                                                    *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-28                                                      *
 * @brief      hal device component head files                                 *
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
 * @defgroup hal device component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_DEVICE_COMPONENT_H__
#define __HAL_DEVICE_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/  
#include "hal_path.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
enum _Hal_Control_Cmd
{
    //< hal device common cmd
    HAL_DEVICE_OPEN_CMD,
    HAL_DEVICE_CLOSE_CMD,
    
    HAL_DEVICE_INIT_CMD,
    HAL_DEVICE_FINI_CMD,
    
    HAL_DEVICE_CLR_TX_FLAG_CMD,
    HAL_DEVICE_GET_TX_FLAG_CMD,
    
    HAL_DEVICE_CLR_RX_FLAG_CMD,
    HAL_DEVICE_GET_RX_FLAG_CMD,
    
    HAL_DEVICE_CONNECT_TX_CMD,
    HAL_DEVICE_DISCONNECT_TX_CMD,
    
    HAL_DEVICE_CONNECT_RX_CMD,
    HAL_DEVICE_DISCONNECT_RX_CMD,
    
    HAL_DEVICE_SEND_BYTE_CMD,
    HAL_DEVICE_RECEIVE_BYTE_CMD,
    
    HAL_DEVICE_SET_TX_CALLBACK_CMD,
    HAL_DEVICE_SET_RX_CALLBACK_CMD,
        
    //< hal device gpio cmd
    HAL_GPIO_SET_BIT_CMD,
    HAL_GPIO_CLR_BIT_CMD,
    
    HAL_GPIO_GET_INTPUT_CMD,
    HAL_GPIO_GET_OUTPUT_CMD,
    
    HAL_GPIO_TOGGLE_CMD,
    
    HAL_GPIO_WRITE_CMD,
    HAL_GPIO_READ_CMD,
    
    //< hal device timer cmd
    HAL_TIMER_START_CMD,
    HAL_TIMER_STOP_CMD,
    
    HAL_TIMER_SET_TIMEOUT_CALLBACK_CMD,
    
    HAL_TIMER_SET_DUTY,
    
    //< device pin driver cmd
    HAL_DEVICE_PIN_OPEN_CMD,
    HAL_DEVICE_PIN_CLOSE_CMD,
    HAL_DEVICE_PIN_SET_DUTY_CMD,
    HAL_DEVICE_PIN_SET_BLINK_CMD,
    HAL_DEVICE_PIN_TOGGLE_CMD,
};
    
/**
 *******************************************************************************
 * @brief       hal device type enum
 *******************************************************************************
 */
enum _Hal_Device_Type
{
    HAL_DEVICE_GPIO,
    HAL_DEVICE_TIMER,
    HAL_DEVICE_SPI,
    HAL_DEVICE_UART,
    HAL_DEVICE_IIC,
};

/**
 *******************************************************************************
 * @brief      define hal Transfer Direction
 *******************************************************************************
 */ 
typedef enum
{
    HAL_DEVICE_TRANSFER_DISABLE = 0,
    HAL_DEVICE_TRANSFER_ENABLE,
    HAL_DEVICE_TRANSFER_ENABLE_ISR,
    HAL_DEVICE_TRANSFER_ENABLE_DMA,
}Hal_Transfer_Config;

/**
 *******************************************************************************
 * @brief      define hal init state
 *******************************************************************************
 */ 
typedef enum
{
    HAL_DEVICE_UNINIT_STATE,
    HAL_DEVICE_INIT_STATE,
}Hal_Device_State;

/**
 *******************************************************************************
 * @brief      define hal device lock state
 *******************************************************************************
 */ 
typedef enum
{
    HAL_DEVICE_UNLOCK,
    HAL_DEVICE_LOCK,
}Hal_Device_Lock_State;

/**
 *******************************************************************************
 * @brief      define hal error code
 *******************************************************************************
 */ 
typedef enum
{
    HAL_DEVICE_ERR_CODE_NONE,
    HAL_DEVICE_ERR_CODE_LOCK,
    HAL_DEVICE_ERR_CODE_UNINIT,
    HAL_DEVICE_ERR_CODE_INITED,
}Hal_Device_ErrCode;

/**
 *******************************************************************************
 * @brief       hal device opera interface structure
 *******************************************************************************
 */
struct Hal_Interface
{
    hal_err_t (*Init)(void*);
    hal_err_t (*Fini)(void*);

    hal_err_t (*Write)(void*, uint8_t, uint8_t*, uint8_t);
    hal_err_t (*Read)(void*, uint8_t, uint8_t*, uint8_t);
    
    hal_err_t (*Control)(void*, uint8_t, va_list);
};

/**
 *******************************************************************************
 * @brief       hal device type structure
 *******************************************************************************
 */
typedef struct
{
    void *Device;
    struct Hal_Interface *Interface;

    Hal_Device_Lock_State Lock;
    Hal_Device_State      State;
    Hal_Device_ErrCode    ErrCode;
}Hal_Device_t;

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       hal device opera interface
 *******************************************************************************
 */
extern __INLINE hal_err_t Hal_Device_Register(Hal_Device_t*, void*, struct Hal_Interface*);
extern __INLINE hal_err_t Hal_Device_Unregister(Hal_Device_t*);
extern __INLINE hal_err_t Hal_Device_Init(Hal_Device_t*);
extern __INLINE hal_err_t Hal_Device_Fini(Hal_Device_t*);
extern __INLINE hal_err_t Hal_Device_Write(Hal_Device_t*, uint8_t, uint8_t*, uint8_t);
extern __INLINE hal_err_t Hal_Device_Read(Hal_Device_t*, uint8_t, uint8_t*, uint8_t);
extern __INLINE hal_err_t Hal_Device_Control(Hal_Device_t*, uint8_t, ...);
extern __INLINE hal_err_t Hal_Device_Lock(Hal_Device_t*);
extern __INLINE hal_err_t Hal_Device_Unlock(Hal_Device_t*);
extern __INLINE uint8_t Hal_Device_GetErrCode(Hal_Device_t*);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal device component interface  */

/**********************************END OF FILE*********************************/
