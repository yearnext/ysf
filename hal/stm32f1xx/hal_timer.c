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
#include _HAL_MAL_PATH
#include _HAL_TIMER_PATH

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define timer assert function
 *******************************************************************************
 */
#define IS_TIMER_ID_INVAILD(id) ( (id) >= MCU_TIMER_MAX )

/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      define tick timer handle function
 *******************************************************************************
 */
static void (*TickHandleFunction)(void);

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
    RCC->APB2RSTR &= (uint32_t)(~(1 << 11));
    RCC->APB2ENR  |= (uint32_t)(1 << 11);
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
    RCC->APB2RSTR |= (uint32_t)(1 << 11);
    RCC->APB2ENR  &= (uint32_t)(~(1 << 11));
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
    RCC->APB1RSTR &= (uint32_t)(~(1 << 0));
    RCC->APB1ENR  |= (uint32_t)(1 << 0);
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
    RCC->APB1RSTR |= (uint32_t)(1 << 0);
    RCC->APB1RSTR &= (uint32_t)(~(1 << 0));
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
    RCC->APB1RSTR &= (uint32_t)(~(1 << 1));
    RCC->APB1ENR  |= (uint32_t)(1 << 1);
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
    RCC->APB1RSTR |= (uint32_t)(1 << 1);
    RCC->APB1RSTR &= (uint32_t)(~(1 << 1));
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
    RCC->APB1RSTR &= (uint32_t)(~(1 << 2));
    RCC->APB1ENR  |= (uint32_t)(1 << 2);
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
    RCC->APB1RSTR |= (uint32_t)(1 << 2);
    RCC->APB1RSTR &= (uint32_t)(~(1 << 2));
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
    RCC->APB1RSTR &= (uint32_t)(~(1 << 3));
    RCC->APB1ENR  |= (uint32_t)(1 << 3);
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
    RCC->APB1RSTR |= (uint32_t)(1 << 3);
    RCC->APB1RSTR &= (uint32_t)(~(1 << 3));
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
    RCC->APB1RSTR &= (uint32_t)(~(1 << 4));
    RCC->APB1ENR  |= (uint32_t)(1 << 4);
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
    RCC->APB1RSTR |= (uint32_t)(1 << 4);
    RCC->APB1RSTR &= (uint32_t)(~(1 << 4));
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
    RCC->APB1RSTR &= (uint32_t)(~(1 << 5));
    RCC->APB1ENR  |= (uint32_t)(1 << 5);
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
    RCC->APB1RSTR |= (uint32_t)(1 << 5);
    RCC->APB1RSTR &= (uint32_t)(~(1 << 5));
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
    RCC->APB2RSTR &= (uint32_t)(~(1 << 13));
    RCC->APB2ENR  |= (uint32_t)(1 << 13);
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
    RCC->APB2RSTR |= (uint32_t)(1 << 13);
    RCC->APB2RSTR &= (uint32_t)(~(1 << 13));
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

