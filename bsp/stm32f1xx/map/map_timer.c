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
TIM_HandleTypeDef htim1;
Hal_Callback_t TIM1_Tick_Callback;

TIM_HandleTypeDef htim2;
Hal_Callback_t TIM2_Tick_Callback;
TIM_HandleTypeDef htim3;
Hal_Callback_t TIM3_Tick_Callback;
TIM_HandleTypeDef htim4;
Hal_Callback_t TIM4_Tick_Callback;
TIM_HandleTypeDef htim5;
Hal_Callback_t TIM5_Tick_Callback;
TIM_HandleTypeDef htim6;
Hal_Callback_t TIM6_Tick_Callback;
TIM_HandleTypeDef htim7;
Hal_Callback_t TIM7_Tick_Callback;
TIM_HandleTypeDef htim8;
Hal_Callback_t TIM8_Tick_Callback;

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void Hal_TIM_Tick_Init(TIM_HandleTypeDef *htim, TIM_TypeDef *tim)
{
    TIM_MasterConfigTypeDef sMasterConfig;

    htim->Instance = tim;
    htim->Init.CounterMode = TIM_COUNTERMODE_UP;
    htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

    if(tim == TIM1)
    {
        __HAL_RCC_TIM1_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
        
        HAL_NVIC_SetPriority(TIM1_UP_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
    }
#ifdef TIM2
    else if(tim == TIM2)
    {
        __HAL_RCC_TIM2_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
        
        HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(TIM12_IRQn);
    }
#endif
    
#ifdef TIM3
    else if(tim == TIM3)
    {
        __HAL_RCC_TIM3_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
                
        HAL_NVIC_SetPriority(TIM3_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(TIM13_IRQn);
    }
#endif
    
#ifdef TIM4
    else if(tim == TIM4)
    {
        __HAL_RCC_TIM4_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
                
        HAL_NVIC_SetPriority(TIM4_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(TIM14_IRQn);
    }
#endif
    
#ifdef TIM5
    else if(tim == TIM5)
    {
        __HAL_RCC_TIM5_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
                
        HAL_NVIC_SetPriority(TIM5_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(TIM5_IRQn);
    }
#endif
    
#ifdef TIM6
    else if(tim == TIM6)
    {
        __HAL_RCC_TIM6_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
                
        HAL_NVIC_SetPriority(TIM6_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(TIM6_IRQn);
    }
#endif
    
#ifdef TIM7
    else if(tim == TIM7)
    {
        __HAL_RCC_TIM7_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
                
        HAL_NVIC_SetPriority(TIM7_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(TIM7_IRQn);
    }
#endif
    
#ifdef TIM8
    else if(tim == TIM8)
    {
        __HAL_RCC_TIM8_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
                
        HAL_NVIC_SetPriority(TIM8_UP_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(TIM8_UP_IRQn);
    }
#endif
    
    HAL_TIM_Base_Init(htim);

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig);
}

void Hal_TIM_PWM_Base_Init(TIM_HandleTypeDef *htim, TIM_TypeDef *tim)
{
    htim->Instance = tim;
    htim->Init.CounterMode = TIM_COUNTERMODE_UP;
    htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

    if(tim == TIM1)
    {
        __HAL_RCC_TIM1_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
    }
#ifdef TIM2
    else if(tim == TIM2)
    {
        __HAL_RCC_TIM2_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
    }
#endif
    
#ifdef TIM3
    else if(tim == TIM3)
    {
        __HAL_RCC_TIM3_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
    }
#endif
    
#ifdef TIM4
    else if(tim == TIM4)
    {
        __HAL_RCC_TIM4_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
    }
#endif
    
#ifdef TIM5
    else if(tim == TIM5)
    {
        __HAL_RCC_TIM5_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
    }
#endif
    
#ifdef TIM6
    else if(tim == TIM6)
    {
        __HAL_RCC_TIM6_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
    }
#endif
    
#ifdef TIM7
    else if(tim == TIM7)
    {
        __HAL_RCC_TIM7_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
    }
#endif
    
#ifdef TIM8
    else if(tim == TIM8)
    {
        __HAL_RCC_TIM8_CLK_ENABLE();
        
        htim->Init.Prescaler = 72;
        htim->Init.Period = 999;
    }
#endif
    
    HAL_TIM_PWM_Init(htim);
}


void Hal_TIM_PWM_Output_Port_Init(TIM_HandleTypeDef *htim_pwm, TIM_TypeDef *tim, uint8_t ch)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    
    if(tim == TIM1)
    {
        __HAL_RCC_TIM1_CLK_ENABLE();
        __HAL_RCC_GPIOE_CLK_ENABLE();
        /**TIM1 GPIO Configuration    
        PE9     ------> TIM1_CH1
        PE11     ------> TIM1_CH2
        PE13     ------> TIM1_CH3
        PE14     ------> TIM1_CH4 
        */
        if(ch == 0)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_9;
        }
        else if(ch == 1)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_11;
        }
        else if(ch == 2)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_13;
        }
        else if(ch == 3)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_14;
        }
        else
        {
            //< do nothing!
        }
        
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
        
        __HAL_AFIO_REMAP_TIM1_ENABLE();
    }
#ifdef TIM2
    else if(tim == TIM2)
    {
        __HAL_RCC_TIM2_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        
        /**TIM2 GPIO Configuration    
        PB10     ------> TIM2_CH3
        PB11     ------> TIM2_CH4
        PA15     ------> TIM2_CH1
        PB3     ------> TIM2_CH2 
        */
        if(ch == 0)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_10;
            HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        }
        else if(ch == 1)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_11;
            HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        }
        else if(ch == 2)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_3;
            HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        }
        else if(ch == 3)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_15;
            HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        }
        else
        {
            //< do nothing!
        }

        __HAL_AFIO_REMAP_TIM2_ENABLE();
    }
