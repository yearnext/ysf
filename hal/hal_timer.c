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
 * @brief       hal api : open device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_Open(Hal_Timer_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    map_timer_api.Open(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : close device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_Close(Hal_Timer_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    map_timer_api.Close(drv->Port);
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
void Hal_Timer_Init(Hal_Timer_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
     
    drv->Opera = (struct Hal_Timer_Opera *)&timer_ops;
    
    map_timer_api.Open(drv->Port);
    map_timer_api.Init(drv->Port, (void *)drv);
}

/**
 *******************************************************************************
 * @brief       hal api : deinit device
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_Fini(Hal_Timer_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    map_timer_api.Fini(drv->Port); 
    
    drv->Opera = NULL;
    drv->Port = 0;
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
void Hal_Timer_SetUpCallback(Hal_Timer_Handle *drv, void *param)
{
    hal_assert(IS_PTR_NULL(drv));

    struct Hal_Callback *callback = (struct Hal_Callback *)param;
    
    map_timer_api.SetUpCallback(drv->Port, callback->Callback, callback->Param);
}

/**
 *******************************************************************************
 * @brief       hal api : timer start
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_Start(Hal_Timer_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));
    
    map_timer_api.Start(drv->Port);
}

/**
 *******************************************************************************
 * @brief       hal api : timer stop
 * @param       [in/out]  *drv        device block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Hal_Timer_Stop(Hal_Timer_Handle *drv)
{
    hal_assert(IS_PTR_NULL(drv));

    map_timer_api.Stop(drv->Port);
}
#endif

/** @}*/     /** hal timer component */

/**********************************END OF FILE*********************************/
