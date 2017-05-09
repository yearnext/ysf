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
 * @file       MAP_timer.c                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-04-22                                                      *
 * @brief      msp timer source files                                          *
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
 * @defgroup timer component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _HAL_PATH
#include _HAL_MAL_PATH
#include _HAL_TIMER_PATH

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define timer assert function
 *******************************************************************************
 */
#define IS_TIMER_ID_INVAILD(id) ( (id) >= MCU_TIMER_MAX )
 
#define STM32F10X_TIMER1_RCC_POS                                            (11)
#define STM32F10X_TIMER2_RCC_POS                                             (0) 
#define STM32F10X_TIMER3_RCC_POS                                             (1)
#define STM32F10X_TIMER4_RCC_POS                                             (2)
#define STM32F10X_TIMER5_RCC_POS                                             (3)
#define STM32F10X_TIMER6_RCC_POS                                             (4)
#define STM32F10X_TIMER7_RCC_POS                                             (5)
#define STM32F10X_TIMER8_RCC_POS                                            (11)

#define STM32F10X_TIMER0_START_POS                                           (0)
#define STM32F10X_TIMER0_STOP_POS                                            (0)

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if USE_MAP_TIMER_COMPONENT
/**
 *******************************************************************************
 * @brief      define tick timer handle function
 *******************************************************************************
 */
