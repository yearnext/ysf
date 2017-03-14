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
#include "ysf_path.h"
#include YSF_HAL_DIR

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
#if USE_HAL_API
const struct HAL_API hal = 
{
#if defined(USE_MSP_GPIO_API) && USE_MSP_GPIO_API
    .gpio.msp.init        = msp_gpio_init,
    .gpio.msp.fini        = msp_gpio_fini,
    .gpio.msp.config      = msp_gpio_config,
    .gpio.msp.set         = msp_gpio_set,
    .gpio.msp.clr         = msp_gpio_clr,
    .gpio.msp.get         = msp_gpio_get,
    
    .gpio.map.init        = map_gpio_init,
    .gpio.map.fini        = map_gpio_fini,
    .gpio.map.config      = map_gpio_config,
    .gpio.map.set         = map_gpio_set,
    .gpio.map.clr         = map_gpio_clr,
    .gpio.map.get         = map_gpio_get,
#endif

#if defined(USE_MSP_TIMER_API) && USE_MSP_TIMER_API
    .timer.msp.enable     = msp_timer_init,
    .timer.msp.disable    = msp_timer_fini,
    .timer.msp.tick.init  = msp_tick_timer_init,
    
    .timer.map.enable     = map_timer_init,
    .timer.map.disable    = map_timer_fini,
#endif
};
#endif

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @}*/     /* hal component  */

/**********************************END OF FILE*********************************/