#endif
    
#ifdef TIM3
    else if(tim == TIM3)
    {
        __HAL_RCC_TIM3_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**TIM3 GPIO Configuration    
        PA6     ------> TIM3_CH1
        PA7     ------> TIM3_CH2
        PB0     ------> TIM3_CH3
        PB1     ------> TIM3_CH4 
        */
        if(ch == 0)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_6;
            HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        }
        else if(ch == 1)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_7;
            HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        }
        else if(ch == 2)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_0;
            HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        }
        else if(ch == 3)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_1;
            HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        }
        else
        {
            //< do nothing!
        }
    }
#endif
    
#ifdef TIM4
    else if(tim == TIM4)
    {
        __HAL_RCC_TIM4_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        /**TIM4 GPIO Configuration    
        PD12     ------> TIM4_CH1
        PD13     ------> TIM4_CH2
        PD14     ------> TIM4_CH3
        PD15     ------> TIM4_CH4 
        */
        if(ch == 0)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_12;
        }
        else if(ch == 1)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_13;
        }
        else if(ch == 2)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_14;
        }
        else if(ch == 3)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_15;
        }
        else
        {
            //< do nothing!
        }
        
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

        __HAL_AFIO_REMAP_TIM4_ENABLE();
        
    }
#endif
    
#ifdef TIM5
    else if(tim == TIM5)
    {
        __HAL_RCC_TIM5_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**TIM5 GPIO Configuration    
        PA0-WKUP     ------> TIM5_CH1
        PA1     ------> TIM5_CH2
        PA2     ------> TIM5_CH3
        PA3     ------> TIM5_CH4 
        */
        if(ch == 0)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_0;
        }
        else if(ch == 1)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_1;
        }
        else if(ch == 2)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_2;
        }
        else if(ch == 3)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_3;
        }
        else
        {
            //< do nothing!
        }
        
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
    }
#endif
    
#ifdef TIM8
    else if(tim == TIM8)
    {
        __HAL_RCC_TIM8_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        /**TIM8 GPIO Configuration    
        PC6     ------> TIM8_CH1
        PC7     ------> TIM8_CH2
        PC8     ------> TIM8_CH3
        PC9     ------> TIM8_CH4 
        */
        if(ch == 0)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_6;
        }
        else if(ch == 1)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_7;
        }
        else if(ch == 2)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_8;
        }
        else if(ch == 3)
        {
            GPIO_InitStruct.Pin = GPIO_PIN_9;
        }
        else
        {
            //< do nothing!
        }
        
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    }
#endif
}