struct
{
    void (*CallBack)(void*);
    void *Param;
}static TimerHandle[MCU_TIMER_MAX];

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       enable timer1
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer1_enable(void)
{
    _CLR_BIT(RCC->APB2RSTR, STM32F10X_TIMER1_RCC_POS);
    _SET_BIT(RCC->APB2ENR, STM32F10X_TIMER1_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       disable timer1
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer1_disable(void)
{
    _SET_BIT(RCC->APB2RSTR, STM32F10X_TIMER1_RCC_POS);
    _CLR_BIT(RCC->APB2RSTR, STM32F10X_TIMER1_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       enable timer2
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer2_enable(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_TIMER2_RCC_POS);
    _CLR_BIT(RCC->APB1ENR, STM32F10X_TIMER2_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       disable timer2
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer2_disable(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_TIMER2_RCC_POS);
    _CLR_BIT(RCC->APB1RSTR, STM32F10X_TIMER2_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       enable timer3
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer3_enable(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_TIMER3_RCC_POS);
    _CLR_BIT(RCC->APB1ENR, STM32F10X_TIMER3_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       disable timer3
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer3_disable(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_TIMER3_RCC_POS);
    _CLR_BIT(RCC->APB1RSTR, STM32F10X_TIMER3_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       enable timer4
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer4_enable(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_TIMER4_RCC_POS);
    _CLR_BIT(RCC->APB1ENR, STM32F10X_TIMER4_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       disable timer4
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer4_disable(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_TIMER4_RCC_POS);
    _CLR_BIT(RCC->APB1RSTR, STM32F10X_TIMER4_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       enable timer5
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer5_enable(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_TIMER5_RCC_POS);
    _CLR_BIT(RCC->APB1ENR, STM32F10X_TIMER5_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       disable timer5
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer5_disable(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_TIMER5_RCC_POS);
    _CLR_BIT(RCC->APB1RSTR, STM32F10X_TIMER5_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       enable timer6
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer6_enable(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_TIMER6_RCC_POS);
    _CLR_BIT(RCC->APB1ENR, STM32F10X_TIMER6_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       disable timer6
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer6_disable(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_TIMER6_RCC_POS);
    _CLR_BIT(RCC->APB1RSTR, STM32F10X_TIMER6_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       enable timer7
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer7_enable(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_TIMER7_RCC_POS);
    _CLR_BIT(RCC->APB1ENR, STM32F10X_TIMER7_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       disable timer7
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer7_disable(void)
{
    _SET_BIT(RCC->APB1RSTR, STM32F10X_TIMER7_RCC_POS);
    _CLR_BIT(RCC->APB1RSTR, STM32F10X_TIMER7_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       enable timer8
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer8_enable(void)
{
    _SET_BIT(RCC->APB2RSTR, STM32F10X_TIMER8_RCC_POS);
    _CLR_BIT(RCC->APB2ENR, STM32F10X_TIMER8_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       disable timer8
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void timer8_disable(void)
{
    _SET_BIT(RCC->APB2RSTR, STM32F10X_TIMER8_RCC_POS);
    _CLR_BIT(RCC->APB2RSTR, STM32F10X_TIMER8_RCC_POS);
}

/**
 *******************************************************************************
 * @brief       enable timer
 * @param       [in/out]  id           timer id
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _open(uint8_t id)
{
    switch(id)
    {
        case MCU_TIMER_0:
            break;
        case MCU_TIMER_1:
            timer1_enable();
            break; 
        case MCU_TIMER_2:
            timer2_enable();
            break;
        case MCU_TIMER_3:
            timer3_enable();
            break;
        case MCU_TIMER_4:
            timer4_enable();
            break;
        case MCU_TIMER_5:
            timer5_enable();
            break; 
        case MCU_TIMER_6:
            timer6_enable();
            break;
        case MCU_TIMER_7:
            timer7_enable();
            break;
        case MCU_TIMER_8:
            timer8_enable();
            break;    
        default:
            break;
    }
}

/**
 *******************************************************************************
 * @brief       disable timer
 * @param       [in/out]  id           timer id
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _close(uint8_t id)
{
    switch(id)
    {
        case MCU_TIMER_0:
            break;
        case MCU_TIMER_1:
            timer1_disable();
            break; 
        case MCU_TIMER_2:
            timer2_disable();
            break;
        case MCU_TIMER_3:
            timer3_disable();
            break;
        case MCU_TIMER_4:
            timer4_disable();
            break;
        case MCU_TIMER_5:
            timer5_disable();
            break; 
        case MCU_TIMER_6:
            timer6_disable();
            break;
        case MCU_TIMER_7:
            timer7_disable();
            break;
        case MCU_TIMER_8:
            timer8_disable();
            break;    
        default:
            break;
    }
}

/**
 *******************************************************************************
 * @brief       timer0 start
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _timer0_start(void)
{
    _SET_BIT(SysTick->CTRL, STM32F10X_TIMER0_START_POS);
}

/**
 *******************************************************************************
 * @brief       timer0 stop
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _timer0_stop(void)
{
    _CLR_BIT(SysTick->CTRL, STM32F10X_TIMER0_START_POS);
}

/**
 *******************************************************************************
 * @brief       timer0 init
 * @param       [in/out]  tick           timing
 * @param       [in/out]  *func          timer handle function
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _timer0_init(uint32_t tick)
{
    SysTick->LOAD  = (MCU_CLOCK_FREQ/8000*tick-1);   
    _CLEAR_REG(SysTick->VAL);                                              
    NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); 
    SysTick->CTRL  = (uint32_t)((1 << 1) | (1 << 2));
}

/**
 *******************************************************************************
 * @brief       timer0 handle function regeister
 * @param       [in/out]  *cb           timer handle function
 * @param       [in/out]  *param        timer handle param
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
void _timer0_cb_register(void (*cb)(void *), void *param)
{
    TimerHandle[MCU_TIMER_0].CallBack = cb;
    TimerHandle[MCU_TIMER_0].Param    = param;
}

/**
 *******************************************************************************
 * @brief       timer base init
 * @param       [in/out]  id              timer id
 * @param       [in/out]  tick            timing
 * @param       [in/out]  *func           timer handle function
 * @return      [in/out]  HAL_ERR_NONE    init success
 * @return      [in/out]  HAL_ERR_FAIL    init failed
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
hal_err_t _base_init(uint8_t id, uint32_t tick)
{
    switch(id)
    {
        case MCU_TIMER_0:
            _timer0_init(tick);
            break;
        case MCU_TIMER_1:
            break; 
        case MCU_TIMER_2:
            break;
        case MCU_TIMER_3:
            break;
        case MCU_TIMER_4:
            break;
        case MCU_TIMER_5:
            break; 
        case MCU_TIMER_6:
            break;
        case MCU_TIMER_7:
            break;
        case MCU_TIMER_8:
            break;    
        default:
            return HAL_ERR_FAIL;
//            break;
    }
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer start
 * @param       [in/out]  id              timer id
 * @return      [in/out]  HAL_ERR_NONE    start success
 * @return      [in/out]  HAL_ERR_FAIL    start failed
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
hal_err_t _start(uint8_t id)
{
    switch(id)
    {
        case MCU_TIMER_0:
            _timer0_start();
            break;
        case MCU_TIMER_1:
            break; 
        case MCU_TIMER_2:
            break;
        case MCU_TIMER_3:
            break;
        case MCU_TIMER_4:
            break;
        case MCU_TIMER_5:
            break; 
        case MCU_TIMER_6:
            break;
        case MCU_TIMER_7:
            break;
        case MCU_TIMER_8:
            break;    
        default:
            return HAL_ERR_FAIL;
            break;
    }

    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer stop
 * @param       [in/out]  id              timer id
 * @return      [in/out]  HAL_ERR_NONE    stop success
 * @return      [in/out]  HAL_ERR_FAIL    stop failed
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
hal_err_t _stop(uint8_t id)
{
    switch(id)
    {
        case MCU_TIMER_0:
            _timer0_stop();
            break;
        case MCU_TIMER_1:
            break; 
        case MCU_TIMER_2:
            break;
        case MCU_TIMER_3:
            break;
        case MCU_TIMER_4:
            break;
        case MCU_TIMER_5:
            break; 
        case MCU_TIMER_6:
            break;
        case MCU_TIMER_7:
            break;
        case MCU_TIMER_8:
            break;    
        default:
            return HAL_ERR_FAIL;
//            break;
    }
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer0 handle function regeister
 * @param       [in/out]  id            timer id
 * @param       [in/out]  *cb           timer handle function
 * @param       [in/out]  *param        timer handle param
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
__STATIC_INLINE
hal_err_t _timer_cb_register(uint8_t id, void (*cb)(void *), void *param)
{
    switch(id)
    {
        case MCU_TIMER_0:
            _timer0_cb_register(cb, param);
            break;
        case MCU_TIMER_1:
            break; 
        case MCU_TIMER_2:
            break;
        case MCU_TIMER_3:
            break;
        case MCU_TIMER_4:
            break;
        case MCU_TIMER_5:
            break; 
        case MCU_TIMER_6:
            break;
        case MCU_TIMER_7:
            break;
        case MCU_TIMER_8:
            break;    
        default:
            return HAL_ERR_FAIL;
//            break;
    }
    
    return HAL_ERR_NONE;
}

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       timer enable
 * @param       [in/out]  id              timer id
 * @return      [in/out]  HAL_ERR_NONE    enable success
 * @return      [in/out]  HAL_ERR_FAIL    enable failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MAP_Timer_Open(uint8_t id)
{
    hal_assert(IS_TIMER_ID_INVAILD(id));
    
    _open(id);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer disable
 * @param       [in/out]  id              timer id
 * @return      [in/out]  HAL_ERR_NONE    disable success
 * @return      [in/out]  HAL_ERR_FAIL    disable failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MAP_Timer_Close(uint8_t id)
{
    hal_assert(IS_TIMER_ID_INVAILD(id));
    
    _close(id);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer start
 * @param       [in/out]  id              timer id
 * @return      [in/out]  HAL_ERR_NONE    start success
 * @return      [in/out]  HAL_ERR_FAIL    start failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MAP_Timer_Start(uint8_t id)
{
    hal_assert(IS_TIMER_ID_INVAILD(id));
    
    _start(id); 
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer stop
 * @param       [in/out]  id              timer id
 * @return      [in/out]  HAL_ERR_NONE    stop success
 * @return      [in/out]  HAL_ERR_FAIL    stop failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MAP_Timer_Stop(uint8_t id)
{
    hal_assert(IS_TIMER_ID_INVAILD(id));
    
    _stop(id); 
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer base init
 * @param       [in/out]  id              timer id
 * @param       [in/out]  tick            timing
 * @return      [in/out]  HAL_ERR_NONE    init success
 * @return      [in/out]  HAL_ERR_FAIL    init failed
 * @note        the function is static inline type
 *******************************************************************************
 */
hal_err_t MAP_TimerBase_Init(uint8_t id, uint32_t tick)
{
    hal_assert(IS_TIMER_ID_INVAILD(id));
    
    _stop(id);
    _base_init(id, tick); 
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer handle function register
 * @param       [in/out]  id              timer id
 * @param       [in/out]  *cb             timer handle function
 * @param       [in/out]  *param          timer handle param
 * @return      [in/out]  HAL_ERR_NONE    init success
 * @return      [in/out]  HAL_ERR_FAIL    init failed
 * @note        the function is static inline type
 *******************************************************************************
 */
hal_err_t MAP_TimerBaseHandle_Register(uint8_t id, void (*cb)(void *), void *param)
{
    hal_assert(IS_TIMER_ID_INVAILD(id));
    hal_assert(IS_PTR_NULL(cb));
    
    _timer_cb_register(id, cb, param);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer base init and start
 * @param       [in/out]  id              timer id
 * @param       [in/out]  tick            timing
 * @param       [in/out]  *cb             timer handle function
 * @param       [in/out]  *param          timer handle param
 * @return      [in/out]  HAL_ERR_NONE    init success
 * @return      [in/out]  HAL_ERR_FAIL    init failed
 * @note        the function is static inline type
 *******************************************************************************
 */
hal_err_t MAP_TimerBase_Arm(uint8_t id, uint32_t tick, void (*cb)(void *), void *param)
{
    hal_assert(IS_TIMER_ID_INVAILD(id));
    
    _stop(id);
    _base_init(id, tick);
    _timer_cb_register(id, cb, param);
    _start(id);

    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       SysTick Timer Handle Function
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        this function is interrupt handle function
 *******************************************************************************
 */
void SysTick_Handler(void)
{
#if USE_HAL_DEBUG
    if(IS_PTR_NULL(TimerHandle[MCU_TIMER_0].CallBack))
    {
        return;
    }
#endif
    
    TimerHandle[MCU_TIMER_0].CallBack(TimerHandle[MCU_TIMER_0].Param);
}

#endif

/** @}*/     /** timer component */

/**********************************END OF FILE*********************************/
