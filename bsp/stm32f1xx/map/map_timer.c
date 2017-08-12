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
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_bus.h"

#include "map_timer.h"
#include "comm_path.h"

/* Private constants ---------------------------------------------------------*/
#if USE_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief       define timer register
 *******************************************************************************
 */
static TIM_TypeDef * const Timer[] = 
{
    NULL,
    
#ifdef TIM1
    TIM1,
#endif
    
#ifdef TIM2
    TIM2,
#endif
    
#ifdef TIM3
    TIM3, 
#endif
    
#ifdef TIM4
    TIM4, 
#endif
    
#ifdef TIM5
    TIM5,
#endif
    
#ifdef TIM6
    TIM6,
#endif
    
#ifdef TIM7
    TIM7,
#endif
    
#ifdef TIM8
    TIM8,
#endif
    
#ifdef TIM9
    TIM9,
#endif
    
#ifdef TIM10
    TIM10,
#endif
    
#ifdef TIM11
    TIM11,
#endif
    
#ifdef TIM12
    TIM12,
#endif
    
#ifdef TIM13
    TIM13,
#endif
    
#ifdef TIM14
    TIM14,
#endif
    
#ifdef TIM15
    TIM15,
#endif
    
#ifdef TIM16
    TIM16,
#endif
    
#ifdef TIM17
    TIM17,
#endif
};

/**
 *******************************************************************************
 * @brief       define timer irqn
 *******************************************************************************
 */
static const IRQn_Type TimerIrqn[] = 
{
    NULL,
    
#ifdef TIM1
    TIM1_UP_IRQn, 
#endif
    
#ifdef TIM2
    TIM2_IRQn, 
#endif
    
#ifdef TIM3
    TIM3_IRQn,
#endif
    
#ifdef TIM4
    TIM4_IRQn, 
#endif
    
#ifdef TIM5
    TIM5_IRQn, 
#endif
    
#ifdef TIM6
    TIM6_IRQn, 
#endif
    
#ifdef TIM7
    TIM7_IRQn,
#endif
    
#ifdef TIM8
    TIM8_UP_IRQn,
#endif
        
#ifdef TIM9
    TIM1_BRK_TIM9_IRQn,
#endif
        
#ifdef TIM10
    TIM1_UP_TIM10_IRQn,
#endif
        
#ifdef TIM11
    TIM1_TRG_COM_TIM11_IRQn,
#endif
        
#ifdef TIM12
    TIM8_BRK_TIM12_IRQn,
#endif
        
#ifdef TIM13
    TIM8_UP_TIM13_IRQn,
#endif
        
#ifdef TIM14
    TIM8_TRG_COM_TIM14_IRQn,
#endif
        
#ifdef TIM15
    TIM1_BRK_TIM15_IRQn,
#endif
        
#ifdef TIM16
    TIM1_UP_TIM16_IRQn,
#endif
    
#ifdef TIM17
    TIM1_TRG_COM_TIM17_IRQn,
#endif
};


/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define timer time mode call back
 *******************************************************************************
 */
static struct HalCallback TimerUpCallback[_dimof(Timer)];
#endif

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define timer assert macro
 *******************************************************************************
 */
#define IS_TIMER_PORT_INVAILD(n) ((n) >= _dimof(Timer))

