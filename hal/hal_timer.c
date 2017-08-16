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
#if USE_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief      define mcu application pack gpio opera interface
 *******************************************************************************
 */ 
static struct Map_Timer_Opera *_timer_ops = NULL;

/**
 *******************************************************************************
 * @brief      define timer opera interface
 *******************************************************************************
 */ 
static const struct Hal_Timer_Opera timer_ops = 
{
    .Open = Hal_Timer_Open,
    .Close = Hal_Timer_Close, 
    
    .Init = Hal_Timer_Init,
    .Fini = Hal_Timer_Fini,
    .SetUpCallback = Hal_Timer_SetUpCallback,
    
    .Start = Hal_Timer_Start,
    .Stop = Hal_Timer_Stop,
};
#endif

/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief       register hal gpio module
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_Module_Register(void)
{
    Map_Timer_API_Register((void **)&_timer_ops);
}

/**
 *******************************************************************************
 * @brief       hal api : open device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_Open(Hal_Device_t *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    struct Hal_Timer_Device *timer = (struct Hal_Timer_Device *)&drv->Device;
    
    _timer_ops->Open(timer->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : close device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_Close(Hal_Device_t *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    struct Hal_Timer_Device *timer = (struct Hal_Timer_Device *)&drv->Device;
    
    _timer_ops->Close(timer->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : init device
 * @param       [in/out]  *drv        device block
 * @param       [in/out]  *param      device config param
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_Init(Hal_Device_t *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));
    
    struct Hal_Timer_Device *timer = (struct Hal_Timer_Device *)&drv->Device;
    
    timer->Opera = (struct Hal_Timer_Opera *)&timer_ops;
    
    _timer_ops->Open(timer->Port);
    _timer_ops->Init(timer->Port, param);
}

/**
 *******************************************************************************
 * @brief       hal api : deinit device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_Fini(Hal_Device_t *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    struct Hal_Timer_Device *timer = (struct Hal_Timer_Device *)&drv->Device;
    
    timer->Opera = NULL;
    timer->Port = 0;
    
    _timer_ops->Fini(timer->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : set timer up isr call back
 * @param       [in/out]  *drv        device block
 * @param       [in/out]  *param      config data
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_SetUpCallback(Hal_Device_t *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));
    
    struct Hal_Timer_Device *timer = (struct Hal_Timer_Device *)&drv->Device;
    struct Hal_Callback *callback = (struct Hal_Callback *)param;
    
    _timer_ops->SetUpCallback(timer->Port, callback->Callback, callback->Param);
}

/**
 *******************************************************************************
 * @brief       hal api : timer start
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_Start(Hal_Device_t *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    struct Hal_Timer_Device *timer = (struct Hal_Timer_Device *)&drv->Device;

    _timer_ops->Start(timer->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : timer stop
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_Stop(Hal_Device_t *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    struct Hal_Timer_Device *timer = (struct Hal_Timer_Device *)&drv->Device;

    _timer_ops->Stop(timer->Port);
}
#endif

/** @}*/     /** hal timer component */

/**********************************END OF FILE*********************************/