void HAL_TIM_PWM_Output_Init(TIM_HandleTypeDef *htim_pwm, TIM_TypeDef *tim, uint8_t ch)
{

    TIM_OC_InitTypeDef sConfigOC;
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;
    
    htim_pwm->Instance = tim;
    
    Hal_TIM_PWM_Base_Init(htim_pwm, tim);
    
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    
    if(ch == 0)
    {
        HAL_TIM_PWM_ConfigChannel(htim_pwm, &sConfigOC, TIM_CHANNEL_1);
    }
    else if(ch == 1)
    {
        HAL_TIM_PWM_ConfigChannel(htim_pwm, &sConfigOC, TIM_CHANNEL_2);
    }
    else if(ch == 2)
    {
        HAL_TIM_PWM_ConfigChannel(htim_pwm, &sConfigOC, TIM_CHANNEL_3);
    }
    else if(ch == 3)
    {
        HAL_TIM_PWM_ConfigChannel(htim_pwm, &sConfigOC, TIM_CHANNEL_4);
    }
    else
    {
        //< do nothing!
    } 

    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    HAL_TIMEx_ConfigBreakDeadTime(htim_pwm, &sBreakDeadTimeConfig);
    
    Hal_TIM_PWM_Output_Port_Init(htim_pwm, tim, ch);
    
//    if(ch == 1)
//    {
//        HAL_TIM_PWM_Start(htim_pwm, TIM_CHANNEL_1);
//    }
//    else if(ch == 2)
//    {
//        HAL_TIM_PWM_Start(htim_pwm, TIM_CHANNEL_2);
//    }
//    else if(ch == 3)
//    {
//        HAL_TIM_PWM_Start(htim_pwm, TIM_CHANNEL_3);
//    }
//    else if(ch == 4)
//    {
//        HAL_TIM_PWM_Start(htim_pwm, TIM_CHANNEL_4);
//    }
//    else
//    {
//        //< do nothing!
//    } 
}

static void *Map_Timer_Find(char *s)
{

    if(memcmp(s, "timer1", strlen("timer1")) == 0)
    {
        return (void *)&htim1;
    }

    if(memcmp(s, "timer2", strlen("timer2")) == 0)
    {
        return (void *)&htim2;
    }

    if(memcmp(s, "timer3", strlen("timer3")) == 0)
    {
        return (void *)&htim3;
    }

    if(memcmp(s, "timer4", strlen("timer4")) == 0)
    {
        return (void *)&htim4;
    }
    
    if(memcmp(s, "timer5", strlen("timer5")) == 0)
    {
        return (void *)&htim1;
    }

    if(memcmp(s, "timer6", strlen("timer6")) == 0)
    {
        return (void *)&htim2;
    }

    if(memcmp(s, "timer7", strlen("timer7")) == 0)
    {
        return (void *)&htim3;
    }

    if(memcmp(s, "timer8", strlen("timer8")) == 0)
    {
        return (void *)&htim4;
    }
 
    return NULL;
}

static hal_err_t Map_Timer_Init(void *dev, uint32_t flag)
{
    hTimFlag hFlag;
    hFlag.Flag = flag;
    
    if(dev == (void *)&htim1)
    {
        if(hFlag.Mode == 0)
        {
            Hal_TIM_Tick_Init(&htim1, TIM1);
        }
        else if(hFlag.Mode == 1)
        {
            HAL_TIM_PWM_Output_Init(&htim1, TIM1, hFlag.Channel);
        }
        else
        {
            //< do nothing!
        }
        return HAL_ERR_NONE;
    } 

    if(dev == (void *)&htim2)
    {
        if(hFlag.Mode == 0)
        {
            Hal_TIM_Tick_Init(&htim2, TIM2);
        }
        else if(hFlag.Mode == 1)
        {
            HAL_TIM_PWM_Output_Init(&htim2, TIM2, hFlag.Channel);
        }
        else
        {
            //< do nothing!
        }
        return HAL_ERR_NONE;
    }

    if(dev == (void *)&htim3)
    {
        if(hFlag.Mode == 0)
        {
            Hal_TIM_Tick_Init(&htim3, TIM3);
        }
        else if(hFlag.Mode == 1)
        {
            HAL_TIM_PWM_Output_Init(&htim3, TIM3, hFlag.Channel);
        }
        else
        {
            //< do nothing!
        }
        return HAL_ERR_NONE;
    }

    if(dev == (void *)&htim4)
    {
        if(hFlag.Mode == 0)
        {
            Hal_TIM_Tick_Init(&htim4, TIM4);
        }
        else if(hFlag.Mode == 1)
        {
            HAL_TIM_PWM_Output_Init(&htim4, TIM4, hFlag.Channel);
        }
        else
        {
            //< do nothing!
        }
        return HAL_ERR_NONE;
    }

    if(dev == (void *)&htim5)
    {
        if(hFlag.Mode == 0)
        {
            Hal_TIM_Tick_Init(&htim5, TIM5);
        }
        else if(hFlag.Mode == 1)
        {
            HAL_TIM_PWM_Output_Init(&htim5, TIM5, hFlag.Channel);
        }
        else
        {
            //< do nothing!
        }
        return HAL_ERR_NONE;
    }

    if(dev == (void *)&htim6)
    {
        if(hFlag.Mode == 0)
        {
            Hal_TIM_Tick_Init(&htim6, TIM6);
        }
        else
        {
            //< do nothing!
        }
        return HAL_ERR_NONE;
    }

    if(dev == (void *)&htim7)
    {
        if(hFlag.Mode == 0)
        {
            Hal_TIM_Tick_Init(&htim7, TIM7);
        }
        else
        {
            //< do nothing!
        }
        return HAL_ERR_NONE;
    }

    if(dev == (void *)&htim8)
    {
        if(hFlag.Mode == 0)
        {
            Hal_TIM_Tick_Init(&htim8, TIM8);
        }
        else if(hFlag.Mode == 1)
        {
            HAL_TIM_PWM_Output_Init(&htim8, TIM8, hFlag.Channel);
        }
        else
        {
            //< do nothing!
        }
        return HAL_ERR_NONE;
    }    

    return HAL_ERR_FAIL;
}