/* Private typedef -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if USE_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief       enable timer
 * @param       [in/out]  port            timer id
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_Timer_Open(uint8_t port)
{
    if (port == 0)
    {
        //< open tick timer clock
    }
#ifdef TIM1
	else if (port == 1)
	{
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
	}	  
#endif 
    
#ifdef TIM2
	else if (port == 2)
	{
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
	}
#endif
    
#ifdef TIM3
	else if (port == 3)
	{
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	}
#endif
    
#ifdef TIM4
	else if (port == 4)
	{
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
	} 
#endif
    
#ifdef TIM5
	else if (port == 5)
	{
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);
	} 
#endif
    
#ifdef TIM6
	else if (port == 6)
	{
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);
	} 
#endif
    
#ifdef TIM7
	else if (port == 7)
	{
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);
	} 
#endif
    
#ifdef TIM8
	else if (port == 8)
	{
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8);
	}
#endif
    
#ifdef TIM9
	else if (port == 9)
	{	   
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM9);
	 }	
#endif
    
#ifdef TIM10
	else if (port == 10)
	{	   
        LL_APB2_GRP1_EnableClockLL_APB2_GRP1_PERIPH_TIM10);
	}  
#endif
    
#if TIM11
	else if (port == 11) 
	{	  
        LL_APB2_GRP1_EnableClockLL_APB2_GRP1_PERIPH_TIM11);
	}  
#endif

#ifdef TIM12    
	else if (port == 12)
	{	   
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM12);
	}  
#endif
    
#ifdef TIM13
	else if (port == 13) 
	{		
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM13);;
	}
#endif
    
#ifdef TIM14
	else if (port == 14) 
	{		
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14);
	}		
#endif
    
#ifdef TIM15
	else if (port == 15)
	{
        LL_APB2_GRP1_EnableClockLL_APB2_GRP1_PERIPH_TIM15);
	} 
#endif
    
#ifdef TIM16
	else if (port == 16)
	{
        LL_APB2_GRP1_EnableClockLL_APB2_GRP1_PERIPH_TIM16);
	} 
#endif
    
#ifdef TIM17
	else if(port == 17)
	{
        LL_APB2_GRP1_EnableClockLL_APB2_GRP1_PERIPH_TIM17);
	}
#endif
    
    else
    {
        //< do nothing
    }
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       enable timer
 * @param       [in/out]  *dev            timer block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
__INLINE hal_err_t Hal_Timer_Open(struct Hal_Timer_Device *dev)
{
    return Map_Timer_Open(dev->Port);
}

/**
 *******************************************************************************
 * @brief       disable timer
 * @param       [in/out]  port            timer id
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_Timer_Close(uint8_t port)
{
	hal_assert(IS_TIMER_PORT_INVAILD(port));

    LL_TIM_DeInit(Timer[port]);
        
	return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       disable timer
 * @param       [in/out]  *dev            timer block
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
__INLINE hal_err_t Hal_Timer_Close(struct Hal_Timer_Device *dev)
{
    hal_assert(IS_PTR_NULL(dev));
        
    return Map_Timer_Close(dev->Port);
}

/**
 *******************************************************************************
 * @brief       init tick time mode
 * @param       [in/out]  *param          set timer param
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        This function type is static inline
 *******************************************************************************
 */
__STATIC_INLINE
void _TimerTickMode_Init(struct Hal_Timer_Param *param)
{
	uint32_t tick = MCU_CLOCK_FREQ/8000;

	//< unit: ms
	tick = tick * param->Period;
	
	SysTick->LOAD = tick - 1;  
    _CLEAR_REG(SysTick->VAL);                                              
    NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); 

	//< enable tick timer isr and set tick timer clock source is core clock
    SysTick->CTRL  = (uint32_t)((1 << 1) | (1 << 2));

	TimerUpCallback[0].Callback = param->Callback.Callback;
	TimerUpCallback[0].Param    = param->Callback.Param;
}

/**
 *******************************************************************************
 * @brief       init timer time mode
 * @param       [in/out]  port            timer id
 * @param       [in/out]  *param          set timer param
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        This function type is static inline
 *******************************************************************************
 */
__STATIC_INLINE
void _TimerTimeMode_Init(uint8_t port, struct Hal_Timer_Param *param)
{
	LL_TIM_InitTypeDef LL_TIM_InitStructure;

    LL_TIM_InitStructure.Autoreload = param->Period;
    LL_TIM_InitStructure.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    LL_TIM_InitStructure.CounterMode = LL_TIM_COUNTERMODE_UP;
    LL_TIM_InitStructure.Prescaler = param->Prescaler;

    LL_TIM_DeInit(Timer[port]);
    LL_TIM_Init(Timer[port], &LL_TIM_InitStructure);
    LL_TIM_EnableARRPreload(Timer[port]);
    LL_TIM_ClearFlag_UPDATE(Timer[port]);
    LL_TIM_EnableIT_UPDATE(Timer[port]);
    
    NVIC_EnableIRQ(TimerIrqn[port]); 
    NVIC_SetPriority(TimerIrqn[port], param->Priority);  

	TimerUpCallback[port].Callback = param->Callback.Callback;
	TimerUpCallback[port].Param    = param->Callback.Param;
    
    LL_TIM_EnableCounter(Timer[port]);
}

