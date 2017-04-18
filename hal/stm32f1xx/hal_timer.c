/**
 ******************************************************************************
 * @file       hal_timer.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017Äê3ÔÂ4ÈÕ
 * @brief      timer source file
 * @par        work paltform                                  
 *                 Windows
 * @par        compiler paltform									                         
 *                 GCC
 ******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup timer component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "core_path.h"
#include _HAL_PATH
#include _HAL_STM32F1XX_MAL_PATH
#include _HAL_STM32F1XX_TIMER_PATH

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define timer assert function
 *******************************************************************************
 */
#define IS_TIMER_ID_INVAILD(id) ( (id) >= MCU_TIMER_MAX )

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static void (*MCU_TICK_FUNTION)(void);

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
__STATIC_INLINE
void timer1_enable(void)
{
    RCC->APB2RSTR &= (uint32_t)(~(1 << 11));
    RCC->APB2ENR  |= (uint32_t)(1 << 11);
}

__STATIC_INLINE
void timer1_disable(void)
{
    RCC->APB2RSTR |= (uint32_t)(1 << 11);
    RCC->APB2ENR  &= (uint32_t)(~(1 << 11));
}

__STATIC_INLINE
void timer2_enable(void)
{
    RCC->APB1RSTR &= (uint32_t)(~(1 << 0));
    RCC->APB1ENR  |= (uint32_t)(1 << 0);
}

__STATIC_INLINE
void timer2_disable(void)
{
    RCC->APB1RSTR |= (uint32_t)(1 << 0);
    RCC->APB1RSTR &= (uint32_t)(~(1 << 0));
}

__STATIC_INLINE
void timer3_enable(void)
{
    RCC->APB1RSTR &= (uint32_t)(~(1 << 1));
    RCC->APB1ENR  |= (uint32_t)(1 << 1);
}

__STATIC_INLINE
void timer3_disable(void)
{
    RCC->APB1RSTR |= (uint32_t)(1 << 1);
    RCC->APB1RSTR &= (uint32_t)(~(1 << 1));
}

__STATIC_INLINE
void timer4_enable(void)
{
    RCC->APB1RSTR &= (uint32_t)(~(1 << 2));
    RCC->APB1ENR  |= (uint32_t)(1 << 2);
}

__STATIC_INLINE
void timer4_disable(void)
{
    RCC->APB1RSTR |= (uint32_t)(1 << 2);
    RCC->APB1RSTR &= (uint32_t)(~(1 << 2));
}

__STATIC_INLINE
void timer5_enable(void)
{
    RCC->APB1RSTR &= (uint32_t)(~(1 << 3));
    RCC->APB1ENR  |= (uint32_t)(1 << 3);
}

__STATIC_INLINE
void timer5_disable(void)
{
    RCC->APB1RSTR |= (uint32_t)(1 << 3);
    RCC->APB1RSTR &= (uint32_t)(~(1 << 3));
}

__STATIC_INLINE
void timer6_enable(void)
{
    RCC->APB1RSTR &= (uint32_t)(~(1 << 4));
    RCC->APB1ENR  |= (uint32_t)(1 << 4);
}

__STATIC_INLINE
void timer6_disable(void)
{
    RCC->APB1RSTR |= (uint32_t)(1 << 4);
    RCC->APB1RSTR &= (uint32_t)(~(1 << 4));
}

__STATIC_INLINE
void timer7_enable(void)
{
    RCC->APB1RSTR &= (uint32_t)(~(1 << 5));
    RCC->APB1ENR  |= (uint32_t)(1 << 5);
}

__STATIC_INLINE
void timer7_disable(void)
{
    RCC->APB1RSTR |= (uint32_t)(1 << 5);
    RCC->APB1RSTR &= (uint32_t)(~(1 << 5));
}

__STATIC_INLINE
void timer8_enable(void)
{
    RCC->APB2RSTR &= (uint32_t)(~(1 << 13));
    RCC->APB2ENR  |= (uint32_t)(1 << 13);
}

