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
 * @file       map_timer.c                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-08-08                                                      *
 * @brief      mcu timer application component source files                    *
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
 * @defgroup map timer component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"
#include "hal_path.h"
#include <string.h>
#include "map_timer.h"

/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef USE_HAL_TIMER
#ifdef USE_HAL_TIMER0
uint8_t htim0;
Hal_Callback_t TIM0_Tick_Callback;
#endif
#endif

#ifdef USE_HAL_TIMER
static void *Map_Timer_Find(char*);
static hal_err_t Map_Timer_Init(void*, uint32_t);
static hal_err_t Map_Timer_Fini(void*);
static uint16_t Map_Timer_Write(void*, uint8_t, uint8_t*, uint16_t);
static uint16_t Map_Timer_Read(void*, uint8_t, uint8_t* , uint16_t);
static hal_err_t Map_Timer_Control(void*, uint8_t, va_list);

const struct Hal_Interface Map_Timer_Interface = 
{
    .Open = Map_Timer_Find,
    .Init = Map_Timer_Init,
    .Fini = Map_Timer_Fini,
    .Write = Map_Timer_Write, 
    .Read = Map_Timer_Read,
    .Control = Map_Timer_Control,
};
#endif

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
#ifdef USE_HAL_TIMER
/**
 *******************************************************************************
 * @brief       systick timer config
 *******************************************************************************
 */
#ifdef USE_HAL_TIMER0
__STATIC_INLINE
void Hal_SysTick_Init(void)
{
    uint32_t tick = MCU_CLOCK_FREQ/8000;
    //< unit: ms
    tick = tick * HAL_TIM0_PERIOD;
    
    SysTick->LOAD = tick - 1;  
    _CLEAR_REG(SysTick->VAL);                                              
    NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); 
    //< enable tick timer isr and set tick timer clock source is core clock
    SysTick->CTRL  = (uint32_t)((1 << 1) | (1 << 2));
}

void Hal_SysTick_Fini(void)
{
    HAL_NVIC_DisableIRQ(SysTick_IRQn);
    
    //< disable tick timer isr and set tick timer clock source is core clock
    SysTick->CTRL  &= ~(uint32_t)((1 << 1) | (1 << 2));
}
#endif

/**
 *******************************************************************************
 * @brief       timer call back set function
 *******************************************************************************
 */
__STATIC_INLINE
void Map_Set_Timer_Callback(void *drv, void *func, void *param)
{
#ifdef USE_HAL_TIMER0
    if(drv == (void *)&htim0)
    {
        TIM0_Tick_Callback.Function = func;
        TIM0_Tick_Callback.Param = param;
    }
#endif
}    

/**
 *******************************************************************************
 * @brief       hal device api
 *******************************************************************************
 */
static void *Map_Timer_Find(char *s)
{
#ifdef USE_HAL_TIMER0
    if(memcmp(s, "systick", strlen("systick")) == 0)
    {
        return (void *)&htim0;
    }
#endif
    
    return NULL;
}

static hal_err_t Map_Timer_Init(void *dev, uint32_t flag)
{
//    hTimFlag hFlag;
//    hFlag.Flag = flag;

#ifdef USE_HAL_TIMER0
    if(dev == (void *)&htim0)
    {
        Hal_SysTick_Init();
        return HAL_ERR_NONE;
    }
#endif

    return HAL_ERR_FAIL;
}

static hal_err_t Map_Timer_Fini(void *dev)
{
#ifdef USE_HAL_TIMER0
    if(dev == (void *)&htim0)
    {
        Hal_SysTick_Fini();
        return HAL_ERR_NONE;
    }
#endif

    return HAL_ERR_FAIL;
}

static uint16_t Map_Timer_Write(void *dev, uint8_t pos, uint8_t *buf, uint16_t size)
{
    return 0;
}

static uint16_t Map_Timer_Read(void *dev, uint8_t pos, uint8_t *buf, uint16_t size)
{
    return 0;
}

static hal_err_t Map_Timer_Control(void *drv, uint8_t cmd, va_list args)
{
    hal_assert(IS_PTR_NULL(drv));
    
    switch(cmd)
    {
        case HAL_DEVICE_SET_CALLBACK_CMD:
        {
            void *func = va_arg(args, void*);
            void *param = va_arg(args, void*);
            Map_Set_Timer_Callback(drv, func, param);
            break;
        }
        default:
            break;
    }
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       systick isr handler
 *******************************************************************************
 */
#ifdef USE_HAL_TIMER0
void SysTick_Handle(void)
{
    if (!IS_PTR_NULL(TIM0_Tick_Callback.Function))
    {
        TIM0_Tick_Callback.TimeOut(TIM0_Tick_Callback.Param);
    }
}
#endif

#endif

/* Exported functions --------------------------------------------------------*/
#ifdef USE_HAL_TIMER
void Map_Timer_InitComponent(void)
{
    Hal_Device_Register(HAL_DEVICE_TIMER, (struct Hal_Interface *)&Map_Timer_Interface);
}
#endif

/** @}*/     /** map timer component */

/**********************************END OF FILE*********************************/