/**
 *******************************************************************************
 * @brief       init timer function
 * @param       [in/out]  port            timer id
 * @param       [in/out]  mode            set timer mode
 * @param       [in/out]  *param          set timer param
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_Timer_Init(uint8_t port, uint8_t mode, void *param)
{
	hal_assert(IS_TIMER_PORT_INVAILD(port));
	hal_assert(IS_PTR_NULL(param));

	switch(mode)
	{
		case TIMER_TICK_MODE:
			_TimerTickMode_Init((struct Hal_Timer_Param*)param);
			break;
		case TIMER_TIME_MODE:
			_TimerTimeMode_Init(port, (struct Hal_Timer_Param*)param);
			break;
		case TIMER_PWM_OUTPUT_MODE:
			return HAL_ERR_FAIL;
//			break;
		case TIMER_PWM_INTPUT_MODE:
			return HAL_ERR_FAIL;
//			break;
		default:
            break;
	}
	
	return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       init timer
 * @param       [in/out]  *dev            timer block
 * @return      [in/out]  HAL_ERR_NONE    init finish
 * @note        None
 *******************************************************************************
 */
__INLINE hal_err_t Hal_Timer_Init(struct Hal_Timer_Device *dev)
{
    struct Hal_Timer_Param config;
    
    config.Period            = dev->Period;
    config.Prescaler         = dev->Prescaler;
    config.Callback.Callback = dev->Callback.Callback;
    config.Callback.Param    = dev->Callback.Param;
    
    return Map_Timer_Init(dev->Port, dev->SetMode, (void *)&config);
}

/**
 *******************************************************************************
 * @brief       set timer call back function
 * @param       [in/out]  port            timer id
 * @param       [in/out]  callback        call back function
 * @param       [in/out]  *param          call back function param
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_Timer_SetUpCallback(uint8_t port, void (*callback)(void*), void *param)
{
    hal_assert(IS_TIMER_PORT_INVAILD(port));
    
    TimerUpCallback[port].Callback = callback;
	TimerUpCallback[port].Param    = param;
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       init timer
 * @param       [in/out]  *dev            timer block
 * @return      [in/out]  HAL_ERR_NONE    init finish
 * @note        None
 *******************************************************************************
 */
__INLINE hal_err_t Hal_Timer_SetUpCallback(struct Hal_Timer_Device *dev)
{
    return Map_Timer_SetUpCallback(dev->Port, 
                                   dev->Callback.Callback, 
                                   dev->Callback.Param);
}

/**
 *******************************************************************************
 * @brief       start timer function
 * @param       [in/out]  port            timer id
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_Timer_Start(uint8_t port)
{
	hal_assert(IS_TIMER_PORT_INVAILD(port));

	if(port != 0)
	{
		Timer[port]->CR1 |= 0x01;
	}
	else
	{
		SysTick->CTRL |= 0x01;
	}

	return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       start timer
 * @param       [in/out]  *dev            timer block
 * @return      [in/out]  HAL_ERR_NONE    init finish
 * @note        None
 *******************************************************************************
 */
__INLINE hal_err_t Hal_Timer_Start(struct Hal_Timer_Device *dev)
{
    return Map_Timer_Start(dev->Port);
}

/**
 *******************************************************************************
 * @brief       stop timer function
 * @param       [in/out]  port            timer id
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
hal_err_t Map_Timer_Stop(uint8_t port)
{
	hal_assert(IS_TIMER_PORT_INVAILD(port));

	if(port != 0)
	{
		Timer[port]->CR1 &= ~0x01;
	}
	else
	{
		SysTick->CTRL &= ~0x01;
	}

	return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       stop timer
 * @param       [in/out]  *dev            timer block
 * @return      [in/out]  HAL_ERR_NONE    init finish
 * @note        None
 *******************************************************************************
 */
