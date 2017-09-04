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
 * @file       hal_timer.c                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-16                                                      *
 * @brief      hal timer component source files                                *
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
 * @defgroup hal timer component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hal_timer.h"
#include "map_timer.h"

/* Exported constants --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define common uart option interface
 *******************************************************************************
 */ 
#ifdef USE_HAL_DEVICE_COMPONENT
const struct Hal_Interface Hal_Timer_Interface = 
{
    .Init = Hal_Timer_Interface_Init, 
    .Fini = Hal_Timer_Interface_Fini, 
    .Control = Hal_Timer_Interface_Control,
};
#endif

/* Exported variables --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define uart opera interface
 *******************************************************************************
 */ 
#if USE_TIMER_COMPONENT
static const struct Map_Timer_Opera *map_api = (struct Map_Timer_Opera *)&map_timer_api;
#endif

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief       hal api : set timer up isr call back
 * @param       [in/out]  *drv        device block
 * @param       [in/out]  *param      config data
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_SetTimeOutCallback(Hal_Device_Timer *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));

    Hal_Callback_t *callback = (Hal_Callback_t *)param;
    
    map_timer_api.SetTimeOutCallback(drv->Config.Port, callback->TimeOut, callback->Param);
}

/**
 *******************************************************************************
 * @brief       hal api : timer start
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_Start(Hal_Device_Timer *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    map_timer_api.Start(drv->Config.Port);
}

/**
 *******************************************************************************
 * @brief       hal api : timer stop
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_Stop(Hal_Device_Timer *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    map_timer_api.Stop(drv->Config.Port);
}
#endif

#if USE_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief       hal api : init device
 * @param       [in/out]  *drv            device block
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Timer_Interface_Init(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_Timer *timer = (Hal_Device_Timer *)drv;
    
    //< init device
    map_timer_api.Open(timer->Config.Port);
    map_timer_api.Init(timer->Config.Port, drv);

    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal api : deinit device
 * @param       [in/out]  *drv            device block
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Timer_Interface_Fini(void *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_Timer *timer = (Hal_Device_Timer *)drv;
    
    map_timer_api.Fini(timer->Config.Port);   

    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       hal api : device control
 * @param       [in/out]  *drv            device block
 * @param       [in/out]  cmd             control cmd
 * @param       [in/out]  args            control param
 * @return      [in/out]  HAL_ERR_NONE    result
 * @note        None
 *******************************************************************************
 */
hal_err_t Hal_Timer_Interface_Control(void *drv, uint8_t cmd, va_list args)
{
    hal_assert(IS_PTR_NULL(drv));
    
    Hal_Device_Timer *timer = (Hal_Device_Timer *)drv;
    
    switch(cmd)
    {
        case HAL_DEVICE_OPEN_CMD:
        {
            if(!IS_PTR_NULL(map_api->Open))
            {
                map_api->Open(timer->Config.Port);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_CLOSE_CMD:
        {
            if(!IS_PTR_NULL(map_api->Close))
            {
                map_api->Close(timer->Config.Port); 
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_INIT_CMD:
        {
            if(!IS_PTR_NULL(map_api->Open) && !IS_PTR_NULL(map_api->Init))
            {
                map_api->Open(timer->Config.Port);
                map_api->Init(timer->Config.Port, &timer->Config);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_DEVICE_FINI_CMD:
        {
            if(!IS_PTR_NULL(map_api->Fini))
            {
                map_api->Fini(timer->Config.Port);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_TIMER_START_CMD:
        {
            if(!IS_PTR_NULL(map_api->Start))
            {
                map_api->Start(timer->Config.Port);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_TIMER_STOP_CMD:
        {
            if(!IS_PTR_NULL(map_api->Stop))
            {
                map_api->Stop(timer->Config.Port);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            break;
        }
        case HAL_TIMER_SET_TIMEOUT_CALLBACK_CMD:
        {
            if(!IS_PTR_NULL(map_api->SetTimeOutCallback))
            {
                Hal_Callback_t callback;
                
                callback.Function = va_arg(args, void*);
                callback.Param = va_arg(args, void*);
                
                map_api->SetTimeOutCallback(timer->Config.Port, callback.TimeOut, callback.Param);
            }
            else
            {
                return HAL_ERR_FAIL;
            }
            
            break;
        }
        default:
            break;
    }
    
    return HAL_ERR_NONE;
}
#endif

/** @}*/     /** hal timer component */

/**********************************END OF FILE*********************************/
