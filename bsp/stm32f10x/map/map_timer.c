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
#include "stm32f10x.h"
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
};

/**
 *******************************************************************************
 * @brief       define timer irqn
 *******************************************************************************
 */
static const IRQn_Type TimerIrqn[] = 
{
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
};

/**
 *******************************************************************************
 * @brief      define map api
 *******************************************************************************
 */ 
void Map_Timer_Open(uint8_t);
void Map_Timer_Close(uint8_t);
void Map_Timer_Init(uint8_t, void*);
void Map_Timer_Fini(uint8_t);
void Map_Timer_SetUpCallback(uint8_t, void (*)(void*), void*);
void Map_Timer_Start(uint8_t);
void Map_Timer_Stop(uint8_t);

const struct Map_Timer_Opera map_timer_api = 
{
    .Open = Map_Timer_Open,
    .Close = Map_Timer_Close, 
    
    .Init = Map_Timer_Init,
    .Fini = Map_Timer_Fini,
    .SetUpCallback = Map_Timer_SetUpCallback,
    
    .Start = Map_Timer_Start,
    .Stop = Map_Timer_Stop,
};
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define timer time mode call back
 *******************************************************************************
 */
static struct Hal_Callback TimerUpCallback[_dimof(Timer)];
#endif

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define timer assert macro
 *******************************************************************************
 */
#define IS_TIMER_PORT_INVAILD(n)                          ((n) >= _dimof(Timer))

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
void Map_Timer_Open(uint8_t port)
{
    hal_assert(IS_TIMER_PORT_INVAILD(port));
    
    if (port == 0)
    {
        //< open tick timer clock
    }
	else if (port == 1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
	}	  
	else if (port == 2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}
	else if (port == 3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	}
	else if (port == 4)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	} 
	else if (port == 5)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	
	} 
	else if (port == 6)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	} 
	else if (port == 7)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	} 
	else if (port == 8)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	}
	else if (port == 9)
	{	   
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	 }	
	else if (port == 10)
	{	   
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE); 
	}  
	else if (port == 11) 
	{	  
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);  
	}  
	else if (port == 12)
	{	   
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
	}  
	else if (port == 13) 
	{		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
	}
	else if (port == 14) 
	{		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	}		 
	else if (port == 15)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);
	} 
	else if (port == 16)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);
	} 
	else
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE);
	}
}

/**
 *******************************************************************************
 * @brief       disable timer
 * @param       [in/out]  port            timer id
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_Timer_Close(uint8_t port)
{
	hal_assert(IS_TIMER_PORT_INVAILD(port));

	if (port == 1)
	{
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, ENABLE);
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, DISABLE);  
	}	  
	else if (port == 2)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, DISABLE);
	}
	else if (port == 3)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, DISABLE);
	}
	else if (port == 4)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, DISABLE);
	} 
	else if (port == 5)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, DISABLE);
	} 
	else if (port == 6)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, DISABLE);
	} 
	else if (port == 7)
	{
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, DISABLE);
	} 
	else if (port == 8)
	{
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, ENABLE);
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, DISABLE);
	}
	else if (port == 9)
	{	   
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM9, ENABLE);
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM9, DISABLE);  
	 }	
	else if (port == 10)
	{	   
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM10, ENABLE);
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM10, DISABLE);  
	}  
	else if (port == 11) 
	{	  
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM11, ENABLE);
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM11, DISABLE);  
	}  
	else if (port == 12)
	{	   
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM12, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM12, DISABLE);  
	}  
	else if (port == 13) 
	{		
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM13, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM13, DISABLE);  
	}
	else if (port == 14) 
	{		
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM14, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM14, DISABLE);  
	}		 
	else if (port == 15)
	{
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM15, ENABLE);
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM15, DISABLE);
	} 
	else if (port == 16)
	{
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM16, ENABLE);
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM16, DISABLE);
	} 
	else
	{
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM17, ENABLE);
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM17, DISABLE);
	}
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
void _TimerTickMode_Init(Hal_Timer_Handle *param)
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
void _TimerTimeMode_Init(uint8_t port, Hal_Timer_Handle *param)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;
    
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = param->Period;
	TIM_TimeBaseInitStruct.TIM_Prescaler = param->Prescaler;

	TIM_DeInit(Timer[port]);
	TIM_TimeBaseInit(Timer[port], &TIM_TimeBaseInitStruct);
	TIM_ARRPreloadConfig(Timer[port], ENABLE);
	TIM_ClearITPendingBit(Timer[port], TIM_IT_Update);
	TIM_ITConfig(Timer[port], TIM_IT_Update, ENABLE);
    
    NVIC_InitStructure.NVIC_IRQChannel = TimerIrqn[port];
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
	TIM_Cmd(Timer[port], ENABLE);

	TimerUpCallback[port].Callback = param->Callback.Callback;
	TimerUpCallback[port].Param    = param->Callback.Param;
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
void Map_Timer_Init(uint8_t port, void *param)
{
	hal_assert(IS_TIMER_PORT_INVAILD(port));
	hal_assert(IS_PTR_NULL(param));

    Hal_Timer_Handle *config = (Hal_Timer_Handle*)param;
    
	switch(config->Mode)
	{
		case TIMER_TICK_MODE:
			_TimerTickMode_Init(config);
			break;
		case TIMER_TIME_MODE:
			_TimerTimeMode_Init(port, config);
			break;
		case TIMER_PWM_OUTPUT_MODE:
			break;
		case TIMER_PWM_INTPUT_MODE:
			break;
		default:
            break;
	}
}

/**
 *******************************************************************************
 * @brief       deinit timer function
 * @param       [in/out]  port            timer id
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Map_Timer_Fini(uint8_t port)
{
	hal_assert(IS_TIMER_PORT_INVAILD(port));

    TIM_DeInit(Timer[port]);
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
void Map_Timer_SetUpCallback(uint8_t port, void (*callback)(void*), void *param)
{
    hal_assert(IS_TIMER_PORT_INVAILD(port));
    
    TimerUpCallback[port].Callback = callback;
	TimerUpCallback[port].Param    = param;
}

/**
 *******************************************************************************
 * @brief       start timer function
 * @param       [in/out]  port            timer id
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_Timer_Start(uint8_t port)
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
}

/**
 *******************************************************************************
 * @brief       stop timer function
 * @param       [in/out]  port            timer id
 * @return      [in/out]  HAL_ERR_NONE    set finish
 * @note        None
 *******************************************************************************
 */
