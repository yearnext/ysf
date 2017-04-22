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
 * @file       hal_interface.h                                                 *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-18                                                      *
 * @brief      hal interface head files                                        *
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
 * @defgroup hal interface
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_INTERFACE_H__
#define __HAL_INTERFACE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/  
#include "core_path.h"
#include _HAL_PATH
#include _HAL_GPIO_PATH   
#include _HAL_TIMER_PATH    

/* Exported types ------------------------------------------------------------*/

/**
 *******************************************************************************
 * @brief      define msp gpio interface
 *******************************************************************************
 */
#if USE_MSP_GPIO_COMPONENT
typedef struct
{
    hal_err_t          (*Open)(uint8_t);
    hal_err_t          (*Close)(uint8_t);
    hal_err_t          (*Init)(uint8_t, uint8_t, uint8_t);
    hal_err_t          (*Fini)(uint8_t, uint8_t);
    
	struct
	{
        hal_err_t      (*Get)(uint8_t, uint8_t, uint8_t*);
	}Input;
	
	struct
	{
        hal_err_t      (*Get)(uint8_t, uint8_t, uint8_t*);
        hal_err_t      (*Set)(uint8_t, uint8_t);
        hal_err_t      (*Clr)(uint8_t, uint8_t);
        hal_err_t      (*Toggle)(uint8_t, uint8_t);
        hal_err_t      (*Cmd)(uint8_t, uint8_t, uint8_t);
	}Output;
}MSP_GPIO_Interface;
#endif

#if USE_MSP_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief       define msp timer interface
 *******************************************************************************
 */
typedef struct
{    
    hal_err_t (*Open)(uint8_t);
    hal_err_t (*Close)(uint8_t);
    
    hal_err_t (*Start)(uint8_t);
    hal_err_t (*Stop)(uint8_t);
    
    struct
    {
        hal_err_t (*Init)(uint8_t, uint32_t);
        hal_err_t (*HandleRegister)(uint8_t, void (*)(void *), void*);
        hal_err_t (*Arm)(uint8_t, uint32_t, void (*)(void *), void*);
    }Base;
}MSP_Timer_Interface;
#endif

/**
 *******************************************************************************
 * @brief        define hal interface
 *******************************************************************************
 */
struct HalInterface
{
    char *Version;
    
#if USE_MSP_GPIO_COMPONENT
    MSP_GPIO_Interface GPIO;
#endif  

#if USE_MSP_TIMER_COMPONENT
    MSP_Timer_Interface Timer;
#endif
};
    
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** hal interface  */

/**********************************END OF FILE*********************************/
