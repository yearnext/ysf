/**
 ******************************************************************************
 * @file       hal.c
 * @author     yearnext
 * @version    1.0.0
 * @date       2017Äê3ÔÂ4ÈÕ
 * @brief      hal source file
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
 * @defgroup hal component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "ysf_hal_conf.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
#if USE_HAL_API
const struct HAL_API hal = 
{
#if defined(USE_MSP_GPIO_API) && USE_MSP_GPIO_API
    .msp.gpio.init        = msp_gpio_init,
    .msp.gpio.fini        = msp_gpio_fini,
    .msp.gpio.config      = msp_gpio_config,
    .msp.gpio.set         = msp_gpio_set,
    .msp.gpio.clr         = msp_gpio_clr,
    .msp.gpio.get         = msp_gpio_get,
    
    .map.gpio.init        = map_gpio_init,
    .map.gpio.fini        = map_gpio_fini,
    .map.gpio.config      = map_gpio_config,
    .map.gpio.set         = map_gpio_set,
    .map.gpio.clr         = map_gpio_clr,
    .map.gpio.get         = map_gpio_get,
#endif

#if defined(USE_MSP_TIMER_API) && USE_MSP_TIMER_API
    .msp.timer.enable     = msp_timer_init,
    .msp.timer.disable    = msp_timer_fini,
    .msp.timer.tick.init  = msp_tick_timer_init,
    
    .map.timer.enable     = map_timer_init,
    .map.timer.disable    = map_timer_fini,
#endif
};
#endif

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @}*/     /* hal component  */

/**********************************END OF FILE*********************************/