void Map_Timer_Stop(uint8_t port)
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
}

/**
 *******************************************************************************
 * @brief       mcu timer api register
 * @param       [in/out]  **ops                   timer opera
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Map_Timer_API_Register(void **ops)
{
    hal_assert(IS_PTR_NULL(ops));
    
    *ops = (void *)&map_timer_api;
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
	if(!IS_PTR_NULL(TimerUpCallback[MCU_TICK_TIMER].Callback))
	{
		TimerUpCallback[MCU_TICK_TIMER].Callback(TimerUpCallback[MCU_TICK_TIMER].Param);
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
void TIM1_UP_IRQHandler(void)
{
	if(!IS_PTR_NULL(TimerUpCallback[MCU_TIMER_1].Callback))
	{
		TimerUpCallback[MCU_TIMER_1].Callback(TimerUpCallback[MCU_TIMER_1].Param);
	}

	Timer[1]->SR &= ~0x01;
}

/**
 *******************************************************************************
 * @brief       timer2 isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
void TIM2_IRQHandler(void)
{
	if(Timer[2]->SR & 0x01)
	{
		if(!IS_PTR_NULL(TimerUpCallback[MCU_TIMER_2].Callback))
		{
			TimerUpCallback[MCU_TIMER_2].Callback(TimerUpCallback[MCU_TIMER_2].Param);
		}
		
		Timer[2]->SR &= ~0x01;
	}
}

/**
 *******************************************************************************
 * @brief       timer3 isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
void TIM3_IRQHandler(void)
{
	if(Timer[3]->SR & 0x01)
	{
		if(!IS_PTR_NULL(TimerUpCallback[MCU_TIMER_3].Callback))
		{
			TimerUpCallback[MCU_TIMER_3].Callback(TimerUpCallback[MCU_TIMER_3].Param);
		}
		
		Timer[3]->SR &= ~0x01;
	}
}

/**
 *******************************************************************************
 * @brief       timer4 isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
void TIM4_IRQHandler(void)
{
	if(Timer[4]->SR & 0x01)
	{
		if(!IS_PTR_NULL(TimerUpCallback[MCU_TIMER_4].Callback))
		{
			TimerUpCallback[MCU_TIMER_4].Callback(TimerUpCallback[MCU_TIMER_4].Param);
		}
		
		Timer[4]->SR &= ~0x01;
	}
}

/**
 *******************************************************************************
 * @brief       timer5 isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
void TIM5_IRQHandler(void)
{
	if(Timer[5]->SR & 0x01)
	{
		if(!IS_PTR_NULL(TimerUpCallback[MCU_TIMER_5].Callback))
		{
			TimerUpCallback[MCU_TIMER_5].Callback(TimerUpCallback[MCU_TIMER_5].Param);
		}
		
		Timer[5]->SR &= ~0x01;
	}
}

/**
 *******************************************************************************
 * @brief       timer6 isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
void TIM6_IRQHandler(void)
{
	if(Timer[6]->SR & 0x01)
	{
		if(!IS_PTR_NULL(TimerUpCallback[MCU_TIMER_6].Callback))
		{
			TimerUpCallback[MCU_TIMER_6].Callback(TimerUpCallback[MCU_TIMER_6].Param);
		}
		
		Timer[6]->SR &= ~0x01;
	}
}

/**
 *******************************************************************************
 * @brief       timer7 isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
void TIM7_IRQHandler(void)
{
	if(Timer[7]->SR & 0x01)
	{
		if(!IS_PTR_NULL(TimerUpCallback[MCU_TIMER_7].Callback))
		{
			TimerUpCallback[MCU_TIMER_7].Callback(TimerUpCallback[MCU_TIMER_7].Param);
		}
		
		Timer[7]->SR &= ~0x01;
	}
}

/**
 *******************************************************************************
 * @brief       timer8 isr handle
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        This function type is interrupt handle
 *******************************************************************************
 */
void TIM8_UP_IRQHandler(void)
{
	if(!IS_PTR_NULL(TimerUpCallback[MCU_TIMER_8].Callback))
	{
		TimerUpCallback[MCU_TIMER_8].Callback(TimerUpCallback[MCU_TIMER_8].Param);
	}

	Timer[8]->SR &= ~0x01;
}
#endif

/** @}*/     /** map timer component */

/**********************************END OF FILE*********************************/
