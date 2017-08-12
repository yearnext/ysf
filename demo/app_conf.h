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
 * @file       app_conf.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-07-10                                                      *
 * @brief      application config head files                                   *
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
 * @defgroup application config
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APPLICATION_CONF_H__
#define __APPLICATION_CONF_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
/* Define and config ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define framework event
 *******************************************************************************
 */
enum Define_Application_Event
{
    LED_ON_EVENT,
    LED_OFF_EVENT,
    LED_BLINK_EVENT,
};

/**
 *******************************************************************************
 * @brief      define signal id
 *******************************************************************************
 */
enum Define_Signal_Id
{
    FW_INIT_SIGNAL = 0,
    
    /** define user task begin */
    DEMO_KEY1_SIGNAL,
    DEMO_KEY2_SIGNAL,
    
    /** define user task end */
    FW_SIGNAL_MAX,
};

/* Exported types ------------------------------------------------------------*/
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** application config  */

/**********************************END OF FILE*********************************/
