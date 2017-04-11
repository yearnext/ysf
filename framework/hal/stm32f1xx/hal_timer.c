/**
 ******************************************************************************
 * @file       hal_timer.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017��3��4��
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
#include "ysf_hal_conf.h"
#include "ysf_path.h"
#include YSF_COMPONENT_DEBUG_PATH
#include YSF_COMPILER_PATH

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static void (*MCU_TICK_FUNTION)(void);

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
__STATIC_INLINE
ysf_err_t timer_enable(uint8_t id)
{
    switch(id)
    {
        case MCU_TIMER_2:
        case MCU_TIMER_3:
        case MCU_TIMER_4:
        case MCU_TIMER_5:
        case MCU_TIMER_6:
        case MCU_TIMER_7:
            RCC->APB1RSTR &= (uint32_t)(~(1 << (id - 2)));
            RCC->APB1ENR  |= (uint32_t)(1 << (id - 2));
            break;
        case MCU_TIMER_1:
            RCC->APB2RSTR &= (uint32_t)(~(1 << 11));
            RCC->APB2ENR  |= (uint32_t)(1 << 11);
            break;
        case MCU_TIMER_8:
            RCC->APB2RSTR &= (uint32_t)(~(1 << 13));
            RCC->APB2ENR  |= (uint32_t)(1 << 13);
            break;
        case MCU_TIMER_0:
            break;
        default:
            return YSF_ERR_FAIL;
//            break;
    }
    
    return YSF_ERR_NONE;
}

__STATIC_INLINE
ysf_err_t timer_disable(uint8_t id)
{
    switch(id)
    {
        case MCU_TIMER_2:
        case MCU_TIMER_3:
        case MCU_TIMER_4:
        case MCU_TIMER_5:
        case MCU_TIMER_6:
        case MCU_TIMER_7:
            RCC->APB1RSTR |= (uint32_t)(1 << (id - 2));
            RCC->APB1ENR  &= (uint32_t)(~(1 << (id - 2)));
            break;
        case MCU_TIMER_1:
            RCC->APB2RSTR |= (uint32_t)(1 << 11);
            RCC->APB2ENR  &= (uint32_t)(~(1 << 11));
            break;
        case MCU_TIMER_8:
            RCC->APB2RSTR |= (uint32_t)(1 << 13);
            RCC->APB2ENR  &= (uint32_t)(~(1 << 13));
            break;
        case MCU_TIMER_0:
            break;
        default:
            return YSF_ERR_FAIL;
//            break;
    }
    
    return YSF_ERR_NONE;
}

ysf_err_t msp_timer_init(uint8_t id)
{
    return timer_enable(id);
}

ysf_err_t msp_timer_fini(uint8_t id)
{
    return timer_disable(id);
}

ysf_err_t map_timer_init(struct ysf_msp_timer_t *timer)
{
    ysf_assert(IS_PTR_NULL(timer));
    
    return timer_enable(timer->id);
}

ysf_err_t map_timer_fini(struct ysf_msp_timer_t *timer)
{
    ysf_assert(IS_PTR_NULL(timer));
    
    return timer_disable(timer->id);
}

ysf_err_t tick_timer_init( uint32_t tick, void (*func)(void) )
{
    if( SysTick_Config(MCU_CLOCK_FREQ/10000) )
    {
        return YSF_ERR_INVAILD_PARAM;
    }
    
    if(!IS_PTR_NULL(func))
    {
        MCU_TICK_FUNTION = func;
    }
    
    return YSF_ERR_NONE;
}

void SysTick_Handler(void)
{
    MCU_TICK_FUNTION();
}

/** @}*/     /* gpio component  */

/**********************************END OF FILE*********************************/
