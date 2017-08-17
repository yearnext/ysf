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
 * @file       hal_type.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-18                                                      *
 * @brief      hal type head files                                             *
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
 * @defgroup hal type
 * @{
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_TYPE_H__
#define __HAL_TYPE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "comm_path.h"
    
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define hal error type
 *******************************************************************************
 */
#define HAL_ERR_NONE                                                 (_ERR_NONE)
#define HAL_ERR_FAIL                                                 (_ERR_FAIL)
#define HAL_ERR_NOT_READY                                       (_ERR_NOT_READY)
#define HAL_ERR_NOT_SUPPORT                                   (_ERR_NOT_SUPPORT)
#define HAL_ERR_INVAILD_PTR                                   (_ERR_INVAILD_PTR)
#define HAL_ERR_INVAILD_PARAM                               (_ERR_INVAILD_PARAM)
#define HAL_ERR_IO                                                     (_ERR_IO)
#define HAL_ERR_BUG                                                   (_ERR_BUG)
#define HAL_ERR_UNKNOW                                             (_ERR_UNKNOW)

typedef _err_t                                                        hal_err_t;
    
/**
 *******************************************************************************
 * @brief      define hal isr call back
 *******************************************************************************
 */ 
struct Hal_Callback
{
	void (*Callback)(void*);
	void *Param;
};

struct Hal_GPIO_Device;
struct Hal_Timer_Device;

enum
{
    HAL_DEVICE_GPIO,
    HAL_DEVICE_TIMER,
};

typedef struct
{
    void *Device;
    
    uint8_t DeviceType;
    
}Hal_Device_t;

struct Hal_Device_Common_Opera
{
    void (*Open)(Hal_Device_t*);
    void (*Close)(Hal_Device_t*);
    
    void (*Init)(Hal_Device_t*, void*);
    void (*Fini)(Hal_Device_t*);
    
    hal_err_t (*Write)(Hal_Device_t*, uint8_t*, uint8_t);
    hal_err_t (*Read)(Hal_Device_t*, uint8_t*, uint8_t);
    
    void (*Control)(Hal_Device_t*, uint8_t, void*);
};

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal type */

/**********************************END OF FILE*********************************/