hal_err_t Hal_TIM_Fini(TIM_HandleTypeDef* htim)
{
    if(htim->Instance==TIM1)
    {
        __HAL_RCC_TIM1_CLK_DISABLE();
    }
    else if(htim->Instance==TIM2)
    {
        __HAL_RCC_TIM2_CLK_DISABLE();
    }
    else if(htim->Instance==TIM3)
    {
        __HAL_RCC_TIM3_CLK_DISABLE();
    }
    else if(htim->Instance==TIM4)
    {
        __HAL_RCC_TIM4_CLK_DISABLE();
    }
    else if(htim->Instance==TIM5)
    {
        __HAL_RCC_TIM5_CLK_DISABLE();
    }
    else if(htim->Instance==TIM6)
    {
        __HAL_RCC_TIM6_CLK_DISABLE();
    }
    else if(htim->Instance==TIM7)
    {
        __HAL_RCC_TIM7_CLK_DISABLE();
    }
    else if(htim->Instance==TIM8)
    {
        __HAL_RCC_TIM8_CLK_DISABLE();
    }
    else
    {
        return HAL_ERR_FAIL;
    }
    
    return HAL_ERR_NONE;
}

static uint16_t Map_Timer_Write(void *dev, uint8_t pos, uint8_t *buf, uint16_t size)
{
    TIM_HandleTypeDef *timer = (TIM_HandleTypeDef *)dev;
    uint16_t param = *((uint16_t *)buf);
    
    if(size != 2)
    {
        return 0;
    }
    
    switch(pos)
    {
        case 0:
            __HAL_TIM_SET_AUTORELOAD(timer, param);
            HAL_TIM_Base_Start_IT(timer);
            break;
        case 1:
            __HAL_TIM_SET_COMPARE(timer, timer->Channel, param);
            HAL_TIM_PWM_Start(timer, timer->Channel);
            break;
        default:
            break;
    }
    
    return size;
}

static hal_err_t Map_Timer_Control(void *drv, uint8_t cmd, va_list args)
{
    return HAL_ERR_NONE;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM1)
    {
        if(!IS_PTR_NULL(TIM1_Tick_Callback.Function))
        {
            TIM1_Tick_Callback.TimeOut(TIM1_Tick_Callback.Param);
        }
    }
    else if(htim->Instance==TIM2)
    {
        if(!IS_PTR_NULL(TIM2_Tick_Callback.Function))
        {
            TIM2_Tick_Callback.TimeOut(TIM2_Tick_Callback.Param);
        }
    }
    else if(htim->Instance==TIM3)
    {
        if(!IS_PTR_NULL(TIM3_Tick_Callback.Function))
        {
            TIM3_Tick_Callback.TimeOut(TIM3_Tick_Callback.Param);
        }
    }
    else if(htim->Instance==TIM4)
    {
        if(!IS_PTR_NULL(TIM4_Tick_Callback.Function))
        {
            TIM4_Tick_Callback.TimeOut(TIM4_Tick_Callback.Param);
        }
    }
    else if(htim->Instance==TIM5)
    {
        if(!IS_PTR_NULL(TIM5_Tick_Callback.Function))
        {
            TIM5_Tick_Callback.TimeOut(TIM5_Tick_Callback.Param);
        }
    }
    else if(htim->Instance==TIM6)
    {
        if(!IS_PTR_NULL(TIM6_Tick_Callback.Function))
        {
            TIM6_Tick_Callback.TimeOut(TIM6_Tick_Callback.Param);
        }
    }
    else if(htim->Instance==TIM7)
    {
        if(!IS_PTR_NULL(TIM7_Tick_Callback.Function))
        {
            TIM7_Tick_Callback.TimeOut(TIM7_Tick_Callback.Param);
        }
    }
    else if(htim->Instance==TIM8)
    {
        if(!IS_PTR_NULL(TIM8_Tick_Callback.Function))
        {
            TIM8_Tick_Callback.TimeOut(TIM8_Tick_Callback.Param);
        }
    }
}

/** @}*/     /** map timer component */

/**********************************END OF FILE*********************************/