/**
 *******************************************************************************
 * @brief       disable timer
 * @param       [in/out]  id           timer id
 * @return      [in/out]  void
 * @note        the function is static inline type
 *******************************************************************************
 */
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
void timer0_base_init(uint32_t tick, void (*func)(void))
{
    SysTick->LOAD  = (uint32_t)(MCU_CLOCK_FREQ/8000*tick-1);                        
    SysTick->VAL   = 0;                                             
    NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); 
    SysTick->CTRL  = (uint32_t)((1 << 1) | (1 << 2));
    
    if(func != NULL)
    {
        TickHandleFunction = func;
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
void timer0_start(void)
{
    SysTick->CTRL |= (uint32_t)0x01;
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
void timer0_stop(void)
{
    SysTick->CTRL &= ~((uint32_t)0x01);
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
hal_err_t timer_base_init(uint8_t id, uint32_t tick, void (*func)(void))
{
    switch(id)
    {
        case MCU_TIMER_0:
            timer0_base_init(tick, func);
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
            return HAL_ERR_FAIL;
//            break;
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
hal_err_t MspTimerEnable(uint8_t id)
{
#if USE_HAL_TIMER_DEBUG
    if( IS_TIMER_ID_INVAILD(id) )
    {
        return HAL_ERR_FAIL;
    }
#endif
    
    timer_enable(id);
    
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
hal_err_t MspTimerDisable(uint8_t id)
{
#if USE_HAL_TIMER_DEBUG
    if( IS_TIMER_ID_INVAILD(id) )
    {
        return HAL_ERR_FAIL;
    }
#endif
    
    timer_disable(id);
    
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
hal_err_t MspTimerStart(uint8_t id)
{
#if USE_HAL_TIMER_DEBUG
    if( IS_TIMER_ID_INVAILD(id) )
    {
        return HAL_ERR_FAIL;
    }
#endif
    
    timer_start(id); 
    
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
hal_err_t MspTimerStop(uint8_t id)
{
#if USE_HAL_TIMER_DEBUG
    if( IS_TIMER_ID_INVAILD(id) )
    {
        return HAL_ERR_FAIL;
    }
#endif
    
    timer_stop(id); 
    
    return HAL_ERR_NONE;
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
hal_err_t MspTimerBaseInit(uint8_t id, uint32_t tick, void (*func)(void))
{
#if USE_HAL_TIMER_DEBUG
    if( IS_TIMER_ID_INVAILD(id) )
    {
        return HAL_ERR_FAIL;
    }
    
    if( func == NULL )
    {
        return HAL_ERR_FAIL;
    }
#endif
    
    timer_base_init(id, tick, func); 
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer enable
 * @param       [in/out]  *timer          timer block
 * @return      [in/out]  HAL_ERR_NONE    enable success
 * @return      [in/out]  HAL_ERR_FAIL    enable failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MapTimerEnable(struct MapTimerBlock *timer)
{   
#if USE_HAL_TIMER_DEBUG
    if( timer == NULL )
    {
        return HAL_ERR_FAIL;
    }
    
    if( IS_TIMER_ID_INVAILD(timer->ID) )
    {
        return HAL_ERR_FAIL;
    }
#endif  

    timer_enable(timer->ID);

    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer disable
 * @param       [in/out]  *timer          timer block
 * @return      [in/out]  HAL_ERR_NONE    disable success
 * @return      [in/out]  HAL_ERR_FAIL    disable failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MapTimerDisable(struct MapTimerBlock *timer)
{
#if USE_HAL_TIMER_DEBUG
    if( timer == NULL )
    {
        return HAL_ERR_FAIL;
    }
    
    if( IS_TIMER_ID_INVAILD(timer->ID) )
    {
        return HAL_ERR_FAIL;
    }
#endif  
    
    timer_disable(timer->ID);
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer start
 * @param       [in/out]  *timer          timer block
 * @return      [in/out]  HAL_ERR_NONE    start success
 * @return      [in/out]  HAL_ERR_FAIL    start failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MapTimerStart(struct MapTimerBlock *timer)
{
#if USE_HAL_TIMER_DEBUG
    if( timer == NULL )
    {
        return HAL_ERR_FAIL;
    }
    
    if( IS_TIMER_ID_INVAILD(timer->ID) )
    {
        return HAL_ERR_FAIL;
    }
#endif  
    
    timer_start(timer->ID); 
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer stop
 * @param       [in/out]  *timer          timer block
 * @return      [in/out]  HAL_ERR_NONE    stop success
 * @return      [in/out]  HAL_ERR_FAIL    stop failed
 * @note        None
 *******************************************************************************
 */
hal_err_t MapTimerStop(struct MapTimerBlock *timer)
{
#if USE_HAL_TIMER_DEBUG
    if( timer == NULL )
    {
        return HAL_ERR_FAIL;
    }
    
    if( IS_TIMER_ID_INVAILD(timer->ID) )
    {
        return HAL_ERR_FAIL;
    }
#endif  
    
    timer_stop(timer->ID); 
    
    return HAL_ERR_NONE;
}

/**
 *******************************************************************************
 * @brief       timer base init
 * @param       [in/out]  *timer          timer block
 * @param       [in/out]  tick            timing
 * @param       [in/out]  *func           timer handle function
 * @return      [in/out]  HAL_ERR_NONE    init success
 * @return      [in/out]  HAL_ERR_FAIL    init failed
 * @note        the function is static inline type
 *******************************************************************************
 */
hal_err_t MapTimerBaseInit(struct MapTimerBlock *timer, uint32_t tick, void (*func)(void))
{
#if USE_HAL_TIMER_DEBUG
    if( func == NULL )
    {
        return HAL_ERR_FAIL;
    }
    
    if( timer == NULL )
    {
        return HAL_ERR_FAIL;
    }
    
    if( IS_TIMER_ID_INVAILD(timer->ID) )
    {
        return HAL_ERR_FAIL;
    }
#endif
    
    timer_base_init(timer->ID, tick, func); 
    
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
#if USE_HAL_TIMER_DEBUG
    if(TickHandleFunction == NULL)
    {
        return;
    }
#endif
    
    TickHandleFunction();
}

/** @}*/     /* gpio component  */

/**********************************END OF FILE*********************************/
