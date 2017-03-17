/**
 ******************************************************************************
 * @file       timer.h
 * @author     yearnext
 * @version    1.0.0
 * @date       2017Äê3ÔÂ4ÈÕ
 * @brief      timer head file
 * @par        work paltform		                             
 *                 Windows
 * @par        compiler paltform									                         
 * 				   GCC
 ******************************************************************************
 * @note
 * 1.XXXXX                  						                     
 ******************************************************************************
 */

/**
 * @defgroup timer component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10X_TIMER_H__
#define __STM32F10X_TIMER_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "ysf_path.h"
#include YSF_TYPE_PATH

/* Exported macro ------------------------------------------------------------*/
#define USE_MSP_TIMER_API (1)
#define USE_MAP_TIMER_API (1)  
#define USE_TICK_TIMER (1)
    
/* Exported types ------------------------------------------------------------*/
enum
{
    MCU_TIMER_0 = 0,  /** stm32 tick timer */
    MCU_TIMER_1,
    MCU_TIMER_2,
    MCU_TIMER_3,
    MCU_TIMER_4,
    MCU_TIMER_5,
    MCU_TIMER_6,
    MCU_TIMER_7,
    MCU_TIMER_8,
};
    
struct ysf_msp_timer_t
{
    uint8_t id;
};

struct MSP_TIMER_API
{    
    ysf_err_t (*enable)(uint8_t id);
    ysf_err_t (*disable)(uint8_t id);
#if USE_TICK_TIMER
    struct
    {
        ysf_err_t (*init)(void (*func)(void));
    }tick;
#endif
};
    
struct MAP_TIMER_API
{
    ysf_err_t (*enable)(struct ysf_msp_timer_t *timer);
    ysf_err_t (*disable)(struct ysf_msp_timer_t *timer);
};
    
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern ysf_err_t msp_timer_init(uint8_t);
extern ysf_err_t msp_timer_fini(uint8_t);
#if USE_TICK_TIMER
extern ysf_err_t msp_tick_timer_init(void (*func)(void));
#endif

extern ysf_err_t map_timer_init(struct ysf_msp_timer_t*);
extern ysf_err_t map_timer_fini(struct ysf_msp_timer_t*);

extern void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /* gpio component  */

/**********************************END OF FILE*********************************/