__STATIC_INLINE
void timer8_disable(void)
{
    RCC->APB2RSTR |= (uint32_t)(1 << 13);
    RCC->APB2RSTR &= (uint32_t)(~(1 << 13));
}

__STATIC_INLINE
void timer_enable(uint8_t id)
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

__STATIC_INLINE
void timer_disable(uint8_t id)
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

__STATIC_INLINE
void timer0_init(uint32_t tick, void (*func)(void))
{
    SysTick->LOAD  = (uint32_t)(MCU_CLOCK_FREQ/8000*tick-1);                        
    SysTick->VAL   = 0;                                             
    NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); 
    SysTick->CTRL  = (uint32_t)((1 << 1) | (1 << 2));
    
    if(func != NULL)
    {
        MCU_TICK_FUNTION = func;
    }
}

__STATIC_INLINE
void timer0_start(void)
{
    SysTick->CTRL |= (uint32_t)0x01;
}

__STATIC_INLINE
void timer0_stop(void)
{
    SysTick->CTRL &= ~((uint32_t)0x01);
}

__STATIC_INLINE
hal_err_t timer_base_init(uint8_t id, uint32_t tick, void (*func)(void))
{
    switch(id)
    {
        case MCU_TIMER_0:
            timer0_init(tick, func);
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
            break;
    }
    
    return HAL_ERR_NONE;
}

__STATIC_INLINE
hal_err_t timer_start(uint8_t id)
{
    switch(id)
    {
        case MCU_TIMER_0:
            timer0_start();
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
            break;
    }

    return HAL_ERR_NONE;
}

__STATIC_INLINE
hal_err_t timer_stop(uint8_t id)
{
    switch(id)
    {
        case MCU_TIMER_0:
            timer0_stop();
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
            break;
    }
    
    return HAL_ERR_NONE;
}

/* Exported functions --------------------------------------------------------*/
void msp_timer_enable(uint8_t id)
{
    hal_assert(IS_TIMER_ID_INVAILD(id));
    
    timer_enable(id);
}

void msp_timer_disable(uint8_t id)
{
    hal_assert(IS_TIMER_ID_INVAILD(id));
    
    timer_disable(id);
}

void msp_timer_base_init(uint8_t id, uint32_t tick, void (*func)(void))
{
    hal_assert(IS_TIMER_ID_INVAILD(id));
    
    timer_base_init(id, tick, func); 
}

void msp_timer_start(uint8_t id)
{
    hal_assert(IS_TIMER_ID_INVAILD(id));
    
    timer_start(id); 
}

void msp_timer_stop(uint8_t id)
{
    hal_assert(IS_TIMER_ID_INVAILD(id));
    
    timer_stop(id); 
}

void map_timer_enable(struct map_timer_t *timer)
{
    hal_assert(IS_PTR_NULL(timer));
    hal_assert(IS_TIMER_ID_INVAILD(timer->id));
    
    timer_enable(timer->id);
}

void map_timer_disable(struct map_timer_t *timer)
{
    hal_assert(IS_PTR_NULL(timer));
    hal_assert(IS_TIMER_ID_INVAILD(timer->id));
    
    timer_disable(timer->id);
}

void map_timer_base_init(struct map_timer_t *timer, uint32_t tick, void (*func)(void))
{
    hal_assert(IS_PTR_NULL(timer));
    hal_assert(IS_TIMER_ID_INVAILD(timer->id));
    
    timer_base_init(timer->id, tick, func); 
}

void map_timer_start(struct map_timer_t *timer)
{
    hal_assert(IS_PTR_NULL(timer));
    hal_assert(IS_TIMER_ID_INVAILD(timer->id));
    
    timer_start(timer->id); 
}

void map_timer_stop(struct map_timer_t *timer)
{
    hal_assert(IS_PTR_NULL(timer));
    hal_assert(IS_TIMER_ID_INVAILD(timer->id));
    
    timer_stop(timer->id); 
}

void SysTick_Handler(void)
{
    MCU_TICK_FUNTION();
}

/** @}*/     /* gpio component  */

/**********************************END OF FILE*********************************/