__INLINE hal_err_t Hal_Timer_Stop(struct Hal_Timer_Device *dev)
{
    return Map_Timer_Stop(dev->Port);
}
/**
 *******************************************************************************
 * @brief       tick timer isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
void SysTick_Handler(void)
{
	if(!IS_PTR_NULL(TimerUpCallback[0].Callback))
	{
		TimerUpCallback[0].Callback(TimerUpCallback[0].Param);
	}
}

/**
 *******************************************************************************
 * @brief       timer1 isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
#ifdef TIM1
void TIM1_UP_IRQHandler(void)
{
	if(!IS_PTR_NULL(TimerUpCallback[1].Callback))
	{
		TimerUpCallback[1].Callback(TimerUpCallback[1].Param);
	}

	Timer[1]->SR &= ~0x01;
}
#endif

/**
 *******************************************************************************
 * @brief       timer2 isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
#ifdef TIM2
void TIM2_IRQHandler(void)
{
	if(Timer[2]->SR & 0x01)
	{
		if(!IS_PTR_NULL(TimerUpCallback[2].Callback))
		{
			TimerUpCallback[2].Callback(TimerUpCallback[2].Param);
		}
		
		Timer[2]->SR &= ~0x01;
	}
}
#endif

/**
 *******************************************************************************
 * @brief       timer3 isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
#ifdef TIM3
void TIM3_IRQHandler(void)
{
	if(Timer[3]->SR & 0x01)
	{
		if(!IS_PTR_NULL(TimerUpCallback[3].Callback))
		{
			TimerUpCallback[3].Callback(TimerUpCallback[3].Param);
		}
		
		Timer[3]->SR &= ~0x01;
	}
}
#endif

/**
 *******************************************************************************
 * @brief       timer4 isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
#ifdef TIM4
void TIM4_IRQHandler(void)
{
	if(Timer[4]->SR & 0x01)
	{
		if(!IS_PTR_NULL(TimerUpCallback[4].Callback))
		{
			TimerUpCallback[4].Callback(TimerUpCallback[4].Param);
		}
		
		Timer[4]->SR &= ~0x01;
	}
}
#endif

/**
 *******************************************************************************
 * @brief       timer5 isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
#ifdef TIM5
void TIM5_IRQHandler(void)
{
	if(Timer[5]->SR & 0x01)
	{
		if(!IS_PTR_NULL(TimerUpCallback[5].Callback))
		{
			TimerUpCallback[5].Callback(TimerUpCallback[5].Param);
		}
		
		Timer[5]->SR &= ~0x01;
	}
}
#endif

/**
 *******************************************************************************
 * @brief       timer6 isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
#ifdef TIM6
void TIM6_IRQHandler(void)
{
	if(Timer[6]->SR & 0x01)
	{
		if(!IS_PTR_NULL(TimerUpCallback[6].Callback))
		{
			TimerUpCallback[6].Callback(TimerUpCallback[6].Param);
		}
		
		Timer[6]->SR &= ~0x01;
	}
}
#endif

/**
 *******************************************************************************
 * @brief       timer7 isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
#ifdef TIM7
void TIM7_IRQHandler(void)
{
	if(Timer[7]->SR & 0x01)
	{
		if(!IS_PTR_NULL(TimerUpCallback[7].Callback))
		{
			TimerUpCallback[7].Callback(TimerUpCallback[7].Param);
		}
		
		Timer[7]->SR &= ~0x01;
	}
}
#endif

/**
 *******************************************************************************
 * @brief       timer8 isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
#ifdef TIM8
void TIM8_UP_IRQHandler(void)
{
	if(!IS_PTR_NULL(TimerUpCallback[8].Callback))
	{
		TimerUpCallback[8].Callback(TimerUpCallback[8].Param);
	}

	Timer[8]->SR &= ~0x01;
}
#endif

#endif

/** @}*/     /** map timer component */

/**********************************END OF FILE*********************************/
